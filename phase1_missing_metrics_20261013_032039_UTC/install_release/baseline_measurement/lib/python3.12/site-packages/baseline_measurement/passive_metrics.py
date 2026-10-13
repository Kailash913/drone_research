"""Bounded ROS/Gazebo subscriptions preserving raw evidence without flight publishers."""
import argparse
from collections import Counter
from datetime import datetime, timezone
import hashlib
import json
import math
from pathlib import Path
import threading
import time

from .dataset import digest
from .measurements import battery_energy


class EvidenceWriter:
    """Serialize callback-entry timestamps and keep nonfinite observations explicit."""

    def __init__(self, path):
        self.file = Path(path).open('x', encoding='utf-8')
        self.lock = threading.Lock()
        self.counts = Counter()

    def write(self, record):
        """Write one complete JSON record even when transport callbacks overlap."""
        def clean(value):
            if isinstance(value, float) and not math.isfinite(value):
                return None
            if isinstance(value, dict):
                return {k: clean(v) for k, v in value.items()}
            if isinstance(value, (list, tuple)):
                return [clean(v) for v in value]
            return value
        with self.lock:
            self.file.write(json.dumps(clean(record), allow_nan=False) + '\n')
            self.file.flush()
            self.counts[record['kind']] += 1

    def close(self):
        """Flush evidence after subscription callbacks stop."""
        with self.lock:
            self.file.close()


def collect(output, seconds, model, config=None):
    """Observe an existing simulation; never start one or create control publishers."""
    from gz.msgs10.pose_v_pb2 import Pose_V
    from gz.transport13 import Node as GazeboNode
    from px4_msgs.msg import (
        BatteryStatus, VehicleLandDetected, VehicleLocalPosition, VehicleStatus)
    import rclpy
    from rclpy.node import Node
    from rclpy.qos import qos_profile_sensor_data
    from rclpy.serialization import serialize_message

    if not math.isfinite(seconds) or not 0 < seconds <= 300:
        raise ValueError('Passive window must be finite and between 0 and 300 seconds')
    directory = Path(output)
    directory.mkdir(exist_ok=False, parents=True)
    writer = EvidenceWriter(directory / 'observations.jsonl')
    start = time.monotonic_ns()
    writer.write({'kind': 'metadata', 'utc': datetime.now(timezone.utc).isoformat(),
                  'mode': 'PASSIVE_METRICS', 'mission_outcome': 'NOT_ATTEMPTED',
                  'publishers_created': 0, 'model': model, 'start_monotonic_ns': start,
                  'requested_seconds': seconds,
                  'config_sha256': digest(config) if config else None,
                  'config_path': str(Path(config).resolve()) if config else None,
                  'source_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
                  'clock': 'Host reception monotonic_ns; source domains retained separately',
                  'scope': 'Current WSL simulation observation, separate from historical '
                           'missions'})
    status = 'COMPLETE'
    latest = {}
    subscriptions = []
    batteries = []
    rclpy.init(args=[])
    node = Node('phase1_passive_metrics')
    gazebo = GazeboNode()

    def receive(kind, topic, msg):
        now = time.monotonic_ns()
        latest[kind] = (now, msg)
        row = {'kind': kind, 'topic': topic, 'receive_monotonic_ns': now,
               'source_timestamp': msg.timestamp, 'source_domain': 'px4_delivered_us',
               'payload_cdr_bytes': len(serialize_message(msg))}
        if kind == 'estimate':
            row.update(position=[msg.x, msg.y, msg.z],
                       timestamp_sample_us=msg.timestamp_sample,
                       position_valid=bool(msg.xy_valid and msg.z_valid
                                           and not msg.dead_reckoning),
                       reset_counters={k: getattr(msg, k) for k in
                                       ('xy_reset_counter', 'z_reset_counter',
                                        'heading_reset_counter')})
            fresh = all(k in latest and now - latest[k][0] < 2000000000
                        for k in ('status', 'land'))
            row['airborne'] = (bool(latest['status'][1].arming_state ==
                                    VehicleStatus.ARMING_STATE_ARMED
                                    and not latest['land'][1].landed)
                               if fresh else None)
        elif kind == 'battery':
            row.update(voltage_v=msg.voltage_v, current_a=msg.current_a, connected=msg.connected,
                       monotonic_s=now / 1e9)
            batteries.append(row.copy())
        elif kind == 'status':
            row.update(arming_state=msg.arming_state, nav_state=msg.nav_state,
                       failsafe=msg.failsafe)
        elif kind == 'land':
            row['landed'] = msg.landed
        writer.write(row)

    def pose(msg):
        now = time.monotonic_ns()
        stamp = msg.header.stamp.sec * 1000000000 + msg.header.stamp.nsec
        for item in msg.pose:
            if item.name == model:
                writer.write({'kind': 'truth', 'topic': '/world/default/pose/info',
                              'model': model, 'source_timestamp': stamp,
                              'source_domain': 'gazebo_sim_ns', 'receive_monotonic_ns': now,
                              'position': [item.position.x, item.position.y, item.position.z]})

    try:
        subscribed = gazebo.subscribe(Pose_V, '/world/default/pose/info', pose)
        writer.write({'kind': 'gazebo_subscription', 'success': bool(subscribed)})
        for kind, topic, cls in (
            ('estimate', '/fmu/out/vehicle_local_position_v1', VehicleLocalPosition),
            ('battery', '/fmu/out/battery_status_v1', BatteryStatus),
            ('status', '/fmu/out/vehicle_status_v4', VehicleStatus),
            ('land', '/fmu/out/vehicle_land_detected', VehicleLandDetected)
        ):
            subscriptions.append(node.create_subscription(
                cls, topic, lambda msg, k=kind, t=topic: receive(k, t, msg),
                qos_profile_sensor_data))
        while rclpy.ok() and time.monotonic_ns() - start < seconds * 1e9:
            rclpy.spin_once(node, timeout_sec=0.1)
    except BaseException:
        status = 'ERROR_OR_INTERRUPTED'
        raise
    finally:
        gazebo.unsubscribe('/world/default/pose/info')
        node.destroy_node()
        rclpy.shutdown()
        end = time.monotonic_ns()
        report = {'status': status, 'counts': dict(writer.counts),
                  'start_monotonic_ns': start, 'end_monotonic_ns': end,
                  'window_s': (end - start) / 1e9, 'mission_outcome': 'NOT_ATTEMPTED',
                  'trajectory_rmse_status': 'NOT_MEASURED',
                  'trajectory_reason': 'No independently validated source-clock/frame mapping '
                                       'supplied',
                  'battery': battery_energy(batteries, max_gap_s=2.)}
        writer.write({'kind': 'result', **report})
        writer.close()
        report['raw_sha256'] = digest(directory / 'observations.jsonl')
        with (directory / 'collection.json').open('x') as stream:
            json.dump(report, stream, indent=2, allow_nan=False)
    return report


def main(args=None):
    """Run only bounded subscriptions; require explicit simulator model identity."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', required=True)
    parser.add_argument('--seconds', type=float, default=15.)
    parser.add_argument('--model', required=True)
    parser.add_argument('--config')
    options = parser.parse_args(args)
    print(json.dumps(collect(options.output, options.seconds, options.model, options.config),
                     indent=2))


if __name__ == '__main__':
    main()
