"""Exercise the automatic takeoff command and estimator gates with real ROS types."""
import math
import unittest
from unittest import mock

from baseline_measurement.mission_node import MissionNode
from px4_msgs.msg import EstimatorStatusFlags, VehicleCommand, VehicleStatus
import test_preflight as preflight


class AutoAdapterTests(unittest.TestCase):

    def adapter(self):
        node = preflight.PreflightTests().adapter()
        node.latest['position'].xy_global = node.latest['position'].z_global = True
        flags = EstimatorStatusFlags()
        flags.cs_yaw_align = True
        node.latest['estimator'] = flags
        node.received['estimator'] = 10.0
        return node

    def test_bootstrap_requires_fresh_initial_yaw_and_global_reference(self):
        node = self.adapter()
        self.assertTrue(MissionNode.telemetry(node, 10.0).auto_takeoff_ready)
        self.assertFalse(MissionNode.telemetry(node, 12.0).auto_takeoff_ready)
        for field in ('cs_mag_fault', 'cs_mag_field_disturbed', 'fs_bad_hdg'):
            node = self.adapter()
            setattr(node.latest['estimator'], field, True)
            self.assertFalse(MissionNode.telemetry(node, 10.0).auto_takeoff_ready)
        for field in ('xy_global', 'z_global'):
            node = self.adapter()
            setattr(node.latest['position'], field, False)
            self.assertFalse(MissionNode.telemetry(node, 10.0).auto_takeoff_ready)
        node = self.adapter()
        node.latest['estimator'].cs_yaw_align = False
        self.assertFalse(MissionNode.telemetry(node, 10.0).auto_takeoff_ready)

    def test_takeoff_altitude_is_amsl_and_has_no_absolute_yaw(self):
        node = preflight.PreflightTests().callback_adapter()
        node.latest['position'].xy_global = node.latest['position'].z_global = True
        node.latest['position'].ref_alt = 488.0
        node.mission.home = (3.0, 4.0, -0.2)
        node.publish = mock.Mock()
        node.get_logger = mock.Mock()
        MissionNode.command(node, 'AUTO_TAKEOFF')
        message = node.publish.call_args.args[1]
        self.assertEqual(message.command, VehicleCommand.VEHICLE_CMD_NAV_TAKEOFF)
        self.assertAlmostEqual(message.param7, 498.2)
        self.assertTrue(
            all((math.isnan(value) for value in (message.param4, message.param5, message.param6)))
        )
        node.latest['position'].z_global = False
        with self.assertRaises(RuntimeError):
            MissionNode.command(node, 'AUTO_TAKEOFF')

    def test_only_heading_resets_during_auto_alignment_are_expected(self):
        for state, xy_reset, expected in [
            ('TAKEOFF', False, False),
            ('WAIT_FOR_HEADING', False, False),
            ('TAKEOFF', True, True),
            ('PREFLIGHT_SETPOINT', False, True),
            ('WAYPOINT_1', False, True)
        ]:
            with self.subTest(state=state, xy_reset=xy_reset):
                node = preflight.PreflightTests().callback_adapter()
                node.mission.home = (0.0, 0.0, 0.0)
                node.mission.auto_takeoff = True
                node.mission.state = state
                position = node.latest['position']
                position.timestamp = 100
                MissionNode.receive(node, 'position', position)
                position.timestamp = 200
                position.heading_reset_counter += 1
                if xy_reset:
                    position.xy_reset_counter += 1
                MissionNode.receive(node, 'position', position)
                self.assertEqual(node.reset, expected)

    def test_offboard_captures_aligned_heading_and_holds_at_takeoff_altitude(self):
        node = preflight.PreflightTests().timer_adapter(True)
        node.mission.auto_takeoff = node.mission.owned = True
        node.mission.home = (3.0, 4.0, -0.2)
        node.mission.target = (3.0, 4.0, -10.2)
        node.mission.hold_since = 8.0
        node.latest['status'].arming_state = VehicleStatus.ARMING_STATE_ARMED
        node.latest['status'].nav_state = VehicleStatus.NAVIGATION_STATE_AUTO_TAKEOFF
        node.latest['land'].landed = False
        position = node.latest['position']
        position.xy_global = position.z_global = True
        position.heading_good_for_control = True
        position.heading = 0.25
        flags = EstimatorStatusFlags()
        flags.cs_yaw_align = True
        node.latest['estimator'] = flags
        node.received['estimator'] = 10.0
        with mock.patch('baseline_measurement.mission_node.time.monotonic', return_value=10.05):
            MissionNode.tick(node)
        self.assertEqual(node.mission.state, 'PREFLIGHT_SETPOINT')
        message = node.publish.call_args_list[0].args[1]
        self.assertEqual(message.yaw, 0.25)
        self.assertAlmostEqual(message.position[2], -10.2, places=5)
        node.command.assert_not_called()

    def test_clock_change_is_audited_and_rebased_only_after_route_and_touchdown(self):
        from baseline_measurement.mission_state import STAGES
        for state, expected_stamp, expected_time in [
            ('LAND', 50, 10.1),
            ('WAYPOINT_1', 200, 10.0)
        ]:
            node = preflight.PreflightTests().callback_adapter()
            node.mission.reached = list(STAGES)
            node.mission.state = state
            position = node.latest['position']
            position.timestamp = 200
            with mock.patch('baseline_measurement.mission_node.time.monotonic', return_value=10.0):
                MissionNode.receive(node, 'position', position)
            position.timestamp = 50
            with mock.patch('baseline_measurement.mission_node.time.monotonic', return_value=10.1):
                MissionNode.receive(node, 'position', position)
            self.assertTrue(node.reset)
            self.assertEqual(node.stamps['position'], expected_stamp)
            self.assertEqual(node.received['position'], expected_time)

    def test_hold_command_uses_px4_auto_loiter_submode(self):
        node = preflight.PreflightTests().callback_adapter()
        node.publish = mock.Mock()
        node.get_logger = mock.Mock()
        MissionNode.command(node, 'HOLD')
        message = node.publish.call_args.args[1]
        self.assertEqual(message.command, VehicleCommand.VEHICLE_CMD_DO_SET_MODE)
        self.assertEqual((message.param1, message.param2, message.param3), (1.0, 4.0, 3.0))
