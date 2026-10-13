"""Unsecured Phase 1 SITL controller and integrated measurement adapter."""
import argparse
import hashlib
import json
import math
import os
from pathlib import Path
import platform
import re
import time
import uuid

import psutil
from px4_msgs.msg import (
    BatteryStatus,
    EstimatorStatusFlags,
    OffboardControlMode,
    TrajectorySetpoint,
    VehicleAttitude,
    VehicleCommand,
    VehicleCommandAck,
    VehicleLandDetected,
    VehicleLocalPosition,
    VehicleStatus
)
import rclpy
from rclpy.clock import Clock, ClockType
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, HistoryPolicy, QoSProfile, ReliabilityPolicy
from rclpy.serialization import serialize_message

from .cli import validate_options
from .experiment import aggregate_runs, Experiment
from .experiment_logger import RunLog
from .mission_state import Mission, Telemetry
from .qgc_plan import make_plan
from .resource_monitor import ResourceMonitor
from .run_provenance import run_metadata
OUTPUTS = (
    {
        'status': ('/fmu/out/vehicle_status_v4', VehicleStatus),
        'position': ('/fmu/out/vehicle_local_position_v1', VehicleLocalPosition),
        'attitude': ('/fmu/out/vehicle_attitude', VehicleAttitude),
        'land': ('/fmu/out/vehicle_land_detected', VehicleLandDetected),
        'ack': ('/fmu/out/vehicle_command_ack_v1', VehicleCommandAck),
        'battery': ('/fmu/out/battery_status_v1', BatteryStatus),
        'estimator': ('/fmu/out/estimator_status_flags', EstimatorStatusFlags)
    }
)
INPUTS = (
    {
        'mode': ('/fmu/in/offboard_control_mode', OffboardControlMode),
        'trajectory': ('/fmu/in/trajectory_setpoint', TrajectorySetpoint),
        'command': ('/fmu/in/vehicle_command', VehicleCommand)
    }
)


def simulation_processes():
    """Read-only check; never starts/stops simulator or agent processes."""
    found = {'px4': [], 'agent': [], 'gazebo': []}
    for process in psutil.process_iter(['pid', 'name', 'cmdline']):
        try:
            info = process.info
            name = (info['name'] or '').lower()
            cmd = ' '.join(info['cmdline'] or [])
            if name == 'px4' and 'px4_sitl' in cmd:
                found['px4'].append(info['pid'])
            if name.startswith('microxrceagent'):
                found['agent'].append(info['pid'])
            if ('gz sim' in cmd or 'gz-sim' in name) and process.pid != os.getpid():
                found['gazebo'].append(info['pid'])
        except (psutil.NoSuchProcess, psutil.AccessDenied):
            continue
    return found


