"""Collect subscription-only clock/estimator evidence without controlling PX4."""
import argparse
import csv
from datetime import datetime, timezone
import hashlib
import json
import math
from pathlib import Path
import time
import uuid

from px4_msgs.msg import (
    EstimatorStatusFlags,
    TimesyncStatus,
    VehicleAttitude,
    VehicleLandDetected,
    VehicleLocalPosition,
    VehicleStatus
)
import rclpy
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, HistoryPolicy, QoSProfile, ReliabilityPolicy
from rclpy.serialization import serialize_message

from .dataset import TimestampAudit
TOPICS = (
    {
        '/fmu/out/vehicle_local_position_v1': VehicleLocalPosition,
        '/fmu/out/vehicle_attitude': VehicleAttitude,
        '/fmu/out/vehicle_status_v4': VehicleStatus,
        '/fmu/out/vehicle_land_detected': VehicleLandDetected,
        '/fmu/out/estimator_status_flags': EstimatorStatusFlags,
        '/fmu/out/timesync_status': TimesyncStatus
    }
)
EVIDENCE_FIELDS = (
    (
        'timestamp',
        'timestamp_sample',
        'xy_reset_counter',
        'z_reset_counter',
        'vxy_reset_counter',
        'vz_reset_counter',
        'heading_reset_counter',
        'quat_reset_counter',
        'heading_good_for_control',
        'heading',
        'x',
        'y',
        'z',
        'vx',
        'vy',
        'vz',
        'ref_alt',
        'xy_global',
        'z_global',
        'pre_flight_checks_pass',
        'gcs_connection_lost',
        'calibration_enabled',
        'cs_tilt_align',
        'cs_mag_hdg',
        'cs_mag_3d',
        'cs_yaw_align',
        'cs_mag_aligned_in_flight',
        'cs_mag_fault',
        'cs_mag_field_disturbed',
        'fs_bad_hdg',
        'xy_valid',
        'z_valid',
        'v_xy_valid',
        'v_z_valid',
        'dead_reckoning',
        'arming_state',
        'nav_state',
        'failsafe',
        'landed',
        'source_protocol',
        'remote_timestamp',
        'observed_offset',
        'estimated_offset',
        'round_trip_time'
    )
)
FIELDS = (
    (
        'record_type',
        'utc',
        'local_monotonic_s',
        'elapsed_s',
        'topic',
        'payload_cdr_bytes',
        'source_timestamp_us',
        'timestamp_sample_us',
        'detail'
    )
)


