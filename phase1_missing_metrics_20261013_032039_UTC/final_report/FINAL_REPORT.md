# Phase 1 missing-metrics evidence report

The objective remains incomplete. Five active missions were verified separately from 30 historical passive captures. Missing metrics remain blocked as listed below.

| Metric | Status | Value | Evidence / blocker |
|---|---|---|---|
| mission_completion_s | VALIDATED | 108.781 s | WSL simulation scope; historical configuration/version gaps remain; no independence CI See metric_summary.csv and results.json. |
| node_cpu_pct | VALIDATED | 9.96734 % of one logical CPU | WSL simulation scope; historical configuration/version gaps remain; no independence CI See metric_summary.csv and results.json. |
| system_cpu_pct | VALIDATED | 28.9498 % WSL guest | WSL simulation scope; historical configuration/version gaps remain; no independence CI See metric_summary.csv and results.json. |
| node_rss_mib | VALIDATED | 88.8972 MiB | WSL simulation scope; historical configuration/version gaps remain; no independence CI See metric_summary.csv and results.json. |
| rx_payload_mbps | VALIDATED | 0.114171 Mbit/s | WSL simulation scope; historical configuration/version gaps remain; no independence CI See metric_summary.csv and results.json. |
| tx_payload_mbps | VALIDATED | 0.00914212 Mbit/s | WSL simulation scope; historical configuration/version gaps remain; no independence CI See metric_summary.csv and results.json. |
| active_mission_success | VALIDATED | 5 successful missions | Five observed runs do not establish a general reliability probability See metric_summary.csv and results.json. |
| telemetry_rate:/fmu/out/battery_status_v1 | VALIDATED | 1.00017 Hz | Received callback rates; no transmitted-message denominator See metric_summary.csv and results.json. |
| inter_arrival:/fmu/out/battery_status_v1 | VALIDATED | 1000.19 ms | Summary across run-level statistics, not source-to-receiver latency See metric_summary.csv and results.json. |
| jitter:/fmu/out/battery_status_v1 | VALIDATED | 1.99168 ms | Summary across run-level statistics, not source-to-receiver latency See metric_summary.csv and results.json. |
| telemetry_rate:/fmu/out/estimator_status_flags | VALIDATED | 1.04798 Hz | Received callback rates; no transmitted-message denominator See metric_summary.csv and results.json. |
| inter_arrival:/fmu/out/estimator_status_flags | VALIDATED | 954.468 ms | Summary across run-level statistics, not source-to-receiver latency See metric_summary.csv and results.json. |
| jitter:/fmu/out/estimator_status_flags | VALIDATED | 192.982 ms | Summary across run-level statistics, not source-to-receiver latency See metric_summary.csv and results.json. |
| telemetry_rate:/fmu/out/vehicle_attitude | VALIDATED | 49.9445 Hz | Received callback rates; no transmitted-message denominator See metric_summary.csv and results.json. |
| inter_arrival:/fmu/out/vehicle_attitude | VALIDATED | 20.0024 ms | Summary across run-level statistics, not source-to-receiver latency See metric_summary.csv and results.json. |
| jitter:/fmu/out/vehicle_attitude | VALIDATED | 1.18311 ms | Summary across run-level statistics, not source-to-receiver latency See metric_summary.csv and results.json. |
| telemetry_rate:/fmu/out/vehicle_command_ack_v1 | VALIDATED | 0.0459646 Hz | Received callback rates; no transmitted-message denominator See metric_summary.csv and results.json. |
| inter_arrival:/fmu/out/vehicle_command_ack_v1 | VALIDATED | 26448 ms | Summary across run-level statistics, not source-to-receiver latency See metric_summary.csv and results.json. |
| jitter:/fmu/out/vehicle_command_ack_v1 | VALIDATED | 29406.2 ms | Summary across run-level statistics, not source-to-receiver latency See metric_summary.csv and results.json. |
| telemetry_rate:/fmu/out/vehicle_land_detected | VALIDATED | 1.06084 Hz | Received callback rates; no transmitted-message denominator See metric_summary.csv and results.json. |
| inter_arrival:/fmu/out/vehicle_land_detected | VALIDATED | 944.829 ms | Summary across run-level statistics, not source-to-receiver latency See metric_summary.csv and results.json. |
| jitter:/fmu/out/vehicle_land_detected | VALIDATED | 203.314 ms | Summary across run-level statistics, not source-to-receiver latency See metric_summary.csv and results.json. |
| telemetry_rate:/fmu/out/vehicle_local_position_v1 | VALIDATED | 49.9445 Hz | Received callback rates; no transmitted-message denominator See metric_summary.csv and results.json. |
| inter_arrival:/fmu/out/vehicle_local_position_v1 | VALIDATED | 20.0024 ms | Summary across run-level statistics, not source-to-receiver latency See metric_summary.csv and results.json. |
| jitter:/fmu/out/vehicle_local_position_v1 | VALIDATED | 1.15503 ms | Summary across run-level statistics, not source-to-receiver latency See metric_summary.csv and results.json. |
| telemetry_rate:/fmu/out/vehicle_status_v4 | VALIDATED | 2.0831 Hz | Received callback rates; no transmitted-message denominator See metric_summary.csv and results.json. |
| inter_arrival:/fmu/out/vehicle_status_v4 | VALIDATED | 480.767 ms | Summary across run-level statistics, not source-to-receiver latency See metric_summary.csv and results.json. |
| jitter:/fmu/out/vehicle_status_v4 | VALIDATED | 91.0418 ms | Summary across run-level statistics, not source-to-receiver latency See metric_summary.csv and results.json. |
| command_latency | NOT_MEASURED | N/A | No unique request ID/source identity; future authorized instrumented run needed for candidates and PX4-side evidence for confirmed association See metric_summary.csv and results.json. |
| command_candidate_interval | NOT_MEASURED | N/A | Historical runs predate publication monotonic_ns evidence; do not reconstruct from delayed logger events See metric_summary.csv and results.json. |
| telemetry_latency | NOT_MEASURED | N/A | Native-to-host clock scale/offset validity interval and independent uncertainty validation absent; simultaneous native ULog/calibration needed See metric_summary.csv and results.json. |
| end_to_end_latency | NOT_MEASURED | N/A | Remote application endpoint with unique echoed request ID and common-clock evidence required; localhost bench is not UAV E2E See metric_summary.csv and results.json. |
| application_sequence_loss | NOT_MEASURED | N/A | PX4 path lacks observed sender and receiver sequence IDs and closed drain window See metric_summary.csv and results.json. |
| wire_packet_loss | NOT_MEASURED | N/A | Wire sender/receiver identities and capture/drop accounting at both endpoints required; a single capture is not a loss denominator See metric_summary.csv and results.json. |
| trajectory_rmse | NOT_MEASURED | N/A | Native estimator and Gazebo-derived truth logs exist, but pose event-time uncertainty and frame/origin mapping are not independently verified; further controlled flight requires permission See metric_summary.csv and results.json. |
| physical_power | UNAVAILABLE_IN_CURRENT_SETUP | N/A | Calibrated physical UAV voltage/current instrument required See metric_summary.csv and results.json. |
| physical_energy | UNAVAILABLE_IN_CURRENT_SETUP | N/A | Physical hardware and calibrated synchronized power window required See metric_summary.csv and results.json. |
| simulated_power | UNAVAILABLE_IN_CURRENT_SETUP | N/A | Battery simulator uses current_a=-1; no credible current/power model See metric_summary.csv and results.json. |
| simulated_energy | UNAVAILABLE_IN_CURRENT_SETUP | N/A | Invalid current must not be replaced with zero; model or sensor needed See metric_summary.csv and results.json. |
| physical_link_capacity | UNAVAILABLE_IN_CURRENT_SETUP | N/A | WSL loopback offered traffic cannot measure radio link capacity See metric_summary.csv and results.json. |
| wire_throughput_current | NOT_MEASURED | N/A | tcpdump capture permission denied; dumpcap execution denied; sudo requires a password See metric_summary.csv and results.json. |
| historical_run_provenance | MEASURED_UNVALIDATED | N/A | Historical config file/hash and versions are missing in mission CSV metadata; ULog overlap is not independently proven unique association See metric_summary.csv and results.json. |
| wire_throughput_historical | MEASURED_UNVALIDATED | 580214 bit/s | Both directions, WSL loopback; excludes physical radio. Historical capture window, interface, filter and drops are not recorded See metric_summary.csv and results.json. |

## Run provenance

Original experiment IDs, configuration paths/hashes and PX4/Gazebo version evidence are missing in all five active logs. Source byte hashes and original run IDs are retained; current environment details do not establish historical versions. See active_runs.json.

## Acceptance gate

requirements_to_evidence.csv records implementation, raw source, acceptance criterion, validation method and remaining blockers. No candidate interval is accepted as validated latency. No physical-power or radio-link claim is made.

## Reproduction

Source the ROS Jazzy and px4_msgs workspace environments, then from the package run:

```bash
PYTHONDONTWRITEBYTECODE=1 PYTHONPATH="$PWD:$PYTHONPATH" python3 -m baseline_measurement.metrics_audit --workspace /home/kailash/ros2_ws --output /tmp/new_phase1_report
```

To include the new passive and wire records, place their directories beside the new report directory, as in this evidence bundle. Inputs are never rewritten.
