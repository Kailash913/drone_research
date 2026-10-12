# Grounded heading readiness investigation

The previous validity fix is preserved. No production controller change was
needed in this investigation; the heading guard remains conservative.

## Confirmed cause

Checkout: `v1.18.0-beta1-213-g43cccdea0e`.
`EKF2.cpp:1758` assigns `heading_good_for_control` from
`Ekf::isYawFinalAlignComplete()` (`EKF/ekf.h:268`). With active magnetometer
heading/3D fusion, that predicate requires yaw alignment, in-flight magnetic
alignment, and more than one second since alignment began.

`EKF/aid_sources/magnetometer/mag_control.cpp:375` implements
`checkHaglYawResetReq()`. It requires `in_air`, `yaw_align`, no completed
in-flight mag alignment, and height above 1.5 m. The successful reset sets
`mag_aligned_in_flight` and the start timestamp at lines 224–225. The flag is
cleared on entry to flight (line 54) and when mag fusion stops (line 363).
Build `px4_boardconfig.h:61,66` enables magnetometer and terrain support.
`ekf.h:804` uses last-on-ground vertical position when terrain is invalid;
therefore `dist_bottom_valid=false` alone is not evidence that this check
cannot eventually complete.

Grounded, disarmed observation cannot satisfy the in-air condition. This is
expected estimator behavior, not evidence of a broken or absent magnetometer.

## Recorded evidence

Read-only analysis using the installed `pyulog` package examined:
`/home/kailash/PX4-Autopilot/build/px4_sitl_default/rootfs/log/2026-10-10/06_52_14.ulg`.
The recorded software hash matches this checkout. Snapshot log duration was
1680.984 seconds; no ULog dropouts were recorded.

Recorded initial parameters: SYS_AUTOSTART=4001, SIM_GZ_EN=1,
SIM_GZ_EN_MAG=1, EKF2_MAG_TYPE=0 (AUTO).
Across the recorded samples: in_air=0, landed=1, arming_state=1,
yaw_align=1, mag_hdg=1, mag_aligned_in_flight=0,
heading_good_for_control=0, mag_fault=0, mag_field_disturbed=0, bad_hdg=0,
pre_flight_checks_pass=1, failsafe=0. All 23331 recorded magnetic aid-source
samples had fused=1 and innovation_rejected=0. Maximum per-axis innovation
test ratios were approximately 1.34e-5, 1.43e-5, and 7.46e-6.
Sensor magnetic samples were finite, nonzero, and changing.

Gazebo log:
`/home/kailash/.gz/sim/log/2026-10-10T06:51:58.929546494/server_console.log`
records the Magnetometer system loaded and the x500_0 magnetic sensor topic
advertised. It reports use_units_gauss=1 and use_earth_frame_ned=1. The x500
base SDF has an always-on 100 Hz magnetometer, and default world has a nonzero
magnetic field. The bridge subscribes to that sensor path and applies its
Harmonic units/axis convention. Material and deprecated motor-field warnings
were present; no magnetometer error appeared in the inspected server log.
No sensor/configuration fault explaining the false readiness flag was found.
This does not independently prove absolute yaw accuracy: simultaneous
estimated attitude versus simulator ground-truth attitude was not available
in the filtered ULog. That comparison remains useful for detecting subtle
frame/calibration discrepancies, independently of the expected grounded flag.

A fresh five-second, subscription-only ROS probe confirmed these same estimator
flags. Position/velocity validity flags were true, dead reckoning false,
heading approximately 1.68118 rad, landed true, arming_state=1,
preflight checks passed, failsafe false. All three flight-input topics had
zero ROS publishers. Full captured values are in
`baseline_results/heading_passive_diagnostic.json`.

## Verified control path and policy audit

PX4 does not universally require final in-flight heading alignment before
takeoff. Estimator arming checks use `cs_yaw_align` for the heading reference
(`HealthAndArmingChecks/checks/estimatorCheck.cpp:640`), not this final flag.
Offboard checks require recent control signal and valid local position/velocity
or attitude for the requested control type (`offboardCheck.cpp:49–90`).

Offboard position mode selects trajectory control (`ModeUtil/control_mode.cpp:111`).
FlightModeManager selects Auto only for auto-enabled modes; offboard trajectory
setpoints reach MulticopterPositionControl directly, which reads heading,
consumes trajectory setpoints and handles offboard takeoff. Its PositionControl
uses finite yaw directly. NaN yaw falls back to current yaw (`PositionControl.cpp:120`);
NaN alone does not disable yaw control.

In contrast, FlightTaskAuto uses heading_good_for_control to suppress its
absolute yaw target and send zero yaw speed when readiness is false
(`tasks/Auto/FlightTaskAuto.cpp:513`). That protection is not in the direct
offboard path. Our adapter sends finite captured yaw on every preflight and
flight trajectory. Therefore this implementation requires heading readiness
before its first trajectory, even though takeoff itself is not universally
conditioned on final magnetic alignment in PX4. A different initial control
strategy would require a separately reviewed control-policy change; none was
implemented and no guard was bypassed.

WAIT_FOR_HEADING is bounded at 30 seconds (strictly greater than 30 triggers
failure). It returns no setpoint/intent while waiting. Connectivity, validity,
health, competition, resets, failsafe and scheduling gap checks remain active;
unexpected arming or loss of landing confirmation enters FAILSAFE. With no
mission ownership, abort produces no LAND or DISARM request and finishes on
the same or following tick. Heading loss in every yaw-controlled stage stops
the trajectory. In owned flight the existing policy returns one best-effort
LAND intent; this was tested offline only. Passive mode never ticks policy,
creates flight-control publishers, or publishes commands.

## Changes and validation

Only test_preflight.py was changed beyond the preceding fix: four new tests
cover timeout boundary/latching, unsafe-state races with heading recovery,
actual adapter timer publication gating/heading loss, and passive timer
behavior. Heading-loss coverage now includes all waypoint/return stages.
No PX4 source, parameters or simulator configuration was changed.

Commands executed from ~/ros2_ws:

```bash
source /opt/ros/jazzy/setup.bash
colcon build --packages-select baseline_measurement
source install/setup.bash
python3 -m pytest src/baseline_measurement/test/test_phase1.py src/baseline_measurement/test/test_baseline_new.py src/baseline_measurement/test/test_preflight.py -q
colcon test --packages-select baseline_measurement --event-handlers console_direct+ > /tmp/heading_colcon_test.log 2>&1
colcon test-result
python3 -m compileall -q src/baseline_measurement/baseline_measurement
python3 -c 'import baseline_measurement.mission_node; print("mission_node import OK")'
timeout 12s ros2 topic echo /fmu/out/estimator_status_flags px4_msgs/msg/EstimatorStatusFlags --once --qos-reliability best_effort
```

Final build succeeded. Functional tests: 38 passed. Full package: 38 passed,
2 failed, 1 skipped (existing flake8/pep257 failures; 82 flake8 findings,
unchanged from previous verification). Syntax/import checks succeeded.
An initial new test incorrectly required same-tick termination after a
state-specific failure; corrected to verify immediate FAILSAFE followed by
bounded next-tick termination and no commands. Final results above are after
that correction.

No vehicle command, arming, takeoff or flight demonstration was attempted.
The controller remains blocked before its finite-yaw trajectory in the
observed grounded magnetic-fusion state.

Next diagnostic command, in the existing PX4 SITL shell:

```text
listener vehicle_attitude_groundtruth -n 1
```

This is read-only. Capture its quaternion to compare ground-truth NED yaw
with the simultaneously observed local-position heading; this investigates
absolute heading accuracy rather than trying to force the readiness flag.
