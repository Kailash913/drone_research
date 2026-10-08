"""Unsecured Phase 1 SITL controller and integrated measurement adapter."""

import argparse
import hashlib
import json
import math
import os
from pathlib import Path
import platform
import time

import psutil
import rclpy
from rclpy.clock import Clock, ClockType
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy
from rclpy.serialization import serialize_message
from px4_msgs.msg import (
    VehicleStatus, VehicleLocalPosition, VehicleAttitude, VehicleLandDetected,
    VehicleCommandAck, VehicleCommand, TrajectorySetpoint, OffboardControlMode,
)

from .experiment_logger import RunLog
from .mission_state import Mission, Telemetry


OUTPUTS = {
    'status': ('/fmu/out/vehicle_status_v4', VehicleStatus),
    'position': ('/fmu/out/vehicle_local_position_v1', VehicleLocalPosition),
    'attitude': ('/fmu/out/vehicle_attitude', VehicleAttitude),
    'land': ('/fmu/out/vehicle_land_detected', VehicleLandDetected),
    'ack': ('/fmu/out/vehicle_command_ack_v1', VehicleCommandAck),
}
INPUTS = {
    'mode': ('/fmu/in/offboard_control_mode', OffboardControlMode),
    'trajectory': ('/fmu/in/trajectory_setpoint', TrajectorySetpoint),
    'command': ('/fmu/in/vehicle_command', VehicleCommand),
}


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
        self.latest, self.received, self.stamps = {}, {}, {}
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
        self.yaw = 0.
        self.pending_command = None
        self.publishers_by_key = {}
        processes = simulation_processes()
        if options.execute_sitl:
            if len(processes['px4']) != 1 or len(processes['agent']) != 1 or not processes['gazebo']:
                raise RuntimeError(f'SITL process precheck failed: {processes}')
        metadata = {
            'schema': 1, 'mode': 'SITL_MISSION' if options.execute_sitl else 'PASSIVE_PREFLIGHT',
            'control_rate_hz': 20., 'mission_timeout_s': 480.,
            'stage_timeout_s': 60., 'segment_duration_s': 15., 'dwell_s': 2.,
            'position_tolerance_m': .7, 'settled_speed_m_s': .5,
            'frame': 'local NED; offsets from measured takeoff home',
            'waypoint_offsets_m': [[0,0,-10],[20,0,-10],[20,20,-10],[0,20,-10],[0,0,-10]],
            'telemetry_freshness_s': 2., 'scheduling_gap_limit_s': .25,
            'latency': 'N/A: no independently validated clock mapping or per-command correlation',
            'packet_loss': 'N/A: no transport capture or sequence counters',
            'missing_messages': 'N/A: rate limits are not guaranteed production rates',
            'power': 'N/A: hardware power measurement unavailable',
            'payload': 'ROS CDR serialized bytes including encapsulation; excludes transport headers',
            'cpu_scope': 'WSL Linux guest system and mission process; excludes Windows QGC',
            'processes': processes, 'python': platform.python_version(),
            'ros_distro': os.environ.get('ROS_DISTRO', ''),
            'rmw': os.environ.get('RMW_IMPLEMENTATION', 'default'),
            'source_sha256': {
                f.name: hashlib.sha256(f.read_bytes()).hexdigest()
                for f in Path(__file__).parent.glob('*.py')
            },
            'outputs': {k: v[0] for k, v in OUTPUTS.items()},
        }
        self.log = RunLog(options.output, 'baseline_run' if options.execute_sitl else 'preflight', metadata)
        self.mission = Mission(self.log.start)
        qos = QoSProfile(reliability=ReliabilityPolicy.BEST_EFFORT,
                         history=HistoryPolicy.KEEP_LAST, depth=10,
                         durability=DurabilityPolicy.VOLATILE)
        self.subscriptions_kept = []
        for key, (topic, msg_type) in OUTPUTS.items():
            self.subscriptions_kept.append(self.create_subscription(
                msg_type, topic, lambda msg, k=key: self.receive(k, msg), qos))
        if options.execute_sitl:
            for key, (topic, msg_type) in INPUTS.items():
                self.publishers_by_key[key] = self.create_publisher(msg_type, topic, qos)
        self.timer = self.create_timer(.05, self.tick, clock=Clock(clock_type=ClockType.STEADY_TIME))
        self.get_logger().info(f'CSV: {self.log.path}; execute_sitl={options.execute_sitl}')

    def receive(self, key, msg):
        now = time.monotonic()
        previous = self.stamps.get(key)
        if previous is not None and msg.timestamp < previous:
            self.reset = True
        # Duplicate/frozen source timestamps must not keep the freshness watchdog alive.
        if previous is None or msg.timestamp > previous:
            self.received[key] = now
        self.stamps[key] = max(previous or 0, msg.timestamp)
        self.latest[key] = msg
        self.log.message(OUTPUTS[key][0], 'rx_callback', msg,
                         len(serialize_message(msg)), self.mission.state)
        if key == 'position' and self.mission.home is not None:
            counters = (msg.xy_reset_counter, msg.z_reset_counter, msg.heading_reset_counter)
            if self.reset_counters is not None and counters != self.reset_counters:
                self.reset = True
            self.reset_counters = counters
        if key == 'ack':
            self.log.row('command_ack', state=self.mission.state, detail=json.dumps({
                'command': msg.command, 'result': msg.result,
                'target_system': msg.target_system, 'target_component': msg.target_component,
                'association': 'unmatched; ACK has no unique request identifier',
            }))
            if (self.pending_command == msg.command and msg.target_system == 245
                    and msg.target_component == 191 and msg.result not in (0, 5)):
                self.mission.fail(f'Command {msg.command} rejected: result {msg.result}', now)

    def telemetry(self, now):
        if now - self.last_graph >= 1.:
            self.last_graph = now
            self.graph_ok = all(self.count_subscribers(topic) > 0 for topic, _ in INPUTS.values())
            own = 1 if self.options.execute_sitl else 0
            self.competition = any(self.count_publishers(topic) > own for topic, _ in INPUTS.values())
        t = Telemetry(competition=self.competition, reset=self.reset)
        t.connected = self.graph_ok and all(
            now-self.received.get(k, -math.inf) < 2.
            for k in ('status', 'position', 'attitude', 'land'))
        s, p, land = (self.latest.get(k) for k in ('status', 'position', 'land'))
        if s is not None:
            t.armed = s.arming_state == VehicleStatus.ARMING_STATE_ARMED
            t.offboard = s.nav_state == VehicleStatus.NAVIGATION_STATE_OFFBOARD
            t.landing = s.nav_state == VehicleStatus.NAVIGATION_STATE_AUTO_LAND
            t.failsafe = s.failsafe
            t.healthy = (s.pre_flight_checks_pass and not s.calibration_enabled
                         and not s.rc_calibration_in_progress and not s.gcs_connection_lost
                         and s.arming_state in (1, 2)
                         and s.vehicle_type == VehicleStatus.VEHICLE_TYPE_ROTARY_WING
                         and (not s.safety_button_available or s.safety_off))
        if p is not None:
            t.position = (p.x, p.y, p.z)
            t.velocity = (p.vx, p.vy, p.vz)
            t.valid = (p.xy_valid and p.z_valid and p.v_xy_valid and p.v_z_valid
                       and p.heading_good_for_control and not p.dead_reckoning
                       and all(math.isfinite(x) for x in (*t.position, *t.velocity, p.heading)))
        if land is not None:
            t.landed = land.landed
        return t

    def publish(self, key, msg):
        msg.timestamp = self.get_clock().now().nanoseconds // 1000
        self.publishers_by_key[key].publish(msg)
        self.log.message(INPUTS[key][0], 'tx_publish_call', msg,
                         len(serialize_message(msg)), self.mission.state)

    def command(self, intent):
        s = self.latest.get('status')
        if s is None:
            return
        msg = VehicleCommand()
        msg.target_system, msg.target_component = s.system_id, s.component_id
        msg.source_system, msg.source_component = 245, 191
        msg.from_external = True
        if intent == 'OFFBOARD':
            msg.command = VehicleCommand.VEHICLE_CMD_DO_SET_MODE
            msg.param1, msg.param2 = 1., 6.
        elif intent in ('ARM', 'DISARM'):
            msg.command = VehicleCommand.VEHICLE_CMD_COMPONENT_ARM_DISARM
            msg.param1 = 1. if intent == 'ARM' else 0.
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
            intents = self.mission.tick(now, t)
            if old_home is None and self.mission.home is not None:
                self.yaw = float(self.latest['position'].heading)
                self.log.row('home', detail=json.dumps({'home_ned': self.mission.home, 'yaw': self.yaw}))
            for intent in intents:
                self.command(intent)
            setpoint = self.mission.setpoint(now)
            if setpoint is not None and not self.mission.done:
                mode = OffboardControlMode()
                mode.position = True
                trajectory = TrajectorySetpoint()
                trajectory.position = list(setpoint)
                trajectory.velocity = trajectory.acceleration = trajectory.jerk = [math.nan]*3
                trajectory.yaw, trajectory.yawspeed = self.yaw, math.nan
                self.publish('trajectory', trajectory)
                self.publish('mode', mode)
            for event, timestamp in self.mission.events[self.event_cursor:]:
                self.log.row('event', state=self.mission.state,
                             detail=json.dumps({'event': event, 'elapsed_s': timestamp-self.mission.start}))
                self.get_logger().info(f'[{event}] {self.mission.failure_reason}')
            self.event_cursor = len(self.mission.events)
            if self.mission.done:
                self.log.finish(self.mission.passed, self.mission.failure_state,
                                self.mission.failure_reason, self.mission.state)
                self.done = True
                return
        if now-self.last_resource >= 1.:
            self.last_resource = now
            self.log.row('resource', state=self.mission.state,
                         system_cpu_percent=psutil.cpu_percent(None),
                         node_cpu_percent=self.process.cpu_percent(None),
                         node_rss_mib=self.process.memory_info().rss/(1024**2),
                         x_north_m=t.position[0], y_east_m=t.position[1], z_down_m=t.position[2],
                         armed=t.armed, nav_state=getattr(self.latest.get('status'), 'nav_state', ''),
                         detail=json.dumps({'connected': t.connected, 'healthy': t.healthy,
                                            'valid': t.valid, 'landed': t.landed,
                                            'competition': t.competition}))
            self.log.file.flush()
            if not self.options.execute_sitl:
                self.get_logger().info(f'PASSIVE: connected={t.connected}, healthy={t.healthy}, '
                                       f'valid={t.valid}, landed={t.landed}, '
                                       f'armed={t.armed}, competing_publisher={t.competition}')
        if not self.options.execute_sitl and now-self.started >= self.options.observe_seconds:
            self.log.finish('', reason='Passive observation only; no mission attempted', state='PREFLIGHT')
            self.done = True


