"""Synthetic fixtures validate methods only, never experimental UAV results."""
import json
from pathlib import Path
import struct
import tempfile
from types import SimpleNamespace
import unittest
from unittest import mock

from baseline_measurement.measurements import (
    battery_energy, battery_power, captured_traffic, sequence_loss)
from baseline_measurement.metrics_audit import independent_pcap, summary
from baseline_measurement.native_log_audit import export_logs
from baseline_measurement.passive_metrics import EvidenceWriter
from baseline_measurement.trajectory_metrics import trajectory_rmse, transform
from baseline_measurement.wire_capture import capture


class MissingMetricTests(unittest.TestCase):
    """Test failure boundaries independently of a running ROS graph."""

    def calibration(self):
        return {'source_domain': 'px4_delivered_us', 'receiver_domain': 'gazebo_sim_ns',
                'scale_ns_per_source_unit': 1000, 'offset_ns': 0, 'uncertainty_ns': 10,
                'maximum_pair_error_ns': 100, 'valid_source_min': 1, 'valid_source_max': 100,
                'validation_evidence': 'SYNTHETIC UNIT TEST ONLY'}

    def frame(self):
        return {'rotation': [[0, 1, 0], [1, 0, 0], [0, 0, -1]],
                'gazebo_origin': [10, 20, 30], 'px4_origin': [0, 0, 0],
                'validation_evidence': 'SYNTHETIC UNIT TEST ONLY'}

    def streams(self):
        truth = [{'source_timestamp': i * 1000, 'source_domain': 'gazebo_sim_ns',
                  'position': [11, 22, 33]} for i in (1, 2, 3)]
        estimate = [{'source_timestamp': i, 'source_domain': 'px4_delivered_us',
                     'position': [3, 3, 0], 'airborne': True, 'position_valid': True,
                     'reset_counters': {'xy_reset_counter': 0, 'z_reset_counter': 0,
                                        'heading_reset_counter': 0}} for i in (1, 2, 3)]
        return estimate, truth

    def test_enu_ned_origins_and_rmse(self):
        self.assertEqual(transform([11, 22, 33], self.frame()), [2, 1, -3])
        estimate, truth = self.streams()
        result = trajectory_rmse(estimate, truth, self.calibration(), self.frame())
        self.assertEqual(result['matched_count'], 3)
        self.assertEqual(result['axis_rmse_m'], [1, 2, 3])
        self.assertAlmostEqual(result['horizontal_rmse_m'], 5 ** .5)
        self.assertAlmostEqual(result['rmse_3d_m'], 14 ** .5)
        self.assertEqual(result['status'], 'MEASURED_UNVALIDATED')

    def test_missing_and_mismatched_clock_evidence(self):
        for change in ('evidence', 'domain', 'uncertainty', 'scale', 'interval'):
            with self.subTest(change=change):
                estimate, truth = self.streams()
                calibration = self.calibration()
                if change == 'evidence':
                    calibration['validation_evidence'] = ''
                elif change == 'domain':
                    calibration['source_domain'] = 'host_monotonic_ns'
                elif change == 'uncertainty':
                    calibration['uncertainty_ns'] = 101
                elif change == 'scale':
                    calibration['scale_ns_per_source_unit'] = 0
                else:
                    calibration['valid_source_min'] = 101
                with self.assertRaises(ValueError):
                    trajectory_rmse(estimate, truth, calibration, self.frame())

    def test_invalid_frame_and_origin_evidence(self):
        for field, value in [('validation_evidence', ''), ('rotation', [[1, 0, 0]] * 3),
                             ('gazebo_origin', [float('nan'), 0, 0]),
                             ('rotation', [[1, 0, 0], [0, 1, 0], [0, 0, -1]])]:
            frame = self.frame()
            frame[field] = value
            with self.assertRaises(ValueError):
                transform([0, 0, 0], frame)

    def test_reset_boundary_ground_and_alignment_rejections(self):
        for change in ('reset', 'ground', 'alignment', 'counters', 'invalid', 'interval'):
            with self.subTest(change=change):
                estimate, truth = self.streams()
                if change == 'reset':
                    estimate[1]['reset_counters']['z_reset_counter'] = 1
                    estimate[2]['reset_counters']['z_reset_counter'] = 1
                elif change == 'ground':
                    for row in estimate:
                        row['airborne'] = False
                elif change == 'alignment':
                    for row in truth:
                        row['source_timestamp'] += 200
                elif change == 'counters':
                    for row in estimate:
                        row['reset_counters'] = {}
                elif change == 'invalid':
                    for row in estimate:
                        row['position_valid'] = False
                else:
                    for row in estimate:
                        row['source_timestamp'] += 100
                result = trajectory_rmse(estimate, truth, self.calibration(), self.frame())
                self.assertEqual(result['matched_count'], 1 if change == 'reset' else 0)
                self.assertEqual(sum(result['rejected'].values()), 2 if change == 'reset' else 3)
                if change != 'reset':
                    self.assertIsNone(result['rmse_3d_m'])

    def test_truth_is_not_reused_and_order_is_checked(self):
        estimate, truth = self.streams()
        estimate[1]['source_timestamp'] = 1.01
        result = trajectory_rmse(estimate, truth, self.calibration(), self.frame())
        self.assertEqual(result['rejected']['truth_already_used'], 1)
        truth[1]['source_timestamp'] = truth[0]['source_timestamp']
        with self.assertRaises(ValueError):
            trajectory_rmse(estimate, truth, self.calibration(), self.frame())

    def test_epoch_nanosecond_alignment_preserves_small_differences(self):
        estimate, truth = self.streams()
        calibration = self.calibration()
        calibration['offset_ns'] = 1790000000000000000
        for row in truth:
            row['source_timestamp'] += calibration['offset_ns'] + 11
        result = trajectory_rmse(estimate, truth, calibration, self.frame())
        self.assertEqual([p['alignment_error_ns'] for p in result['pairs']], [11., 11., 11.])

    def test_battery_invalid_sentinels_and_units(self):
        self.assertEqual(battery_power(12, 2, True), 24)
        for voltage, current, connected in [(12, -1, True), (0, 2, True),
                                            (12, float('nan'), True), (12, 2, False)]:
            with self.assertRaises(ValueError):
                battery_power(voltage, current, connected)
        result = battery_energy([{'monotonic_s': i, 'voltage_v': 12, 'current_a': -1,
                                  'connected': True} for i in (0, 1)], 2)
        self.assertIsNone(result['energy_j'])
        self.assertEqual(result['valid_sample_count'], 0)

    def test_energy_invalid_samples_and_large_gaps_are_not_bridged(self):
        rows = [{'monotonic_s': i, 'voltage_v': 12, 'current_a': 2,
                 'connected': True} for i in (0, 1, 2, 3, 10)]
        rows[2]['current_a'] = -1
        result = battery_energy(rows, 2)
        self.assertEqual(result['energy_j'], 24)
        self.assertEqual(result['energy_wh'], 24 / 3600)
        self.assertEqual(result['integrated_duration_s'], 1)
        self.assertEqual(len(result['rejected']), 2)

    def test_sequence_window_invalid_denominator_and_duplicate_accounting(self):
        sent = {'event': 'sent', 'run_id': 'fixture', 'sequence': 1}
        received = dict(sent, event='received')
        closed = {'event': 'window_closed'}
        result = sequence_loss([sent, received, received, closed])
        self.assertEqual(result['duplicate_received'], 1)
        self.assertEqual(result['loss_fraction'], 0)
        for rows in ([closed], [sent], [sent, closed, received], [sent, sent, closed],
                     [dict(sent, sequence=1.1), closed], [dict(sent, sequence=True), closed]):
            with self.assertRaises(ValueError):
                sequence_loss(rows)

    def test_pcap_endianness_precision_and_byte_totals(self):
        for endian, magic, divisor in [('<', b'\xd4\xc3\xb2\xa1', 1000000),
                                       ('>', b'\xa1\xb2\xc3\xd4', 1000000),
                                       ('<', b'M<\xb2\xa1', 1000000000)]:
            with self.subTest(endian=endian, divisor=divisor):
                self.check_pcap_format(endian, magic, divisor)

    def check_pcap_format(self, endian, magic, divisor):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / 'fixture.pcap'
            header = magic + struct.pack(endian + 'HHIIII', 2, 4, 0, 0, 65535, 1)
            packets = b''.join(struct.pack(endian + 'IIII', 100 + i, divisor // 2, 4, 10)
                               + b'abcd' for i in (0, 1))
            path.write_bytes(header + packets)
            result = captured_traffic(path, 100, 102, 'SYNTHETIC UNIT TEST ONLY')
            self.assertEqual(result['original_frame_bytes'], 20)
            self.assertEqual(result['captured_bytes'], 8)
            self.assertEqual(result['truncated_packets'], 2)
            self.assertEqual(result['bits_per_s'], 80)
            self.assertEqual(result['packets_per_s'], 1)
            for start, end in [(100, 100), (102, 100)]:
                with self.assertRaises(ValueError):
                    captured_traffic(path, start, end, 'fixture')
            for bad in (header + packets[:-1], header[:-1],
                        header + struct.pack(endian + 'IIII', 100, divisor, 4, 10) + b'abcd'):
                path.write_bytes(bad)
                with self.assertRaises(ValueError):
                    captured_traffic(path, 100, 102, 'fixture')

    def test_raw_writer_preserves_clock_domains_and_nulls(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / 'fixture.jsonl'
            writer = EvidenceWriter(path)
            writer.write({'kind': 'truth', 'source_domain': 'gazebo_sim_ns',
                          'receive_monotonic_ns': 123456789, 'position': [float('nan'), 2, 3]})
            writer.close()
            row = json.loads(path.read_text())
            self.assertEqual(row['receive_monotonic_ns'], 123456789)
            self.assertIsNone(row['position'][0])
            self.assertEqual(row['source_domain'], 'gazebo_sim_ns')
            with self.assertRaises(FileExistsError):
                EvidenceWriter(path)

    def test_independent_packet_decoder_direction_and_totals(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / 'fixture.pcap'
            header = struct.pack('<IHHIIII', 2712847316, 2, 4, 0, 0, 65535, 1)
            ip = bytearray(20)
            ip[0], ip[9] = 0x45, 17
            ip[2:4] = (32).to_bytes(2, 'big')
            ip[12:16] = ip[16:20] = bytes([127, 0, 0, 1])
            frames = [bytes(12) + bytes([8, 0]) + ip + struct.pack('!HHHH', src, dst, 12, 0)
                      + b'abcd' for src, dst in [(40000, 8888), (8888, 40000)]]
            path.write_bytes(header + b''.join(
                struct.pack('<IIII', 100 + i, 0, len(frame), len(frame)) + frame
                for i, frame in enumerate(frames)))
            result = independent_pcap(path, Path(tmp) / 'packets.csv')
            self.assertEqual(result['totals']['packets'], 2)
            self.assertEqual(result['totals']['original_bytes'], 92)
            self.assertEqual(result['flows']['px4_to_agent']['ip_bytes'], 32)
            self.assertEqual(result['flows']['agent_to_px4']['udp_bytes'], 12)
            parsed = captured_traffic(path, 99, 102, 'SYNTHETIC UNIT TEST ONLY')
            self.assertEqual(parsed['original_frame_bytes'], result['totals']['original_bytes'])

    def test_empty_statistics_do_not_impute_zero(self):
        self.assertIsNone(summary([])['mean'])
        self.assertIsNone(summary([])['p95'])
        self.assertEqual(summary([1, 2, 3, 4, 5])['p95'], 5)
        result = summary([None, float('nan'), float('inf')])
        self.assertIsNone(result['mean'])
        self.assertIsNone(result['p95'])
        self.assertEqual(result['rejected_count'], 3)

    def test_native_export_retains_recorded_provenance_without_claiming_clock_validation(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / 'SYNTHETIC_FIXTURE.ulg'
            path.write_bytes(b'SYNTHETIC UNIT TEST ONLY')

            def values(numbers):
                return [mock.Mock(item=mock.Mock(return_value=n)) for n in numbers]
            topic = SimpleNamespace(name='battery_status', multi_id=0, data={
                'timestamp': values([1000000, 2000000]), 'voltage_v': values([12., 12.]),
                'current_a': values([-1., -1.]), 'connected': values([True, True])})
            log = SimpleNamespace(data_list=[topic], start_timestamp=1000000,
                                  last_timestamp=2000000,
                                  msg_info_dict={'ver_sw': 'SYNTHETIC FIXTURE HASH'},
                                  initial_parameters={'UXRCE_DDS_SYNCT': 1})
            module = SimpleNamespace(ULog=mock.Mock(return_value=log))
            with mock.patch.dict('sys.modules', {'pyulog': module}):
                report = export_logs([path], Path(tmp) / 'export')
            row = report['logs'][0]
            self.assertEqual(row['recorded_firmware_hash'], 'SYNTHETIC FIXTURE HASH')
            self.assertFalse(row['clock_calibration_validated'])
            self.assertEqual(row['observed_current_values'], [-1.])
            self.assertIsNone(row['battery']['energy_j'])
            self.assertEqual(path.read_bytes(), b'SYNTHETIC UNIT TEST ONLY')
            self.assertEqual(row['trajectory_rmse_status'], 'NOT_MEASURED')

    def test_unknown_reset_interval_is_not_crossed(self):
        estimate, truth = self.streams()
        estimate[1]['reset_counters'] = {}
        result = trajectory_rmse(estimate, truth, self.calibration(), self.frame())
        self.assertEqual(result['matched_count'], 1)
        self.assertEqual(result['rejected']['missing_reset_counters'], 1)
        self.assertEqual(result['rejected']['reset_boundary_requires_new_calibration'], 1)

    def test_capture_invalid_window_rejected_before_process_launch(self):
        for seconds in (0, -1, float('nan'), 61):
            with self.assertRaises(ValueError):
                capture('/unused', seconds, 'lo', 8888)

    def test_capture_permission_failure_is_unavailable(self):
        with tempfile.TemporaryDirectory() as tmp:
            with mock.patch('baseline_measurement.wire_capture.subprocess.Popen',
                            side_effect=PermissionError('SYNTHETIC permission fixture')):
                report = capture(Path(tmp) / 'capture', 1, 'lo', 8888)
            self.assertEqual(report['status'], 'NOT_MEASURED')
            self.assertIsNone(report['traffic'])
            self.assertTrue((Path(tmp) / 'capture/capture.json').is_file())
