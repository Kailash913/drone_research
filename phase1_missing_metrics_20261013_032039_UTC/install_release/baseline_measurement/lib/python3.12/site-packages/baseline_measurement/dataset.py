"""Import immutable baseline records and report metric eligibility without ROS."""
import argparse
from collections import defaultdict
import csv
from datetime import datetime, timezone
import hashlib
import json
import math
from pathlib import Path
import statistics
import uuid

from .experiment_logger import FIELDS
from .mission_state import STAGES
DEFINITIONS = (
    {
        'end_to_end_latency_ms': (
            'ms',
            'Unavailable: no correlated sender/receiver probe and clock error bound.'
        ),
        'telemetry_latency_ms': (
            'ms',
            'Unavailable: DDS timestamps are offset-adjusted; no independently validated '
            'clock mapping.'
        ),
        'command_latency_ms': (
            'ms',
            'Unavailable: ACK records lack a unique request identifier; no independently '
            'validated correlation.'
        ),
        'packet_loss_pct': (
            '%',
            'Unavailable: no identifiable transmitted transport packet/sequence denominator.'
        ),
        'rx_payload_mbps': (
            'Mbit/s',
            'Sum received ROS CDR bytes * 8 / whole monotonic run duration / 1e6; excludes '
            'transport headers.'
        ),
        'tx_payload_mbps': (
            'Mbit/s',
            'Sum local publish-call CDR bytes * 8 / whole monotonic run duration / 1e6; '
            'delivery unconfirmed.'
        ),
        'bandwidth_mbps': (
            'Mbit/s',
            'Unavailable: no wire capture or physical link-capacity measurement. Payload '
            'throughput is reported separately.'
        ),
        'node_cpu_pct': (
            '% of one logical CPU',
            'Arithmetic mean of finite primed psutil process CPU interval samples; process '
            'can exceed 100%.'
        ),
        'system_cpu_pct': (
            '%',
            'Arithmetic mean of finite psutil WSL guest CPU interval samples; excludes '
            'Windows host/QGC/GPU.'
        ),
        'node_rss_mib': (
            'MiB',
            'Arithmetic mean of mission-process resident bytes / 2^20, measured at resource '
            'callbacks.'
        ),
        'mission_completion_s': (
            's',
            'Logger monotonic initialization to terminal result, including preflight; '
            'successful active missions only.'
        ),
        'attempt_duration_s': (
            's',
            'Logger monotonic initialization to terminal result, including failed/passive '
            'attempts; not successful mission completion.'
        ),
        'energy_wh': (
            'Wh',
            'Physical UAV energy unavailable in SITL; simulated battery estimates are not '
            'physical energy.'
        ),
        'power_w': (
            'W',
            'Physical UAV power unavailable; requires calibrated battery current/voltage or '
            'external power analyzer.'
        )
    }
)


def digest(path):
    """Hash exact source bytes without modifying the input."""
    h = hashlib.sha256()
    with Path(path).open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            h.update(block)
    return h.hexdigest()


def finite(value):
    """Return a finite numeric observation or None, preserving measured zero."""
    try:
        result = float(value)
        return result if math.isfinite(result) else None
    except (TypeError, ValueError, OverflowError):
        return None


def stats(values):
    """Summarize independent run units without assuming experimental independence."""
    data = [v for v in values if v is not None]
    return {
        'n': len(data),
        'mean': statistics.mean(data) if data else None,
        'median': statistics.median(data) if data else None,
        'std': statistics.stdev(data) if len(data) > 1 else None,
        'min': min(data) if data else None,
        'max': max(data) if data else None,
        'ci95': None,
        'ci_note': 'Withheld: independent runs and configuration equivalence are not established.'
    }


