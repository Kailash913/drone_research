# Phase 1 current validation report — 12 October 2026 (Asia/Calcutta)

Phase 1 remains BLOCKED and Phase 2 is not ready. The user selected **Keep current
flight behavior; finish reports only**. No further missions, DDS setting changes,
client restart or candidate control-header patch were performed after that decision.
The vehicle was last observed landed/disarmed by ROS preflight; QGC showed Ready / Hold.

## Evidence-supported diagnosis

One newly authorized active attempt, BASE-001 in `phase1_study_36527160a48f`, failed
in TAKEOFF and entered FAILSAFE, then MISSION_FAIL. At 18:07:01.748566 UTC on
11 October, the DDS protocol-2 estimated offset changed from
-1791735387918623 us to zero. At 18:07:01.749219 UTC, ROS local-position timestamp
changed from 1791742020006623 to 6632104000 us; attitude changed similarly. The next
DDS accepted sample restored a large offset. This is a demonstrated proximate
DDS timestamp-domain discontinuity for this run, rather than proof of an estimator reset.

The contemporaneous native PX4 log `18_06_55.ulg` matches revision
43cccdea0e57cf92a58562d2d7a1cba0854395f7. Native local-position and attitude timestamp
streams contain zero regressions. Captured position/heading/quaternion counters
were unchanged around the event; yaw alignment was set and captured magnetic
fault/disturbance and bad-heading flags did not indicate a reset. No estimator reset
counter-change event occurred in the mission capture. Heading readiness was false
in the AUTO_TAKEOFF bootstrap phase; this does not grant Offboard readiness.

Local native message definitions use boot-relative microseconds. Generated XRCE
serialization adds session.time_offset to timestamp and timestamp_sample; px4_msgs
and the ROS callback retain those adjusted values. MissionNode checks msg.timestamp
ordering. The actual Timesync filter resets its offset to zero after the eleventh
qualifying large-deviation sample; on_time transfers that zero into session.time_offset.
The actual-source C++ fixture reproduces zero-offset reset and next-sample recovery.
This fixture proves the software mechanism and is not an experimental baseline run.

The underlying clock deviation cause remains unproven. A receiver wall-clock step
of approximately +1.984 s relative to monotonic time was observed AFTER the failure;
it must not be presented as the cause of the earlier failure. Scheduling, simulator
clock rate and WSL/host clock behavior need independent evidence. Historical runs
015/021/043/045 contain confirmed reversals, but lack synchronized native/offset
records; attribution of every historical failure remains unproven.

Fresh passive observations also recorded a grounded source-clock reset in one
window. Subsequent preflight windows remained landed/disarmed, connected and healthy,
but heading_ready=false. They did not authorize another flight. The read-only
MAVLink API probe did not obtain a verified PX4 heartbeat; earlier forwarded GCS
heartbeat data is not PX4 identity evidence. Native ULog parameter evidence shows
UXRCE_DDS_SYNCT=1 for the failed run; fresh API readback is unavailable.

## Dataset and statistics

Historical cohort: 45 unique active attempts, 12 PASS and 33 FAIL. Thirty partial
BASE-001 through BASE-030 records are assigned; strict original provenance is 0/30.
New cohort: 1 active attempt, 0 PASS and 1 FAIL, with strict metadata provenance.
It is a valid diagnostic measurement record, not a successful mission. New study
completeness is 1/30 and 29 records remain missing. The empty preflight-error study
contains no active attempt and contributes nothing to these counts.

The cross-study inventory contains 46 unique active attempts, 12 PASS and 34 FAIL.
It does not pool materially different configuration metrics. Zero records contain
all required measured latency/loss/wire-traffic/physical-energy metrics. Study-scoped
IDs plus unique run IDs distinguish BASE-001 in different studies. Raw inputs and
SHA-256 links are retained in each manifest and combined_inventory.json.

The largest historical configuration group has 12/36 successes (33.33%). Its valid
RX CDR payload observations (n=36) have mean 0.113007 Mbit/s, median 0.114064,
SD 0.00389681, min 0.0914687 and max 0.114401. Node CPU mean is 11.1922% of one
logical core and RSS mean is 88.6317 MiB. Historical successful mission duration
(n=12) has mean 109.186 s, median 108.926 s, SD 0.869205 s, min 108.618 s and
max 111.815 s; 24 failures in that group do not contribute zero completion times.
Confidence intervals are withheld because independence and full configuration
equivalence are unverified. The new single failure has no meaningful SD or CI.
Full metric-specific n, missing n, mean/median/SD/min/max are in each generated summary.

