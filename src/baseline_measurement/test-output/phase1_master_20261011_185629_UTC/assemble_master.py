"""Assemble a new reports-only evidence bundle from actual persisted results."""
import csv
import hashlib
import json
from pathlib import Path
import shutil
import xml.etree.ElementTree as ET
import zipfile

home = Path(r'\\wsl.localhost\Ubuntu-24.04\home\kailash')
package = home / 'ros2_ws/src/baseline_measurement'
audit = package / 'test-output/phase1_master_20261011_185629_UTC'
destination = Path('outputs/phase1_master_20261011_185629_UTC').resolve()


def read(path):
    return json.loads(path.read_text(encoding='utf-8'))


def save(name, data):
    path = audit / name
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(data, indent=2) + '\n' if not isinstance(data, str) else data,
                    encoding='utf-8')


state = read(audit / 'audit_state.json')
verification_dir = sorted(audit.glob('verification_*'))[-1]
verification = read(verification_dir / 'verification.json')
assert verification['verification_exit_code'] == 0, 'Latest verification must actually pass.'
reports = sorted(package.glob('test-output/final_reports_*'))[-1]
full = read(reports / 'verification.json')
assert full['verification_exit_code'] == 0
tree = ET.parse(reports / 'full_suite.xml')
testsuites = list(tree.getroot().iter('testsuite'))
counts = {k: sum(int(s.get(k, 0)) for s in testsuites)
          for k in ['tests', 'failures', 'errors', 'skipped']}
counts['passed'] = counts['tests'] - counts['failures'] - counts['errors'] - counts['skipped']
cohorts = []
all_records = []
for directory in sorted(verification_dir.glob('validator_*')):
    if not directory.is_dir():
        continue
    manifest = read(directory / 'manifest.json')
    cohorts.append({'study': directory.name.removeprefix('validator_'),
                    'counts': manifest['counts'], 'phase1': manifest['overall_phase1'],
                    'source_manifest': str(directory / 'manifest.json'),
                    'primary_configuration_group': manifest['primary_configuration_group']})
    all_records.extend(dict(record, inventory_study=cohorts[-1]['study'])
                       for record in manifest['records'] if record['mode'] == 'SITL_MISSION')
assert len(all_records) == 46 and len({r['sha256'] for r in all_records}) == 46
combined = {'cohorts': cohorts, 'unique_active_attempts': len(all_records),
            'active_pass': sum(r['mission_outcome'] == 'PASS' for r in all_records),
            'active_fail': sum(r['mission_outcome'] == 'FAIL' for r in all_records),
            'records': all_records, 'statistics_pooled_across_studies': False,
            'phase1': 'BLOCKED', 'phase2': 'NOT READY'}
save('combined_inventory.json', combined)
fields = ['inventory_study', 'study_id', 'experiment_id', 'id_provenance', 'run_id',
          'original_run_id', 'run_id_provenance', 'source_file', 'sha256',
          'mission_outcome', 'configuration_group', 'strict_experiment_valid', 'metadata_gaps']
with (audit / 'dataset_manifest.csv').open('w', newline='', encoding='utf-8') as stream:
    writer = csv.DictWriter(stream, fieldnames=fields, extrasaction='ignore')
    writer.writeheader()
    for record in all_records:
        row = dict(record)
        row['metadata_gaps'] = json.dumps(record.get('metadata_gaps', []))
        writer.writerow(row)

protected = state['protected_before']
after = {}
for path in protected:
    relative = path.removeprefix('/home/kailash/')
    candidate = home / relative
    after[path] = hashlib.sha256(candidate.read_bytes()).hexdigest() if candidate.is_file() else None
preservation = {'protected_before': protected, 'protected_after': after,
                'unchanged': protected == after, 'changed': [p for p in protected if protected[p] != after[p]],
                'flight_commands_sent': 0, 'component_restarts': 0, 'parameter_writes': 0}
assert preservation['unchanged']
save('preservation.json', preservation)
save('actual_verification.json', {'full_suite': counts, 'build': full['build'],
     'verification_directory': str(verification_dir), 'report_directory': str(reports),
     'commands': verification['commands'], 'protected_unchanged': True})

