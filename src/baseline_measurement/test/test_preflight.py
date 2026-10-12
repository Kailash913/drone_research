"""Exercise the real ROS adapter predicates without a live ROS graph."""

import math
from types import SimpleNamespace
import unittest
from unittest import mock

from baseline_measurement.mission_node import MissionNode, OUTPUTS
from baseline_measurement.mission_state import Mission, STAGES
from px4_msgs.msg import VehicleLandDetected, VehicleLocalPosition, VehicleStatus


class PreflightTests(unittest.TestCase):
    def adapter(self):
        status = VehicleStatus()
        status.pre_flight_checks_pass = True
        status.arming_state = VehicleStatus.ARMING_STATE_DISARMED
        status.vehicle_type = VehicleStatus.VEHICLE_TYPE_ROTARY_WING
        position = VehicleLocalPosition()
        position.xy_valid = position.z_valid = True
        position.v_xy_valid = position.v_z_valid = True
        land = VehicleLandDetected()
        land.landed = True
        return SimpleNamespace(
            options=SimpleNamespace(execute_sitl=False),
            latest={'status': status, 'position': position, 'land': land},
            received=dict.fromkeys(('status', 'position', 'attitude', 'land'), 10.),
            last_graph=-math.inf, graph_ok=False, competition=False, reset=False,
            count_subscribers=lambda topic: 1, count_publishers=lambda topic: 0)

    def test_grounded_heading_is_independent(self):
        for heading in (False, True):
            with self.subTest(heading=heading):
                node = self.adapter()
                node.latest['position'].heading_good_for_control = heading
                t = MissionNode.telemetry(node, 10.)
                self.assertTrue(t.connected and t.healthy and t.valid and t.landed)
                self.assertFalse(t.armed or t.competition)
                self.assertEqual(t.heading_ready, heading)
                mission = Mission(10.)
                for i in range(50):
                    self.assertEqual(mission.tick(10.+i*.05, t), [])
                if heading:
                    self.assertEqual(mission.state, 'PREFLIGHT_SETPOINT')
                    self.assertIsNotNone(mission.setpoint(12.5))
                else:
                    self.assertEqual(mission.state, 'WAIT_FOR_HEADING')
                    self.assertIsNone(mission.setpoint(12.5))
                    t.heading_ready = True
                    mission.tick(12.5, t)
                    self.assertEqual(mission.state, 'PREFLIGHT_SETPOINT')

    def test_invalid_position_velocity_and_dead_reckoning(self):
        for flag in ('xy_valid', 'z_valid', 'v_xy_valid', 'v_z_valid', 'dead_reckoning'):
            with self.subTest(flag=flag):
                node = self.adapter()
                setattr(node.latest['position'], flag, flag == 'dead_reckoning')
                self.assertFalse(MissionNode.telemetry(node, 10.).valid)

    def test_nonfinite_values(self):
        for field in ('x', 'y', 'z', 'vx', 'vy', 'vz', 'heading'):
            for value in (math.nan, math.inf):
                with self.subTest(field=field, value=value):
                    node = self.adapter()
                    setattr(node.latest['position'], field, value)
                    self.assertFalse(MissionNode.telemetry(node, 10.).valid)

    def test_stale_missing_and_disconnected(self):
        for key in ('status', 'position', 'attitude', 'land'):
            node = self.adapter()
            node.received[key] = 8.
            t = MissionNode.telemetry(node, 10.)
            self.assertFalse(t.connected or t.valid)
            del node.received[key]
            self.assertFalse(MissionNode.telemetry(node, 10.).valid)
        node = self.adapter()
        node.count_subscribers = lambda topic: 0
        self.assertFalse(MissionNode.telemetry(node, 10.).valid)

    def test_failsafe_health_and_reset(self):
        for flag, value in (('failsafe', True), ('pre_flight_checks_pass', False),
                            ('calibration_enabled', True), ('rc_calibration_in_progress', True),
                            ('gcs_connection_lost', True)):
            node = self.adapter()
            setattr(node.latest['status'], flag, value)
            self.assertFalse(MissionNode.telemetry(node, 10.).valid)
        node = self.adapter()
        node.reset = True
        self.assertFalse(MissionNode.telemetry(node, 10.).valid)

    def test_invalid_after_preflight_and_heading_loss(self):
        for state in ('WAIT_FOR_HEADING', 'PREFLIGHT_SETPOINT', 'OFFBOARD', 'ARM', *STAGES):
            for flag in ('valid', 'heading_ready'):
                if state == 'WAIT_FOR_HEADING' and flag == 'heading_ready':
                    continue
                with self.subTest(state=state, flag=flag):
                    node = self.adapter()
                    node.latest['position'].heading_good_for_control = True
                    t = MissionNode.telemetry(node, 10.)
                    mission = Mission(10.)
                    mission.transition(state, 10.)
                    setattr(t, flag, False)
                    self.assertEqual(mission.tick(10.05, t), [])
                    self.assertTrue(mission.done)
                    self.assertFalse(mission.passed)
                    self.assertIsNone(mission.setpoint(10.05))

    def test_passive_publication_rejected(self):
        node = self.adapter()
        for key in ('command', 'mode', 'trajectory'):
            with self.subTest(key=key), self.assertRaisesRegex(RuntimeError, 'passive'):
                MissionNode.publish(node, key, object())

    def test_heading_wait_timeout_is_bounded_and_latched(self):
        t = MissionNode.telemetry(self.adapter(), 10.)
        mission = Mission(10.)
        mission.transition('WAIT_FOR_HEADING', 10.)
        for i in range(601):
            now = 10. + i * .05
            self.assertEqual(mission.tick(now, t), [])
            self.assertIsNone(mission.setpoint(now))
        self.assertFalse(mission.done)
        self.assertEqual(mission.tick(40.05, t), [])
        self.assertTrue(mission.done)
        self.assertEqual(mission.failure_state, 'WAIT_FOR_HEADING')
        self.assertEqual(mission.failure_reason, 'State timeout')
        t.heading_ready = True
        self.assertEqual(mission.tick(40.1, t), [])
        self.assertIsNone(mission.setpoint(40.1))
        self.assertFalse(mission.passed)

    def test_heading_wait_rejects_unsafe_state_even_when_heading_recovers(self):
        for flag, value in (('armed', True), ('landed', False), ('connected', False),
                            ('healthy', False), ('competition', True), ('reset', True),
                            ('failsafe', True)):
            with self.subTest(flag=flag):
                t = MissionNode.telemetry(self.adapter(), 10.)
                t.heading_ready = True
                setattr(t, flag, value)
                mission = Mission(10.)
                mission.transition('WAIT_FOR_HEADING', 10.)
                self.assertEqual(mission.tick(10.05, t), [])
                self.assertEqual(mission.state, 'FAILSAFE')
                self.assertEqual(mission.tick(10.1, t), [])
                self.assertTrue(mission.done)
                self.assertFalse(mission.owned or mission.passed)
                self.assertIsNone(mission.home)
                self.assertIsNone(mission.setpoint(10.05))

    def timer_adapter(self, execute_sitl):
        node = self.adapter()
        node.options = SimpleNamespace(execute_sitl=execute_sitl, observe_seconds=100.)
        node.mission = Mission(10.)
        node.mission.transition('WAIT_FOR_HEADING', 10.)
        node.telemetry = lambda now: MissionNode.telemetry(node, now)
        node.last_resource = 10.
        node.started = 10.
        node.experiment = None
        node.event_cursor = 0
        node.done = False
        node.log = mock.Mock()
        node.get_logger = mock.Mock()
        node.publish = mock.Mock()
        node.command = mock.Mock()
        return node

    def test_timer_never_publishes_before_heading_and_stops_on_heading_loss(self):
        node = self.timer_adapter(True)
        with mock.patch('baseline_measurement.mission_node.time.monotonic', return_value=10.05):
            MissionNode.tick(node)
        node.publish.assert_not_called()
        node.command.assert_not_called()
        node.latest['position'].heading_good_for_control = True
        node.latest['position'].heading = .25
        with mock.patch('baseline_measurement.mission_node.time.monotonic', return_value=10.1):
            MissionNode.tick(node)
        self.assertEqual([c.args[0] for c in node.publish.call_args_list], ['trajectory', 'mode'])
        self.assertEqual(node.publish.call_args_list[0].args[1].yaw, .25)
        node.publish.reset_mock()
        node.latest['position'].heading_good_for_control = False
        with mock.patch('baseline_measurement.mission_node.time.monotonic', return_value=10.15):
            MissionNode.tick(node)
        node.publish.assert_not_called()
        node.command.assert_not_called()
        self.assertTrue(node.done)
        self.assertEqual(node.mission.failure_reason, 'Heading readiness lost during yaw control')

    def test_passive_timer_does_not_tick_policy_even_with_heading_ready(self):
        node = self.timer_adapter(False)
        node.latest['position'].heading_good_for_control = True
        node.mission.tick = mock.Mock(side_effect=AssertionError('Passive policy tick'))
        with mock.patch('baseline_measurement.mission_node.time.monotonic', return_value=10.05):
            MissionNode.tick(node)
        node.mission.tick.assert_not_called()
        node.publish.assert_not_called()
        node.command.assert_not_called()

    def callback_adapter(self):
        node = self.adapter()
        node.stamps = {}
        node.outputs = OUTPUTS
        node.log = mock.Mock()
        node.experiment = None
        node.mission = Mission(10.)
        node.pending_command = None
        node.reset_counters = None
        return node

    def test_source_freeze_and_clock_reversal_do_not_refresh_telemetry(self):
        node = self.callback_adapter()
        msg = VehicleStatus()
        msg.timestamp = 100
        for now, stamp in ((10., 100), (11., 100), (12., 99)):
            msg.timestamp = stamp
            with mock.patch('baseline_measurement.mission_node.time.monotonic', return_value=now):
                MissionNode.receive(node, 'status', msg)
        self.assertEqual(node.received['status'], 10.)
        self.assertTrue(node.reset)
        self.assertFalse(MissionNode.telemetry(node, 12.).valid)

    def test_telemetry_startup_recovery_and_status_interpretation(self):
        node = self.adapter()
        node.received = {}
        self.assertFalse(MissionNode.telemetry(node, 10.).connected)
        node.received = dict.fromkeys(('status', 'position', 'attitude', 'land'), 11.)
        t = MissionNode.telemetry(node, 11.)
        self.assertTrue(t.connected and t.healthy and t.valid)
        node.latest['status'].arming_state = VehicleStatus.ARMING_STATE_ARMED
        node.latest['status'].nav_state = VehicleStatus.NAVIGATION_STATE_AUTO_LAND
        node.latest['land'].landed = False
        t = MissionNode.telemetry(node, 11.)
        self.assertTrue(t.armed and t.landing)
        self.assertFalse(t.landed or t.offboard)

    def test_publisher_conflicts_respect_own_publisher_budget(self):
        for execute, total, conflict in ((False, 0, False), (False, 1, True),
                                         (True, 1, False), (True, 2, True)):
            with self.subTest(execute=execute, total=total):
                node = self.adapter()
                node.options.execute_sitl = execute
                node.count_publishers = lambda topic: total
                self.assertEqual(MissionNode.telemetry(node, 10.).competition, conflict)

    def test_command_ack_rejection_requires_pending_command_and_target(self):
        from px4_msgs.msg import VehicleCommand, VehicleCommandAck
        for matching, targeted, rejection in ((True, True, True), (False, True, False),
                                              (True, False, False)):
            node = self.callback_adapter()
            command = VehicleCommand.VEHICLE_CMD_COMPONENT_ARM_DISARM
            node.pending_command = command if matching else None
            ack = VehicleCommandAck()
            ack.command = command
            ack.timestamp = 100
            ack.target_system = 245 if targeted else 1
            ack.target_component = 191
            ack.result = VehicleCommandAck.VEHICLE_CMD_RESULT_DENIED
            MissionNode.receive(node, 'ack', ack)
            self.assertEqual(bool(node.mission.failure_reason), rejection)

    def test_accepted_ack_does_not_confirm_arming(self):
        from px4_msgs.msg import VehicleCommand, VehicleCommandAck
        node = self.callback_adapter()
        command = VehicleCommand.VEHICLE_CMD_COMPONENT_ARM_DISARM
        node.pending_command = command
        node.mission.transition('ARM', 10.)
        ack = VehicleCommandAck()
        ack.command = command
        ack.timestamp = 100
        ack.target_system, ack.target_component = 245, 191
        ack.result = VehicleCommandAck.VEHICLE_CMD_RESULT_ACCEPTED
        MissionNode.receive(node, 'ack', ack)
        self.assertEqual(node.mission.state, 'ARM')
        self.assertFalse(node.mission.passed)

    def test_offboard_and_arm_commands_timeout_without_observed_state(self):
        for state in ('OFFBOARD', 'ARM'):
            with self.subTest(state=state):
                node = self.adapter()
                node.latest['position'].heading_good_for_control = True
                t = MissionNode.telemetry(node, 10.)
                t.offboard = state == 'ARM'
                mission = Mission(10.)
                mission.transition(state, 10.)
                requests = []
                for i in range(202):
                    requests.extend(mission.tick(10. + i * .05, t))
                self.assertEqual(requests, [state])
                self.assertTrue(mission.done)
                self.assertEqual(mission.failure_state, state)
                self.assertEqual(mission.failure_reason, 'State timeout')
                self.assertFalse(mission.passed)
