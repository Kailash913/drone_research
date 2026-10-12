"""Bounded passive experiment recording, independent of ROS imports."""
import csv
from datetime import datetime, timezone
import json
import math
import os
from pathlib import Path
import platform
import time
import uuid

from .metrics import describe, OnlineStats, throughput_mbps
RAW_FIELDS = (
    (
        'experiment_id',
        'run_id',
        'timestamp',
        'elapsed_s',
        'metric_name',
        'value',
        'unit',
        'source',
        'status'
    )
)
SUMMARY_FIELDS = (
    (
        'experiment_id',
        'run_id',
        'scenario',
        'start_time',
        'end_time',
        'observation_duration_s',
        'latency_mean_ms',
        'latency_median_ms',
        'latency_std_ms',
        'latency_min_ms',
        'latency_max_ms',
        'latency_ci95_lower_ms',
        'latency_ci95_upper_ms',
        'telemetry_latency_mean_ms',
        'telemetry_rate_hz',
        'telemetry_jitter_ms',
        'command_latency_mean_ms',
        'command_success_rate_pct',
        'packets_sent',
        'packets_received',
        'packets_lost',
        'packet_loss_pct',
        'throughput_mbps',
        'bandwidth_mbps',
        'cpu_pct',
        'memory_mb',
        'memory_mib',
        'mission_time_s',
        'energy_wh',
        'mission_success',
        'measurement_status',
        'error_message'
    )
)


def utc_now():
    return datetime.now(timezone.utc).isoformat()