references = []
sources = [
 ('PX4-Autopilot/platforms/posix/src/px4/common/drv_hrt.cpp', ['hrt_absolute_time', 'px4_clock_settime', 'ENABLE_LOCKSTEP_SCHEDULER']),
 ('PX4-Autopilot/src/modules/simulation/gz_bridge/GZBridge.cpp', ['clockCallback', 'PX4_CLOCK_MONOTONIC']),
 ('PX4-Autopilot/src/modules/uxrce_dds_client/Micro-XRCE-DDS-Client/src/c/util/time.c', ['uxr_nanos', 'hrt_absolute_time']),
 ('PX4-Autopilot/src/modules/uxrce_dds_client/Micro-XRCE-DDS-Client/src/c/core/session/session.c', ['read_submessage_timestamp_reply', 'session->on_time']),
 ('Micro-XRCE-DDS-Agent/include/uxr/agent/utils/Time.hpp', ['get_epoch_time', 'high_resolution_clock']),
 ('Micro-XRCE-DDS-Agent/src/cpp/processor/Processor.cpp', ['receive_timestamp', 'transmit_timestamp', 'get_epoch_time']),
 ('PX4-Autopilot/src/lib/timesync/Timesync.cpp', ['void Timesync::update', 'MAX_CONSECUTIVE_HIGH_DEVIATION', 'reset_filter', 'observed_offset']),
 ('PX4-Autopilot/src/lib/timesync/Timesync.hpp', ['MAX_CONSECUTIVE_HIGH_DEVIATION', 'MAX_DEVIATION_SAMPLE', 'MAX_RTT_SAMPLE']),
 ('PX4-Autopilot/src/modules/uxrce_dds_client/uxrce_dds_client.cpp', ['void on_time', 'time_offset']),
 ('PX4-Autopilot/src/modules/uxrce_dds_client/dds_topics.h.em', ['time_offset', 'ucdr_serialize']),
 ('PX4-Autopilot/build/px4_sitl_default/uORB/ucdr/vehicle_local_position.h', ['timestamp_adjusted', 'timestamp_sample_adjusted']),
 ('PX4-Autopilot/build/px4_sitl_default/uORB/ucdr/vehicle_attitude.h', ['timestamp_adjusted', 'timestamp_sample_adjusted']),
 ('PX4-Autopilot/msg/VehicleLocalPosition.msg', ['timestamp', 'reset_counter', 'heading_good_for_control']),
 ('PX4-Autopilot/msg/VehicleAttitude.msg', ['timestamp', 'quat_reset_counter']),
 ('PX4-Autopilot/src/modules/ekf2/EKF2.cpp', ['heading_good_for_control']),
 ('PX4-Autopilot/src/modules/ekf2/EKF/ekf.h', ['isYawFinalAlignComplete', 'mag_aligned_in_flight', 'flt_mag_align_start']),
 ('PX4-Autopilot/src/modules/ekf2/EKF/aid_sources/magnetometer/mag_control.cpp', ['mag_aligned_in_flight', 'checkHaglYawResetReq']),
 ('ros2_ws/src/baseline_measurement/baseline_measurement/mission_node.py', ['source_clock_reset', 'timestamp_sample', 'heading_good_for_control', 'time.monotonic', 'reset_counter']),
 ('ros2_ws/src/baseline_measurement/baseline_measurement/mission_state.py', ['WAIT_FOR_HEADING', 'FAILSAFE', 'MISSION_COMPLETE', 'heading_ready']),
 ('ros2_ws/src/baseline_measurement/baseline_measurement/experiment_logger.py', ['source_timestamp_us', 'timestamp_sample', 'resource_interval']),
]
for relative, patterns in sources:
    path = home / relative
    if not path.is_file():
        references.append({'path': relative, 'missing': True})
        continue
    lines = path.read_text(encoding='utf-8', errors='replace').splitlines()
    references.append({'path': '/home/kailash/' + relative,
                       'sha256': hashlib.sha256(path.read_bytes()).hexdigest(),
                       'matches': [{'line': i, 'text': line.strip()} for i, line in enumerate(lines, 1)
                                   if any(pattern in line for pattern in patterns)]})
