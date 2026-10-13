"""Validate recorded passive evidence without starting ROS or a controller."""

import argparse
from collections import Counter
import csv
from datetime import datetime
import json
import math
from pathlib import Path

from .experiment_logger import FIELDS


REQUIRED = ('status', 'position', 'attitude', 'land', 'battery')


def validate_capture(path, expected_seconds=15., startup_seconds=5., stable_seconds=5.):
    """Return a passive acceptance decision; never label it a mission success."""
    path = Path(path).expanduser()
    result = {'csv': str(path), 'category': 'A_PASSIVE', 'decision': 'FAIL',
              'errors': [], 'mission_status': 'not_demonstrated'}
    errors = result['errors']
    try:
        with path.open(newline='', encoding='utf-8') as stream:
            reader = csv.DictReader(stream)
            if reader.fieldnames != FIELDS:
                raise ValueError('CSV schema differs from RunLog.FIELDS')
            rows = list(reader)
        if not rows or any(None in row or None in row.values() for row in rows):
            raise ValueError('Empty or malformed CSV')
        elapsed = [float(row['elapsed_s']) for row in rows]
        if (not all(math.isfinite(t) and t >= 0 for t in elapsed)
                or any(b < a for a, b in zip(elapsed, elapsed[1:]))):
            raise ValueError('Invalid or decreasing monotonic elapsed times')
        utc = [datetime.fromisoformat(row['utc']) for row in rows]
        if any(t.tzinfo is None for t in utc):
            errors.append('UTC timestamps lack time zones')
        metadata = [row for row in rows if row['record_type'] == 'metadata']
        finals = [row for row in rows if row['record_type'] == 'result']
        if len(metadata) != 1 or len(finals) != 1 or rows[-1]['record_type'] != 'result':
            raise ValueError('Exactly one metadata and terminal result required')
        meta = json.loads(metadata[0]['detail'])
        final = finals[0]
        duration = float(json.loads(final['detail'])['mission_wall_duration_s'])
        if not math.isfinite(duration):
            raise ValueError('Non-finite duration')
        result.update(start_utc=rows[0]['utc'], end_utc=final['utc'], duration_s=duration)
        if not expected_seconds <= duration <= expected_seconds + 2.:
            errors.append('Observation duration outside requested duration + 2 s tolerance')
        if meta.get('mode') != 'PASSIVE_PREFLIGHT':
            errors.append('Metadata does not identify passive mode')
        if (final['success'] != '' or final['state'] != 'PREFLIGHT'
                or final['failure_reason'] != 'Passive observation only; no mission attempted'):
            errors.append('Final result is incomplete, interrupted, or not passive')
        tx = sum(row['direction'] == 'tx_publish_call' for row in rows)
        commands = sum(row['record_type'] == 'command' for row in rows)
        result['publication_records'] = tx
        if tx or commands:
            errors.append('Control publication/command records found')
        messages = [row for row in rows if row['record_type'] == 'message'
                    and row['direction'] == 'rx_callback']
        prior = {}
        regressions = []
        for row in messages:
            topic, stamp = row['topic'], int(row['source_timestamp_us'])
            if stamp < prior.get(topic, 0):
                regressions.append({'topic': topic, 'elapsed_s': float(row['elapsed_s']),
                                    'previous_us': prior[topic], 'current_us': stamp})
            prior[topic] = max(stamp, prior.get(topic, 0))
        result['source_clock_regressions'] = regressions
        if regressions:
            errors.append('Received source timestamp regressed; '
                          'clock/reset guard must remain latched')
        counts = Counter(row['topic'] for row in messages)
        summaries = {
            row['topic']: row for row in rows
            if row['record_type'] == 'topic_summary' and row['direction'] == 'rx_callback'}
        result['topics'] = {}
        for key in REQUIRED:
            topic = meta['outputs'][key]
            samples = [row for row in messages if row['topic'] == topic]
            summary = summaries.get(topic)
            advancing = len({row['source_timestamp_us'] for row in samples}) >= 2
            if not summary or counts[topic] < 2 or not advancing:
                errors.append(f'{key}: no advancing received telemetry and summary')
                continue
            rate = float(summary['rate_hz'])
            if (int(summary['count']) != counts[topic] or not math.isfinite(rate)
                    or not math.isclose(rate, counts[topic] / duration, rel_tol=1e-6)):
                errors.append(f'{key}: inconsistent count/rate summary')
            if summary['expected_count'] or summary['estimated_missing_messages']:
                errors.append(f'{key}: unsupported expected/lost message measurements')
            result['topics'][key] = {'topic': topic, 'count': counts[topic], 'rate_hz': rate}
        resources = [row for row in rows if row['record_type'] == 'resource']
        result['resource_records'] = len(resources)
        checks = []
        for row in resources:
            state = json.loads(row['detail'])
            safe = (all(state.get(k) is True
                        for k in ('connected', 'healthy', 'valid', 'landed'))
                    and state.get('competition') is False and row['armed'] == 'False')
            checks.append((float(row['elapsed_s']), safe, state.get('heading_ready')))
            if state.get('competition') is not False or row['armed'] != 'False':
                errors.append('Competing publisher or armed vehicle observed')
        first = next((t for t, safe, _ in checks if safe), None)
        result['first_valid_sample_s'] = first
        stable = [(t, safe, heading) for t, safe, heading in checks if t >= startup_seconds]
        result['startup_records'] = sum(t < startup_seconds for t, _, _ in checks)
        result['stable_records'] = len(stable)
        result['heading_ready_at_end'] = checks[-1][2] if checks else None
        clear = checks and all(json.loads(row['detail']).get('competition') is False
                               for row in resources)
        result['publisher_status'] = 'clear' if clear else 'unverified'
        if first is None or first > startup_seconds:
            errors.append('Telemetry did not become valid within startup allowance')
        if (len(stable) < 2 or not all(safe for _, safe, _ in stable)
                or stable[-1][0] - stable[0][0] < stable_seconds
                or duration - stable[-1][0] > 1.5
                or any(b[0] - a[0] > 1.5 for a, b in zip(stable, stable[1:]))):
            errors.append('Insufficient continuous stable sampled telemetry window')
    except (OSError, ValueError, KeyError, TypeError, OverflowError,
            AttributeError, IndexError, csv.Error) as exc:
        errors.append(f'{type(exc).__name__}: {exc}')
    result['decision'] = 'FAIL' if errors else 'PASS'
    return result


