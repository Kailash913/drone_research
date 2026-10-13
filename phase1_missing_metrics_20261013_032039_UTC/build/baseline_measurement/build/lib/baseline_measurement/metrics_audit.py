"""Reproduce baseline metrics from immutable raw evidence, separating active and passive runs."""
import argparse
from collections import Counter, defaultdict
import csv
from datetime import datetime, timezone
import json
import math
from pathlib import Path
import statistics
import struct

from .dataset import digest, inspect_csv
from .measurements import battery_energy, captured_traffic
from .metrics import describe


def summary(values):
    """Add exact nearest-rank p95; do not assume independent experimental samples."""
    values = [float(v) for v in values]
    result = describe(values)
    result['p95'] = sorted(values)[math.ceil(.95 * len(values)) - 1] if values else None
    result['p95_method'] = 'nearest rank'
    return result


def independent_run(path):
    """Recompute totals/statistics directly and cross-check the existing dataset importer."""
    record = inspect_csv(path)
    with Path(path).open(newline='') as stream:
        rows = list(csv.DictReader(stream))
    topics = defaultdict(list)
    resources = defaultdict(list)
    finals = [r for r in rows if r['record_type'] == 'result']
    duration = (json.loads(finals[-1]['detail'])['mission_wall_duration_s']
                if len(finals) == 1 else None)
    for row in rows:
        if row['record_type'] == 'message':
            topics[(row['topic'], row['direction'])].append(row)
        if row['record_type'] == 'resource':
            for field in ('system_cpu_percent', 'node_cpu_percent', 'node_rss_mib'):
                if row[field]:
                    resources[field].append(float(row[field]))
    independent = {'duration_s': duration,
                   'resources': {k: summary(v) for k, v in resources.items()},
                   'topics': [], 'validation_errors': list(record['errors'])}
    for (topic, direction), messages in sorted(topics.items()):
        times = [json.loads(r['detail']).get('local_monotonic_s') for r in messages]
        complete_times = all(t is not None for t in times)
        intervals = [(b - a) * 1000 for a, b in zip(times, times[1:])] if complete_times else []
        reported = [float(r['iat_ms']) for r in messages if r['iat_ms']]
        total = sum(int(r['payload_cdr_bytes']) for r in messages)
        item = {'topic': topic, 'direction': direction, 'count': len(messages), 'cdr_bytes': total,
                'rate_hz': len(messages) / duration if duration else None,
                'payload_mbps': total * 8 / duration / 1e6 if duration else None,
                'inter_arrival_ms': summary(intervals if complete_times else reported),
                'iat_recomputed_from_host_evidence': complete_times}
        if complete_times and (len(intervals) != len(reported) or any(
                not math.isclose(a, b, abs_tol=1e-6) for a, b in zip(intervals, reported))):
            independent['validation_errors'].append('Callback interval mismatch: ' + topic)
        logged_summary = next((r for r in rows if r['record_type'] == 'topic_summary'
                               and r['topic'] == topic and r['direction'] == direction), None)
        if logged_summary:
            for key, expected in [('iat_mean_ms', statistics.mean(reported) if reported else None),
                                  ('iat_stddev_ms', statistics.stdev(reported) if len(reported) > 1
                                   else None)]:
                actual = logged_summary[key]
                if expected is not None and (not actual or not math.isclose(
                        float(actual), expected, rel_tol=1e-6, abs_tol=1e-6)):
                    independent['validation_errors'].append(
                        'Inter-arrival summary mismatch: ' + topic)
        independent['topics'].append(item)
    for direction, name in [('rx_callback', 'rx_payload_mbps'),
                            ('tx_publish_call', 'tx_payload_mbps')]:
        items = [t for t in independent['topics'] if t['direction'] == direction]
        value = (sum(t['cdr_bytes'] for t in items) * 8 / duration / 1e6
                 if items and duration else None)
        independent[name] = value
        expected = record['metrics'].get(name)
        if value is not None and (expected is None or not math.isclose(
                value, expected, rel_tol=1e-12)):
            independent['validation_errors'].append('Importer payload mismatch: ' + name)
    publications = [json.loads(r['detail']) for r in rows
                    if r['record_type'] == 'command_publication']
    acks = [json.loads(r['detail']) for r in rows if r['record_type'] == 'command_ack']
    candidates = [r['elapsed_ns'] for r in acks if
                  r.get('association') == 'candidate_unverified_association' and 'elapsed_ns' in r]
    independent['commands'] = {'publication_count': len(publications), 'ack_count': len(acks),
                               'ack_results': dict(Counter(str(r['result']) for r in acks)),
                               'association_counts': dict(Counter(
                                   r.get('association_status', 'unmatched') for r in acks)),
                               'candidate_elapsed_ns': summary(candidates),
                               'validated_latency_count': 0,
                               'unresolved_publications': [r for r in publications if not any(
                                   a.get('publication_evidence', {}).get('publish_monotonic_ns')
                                   == r['publish_monotonic_ns'] for a in acks)],
                               'mission_timeout_events': [r for r in record['completion_evidence']
                                                          if 'TIMEOUT' in r['event']],
                               'limitations': 'ACK has no request ID or source system/component. '
                                              'Unresolved publications do not prove a '
                                              'command timeout.'}
    record['independent_recomputation'] = independent
    return record


