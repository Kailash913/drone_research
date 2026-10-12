> Historical report. See [PHASE1_VALIDATION.md](PHASE1_VALIDATION.md) for the 11 October 2026 audit, current active-mission counts, dataset validation and remaining blockers.

# Phase 1 test results — PARTIALLY COMPLETE

Observed on 10 October 2026. Times in the table are Asia/Kolkata (UTC+05:30);
CSV and JSON artifacts retain UTC timestamps.

## Actual outcomes

- baseline_measurement colcon build: PASS.
- Functional suite: 57 passed.
- Full package: 57 passed, 2 failed, 1 skipped. The two failures are existing
  flake8/pep257 checks; flake8 has the same 82 findings as the prior baseline.
  No new lint findings remain. Copyright check remains skipped.
- Python syntax/import checks: PASS.
- Standalone read-only C++ probe: CMake configure/build PASS; received 10 status
  messages, checks_pass=1, failsafe=0, arming_state=1, gcs_connection_lost=0.
- Integrated validate_baseline.sh: PASS, including its independent acceptance
  check of supplementary preflight_013.csv (not just process exit).
- Five selected Category A passive demonstrations: PASS.
- Category B mission demonstrations: zero attempted/verified by this work.

## Environment observed

Ubuntu 24.04.4 LTS under WSL, Python 3.12.3, ROS 2 Jazzy;
PX4 checkout v1.18.0-beta1-213-g43cccdea0e, matching recorded software hash;
Gazebo Server 8.15.0 in the existing startup log. Branch master was already
modified when work began. Existing changes were preserved.

One PX4 PID 78833, one MicroXRCEAgent PID 1615 using udp4 port 8888, and
Gazebo server/GUI Ruby launchers PIDs 79035/79036 were observed. No duplicate
simulator or agent was started. PX4 had a loopback UDP socket connected to
agent port 8888. PX4 MAVLink port 18570 matches the existing rc startup file.
A recorded MAVLink instance had heartbeat_type_gcs=1, and live status reported
gcs_connection_lost=false. This does not independently identify QGC or verify
its user interface or control operations.

## Independently checked captures

Output directory: `~/uav_research/baseline`. Each run ID below is its uniquely
named CSV basename; each also has a separate BASE JSON/raw CSV run identifier.
Historical preflight_005.csv was inspected but not counted.

| Experiment / CSV basename | Start IST | Duration s | First valid resource sample s | Publisher status | Decision |
| --- | --- | ---: | ---: | --- | --- |
| BASE-006 / preflight_006 | 13:29:22 | 15.003 | 1.001 | clear / 0 TX | PASS |
| BASE-007 / preflight_007 | 13:29:37 | 15.013 | 2.010 | clear / 0 TX | PASS |
| BASE-008 / preflight_008 | 13:29:52 | 15.007 | 3.054 | clear / 0 TX | PASS |
| BASE-009 / preflight_009 | 13:30:07 | 15.016 | 2.063 | clear / 0 TX | FAIL |
| BASE-010 / preflight_010 | 13:30:22 | 15.007 | 2.006 | clear / 0 TX | PASS |
| BASE-011 / preflight_011 | 13:32:29 | 15.030 | 2.072 | clear / 0 TX | FAIL |
| BASE-012 / preflight_012 | 13:33:51 | 15.013 | 1.008 | clear / 0 TX | PASS |

The five selected passing demonstrations are 006, 007, 008, 010, and 012.
Failed attempts 009 and 011 are retained with their raw/JSON files. Supplementary
013 validates the final integrated procedure and is not needed to reach five.
The five batch invocations were sequential, followed by separate bounded
replacement invocations. They are separate captures, not independent draws
from reset simulator states; no statistical independence or flight success
is inferred.

Acceptance checks exact CSV schema, one metadata/final record, passive outcome,
15–17 s duration, advancing source timestamps, consistent callback counts/rates,
required topic summaries, no command/TX records, and safe sampled state.
Startup allowance is 5 s. Every resource snapshot after that must be connected,
healthy, valid, landed, disarmed and conflict-free; at least 5 s of stable
sampled coverage and <=1.5 s gaps/trailing time are required. This is sampled
telemetry stability, not proof that every internal PX4 update was healthy.
Heading readiness is reported independently and is not required for Category A.
All selected captures ended with heading_ready=true.

## Telemetry directly observed

A separate six-second Python subscription-only probe received 292 position,
292 attitude, 11 status, 6 land and 6 battery messages. Topic types matched the
installed px4_msgs interfaces. All three flight-input topics had zero ROS
publishers and one PX4 subscriber. Landed=true, arming_state=1,
pre_flight_checks_pass=true, failsafe=false, valid local position/velocity flags,
no dead reckoning, and heading_good_for_control=true were observed.

