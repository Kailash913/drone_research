"""Reject unsupported measurement claims and preserve raw provenance."""
import csv
import hashlib
import json
from pathlib import Path
import struct
import tempfile
from types import SimpleNamespace
import unittest

from baseline_measurement.experiment_logger import RunLog
from baseline_measurement.measurements import (
    captured_traffic,
    clock_latency,
    correlated_latency,
    power_energy,
    sequence_loss
)
from baseline_measurement.provenance import recover
from baseline_measurement.sync_evidence import SyncEvidence


class MeasurementTests(unittest.TestCase):
    """Use fixtures for methods only; never label fixtures as flight measurements."""

    def calibration(self):
        return {
            'source_domain': 'native_boot',
            'receiver_domain': 'local_monotonic',
            'validation_evidence': 'fixture-only',
            'scale': 1,
            'offset_us': 1000,
            'uncertainty_us': 2,
            'valid_source_min_us': 100,
            'valid_source_max_us': 200
        }

    def test_clock_mapping_requires_explicit_evidence(self):
        with self.assertRaises(ValueError):
            clock_latency([], {})

    def test_validated_clock_pair_and_uncertainty(self):
        rows = (
            [
                {
                    'native_source_us': 100,
                    'receive_us': 1110,
                    'source_domain': 'native_boot',
                    'receiver_domain': 'local_monotonic'
                }
            ]
        )
        result = clock_latency(rows, self.calibration())
        self.assertEqual(result['samples'][0], {'latency_us': 10, 'uncertainty_us': 2})
        rows[0]['native_source_us'] = 1790000000000000
        with self.assertRaises(ValueError):
            clock_latency(rows, self.calibration())

    def test_clock_domain_mismatch_rejected(self):
        rows = (
            [
                {
                    'native_source_us': 100,
                    'receive_us': 1110,
                    'source_domain': 'epoch',
                    'receiver_domain': 'local_monotonic'
                }
            ]
        )
        with self.assertRaises(ValueError):
            clock_latency(rows, self.calibration())

    def test_command_ack_without_unique_id_is_unavailable(self):
        with self.assertRaises(ValueError):
            correlated_latency(
                [
                    {
                        'request_id': '',
                        'endpoint_evidence': 'ACK',
                        'clock_validation_evidence': 'same clock'
                    }
                ]
            )

    def test_duplicate_command_correlation_rejected(self):
        row = (
            {
                'request_id': 'a',
                'endpoint_evidence': 'fixture',
                'clock_validation_evidence': 'fixture',
                'request_us': 1,
                'response_us': 5
            }
        )
        self.assertEqual(correlated_latency([row])['samples'][0]['latency_us'], 4)
        with self.assertRaises(ValueError):
            correlated_latency([row, row])

    def test_sequence_counts_loss_and_duplicates(self):
        rows = [{'event': 'sent', 'run_id': 'a', 'sequence': n} for n in range(3)]
        rows += [{'event': 'received', 'run_id': 'a', 'sequence': 1}] * 2
        with self.assertRaises(ValueError):
            sequence_loss(rows)
        rows += [{'event': 'window_closed'}]
        result = sequence_loss(rows)
        self.assertEqual(result['missing'], 2)
        self.assertEqual(result['duplicate_received'], 1)

    def test_unknown_received_sequence_rejected(self):
        with self.assertRaises(ValueError):
            sequence_loss(
                [
                    {'event': 'sent', 'run_id': 'a', 'sequence': 0},
                    {'event': 'received', 'run_id': 'b', 'sequence': 0},
                    {'event': 'window_closed'}
                ]
            )

    def test_pcap_window_original_lengths_and_truncation(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'fixture.pcap'
            header = struct.pack('<IHHIIII', 2712847316, 2, 4, 0, 0, 65535, 1)
            packet = struct.pack('<IIII', 100, 500000, 4, 10) + b'abcd'
            path.write_bytes(header + packet)
            result = captured_traffic(path, 100, 102, 'fixture scope, no drops')
            self.assertEqual(result['bits_per_s'], 40)
            self.assertIsNone(result['wire_packet_loss'])
            path.write_bytes(header + packet[:-1])
            with self.assertRaises(ValueError):
                captured_traffic(path, 100, 102, 'fixture')

    def test_physical_power_integrates_bounded_samples(self):
        instrument = (
            {
                'scope': 'physical_uav',
                'device_id': 'fixture',
                'calibration_evidence': 'fixture',
                'max_gap_s': 2
            }
        )
        result = (
            power_energy(
                [{'monotonic_s': 0, 'power_w': 10}, {'monotonic_s': 2, 'power_w': 20}],
                instrument
            )
        )
        self.assertEqual(result['energy_j'], 30)
        instrument['scope'] = 'WSL CPU'
        with self.assertRaises(ValueError):
            power_energy([], instrument)

    def test_power_missing_gaps_and_nan_rejected(self):
        instrument = (
            {
                'scope': 'physical_uav',
                'device_id': 'fixture',
                'calibration_evidence': 'fixture',
                'max_gap_s': 1
            }
        )
        for value in (float('nan'), 10):
            with self.assertRaises(ValueError):
                power_energy(
                    [{'monotonic_s': 0, 'power_w': value}, {'monotonic_s': 2, 'power_w': 1}],
                    instrument
                )

    def test_protocol_partition_and_offset_reset_not_estimator_proof(self):
        probe = SyncEvidence()
        probe.observe(2, -1790000000000000, 2)
        self.assertIsNone(probe.observe(1, 0, 2))
        event = probe.observe(2, 0, 2)
        self.assertFalse(event['estimator_reset_proven'])
        self.assertIsNone(probe.observe(2, 0, 2))

    def test_logger_retains_native_sample_counter_and_exact_receive_time(self):
        with tempfile.TemporaryDirectory() as directory:
            log = RunLog(directory)
            message = (
                SimpleNamespace(
                    timestamp=1790000000000000,
                    timestamp_sample=123,
                    xy_reset_counter=2
                )
            )
            log.message('/p', 'rx_callback', message, 10, 'WAYPOINT_1', receive_monotonic=7.0)
            log.finish(False)
            with log.path.open() as stream:
                rows = list(csv.DictReader(stream))
            evidence = json.loads(rows[1]['detail'])
            self.assertEqual(evidence['local_monotonic_s'], 7.0)
            self.assertEqual(evidence['timestamp_sample_us'], 123)
            self.assertEqual(evidence['reset_counters']['xy_reset_counter'], 2)

    def test_provenance_recovers_only_retained_byte_matches(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / 'retained.py'
            source.write_text('print(1)\n')
            digest = hashlib.sha256(source.read_bytes()).hexdigest()
            raw = root / 'baseline_run_001.csv'
            with raw.open('w', newline='') as stream:
                writer = csv.DictWriter(stream, fieldnames=['record_type', 'detail'])
                writer.writeheader()
                writer.writerow(
                    {
                        'record_type': 'metadata',
                        'detail': json.dumps(
                            {'source_sha256': {'retained.py': digest, 'missing.py': 'unknown'}}
                        )
                    }
                )
            before = raw.read_bytes()
            record = recover(root, [root])['records'][0]
            self.assertEqual(len(record['source_identity']['retained.py']['retained_matches']), 1)
            self.assertEqual(record['source_identity']['missing.py']['retained_matches'], [])
            self.assertIsNone(record['historical_config_sha256'])
            self.assertIsNone(record['historical_px4_version'])
            self.assertEqual(raw.read_bytes(), before)