class TimestampAudit:
    """Diagnose native delivered timestamps; never normalizes or controls flight."""

    def __init__(self):
        self.previous = {}
        self.high_water = {}
        self.receive_time = {}
        self.events = []

    def observe(self, topic, stamp, received, line=None, state=None):
        """Record receipt freshness separately from source ordering evidence."""
        self.receive_time[topic] = received
        try:
            value = int(stamp) if isinstance(stamp, int) or str(stamp).isdigit() else None
        except (TypeError, ValueError, OverflowError):
            value = None
        previous = self.previous.get(topic)
        high = self.high_water.get(topic)
        kind = None
        if value is None or value <= 0:
            kind = 'missing_or_invalid_source_timestamp'
        elif previous is not None and value < previous:
            kind = 'source_timestamp_regression'
        elif previous is not None and value == previous:
            kind = 'repeated_source_timestamp'
        elif high is not None and value < high:
            kind = 'source_timestamp_below_high_water'
        if kind:
            event = (
                {
                    'kind': kind,
                    'topic': topic,
                    'elapsed_s': received,
                    'previous_us': previous,
                    'current_us': value,
                    'line': line,
                    'state': state,
                    'estimator_reset_proven': False
                }
            )
            self.events.append(event)
        if value is not None and value > 0:
            self.previous[topic] = value
            self.high_water[topic] = max(value, high or 0)
        return kind

    def stale(self, topic, now, limit=2.0):
        """Check local receive age even if source values are invalid or repeated."""
        return now - self.receive_time.get(topic, -math.inf) >= limit