class MissionNode(Node):
    """Single 20 Hz state-machine loop; 1 Hz resource snapshots are integrated."""

    def __init__(self, options):
        super().__init__('baseline_mission' if options.execute_sitl else 'baseline_preflight')
        if self.get_parameter('use_sim_time').value:
            raise RuntimeError('This experiment requires wall time; use_sim_time must be false')
        self.options = options
        self.outputs = (
            {
                key: (options.topics.get(key, topic), msg_type) for key,
                (topic, msg_type) in OUTPUTS.items()
            }
        )
        self.experiment = None
        self.resource_monitor = None
        self.last_baseline_sample = time.monotonic()
        if not options.execute_sitl:
            self.experiment = (
                Experiment(
                    options.output,
                    options.experiment_id,
                    options.scenario,
                    {
                        'px4_version': '1.18.0-beta1 (configured; live version unverified)',
                        'topics': {k: v[0] for k, v in self.outputs.items()},
                        'qos': 'BEST_EFFORT KEEP_LAST 10 VOLATILE'
                    }
                )
            )
            self.resource_monitor = ResourceMonitor()
            self.resource_monitor.sample()
        # prime CPU percentages
        self.latest, self.received, self.stamps = ({}, {}, {})
        self.reset = False
        self.reset_counters = None
        self.last_graph = -math.inf
        self.graph_ok = False
        self.competition = False
        self.process = psutil.Process()
        self.process.cpu_percent(None)
        psutil.cpu_percent(None)
        self.done = False
        self.last_resource = time.monotonic()
        self.started = self.last_resource
        self.event_cursor = 0
        self.yaw = 0.0
        self.pending_command = None
        self.command_publications = []
        self.publishers_by_key = {}
        processes = simulation_processes()
        if options.execute_sitl:
            if (
                    len(processes['px4']) != 1
                    or len(processes['agent']) != 1
                    or (not processes['gazebo'])
            ):
                raise RuntimeError(f'SITL process precheck failed: {processes}')
        metadata = (
            {
                'schema': 1,
                'mode': 'SITL_MISSION' if options.execute_sitl else 'PASSIVE_PREFLIGHT',
                'control_rate_hz': 20.0,
                'mission_timeout_s': 480.0,
                'heading_bootstrap': (
                    'PX4 Auto takeoff with initial yaw alignment and global '
                    'reference; Offboard begins only after final heading readiness'
                ),
                'stage_timeout_s': 60.0,
                'segment_duration_s': 15.0,
                'dwell_s': 2.0,
                'position_tolerance_m': 0.7,
                'settled_speed_m_s': 0.5,
                'frame': 'local NED; offsets from measured takeoff home',
                'waypoint_offsets_m': [
                    [0, 0, -10],
                    [20, 0, -10],
                    [20, 20, -10],
                    [0, 20, -10],
                    [0, 0, -10]
                ],
                'telemetry_freshness_s': 2.0,
                'scheduling_gap_limit_s': 0.25,
                'latency': (
                    'N/A: no independently validated clock mapping or per-command '
                    'correlation'
                ),
                'packet_loss': 'N/A: no transport capture or sequence counters',
                'missing_messages': 'N/A: rate limits are not guaranteed production rates',
                'power': 'N/A: hardware power measurement unavailable',
                'payload': (
                    'ROS CDR serialized bytes including encapsulation; excludes '
                    'transport headers'
                ),
                'cpu_scope': 'WSL Linux guest system and mission process; excludes Windows QGC',
                'processes': processes,
                'python': platform.python_version(),
                'ros_distro': os.environ.get('ROS_DISTRO', ''),
                'rmw': os.environ.get('RMW_IMPLEMENTATION', 'default'),
                'source_sha256': {
                    f.name: hashlib.sha256(f.read_bytes()).hexdigest()
                    for f in Path(__file__).parent.glob('*.py')
                },
                'outputs': {k: v[0] for k, v in self.outputs.items()}
            }
        )
        metadata.update(run_metadata(options))
        self.log = (
            RunLog(
                options.output,
                'baseline_run' if options.execute_sitl else 'preflight',
                metadata
            )
        )
        self.mission = Mission(self.log.start)
        qos = (
            QoSProfile(
                reliability=ReliabilityPolicy.BEST_EFFORT,
                history=HistoryPolicy.KEEP_LAST,
                depth=10,
                durability=DurabilityPolicy.VOLATILE
            )
        )
        self.subscriptions_kept = []
        for key, (topic, msg_type) in self.outputs.items():
            self.subscriptions_kept.append(
                self.create_subscription(
                    msg_type,
                    topic,
                    lambda msg,
                    k=key: self.receive(k, msg),
                    qos
                )
            )
        if options.execute_sitl:
            for key, (topic, msg_type) in INPUTS.items():
                self.publishers_by_key[key] = self.create_publisher(msg_type, topic, qos)
        self.timer = (
            self.create_timer(0.05, self.tick, clock=Clock(clock_type=ClockType.STEADY_TIME))
        )
        self.get_logger().info(f'CSV: {self.log.path}; execute_sitl={options.execute_sitl}')

    def receive(self, key, msg):
        ack_receive_ns = time.monotonic_ns() if key == 'ack' else None
        now = time.monotonic()
        previous = self.stamps.get(key)
        grounded_completion = (
            self.mission.state in ('LAND', 'DISARM', 'RELEASE_CONTROL')
            and self.mission.reached == [
                'TAKEOFF',
                'WAYPOINT_1',
                'WAYPOINT_2',
                'WAYPOINT_3',
                'RETURN_HOME'
            ]
            and bool(getattr(self.latest.get('land'), 'landed', False))
            and (now - self.received.get('status', -math.inf) < 2.0)
            and (now - self.received.get('land', -math.inf) < 2.0)
        )
        if previous is not None and msg.timestamp < previous:
            self.reset = True
            self.log.row(
                'source_clock_reset',
                state=self.mission.state,
                detail=json.dumps(
                    {
                        'topic': self.outputs[key][0],
                        'previous_us': previous,
                        'current_us': msg.timestamp,
                        'grounded_completion': grounded_completion,
                        'local_receive_monotonic_s': now,
                        'timestamp_sample_us': getattr(msg, 'timestamp_sample', None),
                        'estimator_reset_proven': False
                    }
                )
            )
            if grounded_completion:
                # In-flight resets still latch FAILSAFE in the policy.
                # Preserve the reset audit, but rebase freshness for ground confirmation.
                previous = None
        # Duplicate/frozen source timestamps must not keep the freshness watchdog alive.
        if previous is None or msg.timestamp > previous:
            self.received[key] = now
        self.stamps[key] = max(previous or 0, msg.timestamp)
        self.latest[key] = msg
        size = len(serialize_message(msg))
        self.log.message(
            self.outputs[key][0],
            'rx_callback',
            msg,
            size,
            self.mission.state,
            receive_monotonic=now
        )
        if self.experiment is not None:
            self.experiment.message(self.outputs[key][0], size, now)
            self.experiment.sample(
                f'{key}:source_timestamp',
                getattr(msg, 'timestamp', None),
                'us',
                'PX4 clock domain; not host elapsed time',
                now=now
            )
            if key == 'battery':
                self.experiment.battery(msg.voltage_v, msg.current_a, msg.connected, now)
        if key == 'position' and self.mission.home is not None:
            counters = (msg.xy_reset_counter, msg.z_reset_counter, msg.heading_reset_counter)
            if self.reset_counters is not None:
                position_reset = counters[:2] != self.reset_counters[:2]
                heading_reset = counters[2] != self.reset_counters[2]
                aligning_in_auto = (
                    self.mission.auto_takeoff and self.mission.state in (
                        'AUTO_TAKEOFF_REQUEST',
                        'AUTO_ARM',
                        'TAKEOFF',
                        'WAIT_FOR_HEADING'
                    )
                )
                if counters != self.reset_counters:
                    self.log.row(
                        'estimator_reset_counter_change',
                        state=self.mission.state,
                        detail=json.dumps(
                            {
                                'previous': self.reset_counters,
                                'current': counters,
                                'auto_alignment': aligning_in_auto,
                                'source': 'vehicle_local_position reset counters'
                            }
                        )
                    )
                if position_reset or (heading_reset and (not aligning_in_auto)):
                    self.reset = True
                elif heading_reset:
                    self.log.row(
                        'auto_heading_reset',
                        state=self.mission.state,
                        detail='Expected yaw reset while PX4 Auto owns alignment'
                    )
            self.reset_counters = counters
        if key == 'ack':
            candidates = [
                record for record in getattr(self, 'command_publications', [])
                if record['command'] == msg.command
                and record['source_system'] == msg.target_system
                and record['source_component'] == msg.target_component
            ]
            timing = {
                'ack_receive_monotonic_ns': ack_receive_ns,
                'association': 'unmatched; ACK has no unique request identifier'
            }
            # Keep all records: retries and reused command numbers are ambiguous.
            if (
                len(candidates) == 1
                and self.pending_command == msg.command
                and not candidates[0]['ack_seen']
                and ack_receive_ns >= candidates[0]['publish_monotonic_ns']
            ):
                record = candidates[0]
                record['ack_seen'] = True
                timing.update({
                    'association': 'candidate_unverified_association',
                    'publish_monotonic_ns': record['publish_monotonic_ns'],
                    'elapsed_ns': ack_receive_ns - record['publish_monotonic_ns']
                })
            self.log.row(
                'command_ack',
                state=self.mission.state,
                detail=json.dumps(
                    {
                        'command': msg.command,
                        'result': msg.result,
                        'target_system': msg.target_system,
                        'target_component': msg.target_component,
                        **timing
                    }
                )
            )
            if (
                    self.pending_command == msg.command
                    and msg.target_system == 245
                    and (msg.target_component == 191)
                    and (msg.result not in (0, 5))
            ):
                self.mission.fail(f'Command {msg.command} rejected: result {msg.result}', now)

    def telemetry(self, now):
        if now - self.last_graph >= 1.0:
            self.last_graph = now
            self.graph_ok = (
                all((self.count_subscribers(topic) > 0 for topic, _ in INPUTS.values()))
            )
            own = 1 if self.options.execute_sitl else 0
            self.competition = (
                any((self.count_publishers(topic) > own for topic, _ in INPUTS.values()))
            )
        t = Telemetry(competition=self.competition, reset=self.reset)
        t.connected = (
            self.graph_ok and all(
                (
                    now - self.received.get(k, -math.inf) < 2.0 for k in (
                        'status',
                        'position',
                        'attitude',
                        'land'
                    )
                )
            )
        )
        t.landing_connected = (
            self.graph_ok and all(
                (now - self.received.get(k, -math.inf) < 2.0 for k in ('status', 'land'))
            )
        )
        s, p, land = (self.latest.get(k) for k in ('status', 'position', 'land'))
        if s is not None:
            t.armed = s.arming_state == VehicleStatus.ARMING_STATE_ARMED
            t.offboard = s.nav_state == VehicleStatus.NAVIGATION_STATE_OFFBOARD
            t.landing = s.nav_state == VehicleStatus.NAVIGATION_STATE_AUTO_LAND
            t.taking_off = s.nav_state == VehicleStatus.NAVIGATION_STATE_AUTO_TAKEOFF
            t.holding = s.nav_state == VehicleStatus.NAVIGATION_STATE_AUTO_LOITER
            t.failsafe = s.failsafe
            t.healthy = (
                s.pre_flight_checks_pass
                and (not s.calibration_enabled)
                and (not s.rc_calibration_in_progress)
                and (not s.gcs_connection_lost)
                and (s.arming_state in (1, 2))
                and (
                    s.vehicle_type == VehicleStatus.VEHICLE_TYPE_ROTARY_WING
                ) and (not s.safety_button_available or s.safety_off)
            )
        if p is not None:
            t.position = (p.x, p.y, p.z)
            t.velocity = (p.vx, p.vy, p.vz)
            t.valid = (
                p.xy_valid
                and p.z_valid
                and p.v_xy_valid
                and p.v_z_valid
                and (not p.dead_reckoning)
                and all(
                    (math.isfinite(x) for x in (*t.position, *t.velocity, p.heading))
                )
            )
            t.heading_ready = bool(p.heading_good_for_control and math.isfinite(p.heading))
            flags = self.latest.get('estimator')
            t.auto_takeoff_ready = (
                bool(
                    flags is not None
                    and now - self.received.get('estimator', -math.inf) < 2.0
                    and flags.cs_yaw_align
                    and (not flags.cs_mag_fault)
                    and (not flags.cs_mag_field_disturbed)
                    and (not flags.fs_bad_hdg)
                    and p.xy_global
                    and p.z_global
                    and math.isfinite(p.ref_alt)
                )
            )
        t.valid = (
            bool(t.valid and t.connected and t.healthy and (not t.failsafe) and (not t.reset))
        )
        if land is not None:
            t.landed = land.landed
        return t

    def publish(self, key, msg):
        if not self.options.execute_sitl:
            raise RuntimeError('Flight-control publication is disabled in passive mode')
        msg.timestamp = self.get_clock().now().nanoseconds // 1000
        if key == 'command':
            record = {
                'command': msg.command,
                'source_system': msg.source_system,
                'source_component': msg.source_component,
                'target_system': msg.target_system,
                'target_component': msg.target_component,
                'ack_seen': False
            }
            record['publish_monotonic_ns'] = time.monotonic_ns()
        self.publishers_by_key[key].publish(msg)
        if key == 'command':
            self.command_publications.append(record)
            self.log.row(
                'command_publication', state=self.mission.state,
                detail=json.dumps(record)
            )
        self.log.message(
            INPUTS[key][0],
            'tx_publish_call',
            msg,
            len(serialize_message(msg)),
            self.mission.state
        )

    def command(self, intent):
        s = self.latest.get('status')
        if s is None:
            return
        msg = VehicleCommand()
        msg.target_system, msg.target_component = (s.system_id, s.component_id)
        msg.source_system, msg.source_component = (245, 191)
        msg.from_external = True
        if intent == 'OFFBOARD':
            msg.command = VehicleCommand.VEHICLE_CMD_DO_SET_MODE
            msg.param1, msg.param2 = (1.0, 6.0)
        elif intent == 'HOLD':
            msg.command = VehicleCommand.VEHICLE_CMD_DO_SET_MODE
            msg.param1, msg.param2, msg.param3 = (1.0, 4.0, 3.0)
        elif intent == 'AUTO_TAKEOFF':
            p = self.latest['position']
            if (
                    not (
                        p.xy_global
                        and p.z_global
                        and math.isfinite(p.ref_alt)
                        and (self.mission.home is not None)
                    )
            ):
                raise RuntimeError('Auto takeoff requires a valid global altitude reference')
            msg.command = VehicleCommand.VEHICLE_CMD_NAV_TAKEOFF
            msg.param4 = msg.param5 = msg.param6 = math.nan
            msg.param7 = float(p.ref_alt - self.mission.home[2] + 10.0)
        elif intent in ('ARM', 'DISARM'):
            msg.command = VehicleCommand.VEHICLE_CMD_COMPONENT_ARM_DISARM
            msg.param1 = 1.0 if intent == 'ARM' else 0.0
        elif intent == 'LAND':
            msg.command = VehicleCommand.VEHICLE_CMD_NAV_LAND
            msg.param4 = msg.param5 = msg.param6 = msg.param7 = math.nan
        else:
            raise ValueError(intent)
        self.pending_command = msg.command
        self.publish('command', msg)
        self.log.row('command', state=self.mission.state, detail=intent)
        self.get_logger().info(f'[{intent}_REQUESTED]')

    def tick(self):
        now = time.monotonic()
        t = self.telemetry(now)
        if self.options.execute_sitl:
            old_home = self.mission.home
            old_state = self.mission.state
            intents = self.mission.tick(now, t)
            if old_home is None and self.mission.home is not None:
                self.yaw = float(self.latest['position'].heading)
                self.log.row(
                    'home',
                    detail=json.dumps({'home_ned': self.mission.home, 'yaw': self.yaw})
                )
                position = self.latest['position']
                if position.xy_global and position.z_global:
                    plan_path = self.log.path.with_suffix('.plan')
                    plan = (
                        make_plan(
                            self.mission.home,
                            position.ref_lat,
                            position.ref_lon,
                            position.ref_alt
                        )
                    )
                    with plan_path.open('x', encoding='utf-8') as stream:
                        json.dump(plan, stream, indent=2, allow_nan=False)
                        stream.write('\n')
                    self.get_logger().info(f'QGC Plan exported: {plan_path}')
            if (
                    self.mission.auto_takeoff and old_state == 'WAIT_FOR_HEADING' and (
                        self.mission.state == 'PREFLIGHT_SETPOINT'
                    )
            ):
                self.yaw = float(self.latest['position'].heading)
                self.log.row('aligned_heading', detail=json.dumps({'yaw': self.yaw}))
            for intent in intents:
                self.command(intent)
            setpoint = self.mission.setpoint(now)
            if setpoint is not None and (not self.mission.done):
                mode = OffboardControlMode()
                mode.position = True
                trajectory = TrajectorySetpoint()
                trajectory.position = list(setpoint)
                trajectory.velocity = trajectory.acceleration = trajectory.jerk = [math.nan] * 3
                trajectory.yaw, trajectory.yawspeed = (self.yaw, math.nan)
                self.publish('trajectory', trajectory)
                self.publish('mode', mode)
            for event, timestamp in self.mission.events[self.event_cursor:]:
                self.log.row(
                    'event',
                    state=self.mission.state,
                    detail=json.dumps(
                        {'event': event, 'elapsed_s': timestamp - self.mission.start}
                    )
                )
                self.get_logger().info(f'[{event}] {self.mission.failure_reason}')
            self.event_cursor = len(self.mission.events)
            if self.mission.done:
                self.log.finish(
                    self.mission.passed,
                    self.mission.failure_state,
                    self.mission.failure_reason,
                    self.mission.state
                )
                self.done = True
                return
        if now - self.last_resource >= 1.0:
            self.last_resource = now
            self.log.row(
                'resource',
                state=self.mission.state,
                system_cpu_percent=psutil.cpu_percent(None),
                node_cpu_percent=self.process.cpu_percent(None),
                node_rss_mib=self.process.memory_info().rss / 1024 ** 2,
                x_north_m=t.position[0],
                y_east_m=t.position[1],
                z_down_m=t.position[2],
                armed=t.armed,
                nav_state=getattr(self.latest.get('status'), 'nav_state', ''),
                detail=json.dumps(
                    {
                        'connected': t.connected,
                        'healthy': t.healthy,
                        'valid': t.valid,
                        'heading_ready': t.heading_ready,
                        'auto_takeoff_ready': t.auto_takeoff_ready,
                        'landed': t.landed,
                        'competition': t.competition
                    }
                )
            )
            self.log.file.flush()
            if not self.options.execute_sitl:
                self.get_logger().info(
                    f'PASSIVE: connected={t.connected}, healthy={t.healthy}, valid={t.valid}, '
                    f'heading_ready={t.heading_ready}, landed={t.landed}, armed={t.armed}, '
                    f'competing_publisher={t.competition}'
                )
        if (
                self.experiment is not None
                and now - self.last_baseline_sample >= self.options.sampling_interval
        ):
            self.last_baseline_sample = now
            resources = self.resource_monitor.sample()
            for role, pid, cpu, rss in resources:
                self.experiment.resource(role, pid, cpu, rss, now)
            if resources:
                self.experiment.sample(
                    'monitored_process_cpu_total',
                    sum((cpu for _, _, cpu, _ in resources if cpu is not None)),
                    '%_one_logical_cpu',
                    'sum of sampled WSL process CPU',
                    now=now
                )
                self.experiment.sample(
                    'monitored_process_rss_total',
                    sum((rss for _, _, _, rss in resources)),
                    'MiB',
                    'sum of RSS; shared pages may be double-counted',
                    now=now
                )
        if not self.options.execute_sitl and now - self.started >= self.options.observe_seconds:
            graph = dict(self.get_topic_names_and_types())
            for key, (topic, msg_type) in self.outputs.items():
                expected = f'px4_msgs/msg/{msg_type.__name__}'
                found = graph.get(topic, [])
                publishers = self.count_publishers(topic)
                self.experiment.status[f'topic:{key}'] = (
                    {
                        'available': expected in found and publishers > 0,
                        'topic': topic,
                        'expected_type': expected,
                        'discovered_types': found,
                        'publisher_count': publishers,
                        'reason': '' if expected in found and publishers > 0 else (
                            'Missing topic, incompatible type, or no publisher'
                        )
                    }
                )
            sampled_roles = {item['role'] for item in self.experiment.resources.values()}
            for role in ('measurement_node', 'px4_sitl', 'gazebo_sim', 'xrce_agent'):
                self.experiment.status[f'process:{role}'] = (
                    {
                        'available': role in sampled_roles,
                        'reason': '' if role in sampled_roles else 'No matching process sampled'
                    }
                )
            self.experiment.finish('not_attempted')
            self.log.finish(
                '',
                reason='Passive observation only; no mission attempted',
                state='PREFLIGHT'
            )
            self.done = True