def independent_pcap(path, packet_csv):
    """Decode raw packet records independently; classify observed IPv4 UDP endpoints."""
    formats = {b'\xd4\xc3\xb2\xa1': ('<', 1e6), b'\xa1\xb2\xc3\xd4': ('>', 1e6),
               b'M<\xb2\xa1': ('<', 1e9), b'\xa1\xb2<M': ('>', 1e9)}
    totals = Counter()
    flows = defaultdict(Counter)
    first = last = None
    with Path(path).open('rb') as stream, Path(packet_csv).open('x', newline='') as output:
        header = stream.read(24)
        if len(header) != 24 or header[:4] not in formats:
            raise ValueError('Classic PCAP required')
        endian, divisor = formats[header[:4]]
        link = struct.unpack(endian + 'I', header[20:24])[0]
        writer = csv.DictWriter(output, fieldnames=[
            'timestamp_s', 'original_bytes', 'captured_bytes',
            'source_ip', 'destination_ip', 'source_port',
            'destination_port', 'ip_bytes', 'udp_bytes'])
        writer.writeheader()
        while record := stream.read(16):
            if len(record) != 16:
                raise ValueError('Truncated packet header')
            seconds, fraction, included, original = struct.unpack(endian + 'IIII', record)
            if included > 16 * 1024 * 1024:
                raise ValueError('Capture packet size exceeds inspection bound')
            payload = stream.read(included)
            if len(payload) != included:
                raise ValueError('Truncated packet payload')
            stamp = seconds + fraction / divisor
            first = stamp if first is None else first
            last = stamp
            totals.update(packets=1, original_bytes=original, captured_bytes=included)
            row = {'timestamp_s': stamp, 'original_bytes': original, 'captured_bytes': included}
            offset = {1: 14, 113: 16, 276: 20}.get(link)
            if offset is not None and len(payload) >= offset + 28 and payload[offset] >> 4 == 4:
                ip = payload[offset:]
                ihl = (ip[0] & 15) * 4
                frag = int.from_bytes(ip[6:8], 'big')
                if ip[9] == 17 and ihl >= 20 and not frag & 0x3fff and len(ip) >= ihl + 8:
                    src, dst = struct.unpack('!HH', ip[ihl:ihl + 4])
                    ip_bytes = int.from_bytes(ip[2:4], 'big')
                    udp_bytes = int.from_bytes(ip[ihl + 4:ihl + 6], 'big')
                    row.update(source_ip='.'.join(str(v) for v in ip[12:16]),
                               destination_ip='.'.join(str(v) for v in ip[16:20]),
                               source_port=src, destination_port=dst,
                               ip_bytes=ip_bytes, udp_bytes=udp_bytes)
                    direction = ('agent_to_px4' if src == 8888 else
                                 'px4_to_agent' if dst == 8888 else 'other')
                    flows[direction].update(packets=1, original_frame_bytes=original,
                                            ip_bytes=ip_bytes, udp_bytes=udp_bytes)
            writer.writerow(row)
    return {'totals': dict(totals), 'flows': {k: dict(v) for k, v in flows.items()},
            'first_packet_s': first, 'last_packet_s': last, 'link_type': link,
            'pcap_sha256': digest(path), 'packet_csv': str(packet_csv)}