def inspect_csv(path):
    """Validate a RunLog CSV and retain raw-to-summary provenance."""
    path = Path(path).resolve()
    record = (
        {
            'source_file': str(path),
            'sha256': digest(path),
            'errors': [],
            'metadata_gaps': [],
            'metrics': {},
            'metric_validity': {},
            'mission_outcome': 'NOT_ATTEMPTED',
            'complete_record': False,
            'strict_experiment_valid': False,
            'experiment_id': None,
            'run_id': None,
            'duplicate_of': None
        }
    )
    errors = record['errors']
    meta = {}
    finals = []
    events = []
    resources = defaultdict(list)
    topic = (
        defaultdict(
            lambda: {'count': 0, 'bytes': 0, 'first_line': None, 'last_line': None, 'iat_ms': []}
        )
    )
    summaries = {}
    audit = TimestampAudit()
    previous_elapsed = -1.0
    metadata_count = 0
    reset_logs = []
    try:
        with path.open(newline='', encoding='utf-8') as stream:
            reader = csv.DictReader(stream)
            if reader.fieldnames != FIELDS:
                raise ValueError('Header does not match RunLog schema')
            for line, row in enumerate(reader, 2):
                if None in row or None in row.values():
                    raise ValueError(f'Malformed CSV row {line}')
                elapsed = finite(row['elapsed_s'])
                if elapsed is None or elapsed < previous_elapsed or elapsed < 0:
                    raise ValueError(f'Invalid/decreasing local elapsed time at {line}')
                previous_elapsed = elapsed
                utc = datetime.fromisoformat(row['utc'])
                if utc.tzinfo is None or utc.utcoffset().total_seconds() != 0:
                    raise ValueError(f'Timestamp not explicitly UTC at {line}')
                if line == 2:
                    record['start_utc'] = row['utc']
                record['end_utc'] = row['utc']
                kind = row['record_type']
                if kind == 'metadata':
                    metadata_count += 1
                    meta = json.loads(row['detail'])
                elif kind == 'message':
                    if row['direction'] not in ('rx_callback', 'tx_publish_call'):
                        raise ValueError(f'Unknown direction at {line}')
                    key = (row['topic'], row['direction'])
                    item = topic[key]
                    size = finite(row['payload_cdr_bytes'])
                    if size is None or size <= 0 or size != int(size):
                        raise ValueError(f'Invalid serialized payload size at {line}')
                    item['count'] += 1
                    item['bytes'] += int(size)
                    item['first_line'] = item['first_line'] or line
                    item['last_line'] = line
                    if int(row['count']) != item['count']:
                        raise ValueError(f'Inconsistent callback counter at {line}')
                    iat = finite(row['iat_ms'])
                    if iat is not None:
                        if iat < 0:
                            raise ValueError(f'Negative receive interval at {line}')
                        item['iat_ms'].append(iat)
                    if row['direction'] == 'rx_callback':
                        audit.observe(
                            row['topic'],
                            row['source_timestamp_us'],
                            elapsed,
                            line,
                            row['state']
                        )
                elif kind == 'topic_summary':
                    key = (row['topic'], row['direction'])
                    if key in summaries:
                        raise ValueError('Duplicate topic summary')
                    summaries[key] = row
                elif kind == 'resource':
                    for field in ('node_cpu_percent', 'system_cpu_percent', 'node_rss_mib'):
                        value = finite(row[field])
                        if row[field] and (value is None or value < 0):
                            errors.append(f'Invalid {field} at {line}')
                        if value is not None and value >= 0:
                            resources[field].append((line, elapsed, value))
                elif kind == 'event':
                    event = json.loads(row['detail'])['event']
                    events.append({'event': event, 'line': line, 'elapsed_s': elapsed})
                elif kind == 'source_clock_reset':
                    reset_logs.append(
                        {
                            'line': line,
                            'elapsed_s': elapsed,
                            'state': row['state'],
                            **json.loads(row['detail'])
                        }
                    )
                elif kind == 'result':
                    finals.append({'line': line, **row})
            if metadata_count != 1:
                errors.append('Exactly one metadata record required')
            if len(finals) != 1 or kind != 'result':
                errors.append('Exactly one terminal result required; incomplete record')
        duration = None
        final = finals[0] if len(finals) == 1 else {}
        if final:
            duration = finite(json.loads(final['detail']).get('mission_wall_duration_s'))
            if (
                    duration is None or duration <= 0
                    or abs(duration - float(final['elapsed_s'])) > 0.25
            ):
                errors.append('Invalid or inconsistent final monotonic duration')
        mode = meta.get('mode')
        record['mode'] = mode
        record['metadata'] = meta
        record['failure_stage'] = final.get('failure_state') or None
        record['failure_reason'] = final.get('failure_reason') or None
        record['reported_success'] = final.get('success')
        required = (
            [s + '_REACHED' for s in STAGES] + ['LANDED', 'DISARM', 'RELEASE_CONTROL', 'COMPLETE']
        )
        names = [e['event'] for e in events]
        complete_events = all((e in names for e in required))
        ordered = (
            complete_events and [names.index(e) for e in required]
            == sorted((names.index(e) for e in required))
        )
        if mode == 'SITL_MISSION':
            passed = (
                final.get('success') == 'True' and final.get('state') == 'COMPLETE'
                and not final.get('failure_reason') and ordered and (
                    not any(
                        (x in names for x in ('FAILSAFE', 'MISSION_FAIL', 'FAILSAFE_UNCONFIRMED'))
                    )
                )
            )
            record['mission_outcome'] = 'PASS' if passed and (not errors) else 'FAIL'
            if final.get('success') == 'True' and (not passed):
                errors.append('Claimed PASS lacks ordered safe-completion events')
        elif mode != 'PASSIVE_PREFLIGHT':
            errors.append('Unknown active/passive mode')
        elif any((k[1] == 'tx_publish_call' for k in topic)) or final.get('success') == 'True':
            errors.append('Passive capture contains control publication or claimed success')
        record['completion_evidence'] = events
        record['complete_record'] = bool(final and (not errors))
        record['original_run_id'] = meta.get('run_id')
        record['run_id'] = meta.get('run_id') or ('import-' + record['sha256'][:24])
        record['run_id_provenance'] = (
            'Recorded original metadata' if meta.get('run_id')
            else 'Deterministic importer identity; original run ID unavailable')
        record['experiment_id'] = meta.get('experiment_id')
        record['record_origin'] = (
            'RECORDED_IDENTITIES' if meta.get('run_id') and meta.get('experiment_id')
            else 'HISTORICAL_IMPORTED')
        record['duration_s'] = duration
        record['clock_anomalies'] = audit.events
        record['logged_reset_events'] = reset_logs
        record['clock_limitations'] = (
            [
                'CSV retains delivered timestamp only, not timestamp_sample, estimator '
                'flags/counters or XRCE session offset.',
                'Local elapsed time is monotonic; ordering anomalies do not prove estimator '
                'resets.'
            ]
        )
        record['topics'] = []
        payload_ok = record['complete_record'] and bool(topic) and (duration is not None)
        for key, item in sorted(topic.items()):
            summary = summaries.get(key)
            if (
                    summary is None or int(summary['count']) != item['count']
                    or int(summary['total_payload_cdr_bytes']) != item['bytes']
                    or duration is None or (
                        not math.isclose(
                            float(summary['rate_hz']),
                            item['count'] / duration,
                            rel_tol=1e-06
                        )
                    )
            ):
                errors.append(f'Raw/summary mismatch for {key}')
                payload_ok = False
            record['topics'].append(
                {
                    'topic': key[0],
                    'direction': key[1],
                    'count': item['count'],
                    'cdr_bytes': item['bytes'],
                    'observed_rate_hz': item['count'] / duration if duration else None,
                    'inter_arrival_ms': stats(item['iat_ms']),
                    'source_lines': [item['first_line'], item['last_line']]
                }
            )
        values = {name: None for name in DEFINITIONS}
        if payload_ok:
            for direction, metric in (
                ('rx_callback', 'rx_payload_mbps'),
                ('tx_publish_call', 'tx_payload_mbps')
            ):
                items = [v for k, v in topic.items() if k[1] == direction]
                if items:
                    values[metric] = sum((i['bytes'] for i in items)) * 8 / duration / 1000000.0
        mapping = (
            {
                'node_cpu_pct': 'node_cpu_percent',
                'system_cpu_pct': 'system_cpu_percent',
                'node_rss_mib': 'node_rss_mib'
            }
        )
        for metric, field in mapping.items():
            samples = resources[field]
            if samples:
                values[metric] = statistics.mean((x[2] for x in samples))
            record.setdefault('provenance', {})[metric] = (
                {
                    'csv_column': field,
                    'n': len(samples),
                    'lines': [x[0] for x in samples],
                    'sampling_interval_s': stats(
                        [b[1] - a[1] for a, b in zip(samples, samples[1:])]
                    ),
                    'scope': meta.get('cpu_scope', 'unknown')
                }
            )
        if record['complete_record'] and duration:
            values['attempt_duration_s'] = duration
            if record['mission_outcome'] == 'PASS':
                values['mission_completion_s'] = duration
        record['metrics'] = values
        record['metric_validity'] = (
            {
                name: {
                    'valid': value is not None,
                    'status': 'MEASURED_LIMITED' if value is not None else 'NOT_MEASURED',
                    'definition': DEFINITIONS[name][1],
                    'unit': DEFINITIONS[name][0],
                    'clock': ('local monotonic for duration/interval; '
                              'UTC for identity; psutil for resources'),
                    'missing_handling': 'null excluded from statistics; never imputed as zero'
                } for name,
                value in values.items()
            }
        )
        for field in (
            'experiment_id',
            'run_id',
            'config_sha256',
            'config_file',
            'px4_version',
            'simulator_version'
        ):
            if not meta.get(field):
                record['metadata_gaps'].append('Metadata missing ' + field)
        if not meta.get('source_sha256'):
            record['metadata_gaps'].append('Missing source hashes')
        grouping = (
            {
                k: meta.get(k) for k in (
                    'source_sha256',
                    'waypoint_offsets_m',
                    'control_rate_hz',
                    'dwell_s',
                    'segment_duration_s',
                    'position_tolerance_m',
                    'scheduling_gap_limit_s',
                    'outputs'
                )
            }
        )
        # Keep legacy grouping stable when original context is unavailable.
        # Separate recorded configuration/environment changes without inventing missing fields.
        for name in ('config_sha256', 'px4_version', 'simulator_version',
                     'publication_timestamp_domain', 'uxrce_dds_synct'):
            if meta.get(name) is not None:
                grouping[name] = meta[name]
        record['configuration_group'] = (
            hashlib.sha256(json.dumps(grouping, sort_keys=True).encode()).hexdigest()
        )
        record['configuration_equivalence'] = (
            'Recorded source/mission settings only; historical config file and environment '
            'not fully established.'
        )
        record['complete_record'] = bool(final and (not errors))
        record['strict_experiment_valid'] = (
            record['complete_record'] and (not record['metadata_gaps'])
        )
        if errors and record['mission_outcome'] == 'PASS':
            record['mission_outcome'] = 'FAIL'
    except (OSError, ValueError, KeyError, TypeError, OverflowError, csv.Error) as exc:
        errors.append(f'{type(exc).__name__}: {exc}')
        record['complete_record'] = False
    return record