save('source_references.json', references)

timestamp = '''# Timestamp findings — production correction NOT APPLIED

The proximate mechanism in diagnostic BASE-001 is strongly supported: the DDS Timesync filter discarded its converged offset, the generated serializer immediately delivered native simulation timestamps, and the controller correctly treated the backwards source timestamps as a discontinuity. It is not proof of an EKF reset. The runtime cause of the qualifying clock deviations remains UNPROVEN.

## Exact clock path

Native uORB `timestamp` and `timestamp_sample` are uint64 microseconds. This SITL build enables lockstep: Gazebo sim time feeds PX4 CLOCK_MONOTONIC; hrt_absolute_time reads the scheduler's simulated time. The XRCE SDK custom PX4 uxr_nanos returns hrt_absolute_time()*1000 nanoseconds. Agent get_epoch_time uses high_resolution_clock; the actual compiled fixture confirms its system_clock alias in this environment. These are independently progressing clocks.

The SDK timestamp-reply callback passes client receive time, Agent receive t1, Agent transmit t2, and client originate t0. PX4's callback parameter names misleadingly identify t2 as agent_receive_timestamp; Timesync actually receives Agent transmit t2. This naming discrepancy is documented, not patched. Offset = (originate/1000 + native_now - 2*Agent_transmit/1000)/2 us; RTT = native_now - originate/1000 us. DDS protocol is 2. Only native-clock RTT <10000 us is accepted; after convergence, deviation >100000 us increments the high-deviation count. Count >10 resets the filter (eleventh qualifying sample). High-RTT rejection does not clear that count; an accepted ordinary sample does. The source comment saying five consecutive is stale.

on_time stores -Timesync.offset()*1000 ns in session.time_offset. The DDS send template converts ns/1000 to us, and generated serializers add it to BOTH timestamp fields. At reset, the offset is zero. px4_msgs delivers the adjusted uint64 fields without normalization. The ROS adapter consumes timestamp for ordering; logging retains it as source_timestamp_us. Receive freshness uses local time.monotonic, with a separate source-progress watchdog so repeated timestamps cannot indefinitely renew validity. The latched airborne guard sends the existing mission to FAILSAFE. Actual reset counters are independent evidence; expected bootstrap yaw-reset handling and guarded grounded completion remain unchanged.

## Correlated evidence

At 2026-10-11 18:07:01.748566 UTC DDS estimated offset changes -1791735387918623 us to 0. Position at 18:07:01.749219 changes 1791742020006623 to 6632104000 us; attitude follows. Native contemporaneous ULog stays ordered, has zero dropouts, and all captured position/velocity/heading/quaternion reset counters remain unchanged across the whole log. The next accepted sample restores a large offset. Actual-source fixtures reproduce the eleven-sample reset, serializer-sized discontinuity, and recovery deterministically using labelled synthetic inputs. No test fixture is an experiment.

Eight captured pre-reset DDS samples qualify if converged, with native RTT <=4000 us. Endpoint progression reconstructed algebraically from remote_timestamp + observed_offset gives cumulative native-midpoint/Agent progression ratio 0.8508925233 before reset. This establishes endpoint progression mismatch, not calibrated telemetry latency; the capture does not contain all eleven triggering samples.

## Hypotheses and uncertainty

Confirmed: serializer conversion switches domains when filter offset resets; native estimator counters do not support a genuine reset in this event. Strongly supported: differing simulation/client and epoch/Agent progression drives the observed offset departures. Unproven alternatives: Gazebo clock pauses/catch-up, WSL scheduling, OS clock rate adjustment, host/guest clock instability, and transport processing delay. Reported native RTT is simulation-time based: small values do NOT exclude real delivery delay while simulation time stalls.

A receiver wall-minus-monotonic step of approximately +1.984 s occurs AFTER failure, so it cannot establish the cause of the earlier event. A later passive Gazebo window has sim/server-real delta ratio approximately 0.999999685 with reported RTF 0.5501–1.8105. This excludes sustained slowdown in that particular window, not historical slowdown. A still later WSL clock sample gives MONOTONIC 14.93265 s and RAW 15.99419 s; REALTIME tracks MONOTONIC. This is evidence of rate disagreement in that later sample, not contemporaneous causal attribution. WSL uses tsc, time synchronization is active; the retained journal does not show a synchronization event at the failure. No clock service or time source was changed.

Source revision, generated serializers, compile definitions, and running binary fingerprints are retained. They provide strong installed identity evidence, not a byte-for-byte reproducible rebuild of the Agent/PX4 binaries. Historical reversals in runs 015/021/043/045 lack synchronized native/offset evidence; do not transfer this diagnosis to each historical failure as proven.

## Closure and safety

Production correction is NOT APPLIED. All current source-ordering, local freshness, actual reset, heading and failsafe checks remain in place. Obtain simultaneous Gazebo sim/server-real, client t0/receive, Agent t1/t2 and OS realtime/monotonic/raw observations spanning a reset to discriminate causes. A future native-clock proposal must coordinate incoming DDS timestamps and outgoing command/setpoint headers, prove native ordering while grounded, and retain genuine-reset/staleness tests. Parameter changes/client restart, live controller changes and flight tests require explicit authorization. See unapplied_clock_proposal.md. Never simply ignore epoch-to-boot reversals.
'''
save('timestamp_root_cause.md', timestamp)
save('heading_readiness_report.md', '''# Heading readiness

The captured grounded false value matches the installed PX4 predicate. EKF2 publishes heading_good_for_control = isYawFinalAlignComplete(). With magnetometer enabled, readiness requires yaw_align and either no active magnetic yaw fusion, or mag_aligned_in_flight with delayed EKF time strictly more than one second after the final magnetic alignment. Finite yaw and initial yaw_align alone do not satisfy this condition.

Current capture: yaw_align=true, mag_hdg=true, mag_3d=false, mag_aligned_in_flight=false, magnetic fault/disturbance and bad-heading flags false, landed=true. This combination explains heading_good_for_control=false; it does not prove magnetometer hardware failure or ROS communications loss. The initial passive callback rates were attitude 47.548 Hz, local position 47.508 Hz, status 1.8795 Hz over 25.0063 monotonic seconds. Rates are observations, not fixed acceptance thresholds.

Native diagnostic ULog begins with retained alignment=true, then clears it at entry to in_air at native 6628804000 us. Heading readiness also clears there. Magnetic fusion switches to mag_hdg and never completes final alignment before this failed flight lands. Therefore the initial true value must not be reported as later successful alignment recovery.

The existing mission permits safe AUTO_TAKEOFF bootstrap with fresh initial yaw, then requires continuous heading readiness before OFFBOARD. The outer study preflight requires final heading readiness already on the ground. This gate mismatch is documented, not relaxed. No flight behavior was edited. Offline actual-source C++ predicate tests cover magnetic/nonmagnetic builds, missing alignment and the strict one-second boundary; adapter/controller tests cover stale finite yaw and airborne heading loss with existing failsafe. The hidden final-alignment start time is not exposed by these ROS flags; public flags cannot establish the elapsed-time branch when already aligned.

Operational heading readiness remains BLOCKED: an explicitly authorized, correctly instrumented bootstrap must show the native final-alignment flags, continuous ready heading, OFFBOARD transition, complete route, landing, disarming and final completion. No new mission was launched during this request.
''')
save('unapplied_clock_proposal.md', '''# UNAPPLIED proposal — requires separate authorization

No candidate patch is merged into flight code. A native PX4 timestamp path could avoid changing publication domains at a DDS offset reset, but cannot safely be enabled on incoming topics alone: command/setpoint header conversion must be coordinated and verified against the generated incoming serializer. Review disabling DDS timestamp conversion while confirmed landed/disarmed, restart only the DDS client, verify native source timestamps and outgoing header semantics, then consider a separately reviewed adapter change and the outer bootstrap gate. Preserve WAIT_FOR_HEADING, reset counters, source-ordering, stale telemetry, loss-of-stream, heading-loss, landing and completion guards. This is a proposal rather than a proven cure for the underlying clock disagreement.

Required authorized sequence: grounded clock/header verification; source fixtures and safety regression suite; one supervised SITL trial; complete route/return/landing/disarm evidence; then a newly identified corrected-configuration study. A changed configuration needs its own 30 records; do not add 29 changed runs to the existing failed diagnostic study. User selected reports only, so none of these operations has been performed.
''')
save('architecture.mmd', '''flowchart LR
 G[Gazebo simulation clock] --> H[PX4 lockstep hrt us]
 H --> U[Native uORB and ULog]
 H --> X[XRCE client uxr_nanos ns]
 A[Agent epoch clock] --> T[Timesync filter]
 X --> T
 T --> O[session.time_offset ns]
 U --> S[Generated serializer adds offset us]
 O --> S
 S --> R[px4_msgs ROS callbacks]
 R --> C[Native-delivered ordering and reset guards]
 M[Local monotonic receive clock] --> F[Freshness and source progress]
 F --> C
 E[Estimator flags and reset counters] --> C
 C --> Q[Existing mission state and failsafe]
 R --> L[Raw CSV provenance logger]
 Q --> L
 L --> V[Offline dataset validator and reports]
''')