class ClockProbe(Node):
    """Keep local receive age separate from delivered source-order diagnostics."""

    def __init__(self, output, seconds, config=None):
        super().__init__('phase1_clock_probe')
        self.start = time.monotonic()
        self.seconds = seconds
        self.audit = TimestampAudit()
        self.counts = {}
        self.previous_counters = {}
        self.subscriptions_kept = []
        directory = Path(output).expanduser()
        directory.mkdir(parents=True, exist_ok=True)
        self.path = directory / ('clock_probe_' + uuid.uuid4().hex + '.csv')
        self.file = self.path.open('x', newline='', encoding='utf-8')
        self.writer = csv.DictWriter(self.file, fieldnames=FIELDS)
        config_path = Path(config).expanduser().resolve() if config else None
        metadata = (
            {
                'mode': 'PASSIVE_CLOCK_DIAGNOSTIC',
                'publishers_created': 0,
                'topics': list(TOPICS),
                'clock': 'time.monotonic at reception; source fields retained unchanged',
                'config_file': str(config_path) if config_path else None,
                'config_sha256': (
                    hashlib.sha256(config_path.read_bytes()).hexdigest()
                    if config_path else None),
                'ros_distro': 'jazzy',
                'power_energy': 'not measured',
                'timesync_rtt_note': (
                    'PX4 timesync round trip, not mission command or end-to-end latency')
            }
        )
        self.writer.writeheader()
        self.row('metadata', detail=metadata)
        qos = (
            QoSProfile(
                reliability=ReliabilityPolicy.BEST_EFFORT,
                history=HistoryPolicy.KEEP_LAST,
                depth=10,
                durability=DurabilityPolicy.VOLATILE
            )
        )
        for topic, message_type in TOPICS.items():
            self.subscriptions_kept.append(
                self.create_subscription(
                    message_type,
                    topic,
                    lambda msg,
                    t=topic: self.receive(t, msg),
                    qos
                )
            )

    def row(self, kind, now=None, **values):
        """Write native diagnostics with monotonic and UTC reception references."""
        now = time.monotonic() if now is None else now
        if 'detail' in values:
            values['detail'] = json.dumps(values['detail'], allow_nan=False)
        self.writer.writerow(
            {
                'record_type': kind,
                'utc': datetime.now(timezone.utc).isoformat(),
                'local_monotonic_s': now,
                'elapsed_s': now - self.start,
                **values
            }
        )

    def receive(self, topic, msg):
        """Record timestamp_sample, reset indicators and time-sync evidence independently."""
        now = time.monotonic()
        self.counts[topic] = self.counts.get(topic, 0) + 1
        fields = {field: getattr(msg, field) for field in EVIDENCE_FIELDS if hasattr(msg, field)}
        invalid = [key for key, value in fields.items()
                   if isinstance(value, float) and not math.isfinite(value)]
        if invalid:
            self.row('invalid_numeric_evidence', now, topic=topic,
                     detail={'fields': invalid,
                             'interpretation': 'Nonfinite values retained as null'})
            for key in invalid:
                fields[key] = None
        kind = self.audit.observe(
            topic, getattr(msg, 'timestamp', None), now - getattr(self, 'start', 0.))
        if kind:
            self.row('source_order_event', now, topic=topic, detail=self.audit.events[-1])
        counters = {k: v for k, v in fields.items() if k.endswith('_reset_counter')}
        previous = self.previous_counters.get(topic)
        if previous is not None and counters != previous:
            self.row(
                'estimator_counter_change',
                now,
                topic=topic,
                detail={
                    'previous': previous,
                    'current': counters,
                    'interpretation': (
                        'Estimator reset counter evidence; not inferred from timestamps.')
                }
            )
        self.previous_counters[topic] = counters
        self.row(
            'message',
            now,
            topic=topic,
            payload_cdr_bytes=len(serialize_message(msg)),
            source_timestamp_us=getattr(msg, 'timestamp', ''),
            timestamp_sample_us=getattr(msg, 'timestamp_sample', ''),
            detail=fields
        )

    def finish(self, status):
        """Finalize the passive capture without asserting mission success."""
        now = time.monotonic()
        duration = now - self.start
        self.row(
            'result',
            now,
            detail={
                'status': status,
                'duration_s': duration,
                'mission_outcome': 'NOT_ATTEMPTED',
                'topics': {
                    t: {
                        'count': self.counts.get(t, 0),
                        'observed_callback_hz': self.counts.get(t, 0) / duration,
                        'last_receive_age_s': (
                            duration - self.audit.receive_time[t]
                            if t in self.audit.receive_time else None),
                        'local_receive_stale': self.audit.stale(t, duration)
                    } for t in TOPICS
                }
            }
        )
        self.file.flush()
        self.file.close()


def main(args=None):
    """Observe existing telemetry; never create a vehicle command publisher."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', required=True)
    parser.add_argument('--seconds', type=float, default=20.0)
    parser.add_argument('--config')
    options = parser.parse_args(args)
    if not math.isfinite(options.seconds) or options.seconds <= 0:
        parser.error('--seconds must be finite and positive')
    rclpy.init(args=[])
    node = None
    status = 'COMPLETE'
    try:
        node = ClockProbe(options.output, options.seconds, options.config)
        while rclpy.ok() and time.monotonic() - node.start < options.seconds:
            rclpy.spin_once(node, timeout_sec=0.1)
    except KeyboardInterrupt:
        status = 'INTERRUPTED'
    except Exception:
        status = 'ERROR'
        raise
    finally:
        if node is not None:
            node.finish(status)
            print(str(node.path), flush=True)
            node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
