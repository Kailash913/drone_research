# Phase 1 validation audit — 11 October 2026

Phase 1 remains **BLOCKED**. Phase 2 is not ready. This audit validates existing
records and adds reproducible measurement diagnostics. No new autonomous mission
was launched. No flight policy, waypoints, thresholds, reset guard, PX4 parameters,
system component or cryptographic dependency was changed.

## Inspection and preservation

The Git root is `/home/kailash/ros2_ws`, branch `master`, commit
`5affc1548a85c081b8c37e068a0ea9ffca9081ef`. There were extensive pre-existing
source/build/install/results changes and untracked files. Initial status, staged
and unstaged diffs, inventory and test logs are in
`test-output/phase1_audit_20261011_163757/`. Two new inspection helper files existed
before the first Linux Git snapshot; the production package was still unchanged.
No changes were discarded, staged, committed or reset. A separate local snapshot
was also preserved before implementation.

Inspected: package metadata/entry points, YAML, source and installed package,
ROS interfaces, mission policy, receive callbacks, logger, process monitor,
passive experiment recorder, acceptance validator, all existing tests and notes,
45 active run CSVs, three preflight CSVs, two passive JSON/raw pairs, exported QGC
plans, and PX4 timestamp/serializer/time-sync source. No package launch files are
present; the established interface is `ros2 run` and the existing VS Code configs.

The implementation plan was to preserve working control, validate records before
counting them, add an immutable importer and separate diagnostic recorder, add
regressions for the existing safety policy, then build/test and report gaps.
New code is confined to dataset import, passive diagnostics, context snapshots,
tests and validation helpers. `setup.py` registers three new executables. The
README points to this audit; historical reports are retained as history.

Protected controller/config hashes:

| File | SHA-256 |
|---|---|
| mission_node.py | `8f80d711730e9b5c868d2aafe9bf3c583362813c8461340ce62a6611a59322b7` |
| mission_state.py | `261c1558540238706b1010523424d400178304608ec4047bd10ea02d4985a98a` |
| config/baseline.yaml | `24b0e3e7aa3123036167af151c727bcc0c4820a723c222d76b4a814f2d4703df` |

Verification hashes every existing results file before/after execution, including
CSV, JSON, plans and logs. It also checks the three protected files above.

## Current environment and architecture

| Component | Observed inventory |
|---|---|
| Guest OS | Ubuntu 24.04, WSL |
| ROS | Jazzy; rclpy `7.1.11-1noble.20260615.133206`; ros2cli `0.32.10-1noble.20260615.145444` |
| Python | `/usr/bin/python3`, 3.12.3 |
| PX4 | `v1.18.0-beta1-213-g43cccdea0e`; clean PX4 tree, branch main behind remote |
| Gazebo | `gz sim --versions` reports **8.15.0**, unlike the earlier 8.14.0 observation |
| Agent | Existing `MicroXRCEAgent udp4 -p 8888`, PID 4216 at initial inventory |
| Simulator | One PX4 PID 46593; Gazebo server/client PIDs 46767/46768, x500/default world |
| QGC | Running Windows QGroundControl Daily; exact release version not obtained |
| Package | `/home/kailash/ros2_ws/install/baseline_measurement`; source in `src/baseline_measurement` |

These are current versions, not retrospective attestations for every older run.
See `docs/architecture.mmd` for the diagram source. Gazebo feeds PX4 simulation
sensors; MAVLink connects QGC; uORB passes through PX4's XRCE client and UDP agent
to ROS DDS subscriptions. Only explicitly enabled mission_node creates flight
publishers. Offline validation never imports ROS or launches a flight. The
clock probe creates subscriptions only.

QGC inspection showed a loaded route, connected vehicle telemetry, **Not Ready /
Offboard** at ground level. The passive status capture reported disarmed
`arming_state=1`, `nav_state=14`, `failsafe=false`. This establishes observation
of the connection, not readiness for a new flight. No QGC mode/arm/start action
was taken. Earlier mission repair evidence contains a plan upload/readback, but
that was not repeated during this audit.

## Mission audit

The current preferred path is:

`WAIT_FOR_PX4 → WAIT_FOR_HEALTH → WAIT_FOR_HEADING → AUTO_TAKEOFF_REQUEST →
AUTO_ARM → TAKEOFF → WAIT_FOR_HEADING → PREFLIGHT_SETPOINT → OFFBOARD →
WAYPOINT_1 → WAYPOINT_2 → WAYPOINT_3 → RETURN_HOME → LAND → DISARM →
RELEASE_CONTROL → COMPLETE`.

