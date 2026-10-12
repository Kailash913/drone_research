"""PX4 Auto bootstrap policy regression tests; no vehicle commands are sent."""

import unittest

from baseline_measurement.mission_state import Mission, STAGES, Telemetry


def ready():
    return Telemetry(connected=True, healthy=True, valid=True, landed=True,
                     auto_takeoff_ready=True, holding=True, position=(3., 4., -.2))


class AutoTakeoffTests(unittest.TestCase):
    def start_auto(self):
        mission, telemetry = Mission(0.), ready()
        requests = []
        for index in range(100):
            now = index * .05
            intents = mission.tick(now, telemetry)
            requests.extend(intents)
            for intent in intents:
                if intent == 'AUTO_TAKEOFF':
                    telemetry.taking_off, telemetry.holding = True, False
                elif intent == 'ARM':
                    telemetry.armed = True
            self.assertIsNone(mission.setpoint(now))
            if mission.state == 'TAKEOFF':
                return mission, telemetry, now, requests
        self.fail('Auto takeoff did not start')

    def reach_altitude(self, mission, telemetry, start):
        telemetry.position = mission.target
        telemetry.landed = False
        for index in range(1, 400):
            now = start + index * .05
            self.assertEqual(mission.tick(now, telemetry), [])
            self.assertIsNone(mission.setpoint(now))
            if mission.state == 'WAIT_FOR_HEADING':
                return now
        self.fail('Takeoff was not completed')

    def test_initial_alignment_can_take_off_without_final_heading(self):
        mission, telemetry, _, requests = self.start_auto()
        self.assertEqual(requests, ['AUTO_TAKEOFF', 'ARM'])
        self.assertFalse(telemetry.heading_ready)
        self.assertTrue(mission.auto_takeoff and mission.owned)

    def test_missing_initial_alignment_keeps_grounded_gate(self):
        mission, telemetry = Mission(0.), ready()
        telemetry.auto_takeoff_ready = False
        for index in range(700):
            self.assertEqual(mission.tick(index * .05, telemetry), [])
            self.assertIsNone(mission.setpoint(index * .05))
        self.assertTrue(mission.done)
        self.assertEqual(mission.failure_state, 'WAIT_FOR_HEADING')

    def test_final_alignment_requires_continuous_readiness_before_offboard(self):
        mission, telemetry, start, _ = self.start_auto()
        now = self.reach_altitude(mission, telemetry, start)
        telemetry.heading_ready = True
        for index in range(1, 20):
            self.assertEqual(mission.tick(now + index * .05, telemetry), [])
            self.assertIsNone(mission.setpoint(now + index * .05))
        telemetry.heading_ready = False
        mission.tick(now + 1., telemetry)
        telemetry.heading_ready = True
        for index in range(1, 43):
            mission.tick(now + 1. + index * .05, telemetry)
        self.assertEqual(mission.state, 'PREFLIGHT_SETPOINT')
        self.assertEqual(mission.setpoint(now + 3.2), mission.target)
        self.assertNotEqual(mission.target, mission.home)

    def test_auto_alignment_timeout_lands_and_latches_failure(self):
        mission, telemetry, start, _ = self.start_auto()
        now = self.reach_altitude(mission, telemetry, start)
        requests = []
        for index in range(1, 605):
            requests.extend(mission.tick(now + index * .05, telemetry))
        self.assertEqual(requests, ['LAND'])
        self.assertEqual(mission.failure_state, 'WAIT_FOR_HEADING')
        telemetry.heading_ready = True
        self.assertEqual(mission.tick(now + 30.3, telemetry), [])
        self.assertIsNone(mission.setpoint(now + 30.3))
        self.assertFalse(mission.passed)

    def test_initial_yaw_fault_or_mode_loss_aborts_auto_flight(self):
        for field in ('auto_takeoff_ready', 'taking_off', 'armed'):
            with self.subTest(field=field):
                mission, telemetry, now, _ = self.start_auto()
                telemetry.landed = False
                setattr(telemetry, field, False)
                requests = mission.tick(now + .05, telemetry)
                requests += mission.tick(now + .1, telemetry)
                self.assertEqual(requests, ['LAND'])
                self.assertIsNone(mission.setpoint(now + .05))
                self.assertEqual(mission.state, 'FAILSAFE')

    def test_never_retries_takeoff_command_or_arms_without_mode_confirmation(self):
        mission, telemetry = Mission(0.), ready()
        requests = []
        for index in range(400):
            requests.extend(mission.tick(index * .05, telemetry))
        self.assertEqual(requests, ['AUTO_TAKEOFF'])
        self.assertEqual(mission.failure_state, 'AUTO_TAKEOFF_REQUEST')
        self.assertFalse(mission.owned)

    def test_complete_auto_bootstrap_and_offboard_route(self):
        mission, telemetry, start, requests = self.start_auto()
        now = self.reach_altitude(mission, telemetry, start)
        telemetry.heading_ready = True
        for index in range(1, 5000):
            current = now + index * .05
            setpoint = mission.setpoint(current)
            if setpoint is not None:
                telemetry.position = setpoint
            if mission.state == 'LAND' and current - mission.entered > 3.:
                telemetry.landed = True
            intents = mission.tick(current, telemetry)
            requests.extend(intents)
            for intent in intents:
                if intent == 'OFFBOARD':
                    telemetry.offboard, telemetry.taking_off = True, False
                elif intent == 'LAND':
                    telemetry.landing, telemetry.offboard = True, False
                elif intent == 'DISARM':
                    self.assertTrue(telemetry.landed)
                    telemetry.armed = False
                elif intent == 'HOLD':
                    telemetry.holding, telemetry.offboard = True, False
            if mission.done:
                break
        self.assertTrue(mission.passed, mission.failure_reason)
        self.assertEqual(mission.reached, list(STAGES))
        self.assertEqual(requests, ['AUTO_TAKEOFF', 'ARM', 'OFFBOARD', 'LAND', 'DISARM', 'HOLD'])

    def test_final_ground_confirmation_survives_timestamp_domain_change(self):
        mission, telemetry = Mission(0.), ready()
        mission.owned = True
        mission.reached = list(STAGES)
        mission.transition('LAND', 0.)
        telemetry.reset = True
        telemetry.valid = telemetry.connected = telemetry.healthy = False
        telemetry.landing_connected = telemetry.landing = True
        telemetry.armed = False
        for index in range(60):
            mission.tick(index * .05, telemetry)
        self.assertTrue(mission.passed)
        self.assertEqual(mission.state, 'COMPLETE')

    def test_resets_before_touchdown_still_fail(self):
        mission, telemetry = Mission(0.), ready()
        mission.owned = True
        mission.reached = list(STAGES)
        mission.transition('LAND', 0.)
        telemetry.reset = telemetry.armed = telemetry.landing = True
        telemetry.landed = False
        self.assertEqual(mission.tick(.05, telemetry), ['LAND'])
        self.assertEqual(mission.state, 'FAILSAFE')

    def test_ground_confirmation_needs_fresh_status_and_landing(self):
        mission, telemetry = Mission(0.), ready()
        mission.owned = True
        mission.reached = list(STAGES)
        mission.transition('LAND', 0.)
        telemetry.connected = telemetry.landing_connected = False
        self.assertEqual(mission.tick(.05, telemetry), ['LAND'])
        self.assertFalse(mission.passed)
        self.assertEqual(mission.state, 'FAILSAFE')

    def test_repeated_flight_uses_auto_even_if_ground_heading_remains_ready(self):
        mission, telemetry = Mission(0.), ready()
        telemetry.heading_ready = True
        for index in range(50):
            mission.tick(index * .05, telemetry)
        self.assertTrue(mission.auto_takeoff)
        self.assertIsNone(mission.setpoint(2.5))

    def test_disarmed_offboard_is_released_before_preflight(self):
        mission, telemetry = Mission(0.), ready()
        telemetry.offboard = True
        telemetry.healthy = telemetry.valid = False
        self.assertEqual(mission.tick(0., telemetry), [])
        self.assertEqual(mission.tick(.05, telemetry), ['HOLD'])
        self.assertFalse(mission.owned)
        self.assertEqual(mission.tick(.1, telemetry), [])
        telemetry.offboard = False
        telemetry.healthy = telemetry.valid = True
        for index in range(3, 50):
            mission.tick(index * .05, telemetry)
        self.assertTrue(mission.auto_takeoff)

    def test_does_not_release_another_armed_controller(self):
        mission, telemetry = Mission(0.), ready()
        telemetry.offboard = telemetry.armed = True
        mission.tick(0., telemetry)
        self.assertEqual(mission.tick(.05, telemetry), [])
        self.assertFalse(mission.owned)
        self.assertEqual(mission.state, 'FAILSAFE')


if __name__ == '__main__':
    unittest.main()