historical = next(x for x in cohorts if x['study'] == 'baseline_results')
new = next(x for x in cohorts if x['study'] == 'phase1_study_36527160a48f')
checklist = [
 ('PX4/Gazebo operational', 'PASS', 'Existing native log and current passive topics; no new flight'),
 ('MAVLink/QGroundControl operational', 'BLOCKED', 'Historical plan evidence exists; current plan upload/mission transport not demonstrated by ROS OFFBOARD'),
 ('Micro XRCE-DDS/ROS communication', 'PASS', 'Continuous passive callbacks and protocol-2 status captured'),
 ('Telemetry and vehicle commands demonstrated', 'PASS', 'Historical active logs; local publish is not proof of MAVLink plan upload'),
 ('Takeoff/control/waypoints/return/landing/disarm/completion demonstrated', 'PASS', '12 recorded historical PASS outcomes; original provenance incomplete'),
 ('Five repeated successful active missions', 'PASS', '12 historical PASS, zero new diagnostic PASS'),
 ('Architecture/source/configuration evidence', 'PASS', 'Current hash/source/clock inventory, Mermaid and raw provenance references'),
 ('30 baseline records with prescribed provenance', 'BLOCKED', 'Historical strict 0/30; diagnostic strict 1/30; 29 missing'),
 ('Required metrics measured or limitations explicitly accepted', 'BLOCKED', 'Missing latency/loss/wire/power measurements documented; no formal waiver or thresholds found'),
 ('Timestamp safely understood and resolved', 'BLOCKED', 'Proximate mechanism proved; runtime cause unresolved; production fix not applied'),
 ('Heading readiness operationally verified', 'BLOCKED', 'Grounded predicate understood; final alignment and successful new flight unverified'),
 ('Raw data preserved', 'PASS', 'Stage A and final protected SHA-256 maps equal'),
 ('Safety/full regression suite', 'PASS', f"{counts['passed']} passed, {counts['skipped']} skipped; failures/errors zero"),
 ('Package build', 'PASS', 'colcon affected-package build return code 0'),
 ('Reproducible validator/report generation', 'PASS', 'All per-cohort validators produce artifacts and return 2 for incomplete acceptance'),
]
save('phase1_acceptance.json', {'phase1': 'BLOCKED', 'phase2': 'NOT READY',
      'checklist': [{'item': a, 'status': b, 'evidence': c} for a, b, c in checklist],
      'metrics_unmeasured': ['end_to_end_latency', 'telemetry_latency', 'command_latency',
                             'packet_loss', 'wire_bandwidth', 'physical_power', 'physical_energy'],
      'cohorts': cohorts, 'formal_metric_thresholds_or_waivers_available': False})

