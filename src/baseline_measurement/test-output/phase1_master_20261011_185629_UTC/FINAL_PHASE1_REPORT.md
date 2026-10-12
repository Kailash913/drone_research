# Final Phase 1 report — reports only

**Phase 1 BLOCKED. Phase 2 NOT READY.** No flight commands, parameter writes, component restarts or production flight changes were performed in this request.

## Audit and changes

Repository master at 5affc1548a85c081b8c37e068a0ea9ffca9081ef; PX4 43cccdea0e57cf92a58562d2d7a1cba0854395f7, v1.18.0-beta1-213-g43cccdea0e; ROS jazzy; Gazebo 8.15.0. Existing dirty tree and source revisions were recorded before editing; no reset/clean/upgrade. Protected raw CSV/JSON/plan files, mission_node/state, baseline/qgc code, YAML and relevant PX4 sources match Stage A SHA-256 values.

Offline changes: dataset.py preserves original experiment/run IDs, distinguishes retrospective IDs and study namespaces, rejects conflicting relabels, and separates known YAML/firmware/simulator/clock configurations. diagnostic_analysis.py explains DDS and heading observations without invented normalization. reporting.py and final_report_runner.py now propagate test/build/preservation failures. New source fixtures and regression tests validate filter/SDK conversion, heading boundaries, stale telemetry, failsafe, dataset identity and reporting exit codes. Read-only audit/clock/verification tools collect reproducible evidence. Mission behavior is unchanged. The coordinated native-clock correction is a NOT APPLIED proposal.

## Timestamp and heading conclusions

DDS offset reset followed by generated timestamp conversion explains the diagnostic source-clock failure; native ULog ordering and unchanged reset counters do not support an EKF reset. Simulation/client versus Agent epoch progression disagreement is observed, but its physical/runtime cause remains unproven. A later wall step cannot explain the earlier failure. Small simulated-clock RTT cannot rule out real transport/scheduling delay. See timestamp_root_cause.md, source_references.json and analysis/.

Grounded heading false is explained by active magnetic yaw fusion without final in-flight magnetic alignment. Finite heading and yaw_align are insufficient. Actual-source predicate and adapter/failsafe tests pass; operational final alignment and new complete mission are not demonstrated. The study preflight/bootstrap gate mismatch remains unchanged. See heading_readiness_report.md.

## Dataset and performance

Historical: 45 active attempts, 12 PASS/33 FAIL (12/45 = 26.67%); 30 retrospective study slots, strict provenance 0/30. Largest recorded configuration: 36 active, 12 PASS/24 FAIL (33.33%). Diagnostic study: 1 active, 0 PASS/1 FAIL, strict provenance 1/30, 29 missing. Empty study: 0 active and no contribution. Combined 46 unique active attempts, 12 PASS/34 FAIL; not pooled for performance statistics. Zero records have all requested measured metrics.

Original IDs remain stable. Historical original experiment/run IDs, actual YAML file/hash and PX4/simulator versions cannot be inferred from current code. Retained source-byte matches support source identity only. provenance.json retains supported matches without rewriting originals. BASE-001 can occur in different study namespaces; do not treat it as globally unique or merge diagnostic and historical data.

Largest historical group: RX CDR payload n=36 mean 0.113007 Mbit/s, median 0.114064, SD 0.00389681, range 0.0914687–0.114401. Node CPU n=36 mean 11.1922% of one logical CPU; RSS n=36 mean 88.6317 MiB. Completed mission duration n=12 mean 109.186 s, median 108.926, SD 0.869205, range 108.618–111.815. Diagnostic failed-attempt observations n=1: RX 0.090341 Mbit/s, node CPU 19.5167%, guest CPU 61.7167%, RSS 87.8641 MiB, attempt duration 19.3089 s; successful completion duration unavailable. Cohort manifests retain exact per-metric n/missing counts and all statistical fields, with 95% confidence intervals explicitly withheld because independence and full configuration equivalence are unverified.

End-to-end/telemetry/command latency, packet loss, wire bandwidth and physical power/energy remain NOT MEASURED. CDR throughput excludes wire overhead; node/guest resources do not measure physical UAV energy. Metric definitions, clocks, collection points, windows, limitations and exact required evidence are in metric_definitions_and_quality.md. No formal numeric acceptance thresholds or explicit waiver is available.

## Actual verification

