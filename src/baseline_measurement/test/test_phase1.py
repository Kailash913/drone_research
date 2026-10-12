"""Policy/measurement tests run without ROS; not a substitute for SITL testing."""
import csv
from pathlib import Path
import tempfile
import unittest

from baseline_measurement.experiment_logger import RunLog, TopicStats
from baseline_measurement.mission_state import Mission, STAGES, Telemetry


def ready():
    return Telemetry(
        connected=True,
        healthy=True,
        valid=True,
        heading_ready=True,
        landed=True,
        position=(3.0, 4.0, -0.2)
    )


class PolicyTests(unittest.TestCase):

    def advance_to_flight(self):
        m, t = (Mission(0.0), ready())
        for i in range(400):
            now = i * 0.05
            for command in m.tick(now, t):
                if command == 'OFFBOARD':
                    t.offboard = True
                if command == 'ARM':
                    t.armed = True
            if m.state == 'TAKEOFF':
                return (m, t, now)
        self.fail('Did not start takeoff')

    def test_complete_mission_requires_all_stages(self):
        m, t, start = self.advance_to_flight()
        for i in range(1, 6000):
            now = start + i * 0.05
            sp = m.setpoint(now)
            if sp is not None:
                t.position = sp
                if t.armed and sp[2] < m.home[2] - 0.1:
                    t.landed = False
            if m.state == 'LAND' and now - m.entered > 3.0:
                t.landed = True
            for command in m.tick(now, t):
                if command == 'LAND':
                    t.landing, t.offboard = (True, False)
                if command == 'DISARM':
                    self.assertTrue(t.landed)
                    t.armed = False
                if command == 'HOLD':
                    t.holding, t.offboard = (True, False)
            if m.done:
                break
        self.assertTrue(m.passed, m.failure_reason)
        self.assertEqual(m.reached, list(STAGES))
        self.assertEqual(m.target, (3.0, 4.0, -10.2))
        self.assertFalse(t.armed)

    def test_no_commands_without_telemetry(self):
        m = Mission(0.0)
        for i in range(800):
            self.assertEqual(m.tick(i * 0.05, Telemetry()), [])
        self.assertTrue(m.done)
        self.assertFalse(m.passed)

    def test_no_takeover_already_armed(self):
        m, t = (Mission(0.0), ready())
        t.armed = True
        for i in range(5):
            self.assertEqual(m.tick(i * 0.05, t), [])
        self.assertIn('already armed', m.failure_reason)

    def test_preflight_requires_continuous_health(self):
        m, t = (Mission(0.0), ready())
        for i in range(100):
            t.healthy = i % 30 != 0
            self.assertEqual(m.tick(i * 0.05, t), [])
        self.assertEqual(m.state, 'WAIT_FOR_HEALTH')

    def test_failures_stop_trajectory_and_never_pass(self):
        for flag, value in [
            ('connected', False),
            ('valid', False),
            ('healthy', False),
            ('heading_ready', False),
            ('failsafe', True),
            ('reset', True),
            ('competition', True)
        ]:
            with self.subTest(flag=flag):
                m, t, now = self.advance_to_flight()
                t.landed = False
                setattr(t, flag, value)
                commands = m.tick(now + 0.05, t)
                self.assertEqual(commands, ['LAND'])
                self.assertIsNone(m.setpoint(now + 0.05))
                self.assertEqual(m.state, 'FAILSAFE')
                self.assertFalse(m.passed)
                self.assertEqual(m.tick(now + 0.1, t), [])

    def test_scheduling_gap_fails(self):
        m, t, now = self.advance_to_flight()
        m.tick(now + 0.3, t)
        self.assertIn('scheduling', m.failure_reason)

    def test_failure_latches_after_recovery(self):
        m, t, now = self.advance_to_flight()
        t.valid = False
        m.tick(now + 0.05, t)
        t.valid, t.landed, t.armed = (True, True, False)
        m.tick(now + 0.1, t)
        self.assertTrue(m.done)
        self.assertFalse(m.passed)
        self.assertTrue(m.failure_reason)

    def test_preflight_stream_before_mode_and_arm(self):
        m, t = (Mission(0.0), ready())
        commands = []
        first_setpoint = None
        for i in range(150):
            now = i * 0.05
            for command in m.tick(now, t):
                commands.append((command, now))
                if command == 'OFFBOARD':
                    t.offboard = True
                if command == 'ARM':
                    t.armed = True
            if m.setpoint(now) is not None and first_setpoint is None:
                first_setpoint = now
        self.assertEqual([x[0] for x in commands], ['OFFBOARD', 'ARM'])
        self.assertGreaterEqual(commands[0][1] - first_setpoint, 2.0)

    def test_unreached_waypoint_times_out(self):
        m, t, now = self.advance_to_flight()
        t.landed = False
        for i in range(1, 1220):
            m.tick(now + i * 0.05, t)
        self.assertEqual(m.failure_state, 'TAKEOFF')
        self.assertFalse(m.passed)

    def test_never_disarms_in_air(self):
        m, t, now = self.advance_to_flight()
        m.transition('DISARM', now)
        t.landed = False
        commands = m.tick(now + 0.05, t)
        self.assertNotIn('DISARM', commands)
        self.assertEqual(m.state, 'FAILSAFE')

    def test_disarmed_without_waypoints_is_not_pass(self):
        m, t = (Mission(0.0), ready())
        m.transition('DISARM', 0.0)
        m.tick(0.05, t)
        self.assertFalse(m.passed)

    def test_landing_detector_not_low_altitude_required(self):
        m, t, now = self.advance_to_flight()
        m.transition('LAND', now)
        t.landed = False
        t.position = m.home
        t.landing = True
        for i in range(1, 60):
            self.assertNotIn('DISARM', m.tick(now + i * 0.05, t))
        self.assertEqual(m.state, 'LAND')


class LogTests(unittest.TestCase):

    def test_rate_jitter_bytes(self):
        stats = TopicStats()
        self.assertIsNone(stats.add(0.0, 100))
        self.assertEqual(stats.add(0.1, 100), 100.0)
        stats.add(0.3, 100)
        result = stats.summary(1.0)
        self.assertEqual(result['rate_hz'], 3.0)
        self.assertAlmostEqual(result['iat_mean_ms'], 150.0)
        self.assertAlmostEqual(result['iat_stddev_ms'], 70.71067811865)
        self.assertEqual(result['total_payload_cdr_bytes'], 300)
        self.assertEqual(result['estimated_missing_messages'], '')

    def test_csv_is_exclusive_and_failure_explicit(self):
        with tempfile.TemporaryDirectory() as directory:
            first, second = (RunLog(directory), RunLog(directory))
            self.assertNotEqual(first.path, second.path)
            first.finish(False, 'ARM', 'denied')
            second.finish(False, 'WAIT_FOR_PX4', 'timeout')
            with first.path.open(newline='', encoding='utf-8') as stream:
                rows = list(csv.DictReader(stream))
            self.assertEqual(rows[-1]['success'], 'False')
            self.assertEqual(rows[-1]['failure_reason'], 'denied')
            self.assertEqual(len(list(Path(directory).glob('baseline_run_*.csv'))), 2)


if __name__ == '__main__':
    unittest.main()
