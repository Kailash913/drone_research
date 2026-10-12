# Unsecured UAV baseline measurement

This extends the existing baseline_measurement ROS 2 Jazzy Python package. The
existing baseline_node executable and the explicitly enabled mission_node
--execute-sitl controller remain in place. The default mission_node invocation
is passive: it does not publish vehicle commands. It retains the numbered
preflight CSV log and also writes experiment files.

## Architecture

- mission_node.py: ROS 2 subscriptions, topic graph checks, CLI, timer, and
  existing opt-in mission controller.
- experiment_logger.py: existing append-only per-run event CSV.
- experiment.py: raw sample CSV, one-row-per-run summary CSV, JSON summary,
  experiment identity, and between-run aggregation.
- metrics.py: pure calculations and bounded streaming statistics.
- resource_monitor.py: read-only WSL process CPU/RSS sampling by current PID.
- cli.py: pure argument validation.
- config/baseline.yaml: example duration, interval, output path and topic names.

Runs use BASE-001 through BASE-030; each has a separate random run ID.
The next free experiment ID is chosen from existing JSON files unless explicitly
provided. No existing raw or JSON file is overwritten. baseline_summary.csv
is appended with one row per run. Batch mode repeats passive observations
sequentially. It never starts a flight.

## Build and inspect

These are commands to execute in the existing Ubuntu WSL environment. A successful
build or live run is not claimed by this README.

    cd ~/ros2_ws
    source /opt/ros/jazzy/setup.bash
    find src/baseline_measurement -maxdepth 4 -type f -print
    colcon list
    colcon build --packages-select baseline_measurement
    source install/setup.bash
    ros2 pkg executables baseline_measurement
    ros2 topic list -t
    ros2 node list
    ros2 pkg prefix px4_msgs

With the existing PX4 SITL, Gazebo and Micro XRCE-DDS Agent running, verify the
actual topics and types first. Then collect a passive run:

    ros2 run baseline_measurement mission_node --observe-seconds 60 \
      --sampling-interval 1.0 --experiment-id BASE-001 \
      --scenario telemetry_only --passive-only \
      --output-dir ~/uav_research/baseline

Optional configuration and passive repeat collection:

    ros2 run baseline_measurement mission_node --config \
      ~/ros2_ws/src/baseline_measurement/config/baseline.yaml \
      --experiment-id BASE-001 --run-count 30 --passive-only

CLI duration, interval and output directory override YAML values. --output
remains an alias of --output-dir. --observe-seconds 15 remains accepted.
Do not run baseline_node concurrently with an active mission; it publishes
an OffboardControlMode heartbeat. Only mission_node --execute-sitl enables
the pre-existing flight controller, and it rejects batch/passive flags.

## Output and metric semantics

Every run writes an experiment/run ID raw CSV, a JSON summary, and one row in
baseline_summary.csv. The earlier preflight CSV log remains. Batch runs also
write an aggregate JSON of run-level statistics. JSON includes environment,
topic names, topic and process availability, errors, definitions and raw file name.
UTC ISO 8601 timestamps identify records; elapsed time uses a host monotonic clock.

| Metric | Unit, source and calculation | Limit |
| --- | --- | --- |
| End-to-end latency | ms | Unavailable: no instrumented sender/receiver probe. |
| Telemetry one-way latency | ms | Unavailable: PX4 microsecond timestamps are retained, but no validated mapping to host monotonic time exists. |
| Command ACK latency | ms | Unavailable in passive runs; no command is sent. The existing ACK does not uniquely identify repeated requests. |
| Packet loss | percent; 100 times (sent minus received) divided by sent | Unavailable without sequence-numbered probes or packet capture. Callback gaps are not proven loss. |
| Payload throughput | Mbps; received ROS CDR bytes times 8 divided by whole observation seconds and 1e6 | Includes CDR encapsulation, excludes DDS/XRCE/network headers. Zero callbacks mean unavailable, not zero link capacity. |
| Bandwidth | Mbps | Physical link capacity unavailable in WSL SITL. Observed ROS CDR receive traffic rate is available in JSON and is not capacity. |
| CPU | percent of one logical CPU, psutil per WSL process; sampled at configured interval | A process or sum can exceed 100 percent. Windows QGC/host and physical UAV CPU are excluded. |
| Memory | MiB per WSL process RSS, plus decimal MB in summary | Summed RSS can count shared pages more than once. |
| Mission completion | seconds from monotonic start to completion; status from controller | Passive runs say not_attempted. The existing opt-in mission log retains terminal PASS/FAIL and duration. |
| Power/energy | W, Wh; valid connected PX4 BatteryStatus voltage times current, trapezoidal time integration | Simulated battery estimate only. If valid samples are absent, unavailable. Never infer UAV energy from CPU. |
| Telemetry rate | Hz; callback count divided by whole observation seconds | Callback delivery rate, not PX4 publication rate. |
| Inter-arrival jitter | ms; sample SD of adjacent callback monotonic intervals | Scheduler and middleware buffering contribute. This is not network latency. |
| Payload size | byte; serialized ROS CDR message length | ROS CDR representation, not wire size. |