def main(args=None):
    """Observe passively by default. --execute-sitl is the explicit one-mission command."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--execute-sitl', action='store_true')
    parser.add_argument('--observe-seconds', type=float, default=None)
    parser.add_argument('--sampling-interval', type=float, default=None)
    parser.add_argument('--output', '--output-dir', dest='output', default=None)
    parser.add_argument('--experiment-id')
    parser.add_argument('--scenario', default='telemetry_only')
    parser.add_argument('--config')
    parser.add_argument('--provenance-json')
    parser.add_argument('--run-count', type=int, default=1)
    parser.add_argument('--passive-only', action='store_true')
    options, ros_args = parser.parse_known_args(args)
    config = {}
    if options.config:
        import yaml
        with Path(options.config).expanduser().open(encoding='utf-8') as stream:
            config = yaml.safe_load(stream) or {}
        if not isinstance(config, dict):
            parser.error('--config must contain a YAML mapping')
    options.observe_seconds = (
        options.observe_seconds
        if options.observe_seconds is not None
        else config.get('observe_seconds', 15.0)
    )
    options.sampling_interval = (
        options.sampling_interval
        if options.sampling_interval is not None
        else config.get('sampling_interval', 1.0)
    )
    options.output = (
        options.output or config.get(
            'output_dir',
            str(Path.home() / 'ros2_ws' / 'baseline_results')
        )
    )
    options.topics = config.get('topics', {})
    try:
        validate_options(
            options.observe_seconds,
            options.sampling_interval,
            options.run_count,
            options.experiment_id,
            options.execute_sitl,
            options.passive_only,
            options.topics,
            OUTPUTS
        )
    except ValueError as exc:
        parser.error(str(exc))
    if not options.execute_sitl:
        if options.experiment_id:
            first = int(options.experiment_id.split('-')[1])
        else:
            directory = Path(options.output).expanduser()
            existing = (
                [
                    int(match.group(1)) for path in directory.glob('BASE-*_*.json') if (
                        match := re.match('BASE-(\\d{3})_', path.name)
                    )
                ]
            )
            first = max(existing, default=0) + 1
        if first + options.run_count - 1 > 30:
            parser.error(
                'BASE-001 through BASE-030 are exhausted; choose an existing ID explicitly or'
                ' a new study directory'
            )
    else:
        first = 0
    rclpy.init(args=ros_args)
    try:
        completed_run_ids = []
        for index in range(options.run_count):
            if not options.execute_sitl:
                options.experiment_id = f'BASE-{first + index:03d}'
            node = None
            error = ''
            interrupted = False
            try:
                node = MissionNode(options)
                while rclpy.ok() and (not node.done):
                    rclpy.spin_once(node, timeout_sec=0.1)
            except KeyboardInterrupt:
                interrupted = True
                error = 'Interrupted by Ctrl+C'
                if node is not None:
                    node.get_logger().warning(error)
            except Exception as exc:
                error = f'{type(exc).__name__}: {exc}'
                if node is not None:
                    node.get_logger().error(error)
                raise
            finally:
                if node is not None:
                    if node.experiment is not None:
                        if not node.experiment.closed:
                            node.experiment.finish(
                                'interrupted' if interrupted else 'failed',
                                error
                            )
                        completed_run_ids.append(node.experiment.run_id)
                    if not node.log.finished:
                        if node.options.execute_sitl and node.mission.owned and rclpy.ok():
                            try:
                                node.command('LAND')
                            except Exception:
                                pass
                        node.log.finish(
                            False,
                            node.mission.state,
                            error or 'Interrupted or runtime error',
                            node.mission.state
                        )
                    node.destroy_node()
            if interrupted:
                break
        if not options.execute_sitl and options.run_count > 1:
            aggregate = (
                aggregate_runs(
                    Path(options.output).expanduser() / 'baseline_summary.csv',
                    completed_run_ids
                )
            )
            destination = (
                Path(options.output).expanduser() / f'aggregate_{uuid.uuid4().hex[:12]}.json'
            )
            with destination.open('x', encoding='utf-8') as stream:
                json.dump(aggregate, stream, indent=2, allow_nan=False)
                stream.write('\n')
    finally:
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
