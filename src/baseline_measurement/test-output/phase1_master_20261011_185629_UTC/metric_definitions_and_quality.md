# Metric definitions, quality and closure evidence

All unavailable values are null and excluded, never zero. Per-configuration counts, mean, median, sample SD, min/max are in the cohort manifests. 95% confidence intervals are withheld because independence and full configuration equivalence are unverified. Small samples and repeated SITL observations do not justify universal performance claims. Failed attempts can provide payload/resource observations but no successful mission duration.

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

Diagnostic resource capture contains 18 retained valid samples with 17 observed intervals: mean 1.023586 s, range 0.994792–1.057056 s. Per-run sample lines and intervals are retained in metric_quality.json. Configuration groups use known recorded fields; unknown historical environment equivalence remains a limitation.