Raw message samples are streamed to CSV. Mean, sample SD, min and max are exact
for accepted finite samples. Median uses a bounded 4096-sample reservoir and
is flagged approximate in JSON if a stream exceeds that size. Within-run time
samples get no 95 percent CI because callback samples are autocorrelated. The batch
aggregate computes a Student t interval over separate run-level values where
there are at least two runs. Failed/interrupted runs remain in the summary;
missing metric values remain empty.

## Validation

Run the two offline suites first:

    cd ~/ros2_ws/src/baseline_measurement
    python3 -m unittest discover -s test -p test_phase1.py -v
    python3 -m unittest discover -s test -p test_baseline_new.py -v

After a build, start the existing Gazebo/PX4/agent sessions using the project's
known procedure. Confirm PX4 and Gazebo processes, XRCE connection, topic types
and callback counts. Perform the passive command above, inspect its raw CSV,
summary CSV and JSON, then interrupt a second observation with Ctrl+C and verify
an interrupted JSON record. Repeat once to verify new run IDs and appended
summary rows. Confirm missing topics have available false and a reason.
Only after these checks may the pre-existing active mission procedure be
considered separately.

No PX4 firmware, Gazebo model, QGC setup, or XRCE architecture is changed here.

Preflight data validity requires fresh connected telemetry, PX4 health, valid
finite position/velocity/heading, no dead reckoning, failsafe, or detected reset.
`heading_ready` separately reports `heading_good_for_control`. After two seconds
of grounded health, the opt-in policy enters `WAIT_FOR_HEADING` (30 s timeout),
with no setpoints or commands until heading is ready. All yaw-bearing setpoint
states abort on heading loss. Passive mode observes only and never ticks the
mission policy or creates flight-control publishers. A grounded estimator that
requires in-flight magnetometer alignment can still block this controller; the
policy deliberately does not bypass that heading requirement.

## Current Phase 1 acceptance

See [PHASE1_ACCEPTANCE.md](PHASE1_ACCEPTANCE.md) and
[PHASE1_TEST_RESULTS.md](PHASE1_TEST_RESULTS.md). Five new passive demonstrations
are independently checked; active missions and QGC interaction remain unverified.
Two rejected captures demonstrate that source-clock regressions are detected.

Run all functional tests with:

```bash
bash ~/ros2_ws/src/baseline_measurement/test_phase1.sh
```

The existing `validate_baseline.sh` now runs the complete functional suite and
validates its bounded passive CSV, returning nonzero if telemetry never becomes
valid or a clock regression/control publication is recorded. Individual captures
can also be checked with `ros2 run baseline_measurement phase1_acceptance CSV`.

A standalone C++ subscription-only example is in `tools/telemetry_probe.cpp`.
With Jazzy and the overlay sourced:

```bash
cmake -S ~/ros2_ws/src/baseline_measurement/tools -B /tmp/phase1_cpp_build
cmake --build /tmp/phase1_cpp_build
timeout 12s /tmp/phase1_cpp_build/telemetry_probe
```

It observes vehicle status for five seconds and creates no flight-input publishers.
Measured zero CPU, memory and jitter remain zero; missing measurements remain
blank. Gazebo's Ruby launchers are included in process resource accounting.

## 11 October 2026 audit

See [PHASE1_VALIDATION.md](PHASE1_VALIDATION.md) for current dataset counts, timestamp evidence, reproducible validation, and remaining Phase 1 blockers. Earlier reports above are historical.