def inspect_passive_json(path):
    """Validate legacy passive sample metadata without counting it as a flight."""
    path = Path(path).resolve()
    result = (
        {
            'source_file': str(path),
            'sha256': digest(path),
            'mode': 'PASSIVE_JSON',
            'mission_outcome': 'NOT_ATTEMPTED',
            'errors': [],
            'duplicate_of': None
        }
    )
    try:
        doc = json.loads(path.read_text())
        raw = (path.parent / doc['raw_sample_file']).resolve()
        if raw.parent != path.parent:
            raise ValueError('Raw file escapes input directory')
        result.update(
            experiment=doc['experiment'],
            raw_file=str(raw),
            raw_sha256=digest(raw),
            availability=doc.get('availability'),
            metrics=doc.get('metrics')
        )
        with raw.open(newline='', encoding='utf-8') as stream:
            reader = csv.DictReader(stream)
            from .experiment import RAW_FIELDS
            if tuple(reader.fieldnames or ()) != RAW_FIELDS:
                raise ValueError('Invalid passive raw schema')
            count = 0
            prior = -1.0
            raw_topics = defaultdict(lambda: {'count': 0, 'bytes': 0})
            for row in reader:
                count += 1
                if None in row or None in row.values():
                    raise ValueError('Malformed passive raw record')
                value = finite(row['value'])
                if row['value'] and value is None:
                    raise ValueError('Nonfinite/nonnumeric passive metric')
                if row['metric_name'].endswith(':payload_size'):
                    if value is None or value <= 0 or value != int(value):
                        raise ValueError('Invalid passive serialized payload size')
                    topic = row['metric_name'].removesuffix(':payload_size')
                    raw_topics[topic]['count'] += 1
                    raw_topics[topic]['bytes'] += int(value)
                if (
                        row['run_id'] != doc['experiment']['run_id']
                        or row['experiment_id'] != doc['experiment']['experiment_id']
                ):
                    raise ValueError('Raw/metadata identity mismatch')
                elapsed = finite(row['elapsed_s'])
                if elapsed is None or elapsed < prior:
                    raise ValueError('Invalid passive monotonic sequence')
                prior = elapsed
            result['raw_samples'] = count
            for topic, measured in raw_topics.items():
                reported = doc.get('topics', {}).get(topic, {})
                if (reported.get('count') != measured['count']
                        or reported.get('delivered_cdr_bytes') != measured['bytes']):
                    raise ValueError('Passive raw/JSON callback count or byte mismatch')
        if not count:
            raise ValueError('Empty passive measurements')
        result['complete_record'] = bool(doc['experiment'].get('end_time'))
        result['strict_experiment_valid'] = False
        result['limitation'] = (
            'Passive record excluded from active mission counts and active BASE cohort; '
            'historical environment/config provenance incomplete.'
        )
    except (OSError, ValueError, KeyError, TypeError) as exc:
        result['errors'].append(repr(exc))
        result['complete_record'] = False
    return result