Selected capture callback rates (whole logged observation, including startup):

| Topic | Rate range Hz | Evidence |
| --- | ---: | --- |
| `/fmu/out/vehicle_status_v4` | 1.67–2.00 | Messages received and advancing timestamps verified |
| `/fmu/out/vehicle_local_position_v1` | 43.51–49.69 | Messages received and advancing timestamps verified |
| `/fmu/out/vehicle_attitude` | 43.45–49.69 | Messages received and advancing timestamps verified |
| `/fmu/out/vehicle_land_detected` | 0.87–1.00 | Messages received and advancing timestamps verified |
| `/fmu/out/battery_status_v1` | 0.87–1.00 | Messages received and advancing timestamps verified |

VehicleCommandAck topic/type/publisher was discovered, but no live ACK was
received because no command was sent. Rejection/target matching, lack of state
confirmation from an accepted ACK, and OFFBOARD/ARM state timeouts are covered
by automated tests only. No ACK latency or live command delivery is claimed.
Battery was connected at approximately 16.2 V, but current_a=-1 is an unavailable
sentinel. Power/energy remain unavailable rather than zero.

## Observed failure and active-control boundary

preflight_009 had an attitude source timestamp regression at 4.762 s from
1791619212526932 to 4056700000 us. preflight_011 had another at 7.879 s from
1791619356759107 to 4200496000 us. Connected/healthy remained true, while the
existing clock/reset guard correctly latched validity false.

PX4's generated vehicle_attitude serializer adds session time_offset to outgoing
timestamps; the XRCE client updates this offset through time synchronization.
The two values resemble a host-epoch/PX4-uptime domain switch, but the exact
trigger is not established. No clock normalization, ignored regression, safety
parameter change, or guard bypass was implemented. This intermittent condition
must be investigated before authorizing active control.

A log snapshot recorded COM_OF_LOSS_T=1, COM_OBL_RC_ACT=0 and NAV_DLL_ACT=2.
They were read, not changed; actual offboard-loss response has not been exercised.
Current heading readiness is true; the previous heading blocker alone is no
longer the live blocker. No arming, offboard mode request, trajectory publication,
takeoff, waypoint movement, landing command, or disarm command was executed.

## Commands executed

```bash
source /opt/ros/jazzy/setup.bash
colcon build --packages-select baseline_measurement
source install/setup.bash
bash src/baseline_measurement/test_phase1.sh
colcon test --packages-select baseline_measurement --event-handlers console_direct+
colcon test-result
python3 -m compileall -q src/baseline_measurement/baseline_measurement
python3 -c 'import baseline_measurement.mission_node, baseline_measurement.acceptance; print("imports OK")'
timeout 110s ros2 run baseline_measurement mission_node --config src/baseline_measurement/config/baseline.yaml --passive-only --observe-seconds 15 --run-count 5
# Executed twice as bounded replacements, each generating a new CSV:
timeout 25s ros2 run baseline_measurement mission_node --config src/baseline_measurement/config/baseline.yaml --passive-only --observe-seconds 15
cmake -S src/baseline_measurement/tools -B /tmp/phase1_cpp_build
cmake --build /tmp/phase1_cpp_build
timeout 12s /tmp/phase1_cpp_build/telemetry_probe
bash src/baseline_measurement/validate_baseline.sh
ros2 run baseline_measurement phase1_acceptance ~/uav_research/baseline/preflight_006.csv ~/uav_research/baseline/preflight_007.csv ~/uav_research/baseline/preflight_008.csv ~/uav_research/baseline/preflight_010.csv ~/uav_research/baseline/preflight_012.csv --output baseline_results/phase1_five_passive_final.json
```

## Durable evidence

`baseline_results/phase1_results.json` contains each attempt, actual UTC/IST
start times, durations, topic counts/rates, source clock regressions, run IDs,
CSV SHA-256 values, associated raw/JSON paths, live state and publisher counts.
Other evidence: phase1_five_passive_final.json, phase1_build.log,
phase1_functional_tests.log, phase1_colcon_tests.log, phase1_colcon_result.log,
phase1_pytest.xml, phase1_live_chain.json, phase1_cpp_probe.log,
phase1_cpp_build.log, phase1_cpp_configure.log, phase1_integrated_validation.log,
phase1_passive_batch.log and the two replacement logs. The five CSVs remain at
the configured baseline output directory; no existing CSV was overwritten.

Measured rates are application ROS CDR/callback rates, not physical bandwidth.
Packet loss, end-to-end latency, hardware power and cryptography are unavailable
or out of scope. No Phase 2 implementation or attack experiment was started.
