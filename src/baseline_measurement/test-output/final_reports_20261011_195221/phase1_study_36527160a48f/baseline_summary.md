# Phase 1 baseline validation

Unique active attempts: 1; PASS: 0; FAIL: 1.
Complete active measurement records: 1; strict provenance-valid records: 1.
BASE-001..030 assigned: 1; complete study records: 1; strict study validity: 1/30.

Mission outcome is independent of measurement usefulness. FAIL attempts can have valid CPU/RSS/payload observations. Passive captures never count as successful flights.

## Configuration groups

Group `c2fa08f91ce2`: 0/1 active successes (0.00%).

| Metric | Valid n | Missing n | Mean | Median | SD | Min | Max | Units |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| end_to_end_latency_ms | 0 | 1 | N/A | N/A | N/A | N/A | N/A | ms |
| telemetry_latency_ms | 0 | 1 | N/A | N/A | N/A | N/A | N/A | ms |
| command_latency_ms | 0 | 1 | N/A | N/A | N/A | N/A | N/A | ms |
| packet_loss_pct | 0 | 1 | N/A | N/A | N/A | N/A | N/A | % |
| rx_payload_mbps | 1 | 0 | 0.090341 | 0.090341 | N/A | 0.090341 | 0.090341 | Mbit/s |
| tx_payload_mbps | 1 | 0 | 7.45771e-05 | 7.45771e-05 | N/A | 7.45771e-05 | 7.45771e-05 | Mbit/s |
| bandwidth_mbps | 0 | 1 | N/A | N/A | N/A | N/A | N/A | Mbit/s |
| node_cpu_pct | 1 | 0 | 19.5167 | 19.5167 | N/A | 19.5167 | 19.5167 | % of one logical CPU |
| system_cpu_pct | 1 | 0 | 61.7167 | 61.7167 | N/A | 61.7167 | 61.7167 | % |
| node_rss_mib | 1 | 0 | 87.8641 | 87.8641 | N/A | 87.8641 | 87.8641 | MiB |
| mission_completion_s | 0 | 1 | N/A | N/A | N/A | N/A | N/A | s |
| attempt_duration_s | 1 | 0 | 19.3089 | 19.3089 | N/A | 19.3089 | 19.3089 | s |
| energy_wh | 0 | 1 | N/A | N/A | N/A | N/A | N/A | Wh |
| power_w | 0 | 1 | N/A | N/A | N/A | N/A | N/A | W |

## Limitations

- No new autonomous mission was launched by this validator.
- PASS requires controller COMPLETE plus ordered route/landing/disarm/release events, not independent external validation of every run.
- Passive JSON and preflight CSV can describe the same capture; their counts are not summed as experiments.
- No historical configuration hash/version is fabricated from current files.
- Thirty partial measurement records do not satisfy complete historical metadata or unavailable required metrics.
- No confidence intervals: independence and full configuration equivalence unverified.