metric_text = '''# Metric definitions, quality and closure evidence

All unavailable values are null and excluded, never zero. Per-configuration counts, mean, median, sample SD, min/max and 95% intervals where supported are in the cohort manifests. Small samples and repeated SITL observations do not justify universal performance claims. Failed attempts can provide payload/resource observations but no successful mission duration.

| Metric | Status/units | Points, clock, collection window and acceptance evidence |
|---|---|---|
| End-to-end latency | NOT MEASURED, ms | Correlated application request to remote application response; bounded common-clock mapping or explicit same-clock round trip. Label round trip separately. Offline import validators/loopback instrumentation exist; no actual UAV correlation capture. |
| Telemetry latency | NOT MEASURED, ms | Native publication to receiver callback with independently validated offset/error bounds spanning the window. Current DDS offset is unstable; receive interval is not latency. |
| Command latency | NOT MEASURED, ms | Unique command send to matching ACK or applied-state response; retries/overlap handled. Existing ACKs cannot independently identify every request. No command was sent in this task. |
| Packet loss | NOT MEASURED, % | Identifiable sent/expected sequence denominator and received unique sequences at a specified layer; separate loss/reordering/duplicate counts and wrap/restart. Topic frequency does not establish expected packet count. |
| RX CDR payload throughput | MEASURED LIMITED, Mbit/s | Received serialized CDR bytes*8 / whole monotonic run seconds /1e6. Callback bytes and run start/end; excludes network headers and uncaptured streams. |
| TX CDR payload throughput | MEASURED LIMITED, Mbit/s where available | Local publish-call CDR bytes over monotonic whole run; does not establish delivered wire bytes. Missing byte instrumentation stays null. |
| Wire bandwidth/use | NOT MEASURED, Mbit/s | Direction/interface/filter-specific packet byte counts over a monotonic window, capture drop counters and transport/IP overhead; do not call topic Hz or payload bytes physical link capacity. |
| CPU | MEASURED LIMITED, % | Primed psutil finite interval samples: node CPU percent of one logical CPU; guest CPU excludes Windows host/QGC/GPU. Arithmetic mean of retained samples; configured sampling interval retained in raw metadata. |
| Memory | MEASURED LIMITED, MiB | Mission-process RSS bytes /2^20 at resource callbacks; excludes PX4/Gazebo/Agent and host allocations. |
| Mission completion | MEASURED LIMITED, s | First active mission event to verified final MISSION_COMPLETE after route, return, landing and disarm; local monotonic. PASS only. Failed attempt duration reported separately. |
| Power/energy | NOT MEASURED, W/Wh | Time-stamped calibrated voltage/current sensor or defensible simulator power model, synchronized sample interval and numerical integral with missing-gap policy. Host CPU is not UAV power. |

Measurement schema validators, correlation/sequence import and loopback instrumentation are present and tested; these do not validate the uncollected UAV metrics. Documented roadmap lacks formal numeric latency/loss/power thresholds and no waiver was supplied. Acceptance remains blocked until the owner specifies accepted evidence/limitations and real measurements meet them.
'''
save('metric_definitions_and_quality.md', metric_text)

