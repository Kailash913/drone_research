# Phase 1 continuation: evidence and measurement methods

The initial nonflight verification changed diagnostic logging and offline tooling.
A later explicitly authorized active BASE-001 attempt failed safely. No flight-policy
correction was applied. The work does not change mission waypoints, timeouts, estimator health
requirements, timestamp reset decisions, grounded-completion policy or failsafe
actions. Historical raw files and archived code remain immutable. Phase 2 is blocked.

## Timestamp path and supported finding

The local PX4 VehicleLocalPosition and VehicleAttitude definitions describe native
`timestamp` and `timestamp_sample` in microseconds since boot. EKF2 sets these from
hrt and the sensor sample. Generated `uORB/ucdr` serializers add the XRCE session
offset to both fields. SendTopicsSubs snapshots `session.time_offset / 1000` before
serialization. The XRCE `on_time` callback assigns `-Timesync.offset() * 1000` to the
session offset. Generated px4_msgs uint64 fields reach the Python subscription
unchanged. MissionNode uses `msg.timestamp`, not `timestamp_sample`, for ordering.
The CSV's source_timestamp_us is that delivered field. It is not independently
validated native boot time, Unix time, ROS time or a telemetry-latency measurement.

The installed PX4 Timesync filter converges at 500 accepted samples. With RTT less
than 10 ms, a deviation greater than 100 ms increments the high-deviation count;
the actual constant is 10 and the comparison is greater-than, so the eleventh
such sample resets the filter. The source comment mentioning five samples is stale.
`reset_filter()` sets the offset to zero; `on_time` can therefore set the session
offset to zero. The following accepted sample initializes the offset again.
The retained native C++ fixture compiles the actual filter methods and constants,
with mocked hrt/uORB, and demonstrates offset zero and recovery. It is a software
mechanism test, not historical telemetry and not a baseline experiment.

Historical CSV discontinuities are confirmed, but they lack synchronized native
uORB timestamps, DDS offset observations and reset counters at the events. Their
root cause remains unproven. A filter reset also does not establish what caused the
deviation. WSL scheduling, host clock changes and simulator timing remain hypotheses.
No guard is relaxed on this evidence.

New mission message details preserve reception monotonic time, timestamp_sample and
available position/velocity/heading/quaternion reset counters. Counter changes in
the existing position guard produce a separate estimator_reset_counter_change
event. Source timestamp reversals retain the existing source_clock_reset event,
with estimator_reset_proven=false: that event alone is not estimator-reset proof.
The passive clock probe partitions TimesyncStatus by protocol and records DDS
offset-to-zero transitions independently. It creates no publishers.

Close the attribution gap with a simultaneous passive ROS capture and native PX4
ULog containing timesync_status with DDS protocol, native vehicle_local_position,
vehicle_attitude, estimator_status_flags and reset counters, plus client debug/time
sync state. Establish a UTC/native/receiver alignment with documented uncertainty.
Correlate an actual discontinuity with native timestamp continuity, DDS offset,
reset-counter changes and estimator flags. If the event is not captured, report it
as not reproduced. Do not infer absence of resets from missing topics.

## Measurement instrumentation and acceptance

All importers write new exclusive outputs and retain SHA-256 of input and metadata.
Schema validation is not independent verification of evidence supplied in metadata.
Review the cited evidence before using measurements in the baseline manifest.
Fixture tests and localhost bench measurements never satisfy UAV mission metrics.

| Metric | Current UAV status | Definition, units and method | Acceptance evidence |
|---|---|---|---|
| End-to-end latency | NOT MEASURED | Correlated request initiation to specified remote application endpoint response, us | Unique request ID, evidenced endpoint and validated common clock; retries/concurrency accounted for |
| Telemetry latency | NOT MEASURED | Native source-event time mapped to receiver event time, us, with uncertainty | Independently validated scale/offset, explicit clock domains and validity interval; simultaneous native/receive capture |
| Command latency | NOT MEASURED | Unique mission request to specified ACK or action endpoint, us | PX4-side unique correlation instrumentation or independently proven association; command number alone is insufficient |
| Packet loss | NOT MEASURED | Missing unique transmitted IDs / transmitted IDs in a closed window | Complete sender and receiver counts and bounded drain; application loss is separate from wire packet loss |
| Throughput | LIMITED MEASURED | Delivered ROS CDR payload bytes / monotonic observation seconds, byte/s or bit/s | Existing CDR serialization counts; excludes XRCE/DDS/UDP/link overhead |
| Wire traffic / bandwidth | NOT MEASURED | Original captured frame bytes * 8 / explicit capture window, bit/s | Real classic PCAP, interface/direction/filter/link type/drop statistics and timestamp source; offered traffic is not capacity |
| CPU | LIMITED MEASURED | psutil process % of one logical core and Linux guest CPU %, nominal 1 s samples | Scope/PID/counter priming retained; excludes Windows QGC and physical UAV |
| Memory | LIMITED MEASURED | Process RSS, MiB, nominal 1 s samples | PID/scope retained; no interpretation as all-system or UAV memory |
| Mission duration | MEASURED for PASS | Run monotonic start to final mission result, s | Full route, return-home, landing, disarm and final completion; FAIL duration is diagnostic, not completion time |
| Physical power/energy | NOT MEASURED | Calibrated UAV power W; trapezoidal integration J over ordered samples | Physical instrument ID/calibration, positive bounded sample gaps, synchronized mission window; SITL battery/host CPU cannot substitute |

