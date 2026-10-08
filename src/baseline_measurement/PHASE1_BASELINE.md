# Phase 1 baseline implementation — not yet flight validated

Date: 8 October 2026. Only the unsecured ROS 2 baseline is implemented.
No security layer, simulator parameters, PX4 source, px4_msgs definitions,
Micro XRCE-DDS settings, or QGC settings were changed.

## Current result

The existing WSL package was inspected and extended directly at
`/home/kailash/ros2_ws/src/baseline_measurement`.
The installed message definitions were read from `install/px4_msgs/share/px4_msgs/msg`.
Python syntax and ROS-independent policy/logger tests were run using Python 3.12 on
Windows. These checks do not prove ROS compatibility, build success, or flight safety.
The WSL execution tool returns `Wsl/E_ACCESSDENIED`, so colcon build, live ROS
discovery/telemetry checks, and controlled missions have NOT been executed.
No vehicle command was sent during this work. No experimental run CSV was generated.

Desktop observations: PyCharm's PX4 console displayed “Ready for takeoff”; QGC
displayed Ready / Hold and ground-level telemetry; Gazebo displayed `x500_0`
in the `default` world. These are observations, not proof of end-to-end mission operation.

## Files and preservation

- `baseline_measurement/baseline_node.py`: restored the existing working build/install
  version into source. It contains the BEST_EFFORT subscriptions missing from the old
  source. Source, build and install had diverged. Its legacy behavior is retained.
- `baseline_measurement/mission_state.py`: ROS-independent finite state machine.
- `baseline_measurement/mission_node.py`: ROS adapter, explicit mission entry point,
  passive observation mode, and integrated measurement/resource sampling.
- `baseline_measurement/experiment_logger.py`: exclusive numbered CSVs and statistics.
- `test/test_phase1.py`: offline policy and logger tests.
- `setup.py`: new `mission_node` executable and psutil dependency.
- `package.xml`: python3-psutil runtime dependency.
- `validate_baseline.sh`: build, offline tests, interface/graph inspection and passive observation.
- `PHASE1_BASELINE.md`: this report.

Backup: `/home/kailash/ros2_ws/baseline_backups/20261008_214651/` contains
`source_original/` and `working_baseline_node.py`. The restored legacy node matches
the previously installed working file. Do not edit `build/` or `install/` copies;
make future changes in `src/` and rebuild.

## Nodes, interfaces and QoS

The new executable creates `baseline_preflight` by default and `baseline_mission`
only with `--execute-sitl`. Measurements are integrated into that same process so
its CPU and memory measurements describe the mission process. There is no separate
measurement node or second autonomous controller. The old `baseline_node` entry
point remains available, but must not run alongside a mission: its 2 Hz heartbeat
would conflict with the new controller. The mission detects extra ROS publishers
and refuses/prohibits normal progression.

| Direction | Topic | px4_msgs interface |
| --- | --- | --- |
| Publish, mission mode only | `/fmu/in/offboard_control_mode` | OffboardControlMode |
| Publish, mission mode only | `/fmu/in/trajectory_setpoint` | TrajectorySetpoint |
| Publish, mission mode only | `/fmu/in/vehicle_command` | VehicleCommand |
| Subscribe | `/fmu/out/vehicle_status_v4` | VehicleStatus |
| Subscribe | `/fmu/out/vehicle_local_position_v1` | VehicleLocalPosition |
| Subscribe | `/fmu/out/vehicle_attitude` | VehicleAttitude |
| Subscribe | `/fmu/out/vehicle_land_detected` | VehicleLandDetected |
| Subscribe | `/fmu/out/vehicle_command_ack_v1` | VehicleCommandAck |

QoS: BEST_EFFORT, KEEP_LAST depth 10, VOLATILE. Land and ACK base topic exports
are present in the local PX4 DDS configuration. The ACK `_v1` suffix follows the
installed message version. Its actual live discovery remains to be verified.
Status/position/attitude/landing telemetry and PX4 input subscribers must be present.

## State machine and flight behavior

`INIT -> WAIT_FOR_PX4 -> WAIT_FOR_HEALTH -> PREFLIGHT_SETPOINT -> OFFBOARD -> ARM ->
TAKEOFF -> WAYPOINT_1 -> WAYPOINT_2 -> WAYPOINT_3 -> RETURN_HOME -> LAND -> DISARM -> COMPLETE`

Failure transitions latch `FAILSAFE`; a recovered link never converts a failure to PASS.
OFFBOARD is confirmed before ARM. Streaming begins while disarmed, at the recorded
ground position. There must be two seconds of healthy preflight state and two
seconds of continuous 20 Hz setpoints before requesting mode change.