class Experiment:
    """One passive observation; raw samples stream to disk and stats stay bounded."""

    def __init__(self, output_dir, experiment_id, scenario, metadata=None):
        self.directory = Path(output_dir).expanduser()
        self.directory.mkdir(parents=True, exist_ok=True)
        self.experiment_id = experiment_id
        self.run_id = uuid.uuid4().hex[:12]
        self.scenario = scenario
        self.start_time = utc_now()
        self.start = time.monotonic()
        self.topic = {}
        self.resources = {}
        self.power = []
        self.last_power = None
        self.energy_wh = 0.0
        self.power_count = 0
        self.metadata = metadata or {}
        self.status = {}
        self.errors = []
        self.closed = False
        stem = f'{experiment_id}_{self.run_id}'
        self.raw_path = self.directory / f'{stem}_raw.csv'
        self.json_path = self.directory / f'{stem}.json'
        self.summary_path = self.directory / 'baseline_summary.csv'
        self.raw_file = self.raw_path.open('x', newline='', encoding='utf-8')
        self.raw_writer = csv.DictWriter(self.raw_file, fieldnames=RAW_FIELDS)
        self.raw_writer.writeheader()
        self.raw_file.flush()

    def sample(self, name, value, unit, source, status='measured', now=None):
        now = time.monotonic() if now is None else now
        self.raw_writer.writerow(
            {
                'experiment_id': self.experiment_id,
                'run_id': self.run_id,
                'timestamp': utc_now(),
                'elapsed_s': max(0.0, now - self.start),
                'metric_name': name,
                'value': value if value is not None else '',
                'unit': unit,
                'source': source,
                'status': status
            }
        )

    def message(self, topic, size, now=None):
        now = time.monotonic() if now is None else now
        item = (
            self.topic.setdefault(
                topic,
                {'count': 0, 'bytes': 0, 'last': None, 'iat': OnlineStats(), 'size': OnlineStats()}
            )
        )
        if item['last'] is not None:
            iat_ms = (now - item['last']) * 1000
            item['iat'].add(iat_ms)
            self.sample(
                f'{topic}:inter_arrival',
                iat_ms,
                'ms',
                'ROS 2 callback monotonic interval',
                now=now
            )
        item['last'] = now
        item['count'] += 1
        item['bytes'] += size
        item['size'].add(size)
        self.sample(
            f'{topic}:payload_size',
            size,
            'byte',
            'ROS 2 CDR serialization including encapsulation',
            now=now
        )

    def resource(self, role, pid, cpu_pct, rss_mib, now=None):
        now = time.monotonic() if now is None else now
        key = f'{role}:{pid}'
        item = (
            self.resources.setdefault(
                key,
                {'role': role, 'pid': pid, 'cpu': OnlineStats(), 'rss': OnlineStats()}
            )
        )
        item['cpu'].add(cpu_pct)
        item['rss'].add(rss_mib)
        self.sample(f'cpu:{key}', cpu_pct, '%_one_logical_cpu', 'WSL process', now=now)
        self.sample(f'rss:{key}', rss_mib, 'MiB', 'WSL process RSS', now=now)

    def battery(self, voltage_v, current_a, connected, now=None):
        now = time.monotonic() if now is None else now
        if (
                not connected or not all(
                    (math.isfinite(x) for x in (voltage_v, current_a))
                ) or voltage_v <= 0 or (current_a < 0)
        ):
            return
        watts = voltage_v * current_a
        if self.last_power is not None:
            previous_t, previous_w = self.last_power
            if now > previous_t:
                self.energy_wh += (watts + previous_w) * (now - previous_t) / 7200
        self.last_power = (now, watts)
        self.power_count += 1
        self.sample(
            'battery_power_estimate',
            watts,
            'W',
            'PX4 simulated BatteryStatus voltage_v * current_a',
            now=now
        )

    def finish(self, mission_status='not_attempted', error=''):
        if self.closed:
            return
        self.closed = True
        end_time = utc_now()
        elapsed = max(time.monotonic() - self.start, 1e-09)
        self.raw_file.flush()
        self.raw_file.close()
        topic_stats = {}
        for name, item in self.topic.items():
            topic_stats[name] = (
                {
                    'count': item['count'],
                    'delivered_cdr_bytes': item['bytes'],
                    'rate_hz': item['count'] / elapsed if elapsed else None,
                    'inter_arrival_ms': item['iat'].summary(),
                    'payload_size_bytes': item['size'].summary()
                }
            )
        received = sum((x['count'] for x in self.topic.values()))
        delivered = sum((x['bytes'] for x in self.topic.values()))
        rate = throughput_mbps(delivered, elapsed)
        resources = (
            {
                key: {
                    'role': item['role'],
                    'pid': item['pid'],
                    'cpu_pct': item['cpu'].summary(),
                    'rss_mib': item['rss'].summary()
                } for key,
                item in self.resources.items()
            }
        )
        reasons = (
            {
                'latency': 'No instrumented sender-to-receiver probe or common clock.',
                'telemetry_latency': (
                    'PX4 source timestamp and host monotonic clock are not '
                    'validated as one domain.'
                ),
                'command_latency': (
                    'Passive mode sends no command; ACK lacks unique request '
                    'correlation.'
                ),
                'packet_loss': (
                    'ROS callbacks do not expose transmitted sequence counts or '
                    'transport packets.'
                ),
                'link_capacity': 'No meaningful physical link-capacity measurement in WSL SITL.',
                'mission_time': 'Passive observation does not execute a mission.'
            }
        )
        if self.power_count < 2:
            reasons['energy'] = 'Fewer than two valid connected battery voltage/current samples.'
        if received == 0:
            reasons['throughput'] = 'No ROS telemetry callbacks received.'
        if not resources:
            reasons['resources'] = 'No matching processes sampled.'
        self.status.update(
            {name: {'available': False, 'reason': reason} for name, reason in reasons.items()}
        )
        self.status['throughput'] = (
            {
                'available': True,
                'kind': 'delivered ROS CDR payload rate'
            } if received else self.status['throughput']
        )
        self.status['traffic_rate'] = (
            {
                'available': bool(received),
                'kind': 'received ROS CDR traffic rate; not link capacity'
            }
        )
        self.status['energy'] = (
            {
                'available': True,
                'kind': 'simulated battery estimate'
            } if self.power_count >= 2 else self.status['energy']
        )
        self.status['mission'] = {'available': True, 'status': mission_status}
        self.errors.extend([error] if error else [])
        row = {key: '' for key in SUMMARY_FIELDS}
        row.update(
            experiment_id=self.experiment_id,
            run_id=self.run_id,
            scenario=self.scenario,
            start_time=self.start_time,
            end_time=end_time,
            observation_duration_s=elapsed,
            packets_received='',
            throughput_mbps=rate if received else '',
            bandwidth_mbps='',
            mission_success='',
            measurement_status='partial' if self.status else 'complete',
            error_message='; '.join(self.errors)
        )
        preferred_topic = self.metadata.get('topics', {}).get('position')
        telemetry = topic_stats.get(preferred_topic) if preferred_topic else None
        if telemetry is None and topic_stats:
            telemetry = next(iter(topic_stats.values()))
        if telemetry is not None:
            row['telemetry_rate_hz'] = telemetry['rate_hz']
            jitter = telemetry['inter_arrival_ms']['std']
            row['telemetry_jitter_ms'] = jitter if jitter is not None else ''
        if self.power_count >= 2:
            row['energy_wh'] = self.energy_wh
        if resources:
            node = [v for v in resources.values() if v['role'] == 'measurement_node']
            if node:
                cpu = node[0]['cpu_pct']['mean']
                rss = node[0]['rss_mib']['mean']
                row['cpu_pct'] = cpu if cpu is not None else ''
                row['memory_mib'] = rss if rss is not None else ''
                row['memory_mb'] = (
                    node[0]['rss_mib']['mean'] * 1.048576
                    if node[0]['rss_mib']['mean'] is not None
                    else ''
                )
        document = (
            {
                'schema_version': 1,
                'experiment': {
                    'experiment_id': self.experiment_id,
                    'run_id': self.run_id,
                    'scenario': self.scenario,
                    'start_time': self.start_time,
                    'end_time': end_time,
                    'observation_duration_s': elapsed,
                    'mission_status': mission_status
                },
                'environment': dict(
                    python=platform.python_version(),
                    ros_distro=os.environ.get('ROS_DISTRO'),
                    **self.metadata
                ),
                'topics': topic_stats,
                'resources': resources,
                'metrics': {
                    'throughput_mbps': rate if received else None,
                    'received_cdr_bytes': delivered,
                    'simulated_energy_wh': self.energy_wh if self.power_count >= 2 else None
                },
                'availability': self.status,
                'errors': self.errors,
                'metric_definitions': {
                    'throughput_mbps': (
                        'received ROS CDR bytes * 8 / monotonic observation seconds'
                        ' / 1e6'
                    ),
                    'traffic_rate_mbps': (
                        'same observed ROS CDR receive rate; not physical link '
                        'capacity'
                    ),
                    'telemetry_rate_hz': 'callback count / entire monotonic observation window',
                    'inter_arrival_ms': 'adjacent callback monotonic interval on one topic',
                    'jitter_ms': (
                        'sample standard deviation of within-topic inter-arrival '
                        'intervals'
                    ),
                    'cpu_pct': 'psutil process CPU; 100% means one logical CPU',
                    'rss_mib': 'resident bytes / 2^20; summed RSS can double-count shared pages',
                    'simulated_energy_wh': (
                        'trapezoidal integral of valid PX4 BatteryStatus '
                        'voltage*current / 3600'
                    ),
                    'latency': (
                        'unavailable until instrumented endpoints and valid clock '
                        'mapping exist'
                    ),
                    'packet_loss': (
                        'unavailable without sent/received sequence-numbered probe '
                        'counts'
                    )
                },
                'raw_sample_file': self.raw_path.name
            }
        )
        with self.json_path.open('x', encoding='utf-8') as stream:
            json.dump(document, stream, indent=2, allow_nan=False)
            stream.write('\n')
        exists = self.summary_path.exists()
        with self.summary_path.open('a', newline='', encoding='utf-8') as stream:
            writer = csv.DictWriter(stream, fieldnames=SUMMARY_FIELDS)
            if not exists or self.summary_path.stat().st_size == 0:
                writer.writeheader()
            writer.writerow(row)
        return document


def aggregate_runs(summary_csv, run_ids=None):
    """Between-run statistics; never treats callbacks as independent runs."""
    path = Path(summary_csv)
    with path.open(newline='', encoding='utf-8') as stream:
        rows = list(csv.DictReader(stream))
    if run_ids is not None:
        selected = set(run_ids)
        rows = [row for row in rows if row['run_id'] in selected]
    numeric = (
        (
            'observation_duration_s',
            'telemetry_rate_hz',
            'telemetry_jitter_ms',
            'throughput_mbps',
            'cpu_pct',
            'memory_mb',
            'memory_mib',
            'energy_wh'
        )
    )
    metrics = {}
    for name in numeric:
        values = []
        for row in rows:
            try:
                values.append(float(row[name]))
            except (KeyError, ValueError, TypeError):
                continue
        metrics[name] = describe(values, independent=True)
    return {
        'schema_version': 1,
        'run_count': len(rows),
        'run_ids': [row['run_id'] for row in rows],
        'statistics': metrics,
        'confidence_interval_note': (
            'Student t for <=30 run means; normal approximation above 30. Runs must'
            ' be independent under the same scenario.'
        )
    }