def validate_dataset(directory, prior_manifest=None):
    """Import all attempts, allocate thirty study slots without success selection."""
    directory = Path(directory).expanduser().resolve()
    records = [inspect_csv(p) for p in sorted(directory.glob('baseline_run_*.csv'))]
    records += [inspect_csv(p) for p in sorted(directory.glob('preflight_*.csv'))]
    passive = [inspect_passive_json(p) for p in sorted(directory.glob('BASE-*_*.json'))]
    seen = {}
    for item in records + passive:
        identity = item['sha256']
        if identity in seen:
            item['duplicate_of'] = seen[identity]
        else:
            seen[identity] = item['source_file']
    groups = defaultdict(list)
    for item in records:
        if item.get('mode') == 'SITL_MISSION' and (not item['duplicate_of']):
            groups[item.get('configuration_group', 'unknown')].append(item)
    eligible_groups = {k: v for k, v in groups.items() if k != 'unknown'}
    primary = (
        max(
            eligible_groups,
            key=lambda k: (len(eligible_groups[k]), k)
        ) if eligible_groups else None
    )
    cohort = (
        sorted(
            eligible_groups.get(primary, []),
            key=lambda r: (r.get('start_utc', ''), r['source_file'])
        )
    )
    reserved = {}
    if prior_manifest:
        prior = json.loads(Path(prior_manifest).read_text())
        primary = prior.get('primary_configuration_group')
        if primary not in eligible_groups:
            old_sources = {r['sha256'] for r in prior['records']
                           if r.get('configuration_group') == primary}
            candidates = {r['configuration_group'] for r in records
                          if r['sha256'] in old_sources and not r['duplicate_of']}
            primary = next(iter(candidates)) if len(candidates) == 1 else None
        cohort = sorted(
            eligible_groups.get(primary, []),
            key=lambda r: (r.get('start_utc', ''), r['source_file']))
        reserved = (
            {r['sha256']: r['experiment_id'] for r in prior['records'] if r.get('experiment_id')}
        )
        if (
                len(set(reserved.values())) != len(reserved) or any(
                    (x not in {f'BASE-{n:03d}' for n in range(1, 31)} for x in reserved.values())
                )
        ):
            raise ValueError('Prior manifest contains duplicate or invalid study IDs')
    for record in records:
        record['study_id'] = str(directory)
        identity = record.get('metadata', {}).get('experiment_id')
        if record.get('mode') != 'SITL_MISSION' or record['duplicate_of'] or not identity:
            continue
        if identity not in {f'BASE-{n:03d}' for n in range(1, 31)}:
            raise ValueError('Recorded experiment ID is outside the study namespace')
        if record['sha256'] in reserved and reserved[record['sha256']] != identity:
            raise ValueError('Prior assignment conflicts with recorded original experiment ID')
        if any(k != record['sha256'] and value == identity for k, value in reserved.items()):
            raise ValueError('Conflicting original experiment IDs within one study')
        reserved[record['sha256']] = identity
    available = [f'BASE-{n:03d}' for n in range(1, 31) if f'BASE-{n:03d}' not in reserved.values()]
    for record in records:
        if not record['duplicate_of'] and record['sha256'] in reserved:
            record['experiment_id'] = reserved[record['sha256']]
    for record in cohort:
        if record['sha256'] in reserved:
            record['experiment_id'] = reserved[record['sha256']]
        elif available:
            record['experiment_id'] = available.pop(0)
        record['id_provenance'] = (
            'Recorded original experiment ID' if record.get('metadata', {}).get('experiment_id')
            else 'Retrospective active study namespace; original files remain unchanged.'
        )
    for record in records:
        if record['experiment_id']:
            record['id_provenance'] = (
                'Recorded original experiment ID'
                if record.get('metadata', {}).get('experiment_id')
                else 'Retrospective active study namespace; original files remain unchanged.')
    active = [r for r in records if r.get('mode') == 'SITL_MISSION' and (not r['duplicate_of'])]
    assigned = [r for r in active if r['experiment_id']]
    counts = (
        {
            'active_attempts': len(active),
            'active_pass': sum((r['mission_outcome'] == 'PASS' for r in active)),
            'active_fail': sum((r['mission_outcome'] == 'FAIL' for r in active)),
            'active_incomplete_or_invalid': sum((not r['complete_record'] for r in active)),
            'active_complete_records': sum((r['complete_record'] for r in active)),
            'study_slots_assigned': len(assigned),
            'study_complete_records': sum((r['complete_record'] for r in assigned)),
            'strict_valid_active_experiments': sum((r['strict_experiment_valid'] for r in active)),
            'strict_valid_study_experiments': sum(
                (r['strict_experiment_valid'] for r in assigned)
            ),
            'passive_runlogs': sum((r.get('mode') == 'PASSIVE_PREFLIGHT' for r in records)),
            'passive_json_records': len(passive),
            'duplicate_files': sum((bool(r['duplicate_of']) for r in records + passive))
        }
    )
    summaries = {}
    for group, runs in sorted(groups.items()):
        valid = [r for r in runs if r['complete_record']]
        metrics = {}
        for name in DEFINITIONS:
            observations = (
                [
                    {
                        'run_id': r['run_id'],
                        'experiment_id': r['experiment_id'],
                        'source_sha256': r['sha256'],
                        'value': r['metrics'].get(name)
                    } for r in valid if r['metric_validity'].get(name, {}).get('valid')
                ]
            )
            summary = stats([x['value'] for x in observations])
            summary.update(
                unit=DEFINITIONS[name][0],
                missing=len(runs) - len(observations),
                observations=observations
            )
            metrics[name] = summary
        passed = sum((r['mission_outcome'] == 'PASS' for r in runs))
        summaries[group] = (
            {
                'attempts': len(runs),
                'pass': passed,
                'fail': len(runs) - passed,
                'success_rate': passed / len(runs),
                'denominator': 'all unique active attempts in this recorded configuration group',
                'metrics': metrics
            }
        )
    return {
        'schema_version': 1,
        'generated_utc': datetime.now(timezone.utc).isoformat(),
        'input_directory': str(directory),
        'records': records,
        'passive_records': passive,
        'counts': counts,
        'primary_configuration_group': primary,
        'group_statistics': summaries,
        'metric_definitions': {k: {'unit': v[0], 'method': v[1]} for k, v in DEFINITIONS.items()},
        'overall_phase1': 'BLOCKED',
        'phase2_ready': False,
        'limitations': [
            'No new autonomous mission was launched by this validator.',
            'PASS requires controller COMPLETE plus ordered route/landing/disarm/release '
            'events, not independent external validation of every run.',
            'Passive JSON and preflight CSV can describe the same capture; their counts are '
            'not summed as experiments.',
            'No historical configuration hash/version is fabricated from current files.',
            'Thirty partial measurement records do not satisfy complete historical metadata '
            'or unavailable required metrics.',
            'No confidence intervals: independence and full configuration equivalence unverified.'
        ]
    }