| States | Entry/success condition | Timeout/failure |
| --- | --- | --- |
| WAIT_FOR_PX4 | Start; fresh telemetry and input subscribers | 30 s |
| WAIT_FOR_HEALTH | Connected; valid, landed, disarmed, healthy for 2 s | 30 s; already armed or competing controller |
| PREFLIGHT_SETPOINT | Home recorded; 2 s stream at 20 Hz | 10 s; health/landed/armed changes |
| OFFBOARD | Stream established; observed Offboard nav state | 10 s or unsafe prearm state |
| ARM | Offboard observed; observed armed state | 10 s or Offboard/health loss |
| TAKEOFF through RETURN_HOME | Previous stage completed; endpoint reached and settled 2 s | 60 s per stage; mode/arming loss |
| LAND | Return reached; landed flag maintained 2 s | 90 s; land mode absent after 8 s or early disarm |
| DISARM | Landing confirmed; disarmed observed | 15 s; landed flag lost |
| COMPLETE | Every required stage, landed and disarmed confirmed | Terminal PASS |
| FAILSAFE | Any failure; landing/disarming observed or unarmed before takeover | 90 s; terminal FAIL even if recovery succeeds |

Global timeout is 480 seconds of monotonic wall time. Active mission states abort
on stale telemetry (>2 s), invalid position/velocity, estimator resets, PX4
failsafe, competing publishers, or a controller scheduling gap >250 ms.
Mode/arm/disarm/land commands are sent once, without retries or force flags.

The coordinate origin is the measured initial home position in PX4 local NED.
Offsets are `(0,0,-10)`, `(20,0,-10)`, `(20,20,-10)`, `(0,20,-10)`, `(0,0,-10)` metres.
This avoids assuming EKF origin equals takeoff home. North/East/Down signs are verified
from installed message definitions. Each leg uses a 15 s quintic position profile
with zero endpoint velocity/acceleration; unused feedforward fields are NaN.
Endpoint tolerance: 0.7 m in 3D; speed <=0.5 m/s; continuous dwell 2 s; not landed.
The initial heading is held. PX4's existing parameters remain unchanged.

FAILSAFE stops normal trajectory and heartbeat publication and attempts one land
request if this node requested arming. A disconnected link may not deliver it.
PX4's configured Offboard-loss response must therefore be inspected and validated
before flight; it is not modified here. The node never force-disarms in flight.
Interruption attempts a land command, records FAIL when possible and stops streaming.
A hard process crash/power loss can leave an incomplete CSV: absence of a terminal
result is INCOMPLETE, never PASS. Logging/serialization overhead and schedule gaps
must be checked under live simulation load.

PASS requires observed completion of takeoff, all three waypoints, return, landing,
and disarming, with no latched failure. Merely building, receiving an ACK, or
reaching a low altitude is insufficient.

## Measurement and CSV methodology

Output directory defaults to `/home/kailash/ros2_ws/baseline_results`.
Mission CSV names are `baseline_run_001.csv`, `baseline_run_002.csv`, etc., reserved
using exclusive creation; existing files are never overwritten. Passive observations
use `preflight_001.csv`, etc., and do not claim mission success.

Each file uses one long-format schema with `record_type` values: `metadata`,
`message`, `resource`, `home`, `event`, `command`, `command_ack`, `topic_summary`, `result`.
Not-applicable columns are empty. `detail` contains JSON or event/command text.

CSV columns:

```
record_type,utc,elapsed_s,state,topic,direction,source_timestamp_us,iat_ms,
payload_cdr_bytes,count,rate_hz,iat_mean_ms,iat_stddev_ms,total_payload_cdr_bytes,
payload_bytes_per_s,expected_count,estimated_missing_messages,system_cpu_percent,
node_cpu_percent,node_rss_mib,x_north_m,y_east_m,z_down_m,armed,nav_state,success,
failure_state,failure_reason,detail
```

- Mission start is logger initialization, including connection/preflight wait;
  terminal result UTC is mission end. Duration uses monotonic wall time. Stage
  events include reach times. These are wall durations, not Gazebo simulation time.
- Receive rates count ROS callbacks. Transmit rates count local `publish()` calls,
  not confirmed delivery to PX4. Summary rates divide total count by the entire
  logged run duration, including idle/preflight time. Individual message rows allow
  flight-stage-only recalculation after a fixed analysis window is chosen.
- IAT is adjacent local monotonic callback/publish-call spacing. Jitter is the
  sample standard deviation of these spacings, with blank values if insufficient data.
  Callback scheduling and middleware buffering affect it. It is NOT network latency.