| Metric | Status | Definition/method and limitation | Evidence to close gap |
|---|---|---|---|
| End-to-end latency | NOT MEASURED | Unique request initiation to specified remote response endpoint, us | Independently validated common clock and unique correlation |
| Telemetry latency | NOT MEASURED | Native source event to receive event, us with uncertainty | Validated clock scale/offset/domain and validity interval; DDS offset alone is insufficient |
| Command latency | NOT MEASURED | Unique request to specified ACK or action endpoint, us | PX4-side correlation; command number alone is ambiguous |
| Packet loss | NOT MEASURED | Missing unique transmissions / complete transmitted denominator | Complete sender/receiver sequence windows; application and wire loss distinguished |
| Throughput | MEASURED LIMITED | Received CDR bytes*8 / monotonic run duration | Excludes link/DDS/XRCE overhead; TX publish-call rate does not establish delivery |
| Wire bandwidth/traffic | NOT MEASURED | Captured original frame bytes*8 / capture window | Real PCAP, interface/filter/direction/drop statistics; offered traffic is not capacity |
| CPU | MEASURED LIMITED | psutil node percent of one logical core, guest-system percent, nominal 1 s | PID/scope; excludes Windows QGC and physical vehicle CPU |
| Memory | MEASURED LIMITED | Node RSS MiB, nominal 1 s | Process scope, not physical UAV or whole host memory |
| Completion time | MEASURED for historical PASS | Monotonic run start to final COMPLETE, s | Full route, return, landing, disarm/release; FAIL duration separate |
| Physical power/energy | NOT MEASURED | Calibrated physical UAV W and integrated J | Hardware instrument/calibration and bounded-gap synchronized power samples |

New diagnostic record: RX 0.090341 Mbit/s, TX publication 0.0000745771 Mbit/s,
node CPU 19.5167%, guest CPU 61.7167%, RSS 87.8641 MiB and failed attempt duration
19.3089 s. Mission completion time is unavailable. No unavailable metric is replaced
by zero. The simultaneous probe's observed position/attitude rate was approximately
39.46 Hz over its actual window; Hz is not throughput and is not an acceptance limit.

The measurement importers validate calibrated clocks, unique correlations, sequence
windows, classic PCAP frame lengths and physical power evidence. Invalid/missing
inputs are rejected. Supplied evidence still requires independent review. The
localhost echo benchmark demonstrates collection mechanics only; it cannot count
as UAV latency or packet-loss evidence. No physical-energy measurement is available
in the current SITL setup.

## Inspected components and changes

Inspected Git state/commit, existing user changes, package source/metadata/config,
mission state machine and preflight, resource/event CSV schemas, historical logs,
installed messages, PX4 native definitions/EKF2/generated serializers/Timesync,
VS Code WSL launch configuration, tests and reports. Git remains on master at
5affc1548a85c081b8c37e068a0ea9ffca9081ef with existing changes preserved.
Observed PX4 version is v1.18.0-beta1-213-g43cccdea0e, ROS 2 Jazzy/Python 3.12.3,
and Gazebo Sim 8.15.0. These present versions are not backfilled into historical runs.

- experiment_logger.py and mission_node.py: exact receive monotonic times, native
  sample fields/reset-counter evidence, separate diagnostic events and provenance.
  Receive/order/freshness/mission/failsafe decisions remain unchanged.
- run_provenance.py and tools/authorized_study.py: unique IDs, actual config/source
  snapshots, verified running binary/build evidence, separate passive preflight,
  stop-on-failure collection, and bounded observer lifecycle regression correction.
- clock_probe.py and sync_evidence.py: passive DDS offset-zero observations partitioned
  by protocol. No publishers.
- measurements.py, provenance.py and transport_probe.py: defensible offline evidence
  import, exact historical source-hash matches and isolated localhost collection.
- native_clock.py: standalone native timestamp contract rejection tests. It is NOT
  wired into mission_node and grants no flight authorization.
- tools/live_clock_audit.py and final_report_runner.py: read-only live state checks,
  zero parameter writes, per-study reports, test/build commands and raw preservation.
- tests/setup.py/docs and maintained formatting: targeted regression tests, entrypoints
  and lint fixes. Archived helpers/generated snapshots are preserved, not rewritten.
  The legacy apply-heading-fix helper can overwrite current code and must not be run.

Baseline YAML, mission_state.py policy, waypoints, health/heading requirements,
reset guards and failsafe behavior are preserved. The optional native-clock candidate
patch is explicitly NOT APPLIED. The user chose current behavior and reports only.
No crypto dependencies, Phase 2 work or system upgrades were introduced.

## Actual verification and reproducibility

Latest functional suite: 135 passed, return code 0. Latest full suite: 137 passed,
1 existing copyright skip, 12 ament-flake8 fork warnings, return code 0. Flake8 and
pep257 pass. Affected-package build: return code 0, one package finished in 11.5 s.
Actual-source Timesync compile/run fixture passed. Earlier lint/collector failures
remain in retained logs; they are not hidden or mislabeled as successful flights.

