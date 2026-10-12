# Phase 1 baseline validation

Unique active attempts: 0; PASS: 0; FAIL: 0.
Complete active measurement records: 0; strictly valid historical experiments: 0.
BASE-001..030 assigned: 0; complete study records: 0; strict study validity: 0/30.

Mission outcome is independent of measurement usefulness. FAIL attempts can have valid CPU/RSS/payload observations. Passive captures never count as successful flights.

## Configuration groups

## Limitations

- No new autonomous mission was launched by this validator.
- PASS requires controller COMPLETE plus ordered route/landing/disarm/release events, not independent external validation of every run.
- Passive JSON and preflight CSV can describe the same capture; their counts are not summed as experiments.
- No historical configuration hash/version is fabricated from current files.
- Thirty partial measurement records do not satisfy complete historical metadata or unavailable required metrics.
- No confidence intervals: independence and full configuration equivalence unverified.