reproduction = '''# Reproduce offline verification (no arming or movement)

```bash
source /opt/ros/jazzy/setup.bash
source ~/ros2_ws/install/setup.bash
cd ~/ros2_ws/src/baseline_measurement
python3 -m pytest test -q --junitxml=test-output/reproduced_full_suite.xml
python3 tools/native_timesync_check.py --help
python3 tools/native_heading_check.py --help
python3 tools/final_report_runner.py
python3 tools/reports_only_verify.py --audit test-output/phase1_master_20261011_185629_UTC
cd ~/ros2_ws
colcon build --packages-select baseline_measurement
```

The actual native fixture compile/run arguments and validator arguments including prior manifests are preserved verbatim in actual_verification.json and verification_*/verification.json. Dataset validators return 2 for incomplete Phase 1; that is a successful rejection, not a crash. final_report_runner returns nonzero for actual test/build/preservation failures. Neither full suite nor these tools publish vehicle commands. reports_only_verify additionally takes a bounded passive DDS/Gazebo capture; requires running SITL but does not restart it.

Use unique new output directories for reanalysis; preserve all historical files. Keep historical/new/empty studies separate. For terminal screenshots, manually display the full test result, build result, validator exit code and study summary, showing commands and output; screenshots are optional supplemental evidence, not substitutes for retained logs. No flight demonstration screenshot was fabricated or claimed. Current source references and configuration hashes are bundled, historical missing metadata remains missing.
'''
save('REPRODUCE.md', reproduction)