Missing, nonfinite, out-of-domain and uncorrelated observations are rejected or
remain unavailable; they are never replaced by zero. The telemetry importer requires
native_source_us, receive_us, source_domain, receiver_domain and calibration JSON
containing scale, offset_us, uncertainty_us, validity source interval and a reference
to independent validation. The correlated importer requires unique request_id,
request_us, response_us, endpoint_evidence and clock_validation_evidence.
Sequence evidence contains run_id, sequence and sent/received events plus a terminal
window_closed record. Power CSV contains monotonic_s and power_w; metadata requires
physical_uav scope, device_id, calibration_evidence and max_gap_s. PCAP metadata
contains start_s/end_s plus capture scope and drop evidence.

The optional transport_probe binds only 127.0.0.1 at an ephemeral UDP port. It
records actual UUID/sequence echo RTT using the same process monotonic_ns clock,
sender IDs and receiver observations. Its output is LOCALHOST_BENCH_ONLY, with
mission_outcome=NOT_ATTEMPTED and no BASE experiment ID. It demonstrates the collector
mechanics, not PX4 or UAV-link performance. No flight endpoints are contacted.

## Historical provenance

provenance_recovery matches recorded source_sha256 values to retained Python bytes
and writes a sidecar. A matching hash supports source identity. It does not prove
the installed package state, PX4 revision, historical YAML contents, Gazebo version
or clock calibration. Missing historical configuration file/hash and verified
versions remain null. Current files must never be substituted for those unknowns.
Existing BASE-001..030 retrospective study assignments and mission outcomes remain
as validated; recovery does not upgrade strict validity without all evidence.

## Reproduce without flight

```bash
source /opt/ros/jazzy/setup.bash
cd ~/ros2_ws
colcon build --packages-select baseline_measurement
source install/setup.bash
cd src/baseline_measurement
python3 -m pytest test -q
python3 tools/continuation_check.py
# Runner records exact return codes in a unique test-output/continuation_* directory.
# Validator exit 2 means the 30 strict experiment criterion is unsatisfied.
ros2 run baseline_measurement baseline_dataset --input ~/ros2_ws/baseline_results \
  --output /tmp/phase1_dataset_$(date +%s)
ros2 run baseline_measurement provenance_recovery --input ~/ros2_ws/baseline_results \
  --evidence-dir heading_fix_backups --evidence-dir test-output/continuation_source_before \
  --output /tmp/phase1_provenance_$(date +%s).json
ros2 run baseline_measurement clock_probe --seconds 60 --output /tmp/clock_probe_$(date +%s)
python3 -m baseline_measurement.transport_probe --output /tmp/loopback_bench_$(date +%s)
ros2 run baseline_measurement measurement_import --help
```

Lint covers all maintained package modules, tests, setup.py and tools, except the
immutable legacy vscode_apply_heading_fix.py migration helper. That helper embeds
historical source and can overwrite the live controller; do not execute it. Archived
heading_fix_backups and generated test-output snapshots are not maintained code and
are excluded from lint rather than rewritten. Active-code style findings are fixed.

## Remaining evidence requirements

1. The new BASE-001 event is correlated with DDS offset reset and native continuity.
   Resolve its underlying trigger and operational correction, or retain the conservative
   response and report the unresolved limitation. Historical attribution remains open.
2. Obtain 30 experiments with contemporaneous configuration hash/path, source/build
   identity, verified environment, unique run ID, mode/outcome and metric-specific
   evidence. Recover historical fields only from retained originals. Missing original
   evidence cannot be reconstructed from current files.
3. Demonstrate instrumented PX4/UAV telemetry, command and end-to-end latency with
   clock/correlation validation; exact sequence counts and captured transport traffic.
4. Measure physical power on physical hardware with calibrated instrumentation, or
   explicitly accept NOT MEASURED as a simulation limitation in the research protocol.
5. Capture required QGC/Gazebo/source/configuration evidence and link it to the run.
   For screenshots, show the actual relevant UI and terminal output, include run ID
   and timestamp, and retain original captures. Screenshots are not substitutes for
   machine-readable measurements. One later human-authorized active attempt failed; subsequent collection stopped.

See the generated continuation report for actual test/build results, counts,
acceptance statuses and protected-file verification. Do not start Phase 2.

## Current continuation result

See PHASE1_CURRENT_REPORT.md for the correlated new-run failure, current counts,
137-pass full suite/build evidence and the user decision to keep flight behavior
unchanged and finish reports only. The native-clock candidate is not applied.
