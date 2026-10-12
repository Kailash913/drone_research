"""Confirm stale heading values cannot admit control and readiness loss cannot pass."""
from baseline_measurement.mission_node import MissionNode
from baseline_measurement.mission_state import Mission
import test_clock_guard
import test_preflight


def test_stale_true_heading_cannot_admit_offboard():
    """Keep independent monotonic freshness gates effective even for a true old flag."""
    node = test_preflight.PreflightTests().adapter()
    node.latest['position'].heading_good_for_control = True
    node.received['position'] = 7.0
    telemetry = MissionNode.telemetry(node, 10.0)
    assert telemetry.heading_ready
    assert not telemetry.connected and not telemetry.valid
    mission = Mission(10.0)
    mission.transition('WAIT_FOR_HEADING', 10.0)
    assert mission.tick(10.05, telemetry) == []
    assert mission.done and not mission.passed
    assert mission.setpoint(10.05) is None
    assert mission.failure_state == 'WAIT_FOR_HEADING'


def test_ready_heading_loss_airborne_fails_without_estimator_reset_claim():
    """Require safe waiting/abort behavior independently of source-reset diagnostics."""
    node = test_clock_guard.ClockGuardTests().adapter()
    node.latest['position'].heading_good_for_control = False
    telemetry = MissionNode.telemetry(node, 10.0)
    requests = node.mission.tick(10.05, telemetry)
    assert requests == ['LAND']
    assert node.mission.state == 'FAILSAFE'
    assert not node.mission.passed and not node.reset
    node.log.row.assert_not_called()
    assert ('FAILSAFE', 10.05) in node.mission.events
