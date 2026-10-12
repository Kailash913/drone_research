"""Synthetic negative fixtures test evidence validation, never flight outcomes."""

import csv
from datetime import datetime, timedelta, timezone
import json
from pathlib import Path
import tempfile
import unittest

from baseline_measurement.acceptance import main, validate_capture
from baseline_measurement.experiment_logger import FIELDS
from baseline_measurement.resource_monitor import role_for


class AcceptanceTests(unittest.TestCase):
    def capture(self):
        keys = ('status', 'position', 'attitude', 'land', 'battery')
        topics = {key: '/test/' + key for key in keys}
        rows = [{'record_type': 'metadata', 'elapsed_s': 0.,
                 'detail': json.dumps({'mode': 'PASSIVE_PREFLIGHT', 'outputs': topics})}]
        for second in range(1, 15):
            for topic in topics.values():
                rows.append({'record_type': 'message', 'elapsed_s': second,
                             'direction': 'rx_callback', 'topic': topic,
                             'source_timestamp_us': second * 1000000})
            rows.append({'record_type': 'resource', 'elapsed_s': second, 'armed': False,
                         'detail': json.dumps({'connected': True, 'healthy': True,
                                               'valid': True, 'landed': True,
                                               'competition': False, 'heading_ready': False})})
        for topic in topics.values():
            rows.append({'record_type': 'topic_summary', 'elapsed_s': 15.,
                         'direction': 'rx_callback', 'topic': topic, 'count': 14,
                         'rate_hz': 14 / 15.02})
        rows.append({'record_type': 'result', 'elapsed_s': 15.02, 'state': 'PREFLIGHT',
                     'failure_reason': 'Passive observation only; no mission attempted',
                     'detail': json.dumps({'mission_wall_duration_s': 15.02})})
        return rows

    def check(self, rows, fields=FIELDS):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'fixture.csv'
            with path.open('w', newline='', encoding='utf-8') as stream:
                writer = csv.DictWriter(stream, fieldnames=fields, extrasaction='ignore')
                writer.writeheader()
                for row in rows:
                    row = dict(row)
                    row['utc'] = (datetime(2026, 1, 1, tzinfo=timezone.utc)
                                  + timedelta(seconds=row['elapsed_s'])).isoformat()
                    writer.writerow(row)
            return validate_capture(path)

    def test_passive_success_is_separate_from_mission_and_heading(self):
        result = self.check(self.capture())
        self.assertEqual(result['decision'], 'PASS', result['errors'])
        self.assertEqual(result['mission_status'], 'not_demonstrated')
        self.assertFalse(result['heading_ready_at_end'])

    def test_never_valid_or_invalid_stable_window_fails(self):
        for all_samples in (True, False):
            rows = self.capture()
            for row in rows:
                if row['record_type'] == 'resource' and (all_samples or row['elapsed_s'] == 10):
                    state = json.loads(row['detail'])
                    state['valid'] = False
                    row['detail'] = json.dumps(state)
            self.assertEqual(self.check(rows)['decision'], 'FAIL')

    def test_startup_recovery_is_reported_separately(self):
        rows = self.capture()
        for row in rows:
            if row['record_type'] == 'resource' and row['elapsed_s'] < 3:
                state = json.loads(row['detail'])
                state['connected'] = state['valid'] = False
                row['detail'] = json.dumps(state)
        result = self.check(rows)
        self.assertEqual(result['decision'], 'PASS', result['errors'])
        self.assertEqual(result['first_valid_sample_s'], 3.)
        self.assertEqual(result['startup_records'], 4)

    def test_command_or_competition_fails(self):
        for case in ('command', 'tx', 'competition', 'armed'):
            rows = self.capture()
            row = next(r for r in rows if r['record_type'] == 'resource')
            if case == 'command':
                row['record_type'] = 'command'
            elif case == 'tx':
                row['direction'] = 'tx_publish_call'
            elif case == 'armed':
                row['armed'] = True
            else:
                state = json.loads(row['detail'])
                state['competition'] = True
                row['detail'] = json.dumps(state)
            with self.subTest(case=case):
                self.assertEqual(self.check(rows)['decision'], 'FAIL')

    def test_schema_incomplete_and_interrupted_results_fail(self):
        self.assertEqual(self.check(self.capture(), FIELDS[:-1])['decision'], 'FAIL')
        self.assertEqual(self.check(self.capture()[:-1])['decision'], 'FAIL')
        rows = self.capture()
        rows[-1]['failure_reason'] = 'Interrupted'
        self.assertEqual(self.check(rows)['decision'], 'FAIL')

    def test_missing_frozen_and_inconsistent_topic_counts_fail(self):
        for case in ('missing', 'frozen', 'count'):
            rows = self.capture()
            if case == 'missing':
                rows = [r for r in rows if r.get('topic') != '/test/status']
            elif case == 'frozen':
                for row in rows:
                    if row.get('topic') == '/test/status' and row['record_type'] == 'message':
                        row['source_timestamp_us'] = 1
            else:
                next(r for r in rows if r['record_type'] == 'topic_summary')['count'] = 1
            with self.subTest(case=case):
                self.assertEqual(self.check(rows)['decision'], 'FAIL')

    def test_short_run_and_missing_resource_window_fail(self):
        rows = self.capture()
        rows[-1]['detail'] = json.dumps({'mission_wall_duration_s': 2.})
        self.assertEqual(self.check(rows)['decision'], 'FAIL')
        rows = [r for r in self.capture() if r['record_type'] != 'resource']
        self.assertEqual(self.check(rows)['decision'], 'FAIL')

    def test_duplicate_demonstrations_rejected(self):
        with self.assertRaises(SystemExit) as raised:
            main(['same.csv', 'same.csv'])
        self.assertEqual(raised.exception.code, 2)

    def test_gazebo_ruby_launcher_accounting(self):
        self.assertEqual(role_for('ruby', ['ruby', '/usr/bin/gz', 'sim', '--headless'], False),
                         'gazebo_sim')
        self.assertIsNone(role_for('ruby', ['ruby', 'application.rb'], False))
        self.assertIsNone(role_for('bash', ['bash', '-c', 'gz sim'], False))

    def test_missing_file_and_nonfinite_duration_fail_cleanly(self):
        with tempfile.TemporaryDirectory() as directory:
            result = validate_capture(Path(directory) / 'absent.csv')
            self.assertEqual(result['decision'], 'FAIL')
        rows = self.capture()
        rows[-1]['detail'] = '{"mission_wall_duration_s": NaN}'
        result = self.check(rows)
        self.assertEqual(result['decision'], 'FAIL')
        json.dumps(result, allow_nan=False)

    def test_clock_regression_is_detected_between_resource_samples(self):
        rows = self.capture()
        samples = [r for r in rows if r.get('topic') == '/test/status'
                   and r['record_type'] == 'message']
        samples[-1]['source_timestamp_us'] = 1
        result = self.check(rows)
        self.assertEqual(result['decision'], 'FAIL')
        self.assertEqual(len(result['source_clock_regressions']), 1)
