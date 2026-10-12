"""Check immutable dataset import, completion evidence and missing measurements."""
import csv
import json
from pathlib import Path
import tempfile
import unittest

from baseline_measurement.dataset import inspect_csv, validate_dataset, write_report
from baseline_measurement.experiment_logger import FIELDS
from baseline_measurement.mission_state import STAGES


class DatasetTests(unittest.TestCase):

    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.directory = Path(self.temp.name)

    def make_csv(
        self,
        name='baseline_run_001.csv',
        passed=True,
        complete=True,
        events=True,
        passive=False,
        cpu='0'
    ):
        path = self.directory / name
        rows = []

        def add(kind, elapsed, **kwargs):
            row = dict.fromkeys(FIELDS, '')
            row.update(
                record_type=kind,
                elapsed_s=elapsed,
                utc=f'2026-10-11T00:00:{int(elapsed):02d}+00:00',
                **kwargs
            )
            rows.append(row)
        add(
            'metadata',
            0,
            detail=json.dumps(
                {
                    'mode': 'PASSIVE_PREFLIGHT' if passive else 'SITL_MISSION',
                    'source_sha256': {'mission_node.py': 'a' * 64},
                    'cpu_scope': 'WSL Linux mission process'
                }
            )
        )
        add(
            'message',
            0.1,
            topic='/p',
            direction='rx_callback',
            source_timestamp_us=100,
            payload_cdr_bytes=10,
            count=1
        )
        add(
            'message',
            0.2,
            topic='/p',
            direction='rx_callback',
            source_timestamp_us=200,
            payload_cdr_bytes=10,
            count=2,
            iat_ms=100
        )
        add('resource', 1, node_cpu_percent=cpu, node_rss_mib=20, system_cpu_percent=5)
        if events:
            for index, event in enumerate(
                [s + '_REACHED' for s in STAGES] + [
                    'LANDED',
                    'DISARM',
                    'RELEASE_CONTROL',
                    'COMPLETE'
                ]
            ):
                add('event', 2 + index, detail=json.dumps({'event': event}))
        add(
            'topic_summary',
            12,
            topic='/p',
            direction='rx_callback',
            count=2,
            rate_hz=2 / 12,
            total_payload_cdr_bytes=20
        )
        if complete:
            add(
                'result',
                12,
                success='' if passive else str(passed),
                state='PREFLIGHT' if passive else 'COMPLETE' if passed else 'FAILSAFE',
                failure_reason='' if passed else 'Estimator or source clock reset',
                failure_state='' if passed else 'WAYPOINT_1',
                detail=json.dumps({'mission_wall_duration_s': 12})
            )
        with path.open('x', newline='') as stream:
            writer = csv.DictWriter(stream, fieldnames=FIELDS)
            writer.writeheader()
            writer.writerows(rows)
        return path

    def test_pass_requires_all_safe_completion_events(self):
        good = inspect_csv(self.make_csv())
        self.assertEqual(good['mission_outcome'], 'PASS')
        self.assertTrue(good['complete_record'])
        self.assertFalse(good['strict_experiment_valid'])
        bad = inspect_csv(self.make_csv('baseline_run_002.csv', events=False))
        self.assertEqual(bad['mission_outcome'], 'FAIL')
        self.assertTrue(bad['errors'])

    def test_failed_attempt_can_have_valid_cpu_and_payload_but_no_completion_time(self):
        record = inspect_csv(self.make_csv(passed=False))
        self.assertEqual(record['mission_outcome'], 'FAIL')
        self.assertTrue(record['metric_validity']['node_cpu_pct']['valid'])
        self.assertEqual(record['metrics']['node_cpu_pct'], 0)
        self.assertIsNotNone(record['metrics']['rx_payload_mbps'])
        self.assertIsNone(record['metrics']['mission_completion_s'])
        self.assertIsNone(record['metrics']['packet_loss_pct'])
        self.assertIsNone(record['metrics']['end_to_end_latency_ms'])

    def test_incomplete_is_never_pass_or_valid_duration(self):
        record = inspect_csv(self.make_csv(complete=False))
        self.assertFalse(record['complete_record'])
        self.assertEqual(record['mission_outcome'], 'FAIL')
        self.assertIsNone(record['metrics']['attempt_duration_s'])

    def test_duplicates_excluded_without_altering_raw(self):
        path = self.make_csv()
        original = path.read_bytes()
        (self.directory / 'baseline_run_002.csv').write_bytes(original)
        report = validate_dataset(self.directory)
        self.assertEqual(report['counts']['active_attempts'], 1)
        self.assertEqual(report['counts']['duplicate_files'], 1)
        self.assertEqual(path.read_bytes(), original)

    def test_passive_never_counted_as_active_or_given_study_slot(self):
        self.make_csv('preflight_001.csv', passive=True)
        report = validate_dataset(self.directory)
        self.assertEqual(report['counts']['active_attempts'], 0)
        self.assertEqual(report['records'][0]['mission_outcome'], 'NOT_ATTEMPTED')
        self.assertIsNone(report['records'][0]['experiment_id'])

    def test_exclusive_reports_and_persistent_assignment(self):
        self.make_csv()
        report = validate_dataset(self.directory)
        out = self.directory / 'report'
        write_report(report, out)
        with self.assertRaises(FileExistsError):
            write_report(report, out)
        repeated = validate_dataset(self.directory, out / 'manifest.json')
        self.assertEqual(repeated['records'][0]['experiment_id'], 'BASE-001')
        self.assertEqual(
            json.loads((out / 'manifest.json').read_text())['counts'],
            report['counts']
        )

    def test_invalid_numeric_measurement_not_zero_and_flags_schema_error(self):
        result = inspect_csv(self.make_csv(cpu='nan'))
        self.assertIsNone(result['metrics']['node_cpu_pct'])
        self.assertTrue(result['errors'])

    def test_passive_nonfinite_metric_rejected(self):
        from baseline_measurement.dataset import inspect_passive_json
        from baseline_measurement.experiment import Experiment
        capture = Experiment(self.directory, 'BASE-001', 'unit_test_fixture')
        capture.message('/p', 10)
        capture.finish()
        self.assertFalse(inspect_passive_json(capture.json_path)['errors'])
        rows = list(csv.DictReader(capture.raw_path.read_text().splitlines()))
        rows[0]['value'] = 'nan'
        with capture.raw_path.open('w', newline='') as stream:
            writer = csv.DictWriter(stream, fieldnames=rows[0].keys())
            writer.writeheader()
            writer.writerows(rows)
        self.assertTrue(inspect_passive_json(capture.json_path)['errors'])

    def test_cohort_ids_stay_fixed_when_a_larger_group_appears(self):
        original = self.make_csv()
        first = validate_dataset(self.directory)
        out = self.directory / 'first_report'
        write_report(first, out)
        for index in (2, 3):
            path = self.make_csv(f'baseline_run_{index:03d}.csv', cpu=str(index))
            text = path.read_text().replace('a' * 64, 'b' * 64)
            path.write_text(text)
        next_report = validate_dataset(self.directory, out / 'manifest.json')
        old = next(r for r in next_report['records'] if r['source_file'] == str(original))
        self.assertEqual(old['experiment_id'], 'BASE-001')
        self.assertEqual(first['primary_configuration_group'],
                         next_report['primary_configuration_group'])

    def test_bad_header_rejected(self):
        path = self.directory / 'baseline_run_001.csv'
        path.write_text('wrong,header\n1,2\n')
        result = inspect_csv(path)
        self.assertFalse(result['complete_record'])
        self.assertTrue(result['errors'])

    def test_summary_count_mismatch_invalidates_payload_and_pass(self):
        path = self.make_csv()
        with path.open(newline='') as stream:
            rows = list(csv.DictReader(stream))
        next((r for r in rows if r['record_type'] == 'topic_summary'))['count'] = '3'
        with path.open('w', newline='') as stream:
            writer = csv.DictWriter(stream, fieldnames=FIELDS)
            writer.writeheader()
            writer.writerows(rows)
        result = inspect_csv(path)
        self.assertFalse(result['complete_record'])
        self.assertEqual(result['mission_outcome'], 'FAIL')
        self.assertIsNone(result['metrics']['rx_payload_mbps'])


if __name__ == '__main__':
    unittest.main()
