"""Append-only run CSVs with explicitly scoped application measurements."""

import csv
from datetime import datetime, timezone
import json
import math
from pathlib import Path
import time


FIELDS = [
    'record_type', 'utc', 'elapsed_s', 'state', 'topic', 'direction',
    'source_timestamp_us', 'iat_ms', 'payload_cdr_bytes', 'count',
    'rate_hz', 'iat_mean_ms', 'iat_stddev_ms', 'total_payload_cdr_bytes',
    'payload_bytes_per_s', 'expected_count', 'estimated_missing_messages',
    'system_cpu_percent', 'node_cpu_percent', 'node_rss_mib',
    'x_north_m', 'y_east_m', 'z_down_m', 'armed', 'nav_state',
    'success', 'failure_state', 'failure_reason', 'detail',
]


class TopicStats:
    """Streaming sample standard deviation of callback inter-arrival intervals."""

    def __init__(self):
        self.count = self.bytes = self.n = 0
        self.mean = self.m2 = 0.
        self.last = None

    def add(self, now, size):
        iat = None if self.last is None else (now - self.last)*1000.
        if iat is not None:
            self.n += 1
            delta = iat - self.mean
            self.mean += delta / self.n
            self.m2 += delta * (iat-self.mean)
        self.last = now
        self.count += 1
        self.bytes += size
        return iat

    def summary(self, elapsed):
        return {
            'count': self.count, 'rate_hz': self.count / elapsed,
            'iat_mean_ms': self.mean if self.n else '',
            'iat_stddev_ms': math.sqrt(max(0., self.m2)/(self.n-1)) if self.n > 1 else '',
            'total_payload_cdr_bytes': self.bytes,
            'payload_bytes_per_s': self.bytes / elapsed,
            'expected_count': '', 'estimated_missing_messages': '',
        }


class RunLog:
    """Reserves run numbers exclusively; a partial file is never a PASS."""

    def __init__(self, directory, prefix='baseline_run', metadata=None):
        directory = Path(directory).expanduser()
        directory.mkdir(parents=True, exist_ok=True)
        number = 1
        while True:
            self.path = directory / f'{prefix}_{number:03d}.csv'
            try:
                self.file = self.path.open('x', newline='', encoding='utf-8')
                break
            except FileExistsError:
                number += 1
        self.writer = csv.DictWriter(self.file, fieldnames=FIELDS)
        self.writer.writeheader()
        self.start = time.monotonic()
        self.stats = {}
        self.finished = False
        self.row('metadata', detail=json.dumps(metadata or {}, sort_keys=True))
        self.file.flush()

    def row(self, record_type, **values):
        self.writer.writerow({
            'record_type': record_type,
            'utc': datetime.now(timezone.utc).isoformat(),
            'elapsed_s': time.monotonic()-self.start, **values,
        })

    def message(self, topic, direction, msg, size, state, receive_monotonic=None):
        now = time.monotonic() if receive_monotonic is None else receive_monotonic
        evidence = {
            'local_monotonic_s': now,
            'timestamp_sample_us': getattr(msg, 'timestamp_sample', None),
            'reset_counters': {name: getattr(msg, name) for name in (
                'xy_reset_counter', 'z_reset_counter', 'vxy_reset_counter',
                'vz_reset_counter', 'heading_reset_counter', 'quat_reset_counter')
                if hasattr(msg, name)},
            'clock_method': 'local reception/publish-call monotonic; native source retained',
        }
        stats = self.stats.setdefault((topic, direction), TopicStats())
        iat = stats.add(now, size)
        self.row('message', state=state, topic=topic, direction=direction,
                 source_timestamp_us=msg.timestamp, iat_ms='' if iat is None else iat,
                 payload_cdr_bytes=size, count=stats.count,
                 detail=json.dumps(evidence, allow_nan=False))

    def finish(self, success, failure_state='', reason='', state=''):
        if self.finished:
            return
        elapsed = max(time.monotonic()-self.start, 1e-9)
        for (topic, direction), stats in self.stats.items():
            self.row('topic_summary', topic=topic, direction=direction,
                     **stats.summary(elapsed))
        self.row('result', state=state, success=success, failure_state=failure_state,
                 failure_reason=reason,
                 detail=json.dumps({'mission_wall_duration_s': elapsed}))
        self.file.flush()
        self.file.close()
        self.finished = True