The fallback path, when no Auto bootstrap is available but final heading is
ready, streams grounded preflight setpoints, confirms Offboard, arms, and then
performs takeoff. Initial Auto readiness needs fresh estimator flags with yaw
alignment and no reported magnetic/heading faults, plus a global altitude
reference. Final `heading_good_for_control` remains required before absolute yaw
control in Offboard. PX4 Auto handles its initial yaw alignment; that existing
behaviour is preserved.

All five configured stages must be recorded in order. Each uses a 15-second
quintic position profile, 0.7 m endpoint tolerance, speed at most 0.5 m/s and
2-second dwell. Offsets from measured home are `(0,0,-10)`, `(20,0,-10)`,
`(20,20,-10)`, `(0,20,-10)`, `(0,0,-10)` in local NED metres. Return-home is a
local leg, not the PX4 RTL mode. Landing requires a maintained landed flag;
disarming must be observed; release-control requires landed, disarmed and Hold.
Only then does the policy mark COMPLETE/PASS.

Global timeout is 480 seconds; source freshness threshold is 2 seconds; scheduling
gap limit is 250 ms. Invalid estimates, heading/health loss, source regressions,
counter changes outside expected Auto yaw alignment, competition and failsafe
remain guarded. Failure latches FAILSAFE, stops normal setpoints and attempts one
LAND if the controller owns arming. It never force-disarms in air. Stream recovery
does not turn a failed mission into PASS. Existing completion-only ground
handling can rebase source freshness after the complete route and confirmed
touchdown, while still auditing/latching the anomaly and enforcing other guards.

The importer requires ordered stage-reached, LANDED, DISARM, RELEASE_CONTROL and
COMPLETE events, terminal success=True/state=COMPLETE, and no failure events or
reason. This is controller-log evidence, not independent external replay of every
flight. Passive captures are always NOT_ATTEMPTED.

ROS Offboard control does not automatically upload a MAVLink mission to QGC.
`qgc_plan.py` exports a `.plan` after home capture. To display it as a native
mission, load/upload/read back that plan in QGC separately while disarmed, after
human authorization; do not start QGC's native mission alongside ROS Offboard.

## Timestamp investigation and limits

The observed failure trigger is proven: `receive()` compares `msg.timestamp`
against its per-topic high-water mark, logs `source_clock_reset`, sets `reset`,
and the policy transitions to FAILSAFE outside grounded completion. Serialization
logs the same `msg.timestamp`. Neither `timestamp_sample` nor estimator flags/
reset counters/session offsets are preserved in the historical run CSV schema.

The checked PX4 message definitions describe timestamp as microseconds since
system start and timestamp_sample as raw-data time. EKF2 populates those fields
from its internal sample/publication clocks. However, the actual generated
`build/px4_sitl_default/uORB/ucdr/vehicle_local_position.h` serializer adds
`time_offset` to **both** fields. `Tools/msg/templates/ucdr/msg.h.em` generates this
logic. `SendTopicsSubs::update()` snapshots `session->time_offset / 1000` and
passes it to serialization. `uxrce_dds_client.cpp::on_time()` sets the offset
from Timesync; session initialization/no-sync paths can use zero. Thus a field
documented as boot-relative in uORB can be delivered offset-adjusted through DDS.