Latest full suite: **170 passed, 1 skipped, 0 failures, 0 errors**, return 0. Flake8 and pep257 pass; copyright check remains the existing skip. Affected-package colcon build return 0. Targeted tests and actual-source C++ fixtures return 0. Each historical/diagnostic/empty validator returns 2 and emits its report: incomplete acceptance is correctly rejected. Final verification runner return 0. Protected SHA-256 equality PASS. Earlier intermediate lint failures and their logs remain in verification_190504/190923 rather than being discarded.

Linux evidence directory: /home/kailash/ros2_ws/src/baseline_measurement/test-output/phase1_master_20261011_185629_UTC. Latest suite/build output: /home/kailash\ros2_ws\src\baseline_measurement\test-output\final_reports_20261011_193212. Commands, exit codes, JUnit XML, git diff/status, provenance recovery, source references and protected fingerprints are retained. See REPRODUCE.md for safe commands.

## Acceptance checklist

| Criterion | Status | Evidence/limitation |
|---|---|---|
| PX4/Gazebo operational | PASS | Existing native log and current passive topics; no new flight |
| MAVLink/QGroundControl operational | BLOCKED | Historical plan evidence exists; current plan upload/mission transport not demonstrated by ROS OFFBOARD |
| Micro XRCE-DDS/ROS communication | PASS | Continuous passive callbacks and protocol-2 status captured |
| Telemetry and vehicle commands demonstrated | PASS | Historical active logs; local publish is not proof of MAVLink plan upload |
| Takeoff/control/waypoints/return/landing/disarm/completion demonstrated | PASS | 12 recorded historical PASS outcomes; original provenance incomplete |
| Five repeated successful active missions | PASS | 12 historical PASS, zero new diagnostic PASS |
| Architecture/source/configuration evidence | PASS | Current hash/source/clock inventory, Mermaid and raw provenance references |
| 30 baseline records with prescribed provenance | BLOCKED | Historical strict 0/30; diagnostic strict 1/30; 29 missing |
| Required metrics measured or limitations explicitly accepted | BLOCKED | Missing latency/loss/wire/power measurements documented; no formal waiver or thresholds found |
| Timestamp safely understood and resolved | BLOCKED | Proximate mechanism proved; runtime cause unresolved; production fix not applied |
| Heading readiness operationally verified | BLOCKED | Grounded predicate understood; final alignment and successful new flight unverified |
| Raw data preserved | PASS | Stage A and final protected SHA-256 maps equal |
| Safety/full regression suite | PASS | 170 passed, 1 skipped; failures/errors zero |
| Package build | PASS | colcon affected-package build return code 0 |
| Reproducible validator/report generation | PASS | All per-cohort validators produce artifacts and return 2 for incomplete acceptance |

## Minimum remaining actions

1. Review and authorize a specific grounded simultaneous-clock/header experiment and coordinated native-clock proposal. Requires explicit approval for DDS setting changes/restart and any operational code change. Resolve or bound the runtime cause; retain all safety tests.
2. Separately authorize one supervised SITL bootstrap and full route to prove final heading, OFFBOARD, return, landing, disarm and completion. Archive native ULog/DDS/callback/ACK/evidence together. No such mission was performed here.
3. Define measurement acceptance thresholds or explicitly accept simulation limitations; collect correlated latency, sequence-based loss, interface byte evidence and calibrated physical power if required. Synthetic loopback tests do not satisfy these requirements.
4. Collect 30 provenance-complete real experiments under one documented configuration. The unchanged diagnostic study lacks 29; if the fix changes configuration, start a separate corrected study needing its own 30. Historical missing original metadata cannot be invented. Preserve every failure and all raw data.
5. Re-run validator/report generation and evaluate each acceptance criterion using that evidence. Phase 2 stays blocked until all mandatory requirements or explicit accepted limitations are met.

Immediate next action: review the NOT APPLIED grounded clock/header procedure in unapplied_clock_proposal.md. Reports-only authorization remains in force; no live operation will be started without a new explicit decision.

QGC finding: .plan export is an inspection artifact; the ROS OFFBOARD path does not implement MAVLink mission upload. See qgc_plan_findings.md. All 30 prior historical IDs and the one diagnostic ID match the prior manifests. All 45 historical records have some retained source byte matches, but zero regain complete original provenance.

The packaged portable timestamp analysis was actually rerun under WSL; all three regenerated analysis documents match the original conclusions after excluding platform-specific source path strings. reanalysis_verification.json records this check. The earlier candidate header patch is included for review only and is NOT APPLIED or operationally complete.
