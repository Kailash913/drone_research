"""Deterministic offline checks; no ROS graph or simulator is implied."""
import csv
import json
from pathlib import Path
import sys
import tempfile
import types
import unittest
from unittest import mock

from baseline_measurement.cli import validate_options
from baseline_measurement.experiment import aggregate_runs, Experiment
from baseline_measurement.metrics import (
    describe,
    integrate_energy_wh,
    OnlineStats,
    packet_loss_pct,
    throughput_mbps
)


class MetricTests(unittest.TestCase):

    def test_latency_and_summary(self):
        values = [10.0, 20.0, 30.0]
        result = describe(values, independent=True)
        self.assertEqual(result['count'], 3)
        self.assertEqual(result['mean'], 20.0)
        self.assertEqual(result['median'], 20.0)
        self.assertEqual(result['std'], 10.0)
        self.assertEqual(result['min'], 10.0)
        self.assertEqual(result['max'], 30.0)
        self.assertAlmostEqual(result['ci95_lower'], -4.846, places=2)
        self.assertAlmostEqual(result['ci95_upper'], 44.846, places=2)

    def test_empty_and_non_independent(self):
        self.assertEqual(describe([])['count'], 0)
        self.assertIsNone(describe([])['mean'])
        self.assertIsNone(describe([1, 2, 3])['ci95_lower'])

    def test_throughput(self):
        self.assertEqual(throughput_mbps(1000000, 2), 4.0)
        self.assertIsNone(throughput_mbps(10, 0))

    def test_packet_loss(self):
        self.assertEqual(packet_loss_pct(100, 90), 10.0)
        self.assertIsNone(packet_loss_pct(0, 0))
        self.assertIsNone(packet_loss_pct(10, 11))

    def test_energy_integral(self):
        self.assertAlmostEqual(integrate_energy_wh([(0, 100), (3600, 100)]), 100.0)
        self.assertIsNone(integrate_energy_wh([]))

    def test_online_bounds(self):
        stats = OnlineStats(capacity=3)
        for value in range(20):
            stats.add(value)
        result = stats.summary()
        self.assertEqual(result['count'], 20)
        self.assertEqual(result['min'], 0)
        self.assertEqual(result['max'], 19)
        self.assertTrue(result['median_approximate'])
        self.assertEqual(len(stats.samples), 3)