def main(args=None):
    """Default is passive. --execute-sitl is the explicit one-mission command."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--execute-sitl', action='store_true')
    parser.add_argument('--observe-seconds', type=float, default=15.)
    parser.add_argument('--output', default=str(Path.home()/'ros2_ws'/'baseline_results'))
    options, ros_args = parser.parse_known_args(args)
    if options.observe_seconds <= 0 or not math.isfinite(options.observe_seconds):
        parser.error('--observe-seconds must be finite and positive')
    rclpy.init(args=ros_args)
    node = None
    try:
        node = MissionNode(options)
        while rclpy.ok() and not node.done:
            rclpy.spin_once(node, timeout_sec=.1)
    except KeyboardInterrupt:
        if node is not None:
            node.get_logger().error('Interrupted: stopping stream; PX4 link-loss failsafe applies')
    except Exception as exc:
        if node is not None:
            node.get_logger().error(f'Unhandled error; stopping stream: {exc}')
        raise
    finally:
        if node is not None:
            if not node.log.finished:
                # Best-effort land on interruption; never force-disarm.
                if node.options.execute_sitl and node.mission.owned and rclpy.ok():
                    try:
                        node.command('LAND')
                    except Exception:
                        pass
                node.log.finish(False, node.mission.state, 'Interrupted or runtime error', node.mission.state)
            node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