table = '\n'.join(f'| {a} | {b} | {c} |' for a, b, c in checklist)
report = f'''# Final Phase 1 report — reports only

**Phase 1 BLOCKED. Phase 2 NOT READY.** No flight commands, parameter writes, component restarts or production flight changes were performed in this request.

## Audit and changes

Repository master at {state['commit']}; PX4 {state['px4_commit']}, {state['px4_version'].strip()}; ROS {state['ros_distro']}; Gazebo {state['gazebo_version'].strip()}. Existing dirty tree and source revisions were recorded before editing; no reset/clean/upgrade. Protected raw CSV/JSON/plan files, mission_node/state, baseline/qgc code, YAML and relevant PX4 sources match Stage A SHA-256 values.

Offline changes: dataset.py preserves original experiment/run IDs, distinguishes retrospective IDs and study namespaces, rejects conflicting relabels, and separates known YAML/firmware/simulator/clock configurations. diagnostic_analysis.py explains DDS and heading observations without invented normalization. reporting.py and final_report_runner.py now propagate test/build/preservation failures. New source fixtures and regression tests validate filter/SDK conversion, heading boundaries, stale telemetry, failsafe, dataset identity and reporting exit codes. Read-only audit/clock/verification tools collect reproducible evidence. Mission behavior is unchanged. The coordinated native-clock correction is a NOT APPLIED proposal.

## Timestamp and heading conclusions

DDS offset reset followed by generated timestamp conversion explains the diagnostic source-clock failure; native ULog ordering and unchanged reset counters do not support an EKF reset. Simulation/client versus Agent epoch progression disagreement is observed, but its physical/runtime cause remains unproven. A later wall step cannot explain the earlier failure. Small simulated-clock RTT cannot rule out real transport/scheduling delay. See timestamp_root_cause.md, source_references.json and analysis/.

Grounded heading false is explained by active magnetic yaw fusion without final in-flight magnetic alignment. Finite heading and yaw_align are insufficient. Actual-source predicate and adapter/failsafe tests pass; operational final alignment and new complete mission are not demonstrated. The study preflight/bootstrap gate mismatch remains unchanged. See heading_readiness_report.md.

## Dataset and performance

Historical: 45 active attempts, 12 PASS/33 FAIL (12/45 = 26.67%); 30 retrospective study slots, strict provenance 0/30. Largest recorded configuration: 36 active, 12 PASS/24 FAIL (33.33%). Diagnostic study: 1 active, 0 PASS/1 FAIL, strict provenance 1/30, 29 missing. Empty study: 0 active and no contribution. Combined 46 unique active attempts, 12 PASS/34 FAIL; not pooled for performance statistics. Zero records have all requested measured metrics.

Original IDs remain stable. Historical original experiment/run IDs, actual YAML file/hash and PX4/simulator versions cannot be inferred from current code. Retained source-byte matches support source identity only. provenance.json retains supported matches without rewriting originals. BASE-001 can occur in different study namespaces; do not treat it as globally unique or merge diagnostic and historical data.

Largest historical group: RX CDR payload n=36 mean 0.113007 Mbit/s, median 0.114064, SD 0.00389681, range 0.0914687–0.114401. Node CPU n=36 mean 11.1922% of one logical CPU; RSS n=36 mean 88.6317 MiB. Completed mission duration n=12 mean 109.186 s, median 108.926, SD 0.869205, range 108.618–111.815. Diagnostic failed-attempt observations n=1: RX 0.090341 Mbit/s, node CPU 19.5167%, guest CPU 61.7167%, RSS 87.8641 MiB, attempt duration 19.3089 s; successful completion duration unavailable. Cohort manifests retain exact per-metric n/missing counts and all statistical fields, including defensible intervals.

End-to-end/telemetry/command latency, packet loss, wire bandwidth and physical power/energy remain NOT MEASURED. CDR throughput excludes wire overhead; node/guest resources do not measure physical UAV energy. Metric definitions, clocks, collection points, windows, limitations and exact required evidence are in metric_definitions_and_quality.md. No formal numeric acceptance thresholds or explicit waiver is available.

## Actual verification

Latest full suite: **{counts['passed']} passed, {counts['skipped']} skipped, {counts['failures']} failures, {counts['errors']} errors**, return 0. Flake8 and pep257 pass; copyright check remains the existing skip. Affected-package colcon build return 0. Targeted tests and actual-source C++ fixtures return 0. Each historical/diagnostic/empty validator returns 2 and emits its report: incomplete acceptance is correctly rejected. Final verification runner return 0. Protected SHA-256 equality PASS. Earlier intermediate lint failures and their logs remain in verification_190504/190923 rather than being discarded.

Linux evidence directory: /home/kailash/ros2_ws/src/baseline_measurement/test-output/phase1_master_20261011_185629_UTC. Latest suite/build output: {str(reports).replace(str(home), '/home/kailash')}. Commands, exit codes, JUnit XML, git diff/status, provenance recovery, source references and protected fingerprints are retained. See REPRODUCE.md for safe commands.

## Acceptance checklist

| Criterion | Status | Evidence/limitation |
|---|---|---|
{table}

## Minimum remaining actions

1. Review and authorize a specific grounded simultaneous-clock/header experiment and coordinated native-clock proposal. Requires explicit approval for DDS setting changes/restart and any operational code change. Resolve or bound the runtime cause; retain all safety tests.
2. Separately authorize one supervised SITL bootstrap and full route to prove final heading, OFFBOARD, return, landing, disarm and completion. Archive native ULog/DDS/callback/ACK/evidence together. No such mission was performed here.
3. Define measurement acceptance thresholds or explicitly accept simulation limitations; collect correlated latency, sequence-based loss, interface byte evidence and calibrated physical power if required. Synthetic loopback tests do not satisfy these requirements.
4. Collect 30 provenance-complete real experiments under one documented configuration. The unchanged diagnostic study lacks 29; if the fix changes configuration, start a separate corrected study needing its own 30. Historical missing original metadata cannot be invented. Preserve every failure and all raw data.
5. Re-run validator/report generation and evaluate each acceptance criterion using that evidence. Phase 2 stays blocked until all mandatory requirements or explicit accepted limitations are met.

Immediate next action: review the NOT APPLIED grounded clock/header procedure in unapplied_clock_proposal.md. Reports-only authorization remains in force; no live operation will be started without a new explicit decision.
'''
save('FINAL_PHASE1_REPORT.md', report)

