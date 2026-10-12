> Historical report. See [PHASE1_VALIDATION.md](PHASE1_VALIDATION.md) for the 11 October 2026 audit, current active-mission counts, dataset validation and remaining blockers.

# Phase 1 acceptance — PARTIALLY COMPLETE

Current evidence: [PHASE1_TEST_RESULTS.md](PHASE1_TEST_RESULTS.md) and
`baseline_results/phase1_results.json` in the workspace.

## Definition and boundary

The existing PHASE1_BASELINE.md defines a mission PASS as observed takeoff,
three waypoints, return, landing, and disarming, without a latched failure.
No separate supervisor rubric was found in the repository. Therefore passive
captures are Category A only and cannot substitute for Category B missions.
Five new Category A captures pass; no Category B mission was attempted here.
The historical preflight_005.csv is excluded from the new demonstration count.

The actual architecture is Gazebo sensors -> PX4 -> Micro XRCE-DDS -> ROS 2,
with PX4 <-> MAVLink <-> QGC as a parallel control/telemetry path. MAVLink and
QGC are not intermediate stages in the PX4-to-ROS DDS transport.

| Requirement | Current evidence | Status |
| --- | --- | --- |
| Package builds | colcon baseline_measurement build | PASS |
| Relevant automated tests | 57 functional tests | PASS |
| Existing unrelated lint checks | Two unchanged failing checks; 82 flake8 findings | Existing failures separated |
| Python/C++ development | Python observer and compiled C++ status subscriber exercised live | PASS for telemetry development |
| Gazebo/PX4/XRCE/ROS chain | Existing processes, agent socket, actual typed callbacks | PASS for telemetry |
| Status, position, velocity, attitude, land, battery | Live values, advancing messages, CSV summaries | PASS for implemented interpretation |
| VehicleCommandAck | Interface discovered; adapter behavior tested with fixtures | Live response NOT DEMONSTRATED |
| Passive mode command-free | Tests, zero graph publishers, zero TX/command records | PASS |
| Publisher conflict and stale/unsafe/reset handling | Adapter/policy negative tests and rejected captures | PASS for detection |
| CSV schema, outcomes, uniqueness and missing values | Automated validator; exclusive filenames; zero-value fix | PASS |
| Five Category A captures | 006, 007, 008, 010, 012; failed attempts retained | PASS |
| QGC connection and interactive operations | Recorded GCS heartbeat, live gcs_connection_lost=false | QGC identity/UI NOT INDEPENDENTLY VERIFIED |
| Offboard/arming/takeoff/waypoints/landing/disarm | Code and offline tests only | NOT DEMONSTRATED |
| Five Category B missions | No missions run here | NOT COMPLETE |
| Stable source clock during control | Two observed timestamp-domain regressions | BLOCKER |

## Convenient checks

All functional acceptance tests, nonzero on failure:

```bash
bash ~/ros2_ws/src/baseline_measurement/test_phase1.sh
```

Build, functional tests, interface/graph inspection, bounded passive capture,
and actual CSV acceptance (returns nonzero on an invalid capture):

```bash
bash ~/ros2_ws/src/baseline_measurement/validate_baseline.sh
```

Validate existing captures independently:

```bash
source /opt/ros/jazzy/setup.bash
source ~/ros2_ws/install/setup.bash
ros2 run baseline_measurement phase1_acceptance ~/uav_research/baseline/preflight_006.csv ~/uav_research/baseline/preflight_007.csv ~/uav_research/baseline/preflight_008.csv ~/uav_research/baseline/preflight_010.csv ~/uav_research/baseline/preflight_012.csv
```

The validator labels its PASS as A_PASSIVE, leaves mission_status as
not_demonstrated, and refuses to overwrite a requested JSON evidence file.
It allows a five-second startup window and requires subsequent safe sampled
telemetry, correct counts/rates, the passive terminal result, and no received
source-clock regression. Required callback paths include battery; current/power
availability is checked separately. Heading is independent of passive data
validity. Clock freshness and all existing mission safety guards remain intact.

## Remaining procedure

1. Investigate the two mixed-domain attitude timestamps before active control.
   In the existing PX4 shell, use these read-only diagnostics:

   ```text
   uxrce_dds_client status
   listener timesync_status -n 10 -r 2
   param show UXRCE_DDS_SYNCT
   param show UXRCE_DDS_SYNCC
   mavlink status
   ```

   On ROS, record the exported synchronization status without publishing:

   ```bash
   source /opt/ros/jazzy/setup.bash
   source ~/ros2_ws/install/setup.bash
   timeout 20s ros2 topic echo /fmu/out/timesync_status px4_msgs/msg/TimesyncStatus --qos-reliability best_effort
   ```

   A timeout is expected for this bounded continuous echo. Correlate source
   timestamp regressions with DDS source_protocol=2 and observed/estimated
   offset changes, plus PX4/agent connection logs. The available CSVs establish
   the discontinuity but not its precise origin. Do not ignore it, reset the
   latch, or change safety parameters to obtain a PASS.

2. In QGC, identify the intended SITL vehicle (live ROS reported system 1,
   component 1), confirm its connected/disarmed/landed state against PX4/ROS,
   and record the QGC vehicle identity, mode, and link. A GCS heartbeat alone
   does not prove QGC interaction.

3. After the clock issue is resolved, review live offboard-loss/failsafe settings
   and the existing single-controller mission procedure. Confirm the simulated
   world is appropriate for the 10 m climb and 20 m waypoint offsets, no hardware
   vehicle is connected, no competing ROS control publisher exists, all preflight
   guards including heading readiness pass, and the operator is ready to observe
   QGC/Gazebo and handle a SITL failure. This manual safety boundary was not
   crossed in this work.

4. Only after those prerequisites and operator confirmation, use the existing
   ONE-mission procedure from PHASE1_BASELINE.md. Verify actual mode/arming,
   takeoff, each waypoint, return, landing and disarming in independent simulator/
   QGC/PX4 observations and the recorded mission CSV. ACK receipt or exit code
   alone is insufficient. Do not automatically batch five active missions.
   If the rubric requires Category B, obtain five separately verified missions,
   retaining every failure and incomplete attempt.

Declare Phase 1 COMPLETE only after all required telemetry/control/QGC criteria,
the rubric's five demonstrations, stable safety prerequisites and evidence are
verified. If the supervisor explicitly accepts Category A instead, document that
rubric decision; it still does not retroactively establish flight operations.

No ML-KEM, ML-DSA, HKDF, AES-GCM, other cryptography, or attack simulation is part
of this implementation or validation.