class ExperimentTests(unittest.TestCase):

    def test_missing_topics_unavailable_and_interrupted(self):
        with tempfile.TemporaryDirectory() as directory:
            run = Experiment(directory, 'BASE-001', 'telemetry_only')
            run.finish('interrupted', 'Ctrl+C')
            data = json.loads(run.json_path.read_text(encoding='utf-8'))
            self.assertFalse(data['availability']['telemetry_latency']['available'])
            self.assertFalse(data['availability']['throughput']['available'])
            self.assertEqual(data['experiment']['mission_status'], 'interrupted')
            self.assertIn('Ctrl+C', data['errors'])
            with run.summary_path.open(newline='', encoding='utf-8') as stream:
                rows = list(csv.DictReader(stream))
            self.assertEqual(rows[0]['throughput_mbps'], '')
            self.assertEqual(rows[0]['mission_success'], '')
            self.assertEqual(rows[0]['error_message'], 'Ctrl+C')

    def test_json_csv_and_unique_runs(self):
        with tempfile.TemporaryDirectory() as directory:
            first = Experiment(directory, 'BASE-002', 'a,"quoted" scenario')
            first.message('/fmu/out/vehicle_status_v4', 100, first.start + 0.1)
            first.message('/fmu/out/vehicle_status_v4', 100, first.start + 0.2)
            first.resource('measurement_node', 42, 5.0, 12.0, first.start + 0.3)
            first.finish()
            second = Experiment(directory, 'BASE-002', 'repeat')
            second.finish()
            self.assertNotEqual(first.raw_path, second.raw_path)
            with first.summary_path.open(newline='', encoding='utf-8') as stream:
                rows = list(csv.DictReader(stream))
            self.assertEqual(len(rows), 2)
            self.assertEqual(rows[0]['scenario'], 'a,"quoted" scenario')
            self.assertTrue(float(rows[0]['throughput_mbps']) > 0)
            with first.raw_path.open(newline='', encoding='utf-8') as stream:
                raw = list(csv.DictReader(stream))
            self.assertEqual(raw[0]['experiment_id'], 'BASE-002')
            self.assertEqual(
                json.loads(first.json_path.read_text())['topics'][
                    '/fmu/out/vehicle_status_v4']['count'],
                2
            )

    def test_simulated_battery_power(self):
        with tempfile.TemporaryDirectory() as directory:
            run = Experiment(directory, 'BASE-003', 'battery')
            run.battery(12.0, 2.0, True, run.start)
            run.battery(12.0, 2.0, True, run.start + 3600)
            result = run.finish()
            self.assertAlmostEqual(result['metrics']['simulated_energy_wh'], 24.0)

    def test_unavailable_battery_current_is_not_zero_power(self):
        with tempfile.TemporaryDirectory() as directory:
            run = Experiment(directory, 'BASE-003', 'battery_unavailable')
            run.battery(16.2, -1.0, True, run.start)
            run.battery(16.2, -1.0, True, run.start + 1.0)
            result = run.finish()
            self.assertFalse(result['availability']['energy']['available'])
            self.assertIsNone(result['metrics']['simulated_energy_wh'])

    def test_measured_zero_cpu_memory_and_jitter_remain_zero(self):
        with tempfile.TemporaryDirectory() as directory:
            run = Experiment(directory, 'BASE-003', 'zero_values')
            for dt in (0.5, 1.0, 1.5):
                run.message('topic', 100, run.start + dt)
            run.resource('measurement_node', 1, 0.0, 0.0, run.start + 1.0)
            run.finish()
            with run.summary_path.open(newline='', encoding='utf-8') as stream:
                row = next(csv.DictReader(stream))
            self.assertEqual(float(row['telemetry_jitter_ms']), 0.0)
            self.assertEqual(float(row['cpu_pct']), 0.0)
            self.assertEqual(float(row['memory_mib']), 0.0)

    def test_between_run_statistics(self):
        with tempfile.TemporaryDirectory() as directory:
            for index in range(2):
                run = Experiment(directory, f'BASE-00{index + 1}', 'same_scenario')
                run.message('topic', 100)
                run.finish()
            aggregate = aggregate_runs(Path(directory) / 'baseline_summary.csv')
            self.assertEqual(aggregate['run_count'], 2)
            self.assertEqual(aggregate['statistics']['throughput_mbps']['count'], 2)
            self.assertIsNotNone(aggregate['statistics']['throughput_mbps']['ci95_lower'])


class ResourceTests(unittest.TestCase):

    def test_missing_processes(self):
        fake = (
            types.SimpleNamespace(
                process_iter=lambda fields: [],
                NoSuchProcess=RuntimeError,
                AccessDenied=PermissionError,
                ZombieProcess=RuntimeError
            )
        )
        with mock.patch.dict(sys.modules, {'psutil': fake}):
            import importlib
            from baseline_measurement import resource_monitor
            importlib.reload(resource_monitor)
            self.assertEqual(resource_monitor.ResourceMonitor().sample(), [])
            self.assertEqual(resource_monitor.role_for('px4', ['px4_sitl'], False), 'px4_sitl')


class CliTests(unittest.TestCase):

    def test_preserved_observation_options(self):
        validate_options(15.0, 1.0, 1, topics={}, allowed_topic_keys=('status',))

    def test_invalid_options(self):
        for kwargs in (
            {'observe_seconds': 0},
            {'sampling_interval': float('nan')},
            {'run_count': 0},
            {'experiment_id': 'BASE-000'},
            {'experiment_id': 'BASE-031'},
            {'execute_sitl': True, 'passive_only': True}
        ):
            with self.subTest(kwargs=kwargs), self.assertRaises(ValueError):
                arguments = (
                    {
                        'observe_seconds': 15.0,
                        'sampling_interval': 1.0,
                        'run_count': 1,
                        'topics': {},
                        'allowed_topic_keys': ('status',)
                    }
                )
                arguments.update(kwargs)
                validate_options(**arguments)


if __name__ == '__main__':
    unittest.main()