This is consistent with the documented automatic bridge synchronization and
`/fmu/out/timesync_status` interface in the
[PX4 ROS 2 user guide](https://docs.px4.io/v1.18/en/ros2/user_guide).
The local revision and generated files, not a current upstream implementation,
are the primary evidence for this audit.

Confirmed raw examples (line numbers count header as line 1):

| Run | Failure stage | Raw line | Observed delivered timestamp drop, µs |
|---|---|---:|---|
| 015 | WAYPOINT_3 | 9101 / 9103 | Position `1791725963111899 → 89180000`; attitude `→ 89184000` |
| 021 | LAND | 13142 | Attitude `1791728528140349 → 2536864000` |
| 043 | LAND | 14115 / 14117 | Position `1791735438286172 → 511880000`; attitude `1791735438290172 → 511880000` |
| 045 | WAYPOINT_2 | 6081 / 6083 | Position `1791735692265668 → 754016000`; attitude `→ 754020000` |

Run 045 also has a 226 µs status reversal after failure; not every discontinuity
is an epoch-to-boot drop. Exact native integers, raw file hashes, line numbers
and event evidence are preserved in the manifest and timestamp evidence JSON.
There are 24 active failures with the combined reset reason and one stale/link
failure. The combined error wording does **not** establish an estimator reset.

**The underlying cause of the intermittent offset/domain changes remains
unproven.** The historical CSVs lack synchronized native uORB timestamps,
session-offset values and complete reset counters. They cannot establish whether
an agent reconnect, session-offset transition, ordering issue or estimator event
caused each sample. No clock-domain normalization or isolated-sample tolerance was
added to flight control. The conservative response remains in effect.

The new `clock_probe` retains local monotonic reception and elapsed time,
timestamp, timestamp_sample, position/velocity/yaw/quaternion reset counters,
heading readiness, estimator flags, land/status and TimesyncStatus fields. It
records source-order events separately from independently observed counter
changes. Receipt freshness is independent of source ordering in this diagnostic
component; the existing controller still requires advancing source stamps. Missing
or repeated diagnostic source stamps cannot erase receipt-age checks. Time-sync
RTT is not labeled command or mission end-to-end latency.

## Dataset, ID allocation and statistical results

There are **45 unique complete active CSV records: 12 PASS and 33 FAIL**, spanning
five recorded configuration groups. Successful runs are 010, 012, 016, 017, 020,
025, 028, 034, 036, 037, 042 and 044. At least five successful repeated missions
are therefore documented by controller logs. Files 010–045 form the largest
group: **12/36 successes (33.33%)**. Overall descriptive success is 12/45 (26.67%),
but metrics are not pooled across the five materially different source groups.

The importer assigns BASE-001 through BASE-030 to the earliest thirty attempts
in the largest recorded configuration group, including failures (runs 010–039).
This is a separate **retrospective active study namespace**. Existing passive
BASE-001/BASE-002 JSONs keep their original identities and are excluded from that
cohort. Each imported run has an identity based on exact source-file SHA-256;
original names/bytes are unchanged. Passes are not preferentially selected.
Use `--prior-manifest` on later validation to preserve cohort/ID reservations;
new output directories are exclusively created. Extra active attempts stay in
the manifest with no new study slot. Duplicate files are excluded by SHA-256.
Three preflight CSVs and two passive JSON/raw pairs are listed separately, never
summed as five independent experiments because the formats can cover one capture.

Thirty assigned study records contain usable partial measurements; **zero meet
the validator's strict historical metadata profile**. Original active metadata
lacks explicit run/experiment IDs, config filename/hash, and verified PX4/Gazebo
versions for each run. Retrospective IDs solve traceability, not historical
attestation. Current context snapshots must not be used to invent old config or
version values. This zero is a provenance gap, not a claim that all CPU/traffic
measurements are unusable.

For the current 36-run group: successful mission duration (n=12) has mean
109.186 s, median 108.926 s, sample SD 0.869205 s, min 108.618 s, max 111.815 s.
Mean RX CDR throughput across 36 attempts is 0.113007 Mbit/s; mean process CPU
is 11.1922% of one logical core, and mean process RSS is 88.6317 MiB. These are
means of per-run means, not pooled callback samples. Failed attempt duration is
reported separately from successful completion. See generated summary for every
metric's n, missing count, mean, median, SD, min and max, and manifest observation
hashes for provenance. Confidence intervals are withheld because run independence
and full configuration equivalence are not established; shared SITL sessions and
serial retries can correlate observations.

## Metric definitions and acceptance checks

All observations use the whole logger-initialization-to-terminal-result window
unless stated otherwise. Reception/interval/duration clocks are local monotonic;
UTC identifies records; delivered PX4 timestamps remain native delivered values.
Missing or invalid values are null/blank, excluded from aggregates, never zero.
Run-level resource means are unweighted means of approximately 1 Hz samples;
actual intervals and source lines are retained in the manifest.

| Metric | Status / units | Collection and acceptance test | Limit or next instrumentation |
|---|---|---|---|
| End-to-end latency | NOT MEASURED, ms | No validated endpoint pairing exists; validator keeps null | Correlated sender/receiver probes and independently verified common-clock error bound |
| Telemetry latency | NOT MEASURED, ms | Source/host subtraction prohibited without mapping | Paired uORB/ROS receive evidence and timesync uncertainty; a timestamp magnitude is not proof of mapping |
| Command latency | NOT MEASURED, ms | ACK has no unique request ID; no timing inferred from mission duration | Authorized correlated command/state/ACK instrumentation and clock/correlation validation |
| Packet loss | NOT MEASURED, % | No reliable sent/expected transport packet denominator; null | Sequence-counted endpoints or validated transport capture; rate caps are not expected packet counts |
| RX payload throughput | MEASURED LIMITED, Mbit/s | Raw CDR byte sums and callback counts must match topic summary; bytes×8/duration/1e6 | Application representation includes CDR encapsulation, excludes network/XRCE headers |
| TX payload throughput | MEASURED LIMITED, Mbit/s | Publish-call byte sum/window, separate direction | Local attempts, not confirmed PX4 receipt; absent TX is unavailable, not measured zero |
| Wire bandwidth/capacity | NOT MEASURED, Mbit/s | No wire data/capacity source; null | Network capture accounting for direction, retransmissions and protocol overhead; capacity needs a separate defined experiment |
| Node CPU | MEASURED LIMITED, % one logical CPU | Finite nonnegative primed psutil interval samples, actual sampling intervals logged | WSL mission process only; can exceed 100%; host/QGC/GPU excluded |
| System CPU | MEASURED LIMITED, % | Finite primed WSL guest psutil samples | WSL guest scope; not physical autopilot CPU |
| Node memory | MEASURED LIMITED, MiB RSS | Finite nonnegative resident bytes/2²⁰ samples | Mission process RSS, not full host/system memory |
| Mission completion | MEASURED, seconds, PASS only | Ordered complete route/land/disarm/release events plus terminal COMPLETE/PASS | Includes preflight wall time; not flight-only or Gazebo simulation time |
| Attempt duration | MEASURED, seconds | Finite positive terminal duration agrees with elapsed row | Failed/passive durations must not be relabeled mission completion |
| Energy/power | NOT MEASURED physical Wh/W | No calibrated physical source | Battery current/voltage with timestamped calibrated sensors or power analyzer; simulated estimate separately labeled |
| Topic delivery rate | MEASURED LIMITED, Hz | Count/whole observation window; recomputed from raw rows | ROS callback delivery frequency, not throughput or guaranteed source publication frequency |
| Inter-arrival jitter | MEASURED LIMITED, ms | Adjacent monotonic callback spacing; sample SD for n≥2 | Includes scheduling/buffering; not communication latency |

The legacy passive Experiment implementation can integrate valid simulated
BatteryStatus voltage×current. It must remain labeled simulated energy, not
physical UAV consumption. Existing active CSVs record no voltage/current energy
samples. Process CPU cannot substitute for UAV energy.

## Reproduction and evidence collection

Keep existing operational sessions; do not start duplicate PX4/agent/controller
processes. If stopped, the observed existing startup commands are:

```bash
# Separate WSL sessions; startup is not an instruction to arm.
cd ~/PX4-Autopilot
make px4_sitl gz_x500
MicroXRCEAgent udp4 -p 8888
```

Open the existing QGroundControl Windows application and verify MAVLink telemetry.
Inspect PX4 `uxrce_dds_client status`, `mavlink status` and Offboard-loss parameters
in the existing PX4 console; record actual outputs before another active batch.
No such parameter changes are made here.

```bash
source /opt/ros/jazzy/setup.bash
cd ~/ros2_ws
colcon build --packages-select baseline_measurement
source install/setup.bash
ros2 pkg executables baseline_measurement
ros2 topic list -t

cd ~/ros2_ws/src/baseline_measurement
python3 -m pytest test -q --ignore=test/test_flake8.py \
  --ignore=test/test_pep257.py --ignore=test/test_copyright.py
python3 -m pytest test -q  # Full suite also reports existing lint failures.

ros2 run baseline_measurement baseline_dataset \
  --input ~/ros2_ws/baseline_results \
  --output ~/ros2_ws/phase1_report_$(date -u +%Y%m%dT%H%M%SZ)
# Current return code 2 means dataset acceptance gaps, not importer failure.
# Later runs: add --prior-manifest /path/to/previous/manifest.json.

# Subscription only: separate from a flight and never counted as active PASS.
ros2 run baseline_measurement clock_probe --seconds 60 \
  --config ~/ros2_ws/src/baseline_measurement/config/baseline.yaml \
  --output ~/ros2_ws/phase1_clock_evidence

ros2 run baseline_measurement record_context \
  --config ~/ros2_ws/src/baseline_measurement/config/baseline.yaml \
  --output ~/ros2_ws/phase1_context

ros2 run baseline_measurement mission_node --config \
  ~/ros2_ws/src/baseline_measurement/config/baseline.yaml --passive-only \
  --output-dir ~/ros2_ws/phase1_passive
```

The YAML defaults to `~/uav_research/baseline`, so the explicit output override
above is deliberate. It configures observation duration/interval/topics, not the
hardcoded mission route. Active CLI rejects batch/passive combinations; default
mission_node execution is passive. **Only after a human decides to launch one
active mission**, confirms disarmed/grounded/healthy status, one controller and
known PX4 link-loss behaviour, the existing command is:

```bash
ros2 run baseline_measurement mission_node --execute-sitl
```

Never automate a new flight batch from the validator. Before an approved future
run, collect context and a simultaneous passive clock probe; record the run's
source file/hash in an experiment envelope. Retain the pre-run config snapshot
and environment, then attach final outcome and raw paths without overwriting.
Historical context remains labeled retrospective. A full new measurement cohort
requires a defined scenario, stable configuration, independence/reset protocol
and missing-latency/loss instrumentation decision.

Capture real terminal screenshots of version inventory, command/CLI, ROS topic
rates, test summary, build and validator output; capture QGC/Gazebo state before
and after any human-authorized demonstration. Keep timestamps and raw console
logs, source/config hashes and filenames alongside images. Screenshots are
supporting evidence, not replacements for raw data. No new flight demonstration
screenshots are claimed by this audit.

## Tests, acceptance and remaining work

The initial full suite was 78 passed, 1 skipped, 2 failed (flake8 and pep257).
New tests cover source ordering, epoch/boot mismatch, isolated/persistent
anomalies, local monotonic stale checks, repeated/zero/missing timestamps,
real reset counters, airborne loss/recovery, completion-ground handling,
failsafe preservation, native uint64 precision and diagnostic event logging.
Dataset tests cover safe completion evidence, duplicates, passive exclusion,
partial/invalid records, zero versus missing measurements, summary consistency,
ID persistence and exclusive output. Fixtures are unit-test data, never dataset
experiments. Functional tests and package build were executed in Ubuntu through
VS Code's existing Linux debugger. No flight publishers were created; the probe
creates zero publishers. Exact final results are in the latest
`test-output/phase1_verify_*/verification.json` and JUnit files.

| Acceptance item | Status and evidence |
|---|---|
| Gazebo/PX4 operational | PASS — actual processes, versions and live telemetry |
| MAVLink/QGC operational | PASS — connected UI telemetry and loaded route; currently Not Ready is not flight-ready acceptance |
| XRCE/ROS communication | PASS — discovered real topics and fresh passive subscriptions |
| Telemetry and commands demonstrated | PASS — live telemetry plus historical command/ACK and mission records |
| Takeoff/control/waypoints/return/landing | PASS — 12 complete controller-log records; no new mission during audit |
| Five successful repeated active missions | PASS — 12 documented; full mission events required |
| Architecture/source/config evidence | PASS for current snapshot/diagram; historical per-run config evidence missing |
| Thirty records against full criteria | BLOCKED — 30 partial study slots; zero strict historical profiles |
| Raw measurements preserved | PASS — immutable importer and before/after hashes |
| Metrics measured or explicitly unavailable | PASS documentation; latency/loss/bandwidth/physical energy NOT MEASURED |
| Timestamp issue investigated | PASS investigation; underlying discontinuity cause/fix BLOCKED |
| Safety regressions | PASS — functional regression evidence; full lint suite is separate |
| Package build | PASS — affected package colcon build |
| Dataset/report reproducibility | PASS execution — exclusive outputs and installed CLI; acceptance exits 2 for real gaps |

Next steps: correlate native uORB/ULog timestamps, reset counters and XRCE session
offset/reconnect evidence during a separately approved observation/mission;
determine why offset-domain transitions occur before proposing any guard change;
retain current conservative safety response meanwhile. Resolve existing lint
debt without rewriting flight code/backups merely to mask failures. Design and
validate endpoint/clock/packet instrumentation, preserve full per-run context,
and complete a defensible 30-experiment cohort under agreed criteria. Physical
energy remains unavailable without defensible instrumentation. Phase 2 stays
blocked until Phase 1 acceptance gaps are resolved.

## Final execution evidence

Final verification: `test-output/phase1_verify_20261011_170616/`. **105 functional tests passed; eight new Python files passed scoped flake8.** Full suite: 105 passed, 1 skipped, 2 failed (existing flake8: 232 findings; existing pep257). Build: one package finished in 5.10 seconds. Installed validator generated its reports and exited 2 for the documented dataset gaps. Protected raw/controller/config hashes were unchanged.

Final passive clock capture: 20.012468 s, zero flight publishers/commands. Observed callback rates: position 49.76897 Hz; attitude 49.81894 Hz; status 1.94879 Hz. These observations are not fixed acceptance thresholds. All six diagnostic topics were locally fresh at capture end.