# Copy actual logs and source snapshots into this new self-contained bundle.
suite_copy = audit / 'latest_suite_build'
shutil.copytree(reports, suite_copy, dirs_exist_ok=False)
with zipfile.ZipFile(audit / 'source_evidence.zip', 'w', zipfile.ZIP_DEFLATED) as archive:
    for pattern in ['baseline_measurement/*.py', 'test/*.py', 'tools/*.py', 'config/*',
                    'package.xml', 'setup.py', 'setup.cfg', 'docs/*.md']:
        for path in package.glob(pattern):
            if path.is_file():
                archive.write(path, str(path.relative_to(package)))
    for reference in references:
        path = home / reference['path'].removeprefix('/home/kailash/')
        if path.is_file():
            archive.write(path, 'native_source/' + str(path.relative_to(home)))
source_index = {str(p.relative_to(package)): hashlib.sha256(p.read_bytes()).hexdigest()
                for folder in ['baseline_measurement', 'test', 'tools', 'config']
                for p in (package / folder).rglob('*') if p.is_file() and p.suffix in ['.py', '.yaml']}
save('source_hash_index.json', source_index)
shutil.copy2(Path(__file__), audit / 'assemble_master.py')
shutil.copytree(audit, destination, dirs_exist_ok=False)
print(json.dumps({'output': str(destination), 'tests': counts,
                  'cohorts': cohorts, 'protected_unchanged': True}, indent=2))