def main(args=None):
    """Check each capture independently and return nonzero on any failure."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('csv', nargs='+')
    parser.add_argument('--expected-seconds', type=float, default=15.)
    parser.add_argument('--output', help='New JSON evidence file; refuses overwrite')
    options = parser.parse_args(args)
    if not math.isfinite(options.expected_seconds) or options.expected_seconds < 10.:
        parser.error('--expected-seconds must be finite and at least 10')
    paths = [Path(p).expanduser().resolve() for p in options.csv]
    if len(set(paths)) != len(paths):
        parser.error('Each capture must have a distinct path')
    runs = [validate_capture(p, options.expected_seconds) for p in paths]
    document = {'schema_version': 1, 'category': 'A_PASSIVE', 'runs': runs,
                'all_passed': all(r['decision'] == 'PASS' for r in runs),
                'phase1_status': 'PARTIALLY COMPLETE',
                'note': 'Passive demonstrations do not establish mission or QGC control success.'}
    serialized = json.dumps(document, indent=2, allow_nan=False)
    if options.output:
        with Path(options.output).expanduser().open('x', encoding='utf-8') as stream:
            stream.write(serialized + '\n')
    print(serialized)
    return 0 if document['all_passed'] else 1


if __name__ == '__main__':
    raise SystemExit(main())