- Payload bytes are `len(rclpy.serialization.serialize_message(msg))`: ROS CDR
  serialized bytes including encapsulation. These are application representation
  sizes; not actual XRCE wire payload, Ethernet/Wi-Fi bandwidth, or overhead.
  Each topic has a total and bytes/s; total application bytes are the sum of the
  `topic_summary` rows. RX and TX direction totals should also be reported separately.
- System CPU is psutil's interval utilization inside the WSL guest; process CPU is
  the mission process's interval utilization (can exceed 100% across cores); RSS is
  current resident memory in MiB. Both CPU counters are primed before sampling at
  approximately 1 Hz. Windows QGC/GPU/host load is outside this measurement scope.
- Expected counts and estimated missing messages remain blank. DDS configured
  rate limits are upper limits, not proven periodic production rates. No packet-loss
  claims are made. Establish source generation rates/sequence evidence or independent
  transport capture before filling these fields.
- Raw PX4 timestamps and local callback/event times are retained. One-way telemetry,
  command, and end-to-end latency remain unavailable until time-domain mapping and
  its error are validated. Existing VehicleCommandAck is recorded, but has no unique
  per-request identifier and repeated arm/disarm command IDs can be ambiguous. No
  ACK RTT is reported as network/one-way latency. No extra probing commands are sent.
- Power/energy is N/A: hardware measurement unavailable.

The existing legacy node retains its earlier limited metrics and overwrite behavior;
its `baseline_measurements.csv` is NOT the new experimental dataset.

## Build and run

Keep the already-running PX4, Gazebo, XRCE agent and QGC sessions.
In an existing WSL shell, the provided script builds this package, verifies imports,
runs offline tests, prints interfaces/graph state, and observes for 15 s. It sends
no vehicle commands:

```bash
bash ~/ros2_ws/src/baseline_measurement/validate_baseline.sh
```

Equivalent build and passive run:

```bash
cd ~/ros2_ws
source /opt/ros/jazzy/setup.bash
source install/setup.bash
colcon build --packages-select baseline_measurement
source install/setup.bash
ros2 run baseline_measurement mission_node --observe-seconds 15
```

After all preflight evidence is checked, no competing legacy/control publisher is
running, and the existing PX4 Offboard-loss behavior is understood, this is the explicit
ONE-mission command (it arms the simulated vehicle):

```bash
ros2 run baseline_measurement mission_node --execute-sitl
```

During that mission verify QGC mode/arming/altitude, Gazebo movement and waypoint
traversal, and PX4 commander/uORB state. Let ROS control the mission; QGC is observation
only. Do not count a run as validated solely from the program's result row.

## Validation status and remaining work

- PASS: source/installed interface inspection; coordinate definitions verified;
  legacy source/build divergence preserved and reconciled; Python syntax parsing;
  14 ROS-independent tests covering successful policy flow, preflight ordering,
  continuous health, stale telemetry, invalid position, estimator resets, competing
  publishers, scheduling gaps, timeouts, no midair disarm, landing detector dependency,
  failure latching, statistics, and exclusive CSV allocation.
- NOT RUN: colcon build, ROS executable launch, live graph/telemetry/ACK inspection,
  ROS-to-PX4 delivery verification, QGC/Gazebo flight demonstration, and repeated
  validation flights. Offline tests simulate telemetry; they are not SITL flights.
- Preserve exact software versions, PX4 parameter dump (including Offboard-loss
  actions), world/model/physics, machine load, DDS implementation/configuration,
  source hashes, time settings and start/reset procedure before the experimental batch.
- Verify the process precheck against this host's actual process names/command lines.
- Validate one mission, inspect every stage and the CSV, fix observed issues, then
  manually repeat several times. Live safety and timing tuning may still be needed.
- Only after reliability is established, implement the 30-run orchestration and
  `baseline_summary.csv` aggregation. They are deliberately not added or started now.
  Report mean, sample SD, median, min/max and justified 95% CIs over run-level
  quantities, rather than treating individual callbacks as independent runs.
  Include failed attempts in success rate and report metric eligibility explicitly.
- True latency and loss methodology remain unresolved research requirements; this
  implementation honestly reports their absence rather than fabricating values.

Reference: PX4's [Offboard documentation](https://docs.px4.io/main/en/flight_modes/offboard)
describes streaming requirements and NED semantics; the
[ROS 2 user guide](https://docs.px4.io/main/en/ros2/user_guide) describes middleware
time synchronization. Local installed interfaces were used for fields/constants.