Final manifests/report generation ran for the historical, new and empty-error
cohorts. They report BLOCKED completeness honestly. The CLI completeness exit code
is 2 when strict study count is below 30; that is a dataset rejection, not a tool crash.
The final report runner uses the same validator API and preserves its status.
Protected-before/after SHA-256 maps match for all raw CSV/JSON and safety/config inputs.

Run these commands manually in the existing WSL environment (all are nonflight):

```bash
source /opt/ros/jazzy/setup.bash
source ~/ros2_ws/install/setup.bash
cd ~/ros2_ws/src/baseline_measurement
python3 -m pytest test -q
cd ~/ros2_ws
colcon build --packages-select baseline_measurement
cd ~/ros2_ws/src/baseline_measurement
python3 tools/final_report_runner.py
ros2 run baseline_measurement baseline_dataset --input ~/ros2_ws/baseline_results \
  --output /tmp/phase1_historical_$(date +%s)
ros2 run baseline_measurement baseline_dataset \
  --input ~/ros2_ws/baseline_results/phase1_study_36527160a48f \
  --output /tmp/phase1_newstudy_$(date +%s)
ros2 run baseline_measurement measurement_import --help
```

Use a new exclusive output each time. The validator is per study, not recursively
pooled. Keep old raw files unchanged. The installed environment is already configured;
no installation or upgrade is needed for these checks.

## Remaining blockers and exact evidence

1. The demonstrated DDS clock-domain failure remains operationally unresolved. The
   native-clock coordination proposal was not approved. Its closure needs verified
   current parameter/client state, independent native timestamp pairs, full control
   header/adapter regression tests and a successful controlled trial with all guards.
   Do not disable DDS synchronization while retaining ROS epoch command headers.
2. Grounded heading readiness is false in current preflight observations. Preserve
   the gate. Establish estimator flags/reset evidence and demonstrate heading_ready
   before Offboard; QGC Ready is not equivalent to that field.
3. The new study needs 29 additional contemporaneously documented records under a
   stable recorded configuration and a reliable mission path. Historical missing
   original configuration/version/ID evidence cannot be fabricated from current files.
   No further active collection is requested after the user's reports-only decision.
4. Validate actual UAV-link latency/correlation, complete packet counts and transport
   capture evidence before reporting those metrics. The implemented importers are
   readiness tooling, not demonstrated measurements.
5. Obtain calibrated physical hardware power evidence or explicitly retain simulation
   NOT MEASURED in the research protocol. WSL CPU and simulated battery are not energy.
6. Capture original terminal/QGC/Gazebo screenshots tied to run ID and timestamps if
   required for the research submission. UI was inspected; no new screenshot export
   or successful demonstration capture is claimed.
7. Establish the underlying time-deviation cause and historical-event attribution
   using synchronized native/probe/system timing evidence. The post-failure wall step
   alone does not establish either causal claim.

## Phase 1 acceptance checklist

| Item | Status | Evidence/limitation |
|---|---|---|
| Gazebo/PX4 SITL operational | PASS | Live ROS telemetry and retained running process/version evidence |
| MAVLink and QGroundControl operational | PASS | Live QGC Ready / Hold and visible route; separate read-only MAVLink API probe returned no verified PX4 heartbeat |
| Micro XRCE-DDS / ROS 2 communication operational | PASS | Continuous passive and mission telemetry; this does not imply clock stability |
| Telemetry and commands demonstrated | PASS | Historical route logs and new ARM/TAKEOFF/LAND events |
| Takeoff, position, waypoints, return and landing demonstrated | PASS | 12 historical PASS logs with ordered route and completion evidence |
| Five successful repeated active missions documented | PASS | At least five historical successes; full historical provenance remains missing |
| Architecture/source/configuration evidence collected | PASS | Mermaid source, source/config snapshots and hashes retained; no new terminal screenshot export claimed |
| 30 baseline experiment records validated | BLOCKED | Historical strict provenance 0/30; new study strict provenance 1/30; unavailable metrics not measured |
| Raw CSV/JSON preserved | PASS | Protected-before/after SHA-256 equal, including the new study |
| Required metrics measured or explicitly documented unavailable | PASS | Per-metric method/limitations table; latency/loss/wire traffic/physical power remain NOT MEASURED |
| Timestamp/reset issue investigated with evidence | PASS | New-run proximate DDS filter reset correlated with native ULog continuity; operational correction not applied |
| Safety regression tests | PASS | 135 functional tests; 137 full-suite passes, one existing copyright skip |
| Package build | PASS | Affected package colcon build return code 0 |
| Dataset validation/report generation reproducible | PASS | Per-cohort manifests/reports regenerated; completeness rejection is preserved |

Overall Phase 1: BLOCKED. Phase 2: not ready.