def write_report(document, output):
    """Create an exclusive report directory; never overwrite raw data or reports."""
    output = Path(output).expanduser().resolve()
    output.mkdir(parents=True, exist_ok=False)
    serialized = json.dumps(document, indent=2, allow_nan=False) + '\n'
    (output / 'manifest.json').write_text(serialized)
    (output / 'validation_report.json').write_text(
        json.dumps(
            {
                'schema_version': 1,
                'counts': document['counts'],
                'phase1': document['overall_phase1'],
                'source_hashes': {
                    r['source_file']: r['sha256']
                    for r in document['records'] + document['passive_records']
                },
                'invalid_records': [
                    {
                        k: r.get(k) for k in ('source_file', 'errors', 'metadata_gaps')
                    } for r in document['records'] if r['errors'] or r['metadata_gaps']
                ],
                'missing_study_requirements': (
                    30 - document['counts']['strict_valid_study_experiments'])
            },
            indent=2,
            allow_nan=False
        ) + '\n'
    )
    fields = (
        [
            'study_id',
            'record_origin',
            'experiment_id',
            'run_id',
            'original_run_id',
            'run_id_provenance',
            'source_file',
            'sha256',
            'mode',
            'mission_outcome',
            'complete_record',
            'strict_experiment_valid',
            'failure_stage',
            'failure_reason',
            'configuration_group',
            'duplicate_of'
        ]
    )
    with (output / 'manifest.csv').open('x', newline='', encoding='utf-8') as stream:
        writer = csv.DictWriter(stream, fieldnames=fields, extrasaction='ignore')
        writer.writeheader()
        writer.writerows(document['records'])
    c = document['counts']
    lines = (
        [
            '# Phase 1 baseline validation',
            '',
            f"Unique active attempts: {c['active_attempts']}; "
            f"PASS: {c['active_pass']}; FAIL: {c['active_fail']}.",
            f"Complete active measurement records: {c['active_complete_records']}; "
            f"strict provenance-valid records: {c['strict_valid_active_experiments']}.",
            f"BASE-001..030 assigned: {c['study_slots_assigned']}; "
            f"complete study records: {c['study_complete_records']}; "
            f"strict study validity: {c['strict_valid_study_experiments']}/30.",
            '',
            'Mission outcome is independent of measurement usefulness. FAIL attempts can have'
            ' valid CPU/RSS/payload observations. Passive captures never count as successful '
            'flights.',
            '',
            '## Configuration groups',
            ''
        ]
    )
    for group, summary in document['group_statistics'].items():
        lines += [
            f"Group `{group[:12]}`: {summary['pass']}/{summary['attempts']} "
            f"active successes ({100 * summary['success_rate']:.2f}%).",
            '',
            '| Metric | Valid n | Missing n | Mean | Median | SD | Min | Max | Units |',
            '|---|---:|---:|---:|---:|---:|---:|---:|---|'
        ]
        for name, metric in summary['metrics'].items():

            def cell(value):
                return 'N/A' if value is None else f'{value:.6g}'
            lines.append(
                '| ' + ' | '.join(
                    [
                        name,
                        str(metric['n']),
                        str(metric['missing'])
                    ] + [cell(metric[k]) for k in ('mean', 'median', 'std', 'min', 'max')]
                    + [metric['unit']]
                ) + ' |'
            )
        lines.append('')
    lines += ['## Limitations', ''] + ['- ' + s for s in document['limitations']]
    (output / 'baseline_summary.md').write_text('\n'.join(lines) + '\n')


def main(args=None):
    """Validate existing measurements only; send no commands and collect no flights."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--input', required=True)
    parser.add_argument('--output')
    parser.add_argument('--prior-manifest')
    options = parser.parse_args(args)
    document = validate_dataset(options.input, options.prior_manifest)
    output = (
        options.output or str(
            Path(options.input).expanduser() / ('validation_' + uuid.uuid4().hex[:12])
        )
    )
    write_report(document, output)
    print(
        json.dumps(
            {'output': output, 'counts': document['counts'], 'phase1': document['overall_phase1']},
            indent=2
        )
    )
    return 0 if document['counts']['strict_valid_study_experiments'] >= 30 else 2


if __name__ == '__main__':
    raise SystemExit(main())
