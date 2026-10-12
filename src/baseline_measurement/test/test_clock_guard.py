"""Regression evidence for the unchanged conservative flight timestamp policy."""
import copy
import json
import unittest
from unittest import mock

from baseline_measurement.dataset import TimestampAudit
from baseline_measurement.mission_node import MissionNode
from baseline_measurement.mission_state import STAGES
from px4_msgs.msg import VehicleStatus
import test_preflight


class ClockGuardTests(unittest.TestCase):

    def adapter(self):
        node = test_preflight.PreflightTests().callback_adapter()
        node.mission.home = (0.0, 0.0, 0.0)
        node.mission.target = (20.0, 0.0, -10.0)
        node.mission.transition('WAYPOINT_1', 10.0)
        node.mission.owned = True
        node.latest['status'].arming_state = VehicleStatus.ARMING_STATE_ARMED
        node.latest['status'].nav_state = VehicleStatus.NAVIGATION_STATE_OFFBOARD
        node.latest['land'].landed = False
        node.latest['position'].heading_good_for_control = True
        return node

    def receive(self, node, timestamp, now, counter=None):
        msg = copy.deepcopy(node.latest['position'])
        msg.timestamp = timestamp
        if counter is not None:
            msg.xy_reset_counter = counter
        with mock.patch('baseline_measurement.mission_node.time.monotonic', return_value=now):
            MissionNode.receive(node, 'position', msg)
        return MissionNode.telemetry(node, now)

    def test_monotonic_source_does_not_log_or_fail(self):
        node = self.adapter()
        for index, stamp in enumerate((100, 200, 300)):
            t = self.receive(node, stamp, 10.0 + index * 0.05)
            node.mission.tick(10.0 + index * 0.05, t)
        self.assertFalse(node.reset)
        self.assertEqual(node.mission.state, 'WAYPOINT_1')
        node.log.row.assert_not_called()

    def test_epoch_boot_mismatch_is_logged_and_fails_without_claiming_reset_proof(self):
        node = self.adapter()
        self.receive(node, 1790000000000000, 10.0)
        t = self.receive(node, 100000000, 10.05)
        node.mission.tick(10.05, t)
        self.assertEqual(node.mission.state, 'FAILSAFE')
        self.assertFalse(node.mission.passed)
        event = node.log.row.call_args
        self.assertEqual(event.args[0], 'source_clock_reset')
        self.assertEqual(json.loads(event.kwargs['detail'])['current_us'], 100000000)
        audit = TimestampAudit()
        audit.observe('p', 1790000000000000, 10.0)
        audit.observe('p', 100000000, 10.05)
        self.assertFalse(audit.events[-1]['estimator_reset_proven'])

    def test_one_anomaly_then_valid_stream_cannot_unlatch_flight_failure(self):
        node = self.adapter()
        self.receive(node, 1000, 10.0)
        node.mission.tick(10.05, self.receive(node, 50, 10.05))
        node.mission.tick(10.1, self.receive(node, 2000, 10.1))
        self.assertTrue(node.reset)
        self.assertEqual(node.mission.state, 'FAILSAFE')
        self.assertFalse(node.mission.passed)
        self.assertEqual(node.received['position'], 10.1)
        self.assertEqual(node.log.row.call_count, 1)

    def test_persistent_discontinuity_keeps_logging_and_never_refreshes_source_progress(self):
        node = self.adapter()
        self.receive(node, 1000, 10.0)
        for index, stamp in enumerate((50, 60, 70), 1):
            now = 10.0 + index * 0.05
            node.mission.tick(now, self.receive(node, stamp, now))
        self.assertEqual(node.received['position'], 10.0)
        self.assertEqual(node.log.row.call_count, 3)
        self.assertEqual(node.mission.state, 'FAILSAFE')

    def test_stale_local_receive_clock_fails_airborne_even_with_epoch_timestamp(self):
        node = self.adapter()
        self.receive(node, 1790000000000000, 10.0)
        node.mission.last_tick = 11.95
        node.mission.tick(12.0, MissionNode.telemetry(node, 12.0))
        self.assertEqual(node.mission.state, 'FAILSAFE')
        self.assertIn('Telemetry stale', node.mission.failure_reason)
        self.assertIn('FAILSAFE', [x[0] for x in node.mission.events])

    def test_out_of_order_message_is_conservatively_logged(self):
        node = self.adapter()
        self.receive(node, 200, 10.0)
        node.mission.tick(10.05, self.receive(node, 199, 10.05))
        self.assertEqual(node.log.row.call_args.args[0], 'source_clock_reset')
        self.assertEqual(node.mission.state, 'FAILSAFE')

    def test_repeated_source_timestamp_does_not_keep_watchdog_alive(self):
        node = self.adapter()
        self.receive(node, 100, 10.0)
        for index in range(1, 41):
            now = 10.0 + index * 0.05
            for key in ('status', 'attitude', 'land'):
                node.received[key] = now
            node.mission.tick(now, self.receive(node, 100, now))
        self.assertFalse(node.reset)
        self.assertEqual(node.received['position'], 10.0)
        self.assertEqual(node.mission.state, 'FAILSAFE')
        self.assertIn('Telemetry stale', node.mission.failure_reason)
        node.log.row.assert_not_called()

    def test_zero_after_valid_timestamp_is_logged_and_fails(self):
        node = self.adapter()
        self.receive(node, 100, 10.0)
        node.mission.tick(10.05, self.receive(node, 0, 10.05))
        self.assertEqual(node.mission.state, 'FAILSAFE')
        self.assertEqual(node.log.row.call_args.args[0], 'source_clock_reset')

    def test_zero_or_missing_diagnostic_timestamp_preserves_receive_freshness_only(self):
        audit = TimestampAudit()
        for stamp in (None, 0, ''):
            self.assertEqual(
                audit.observe('p', stamp, 10.0),
                'missing_or_invalid_source_timestamp'
            )
        self.assertFalse(audit.stale('p', 10.1))
        self.assertTrue(audit.stale('p', 12.0))
        self.assertEqual(len(audit.events), 3)
        node = self.adapter()
        self.receive(node, 0, 10.0)
        self.assertEqual(node.received['position'], 10.0)
        node.mission.last_tick = 11.95
        node.mission.tick(12.0, self.receive(node, 0, 12.0))
        self.assertEqual(node.mission.state, 'FAILSAFE')

    def test_actual_position_reset_counter_latches_failure_without_timestamp_jump(self):
        node = self.adapter()
        self.receive(node, 100, 10.0, 1)
        node.mission.tick(10.05, self.receive(node, 200, 10.05, 2))
        self.assertTrue(node.reset)
        self.assertEqual(node.mission.state, 'FAILSAFE')
        self.assertEqual(node.log.row.call_args.args[0], 'estimator_reset_counter_change')
        self.assertEqual(json.loads(node.log.row.call_args.kwargs['detail'])['current'], [2, 0, 0])
        self.assertIn('FAILSAFE', [x[0] for x in node.mission.events])

    def test_stream_recovery_after_loss_never_turns_failed_attempt_into_pass(self):
        node = self.adapter()
        self.receive(node, 100, 10.0)
        node.mission.last_tick = 11.95
        node.mission.tick(12.0, MissionNode.telemetry(node, 12.0))
        for key in ('status', 'land', 'attitude'):
            node.received[key] = 12.05
        node.mission.tick(12.05, self.receive(node, 200, 12.05))
        self.assertEqual(node.mission.state, 'FAILSAFE')
        self.assertFalse(node.mission.passed)

    def test_landing_requires_grounded_full_route_before_rebase(self):
        for route, landed, expected in (
            (True, True, 'LAND'),
            (False, True, 'FAILSAFE'),
            (True, False, 'FAILSAFE')
        ):
            node = self.adapter()
            node.mission.transition('LAND', 10.0)
            node.mission.reached = list(STAGES) if route else []
            node.latest['land'].landed = landed
            node.latest['status'].nav_state = VehicleStatus.NAVIGATION_STATE_AUTO_LAND
            self.receive(node, 200, 10.0)
            node.mission.tick(10.05, self.receive(node, 50, 10.05))
            self.assertTrue(node.reset)
            self.assertEqual(node.log.row.call_args.args[0], 'source_clock_reset')
            self.assertEqual(node.mission.state, expected)
            self.assertFalse(node.mission.passed)

    def test_grounded_completion_still_rejects_px4_failsafe(self):
        node = self.adapter()
        node.mission.transition('LAND', 10.0)
        node.mission.reached = list(STAGES)
        node.latest['land'].landed = True
        node.latest['status'].nav_state = VehicleStatus.NAVIGATION_STATE_AUTO_LAND
        self.receive(node, 200, 10.0)
        node.latest['status'].failsafe = True
        node.mission.tick(10.05, self.receive(node, 50, 10.05))
        self.assertEqual(node.mission.state, 'FAILSAFE')
        self.assertEqual(node.mission.failure_reason, 'PX4 reports failsafe')

    def test_uint64_source_diagnostics_preserve_exact_integer(self):
        audit = TimestampAudit()
        stamp = 18446744073709551600
        audit.observe('p', str(stamp), 10.0)
        audit.observe('p', str(stamp - 1), 10.1)
        self.assertEqual(audit.events[-1]['previous_us'], stamp)
        self.assertEqual(audit.events[-1]['current_us'], stamp - 1)

    def test_probe_logs_real_counter_changes_and_keeps_source_fields(self):
        from types import SimpleNamespace
        from baseline_measurement.clock_probe import ClockProbe
        probe = (
            SimpleNamespace(
                counts={},
                audit=TimestampAudit(),
                previous_counters={},
                row=mock.Mock()
            )
        )
        node = self.adapter()
        message = copy.deepcopy(node.latest['position'])
        message.timestamp = 100
        message.timestamp_sample = 90
        ClockProbe.receive(probe, '/p', message)
        message.timestamp = 200
        message.timestamp_sample = 190
        message.xy_reset_counter += 1
        ClockProbe.receive(probe, '/p', message)
        kinds = [c.args[0] for c in probe.row.call_args_list]
        self.assertIn('estimator_counter_change', kinds)
        self.assertNotIn('source_order_event', kinds)
        self.assertEqual(probe.row.call_args.kwargs['timestamp_sample_us'], 190)

    def test_probe_records_nonfinite_estimate_without_losing_receipt_watchdog(self):
        from types import SimpleNamespace
        from baseline_measurement.clock_probe import ClockProbe
        probe = SimpleNamespace(
            start=10., counts={}, audit=TimestampAudit(),
            previous_counters={}, row=mock.Mock())
        message = self.adapter().latest['position']
        message.timestamp = 100
        message.heading = float('nan')
        with mock.patch('baseline_measurement.clock_probe.time.monotonic', return_value=11.):
            ClockProbe.receive(probe, '/p', message)
        self.assertEqual(probe.row.call_args_list[0].args[0], 'invalid_numeric_evidence')
        self.assertIsNone(probe.row.call_args.kwargs['detail']['heading'])
        self.assertFalse(probe.audit.stale('/p', 1.1))
        self.assertTrue(probe.audit.stale('/p', 3.))


if __name__ == '__main__':
    unittest.main()
