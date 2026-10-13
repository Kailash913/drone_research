# Audit findings and plan

The audit findings and implementation plan were presented in chat before source modifications.
The initial Git status and source hashes are preserved in git_status_before.txt and source_before.json.

Five active mission CSVs were located in phase1_active_run_001 through phase1_active_run_005.
The phase1_baseline_30 folder contains 30 passive preflight CSVs and separate Experiment raw samples.
The existing phase1_audit_20261012 report was inspected but never used in place of raw validation.
phase1_clock_diagnostics contains passive source-clock data, not successful autonomous missions.
The configured uav_research/baseline output is absent; ros2_ws/baseline_results holds the PCAP only.

Already collected / requiring revalidation: active mission outcomes and duration, host CPU/RSS,
callback rates and intervals, CDR serialized payload bytes. Their raw-row and summary cross-checks
are recorded independently in final_report/active_runs.json. Per-run means remain the statistical
unit; historical provenance gaps are not repaired by current settings.

Initially unmeasured: command candidate intervals, uniquely correlated command/E2E latency,
independently mapped telemetry latency, PX4 sender/receiver sequence loss, validated capture
throughput and independently aligned flight RMSE. Historical command events predate monotonic_ns
publication evidence. Historical PCAP packet counts and lengths exist but capture metadata does not.

Unavailable in current setup: physical radio capacity and physical UAV power/energy. Inspection of
BatterySimulator.cpp found current=-1 (no current sensor). New passive measurements and native
flight ULogs subsequently confirmed the sentinel. Valid voltage alone is not measured power.

Reused components: RunLog.row and its unchanged detail column; dataset.inspect_csv; describe;
provenance.recover; clock_probe and SyncEvidence; correlated_latency; sequence_loss;
captured_traffic; transport_probe. New code adds strict trajectory validation, JSONL recording
of independent streams, native-log export, bounded capture and an offline requirements matrix.
No controller policy, flight states, guards, parameters, firmware or DDS settings were changed.

The bounded passive collectors were actually run against the existing x500_0 simulation.
A fresh wire capture was attempted without changing permissions; tcpdump/dumpcap/sudo could not
obtain the required existing access. Those failures are retained, not hidden or retried as root
with an interactive password. No new active mission was authorized or executed.

See final_report/requirements_to_evidence.csv for every metric and its acceptance criterion.