def create_report(workspace, output):
    """Write a new evidence-backed report; preserve unknowns and historical provenance."""
    workspace, output = Path(workspace), Path(output)
    output.mkdir(parents=True, exist_ok=False)
    active_paths = sorted(workspace.glob('phase1_active_run_*/baseline_run_001.csv'))
    active = [independent_run(p) for p in active_paths]
    passive = [independent_run(p) for p in sorted(
        (workspace / 'phase1_baseline_30').glob('preflight_*.csv'))]
    (output / 'active_runs.json').write_text(json.dumps(active, indent=2, allow_nan=False))
    (output / 'passive_runs.json').write_text(json.dumps(passive, indent=2, allow_nan=False))
    metrics = []

    def add(name, status, unit, values, method, evidence, limitation,
            sample_count=None, window=None):
        stats = summary(values)
        metrics.append({'metric': name, 'status': status, 'unit': unit,
                        'value': stats['mean'], 'statistics': stats,
                        'sample_count': stats['count'] if sample_count is None else sample_count,
                        'observation_window': window, 'method': method, 'data_source': evidence,
                        'validation_result': 'Raw recomputation and cross-check passed'
                        if status == 'VALIDATED'
                        else 'Experimental acceptance unavailable',
                        'limitations': limitation, 'uncertainty': None})
    valid = [r for r in active if r['mission_outcome'] == 'PASS'
             and not r['independent_recomputation']['validation_errors']]
    windows = [{'file': r['source_file'], 'start_utc': r['start_utc'], 'end_utc': r['end_utc'],
                'duration_s': r['duration_s']} for r in valid]
    sources = [r['source_file'] for r in valid]
    for key, unit in [('mission_completion_s', 's'), ('node_cpu_pct', '% of one logical CPU'),
                      ('system_cpu_pct', '% WSL guest'), ('node_rss_mib', 'MiB'),
                      ('rx_payload_mbps', 'Mbit/s'), ('tx_payload_mbps', 'Mbit/s')]:
        values = [r['metrics'][key] for r in valid if r['metrics'][key] is not None]
        add(key, 'VALIDATED' if values else 'NOT_MEASURED', unit, values,
            'Existing dataset importer independently checked against raw RunLog rows; '
            'statistics across per-run means', sources,
            'WSL simulation scope; historical configuration/version gaps remain; no '
            'independence CI',
            window=windows)
    add('active_mission_success', 'VALIDATED' if len(valid) == 5 else 'MEASURED_UNVALIDATED',
        'successful missions', [len(valid)], 'Ordered route/landing/disarm/completion events '
                                             'and terminal PASS',
        [r['source_file'] for r in active], 'Five observed runs do not establish a general '
                                            'reliability probability',
        sample_count=len(active), window=windows)
    by_topic = defaultdict(list)
    for run in valid:
        for topic in run['independent_recomputation']['topics']:
            if topic['direction'] == 'rx_callback':
                by_topic[topic['topic']].append(topic)
    for topic, samples in sorted(by_topic.items()):
        add('telemetry_rate:' + topic, 'VALIDATED', 'Hz', [s['rate_hz'] for s in samples],
            'Callback count / full per-run monotonic window; summary of run rates', sources,
            'Received callback rates; no transmitted-message denominator', window=windows)
        for metric, field in [('inter_arrival', 'mean'), ('jitter', 'std')]:
            values = [s['inter_arrival_ms'][field] for s in samples
                      if s['inter_arrival_ms'][field] is not None]
            add(metric + ':' + topic, 'VALIDATED' if values else 'NOT_MEASURED', 'ms', values,
                'Host monotonic adjacent reception intervals; sample SD for jitter', sources,
                'Summary across run-level statistics, not source-to-receiver latency',
                window=windows)
    blocks = {
        'command_latency': ('ns', 'No unique request ID/source identity; future authorized '
                                  'instrumented run '
                                  'needed for candidates and PX4-side evidence for confirmed '
                                  'association'),
        'command_candidate_interval': ('ns', 'Historical runs predate publication '
                                             'monotonic_ns evidence; '
                                             'do not reconstruct from delayed logger events'),
        'telemetry_latency': ('us', 'Native-to-host clock scale/offset validity interval and '
                                    'independent '
                                    'uncertainty validation absent; simultaneous native '
                                    'ULog/calibration needed'),
        'end_to_end_latency': ('us', 'Remote application endpoint with unique echoed request '
                                     'ID and '
                                     'common-clock evidence required; localhost bench '
                                     'is not UAV E2E'),
        'application_sequence_loss': ('fraction', 'PX4 path lacks observed sender and '
                                                  'receiver sequence '
                                                  'IDs and closed drain window'),
        'wire_packet_loss': ('fraction', 'Wire sender/receiver identities and capture/drop '
                                         'accounting at '
                                         'both endpoints required; a single capture is not a loss '
                                         'denominator'),
        'trajectory_rmse': ('m', 'No synchronized airborne truth/estimate samples and '
                                 'independently '
                                 'verified time/frame/origin mapping; new controlled flight '
                                 'requires permission'),
        'physical_power': ('W', 'Calibrated physical UAV voltage/current instrument required'),
        'physical_energy': ('J', 'Physical hardware and calibrated synchronized power window '
                                 'required'),
        'simulated_power': ('W', 'Battery simulator uses current_a=-1; no credible '
                                 'current/power model'),
        'simulated_energy': ('J', 'Invalid current must not be replaced with zero; model or '
                                  'sensor needed'),
        'physical_link_capacity': ('bit/s', 'WSL loopback offered traffic cannot measure '
                                            'radio link capacity')}
    for name, (unit, reason) in blocks.items():
        status = ('UNAVAILABLE_IN_CURRENT_SETUP'
                  if name.startswith(('physical_', 'simulated_')) else 'NOT_MEASURED')
        add(name, status, unit, [], reason, sources if 'command' in name else [], reason)
    pcaps = []
    historical_pcap = workspace / 'baseline_results/pcap/xrce_baseline.pcap'
    if historical_pcap.is_file():
        pcaps.append(('historical', historical_pcap, None))
    capture_file = output.parent / 'wire/capture.json'
    if capture_file.is_file():
        document = json.loads(capture_file.read_text())
        path = output.parent / 'wire/traffic.pcap'
        if path.is_file() and path.stat().st_size > 24:
            pcaps.append(('passive', path, document))
    pcap_results = []
    for label, path, document in pcaps:
        independent = independent_pcap(path, output / (label + '_packets.csv'))
        start = document['evidence']['start_s'] if document else independent['first_packet_s']
        end = (document['evidence']['end_s'] if document else
               math.nextafter(independent['last_packet_s'], math.inf))
        parsed = captured_traffic(path, start, end, document['evidence'] if document else
                                  {'scope': 'historical PCAP; original observation '
                                            'window/drop metadata missing'})
        matched = (parsed['packet_count'] == independent['totals']['packets'] and
                   parsed['original_frame_bytes'] == independent['totals']['original_bytes'] and
                   parsed['captured_bytes'] == independent['totals']['captured_bytes'])
        independently_valid = matched and document and document['status'] == 'VALIDATED'
        if independently_valid:
            duration = document['evidence']['monotonic_window_s']
        else:
            duration = end - start
        add('wire_throughput_' + label,
            'VALIDATED' if independently_valid else 'MEASURED_UNVALIDATED',
            'bit/s', [parsed['original_frame_bytes'] * 8 / duration],
            'Captured original frame bytes * 8 / bounded capture window; two parsers agree',
            [str(path), str(output / (label + '_packets.csv'))],
            'Both directions, WSL loopback; excludes physical radio. ' + (
                'Captured drop counts present; no inference about network loss'
                if independently_valid
                else 'Historical capture window, interface, filter and drops are not recorded'),
            sample_count=parsed['packet_count'],
            window={'start_s': start, 'end_s': end, 'duration_s': duration})
        pcap_results.append({'source': str(path), 'parser': parsed, 'independent': independent,
                             'byte_totals_agree': matched, 'capture_metadata': document})
    (output / 'pcap_validation.json').write_text(
        json.dumps(pcap_results, indent=2, allow_nan=False))
    observation_file = output.parent / 'passive/observations.jsonl'
    passive_collection = None
    if observation_file.is_file():
        observations = [json.loads(line) for line in observation_file.read_text().splitlines()]
        counts = Counter(r['kind'] for r in observations)
        batteries = [r for r in observations if r['kind'] == 'battery']
        computed = battery_energy(batteries, 2.)
        collection_path = output.parent / 'passive/collection.json'
        recorded = json.loads(collection_path.read_text()) if collection_path.is_file() else {}
        checks = (computed == recorded.get('battery')
                  and digest(observation_file) == recorded.get('raw_sha256'))
        passive_collection = {'counts': dict(counts), 'airborne_estimate_count': sum(
            r.get('airborne') is True for r in observations if r['kind'] == 'estimate'),
                              'battery_recomputation_agrees': checks,
                              'battery': computed,
                              'raw_file': str(observation_file),
                              'sha256': digest(observation_file),
                              'observed_currents': sorted({r.get('current_a') for r in batteries
                                                          if r.get('current_a') is not None}),
                              'mission_outcome': 'NOT_ATTEMPTED'}
    matrix = []
    for item in metrics:
        metric = item['metric']
        implementation = ('mission_node.py; measurements.correlated_latency'
                          if 'command' in metric else
                          'trajectory_metrics.py; passive_metrics.py'
                          if 'trajectory' in metric else
                          'wire_capture.py; measurements.captured_traffic'
                          if 'wire_throughput' in metric else
                          'measurements.sequence_loss' if 'loss' in metric else
                          'measurements.battery_energy; measurements.power_energy' if
                          'power' in metric or 'energy' in metric else
                          'measurements.clock_latency; clock_probe.py' if 'latency' in metric else
                          'dataset.inspect_csv; metrics_audit.independent_run')
        matrix.append({'metric': metric, 'status': item['status'],
                       'implementation': implementation,
                       'data_source': json.dumps(item['data_source']),
                       'validation_test': 'test_missing_metrics.py; test_preflight.py; '
                                          'test_measurements.py; '
                                          'test_dataset.py; independent raw recomputation',
                       'output_file': str(output / 'results.json'),
                       'acceptance_criterion': (item['method'] +
                                                '; real nonempty evidence with correct '
                                                'scope/units, '
                                                'raw recomputation agreement and disclosed '
                                                'invalid observations'),
                       'blocker': item['limitations'] if item['status'] != 'VALIDATED' else '',
                       'actually_measured': item['sample_count'] > 0,
                       'raw_evidence_exists': bool(item['data_source']),
                       'independently_reproducible': item['status'] == 'VALIDATED',
                       'another_run_or_hardware_required': item['status'] != 'VALIDATED'})
    report = {'created_utc': datetime.now(timezone.utc).isoformat(),
              'objective_complete': False, 'active_success_count': len(valid),
              'historical_passive_count': len(passive), 'metrics': metrics,
              'active_run_windows': windows, 'passive_collection': passive_collection,
              'provenance_gaps': {r['source_file']: r['metadata_gaps'] for r in active},
              'raw_hashes': {r['source_file']: r['sha256'] for r in active + passive},
              'blockers': {item['metric']: item['limitations'] for item in metrics
                           if item['status'] not in ('VALIDATED',)},
              'limitations': 'No flight executed. Collector method tests are synthetic '
                             'fixtures only. '
                             'Measured per-run statistics do not repair missing '
                             'historical provenance.'}
    (output / 'results.json').write_text(json.dumps(report, indent=2, allow_nan=False))
    for name, records in [('requirements_to_evidence.csv', matrix), ('metric_summary.csv', [
            {'metric': x['metric'], 'status': x['status'], 'value': x['value'], 'unit': x['unit'],
             'sample_count': x['sample_count'], 'mean': x['statistics']['mean'],
             'std': x['statistics']['std'], 'median': x['statistics']['median'],
             'p95': x['statistics']['p95'],
             'observation_window': json.dumps(x['observation_window']),
             'method': x['method'], 'evidence': json.dumps(x['data_source']),
             'limitations': x['limitations']} for x in metrics])]:
        with (output / name).open('x', newline='') as stream:
            writer = csv.DictWriter(stream, fieldnames=list(records[0]) if records else [])
            writer.writeheader()
            writer.writerows(records)
    lines = ['# Phase 1 missing-metrics evidence report', '',
             'The objective remains incomplete. Five active missions were verified separately '
             'from '
             '30 historical passive captures. Missing metrics remain blocked as listed below.', '',
             '| Metric | Status | Value | Evidence / blocker |', '|---|---|---|---|']
    for item in metrics:
        value = f"{item['value']:.6g} {item['unit']}" if item['value'] is not None else 'N/A'
        lines.append(f"| {item['metric']} | {item['status']} | {value} | "
                     f"{item['limitations']} See metric_summary.csv and results.json. |")
    lines += ['', '## Run provenance', '',
              'Original experiment IDs, configuration paths/hashes and PX4/Gazebo version '
              'evidence '
              'are missing in all five active logs. Source byte hashes and original run IDs '
              'are retained; '
              'current environment details do not establish historical versions. See '
              'active_runs.json.', '',
              '## Acceptance gate', '',
              'requirements_to_evidence.csv records implementation, raw source, acceptance '
              'criterion, '
              'validation method and remaining blockers. No candidate interval is accepted as '
              'validated '
              'latency. No physical-power or radio-link claim is made.', '',
              '## Reproduction', '',
              'Source the ROS Jazzy and px4_msgs workspace environments, then from the '
              'package run:', '',
              '```bash', 'PYTHONDONTWRITEBYTECODE=1 PYTHONPATH="$PWD:$PYTHONPATH" python3 -m '
              f'baseline_measurement.metrics_audit --workspace {workspace} '
              '--output /tmp/new_phase1_report',
              '```', '', 'To include the new passive and wire records, place their '
                         'directories beside '
                         'the new report directory, as in this evidence bundle. '
                         'Inputs are never rewritten.']
    (output / 'FINAL_REPORT.md').write_text('\n'.join(lines) + '\n')
    return report


def main(args=None):
    """Analyze existing evidence and write an exclusive new report directory."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--workspace', required=True)
    parser.add_argument('--output', required=True)
    options = parser.parse_args(args)
    report = create_report(options.workspace, options.output)
    print(json.dumps({'output': options.output,
                      'active_success_count': report['active_success_count'],
                      'objective_complete': report['objective_complete']}, indent=2))


if __name__ == '__main__':
    main()
