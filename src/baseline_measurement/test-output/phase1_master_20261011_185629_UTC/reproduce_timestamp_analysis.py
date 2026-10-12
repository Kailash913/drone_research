"""Analyze retained and new passive evidence; never convert it to flight success."""
import csv
from datetime import datetime
import hashlib
import json
from pathlib import Path
import sys

home = Path.home()
package = home / 'ros2_ws/src/baseline_measurement'
audit = package / 'test-output/phase1_master_20261011_185629_UTC'
import argparse
parser = argparse.ArgumentParser()
parser.add_argument('--output', required=True, help='New destination for regenerated analysis')
args = parser.parse_args()
out = Path(args.output)
assert not out.exists(), 'Use a new evidence destination'
out.mkdir(exist_ok=True)
sys.path.insert(0, str(package))
from baseline_measurement.diagnostic_analysis import dds_deviations, heading_explanation
from pyulog import ULog


def analyze_probe(path):
    with path.open(newline='', encoding='utf-8') as stream:
        rows = list(csv.DictReader(stream))
    messages = [r for r in rows if r['record_type'] == 'message']
    dds = [{'utc': r['utc'], 'receive_monotonic_s': float(r['local_monotonic_s']),
            **json.loads(r['detail'])} for r in messages
           if r['topic'] == '/fmu/out/timesync_status']
    diagnosis = dds_deviations(dds)
    intervals = diagnosis['intervals_before_first_zero']
    diagnosis['native_to_peer_cumulative_ratio_before_zero'] = (
        sum(r['native_midpoint_delta_us'] for r in intervals) /
        sum(r['peer_delta_us'] for r in intervals) if intervals else None)
    before = diagnosis['samples'][:diagnosis['zero_transition_indices'][0]] \
        if diagnosis['zero_transition_indices'] else diagnosis['samples']
    diagnosis['before_zero_count'] = len(before)
    diagnosis['before_zero_qualifying_if_converged'] = sum(
        r['qualifying_if_filter_converged'] for r in before)
    diagnosis['before_zero_max_rtt_us'] = max((r['round_trip_time'] for r in before), default=None)
    steps = []
    for first, second in zip(messages, messages[1:]):
        wall = (datetime.fromisoformat(second['utc']) - datetime.fromisoformat(first['utc'])).total_seconds()
        mono = float(second['local_monotonic_s']) - float(first['local_monotonic_s'])
        if abs(wall - mono) > 0.1:
            steps.append({'before_utc': first['utc'], 'after_utc': second['utc'],
                          'wall_delta_s': wall, 'monotonic_delta_s': mono,
                          'wall_minus_monotonic_s': wall - mono})
    latest = {}
    counts = {}
    flag_sets = {}
    for row in messages:
        topic = row['topic']
        detail = json.loads(row['detail'])
        latest[topic] = {'utc': row['utc'], 'local_monotonic_s': row['local_monotonic_s'],
                         'native_delivered_fields': detail}
        counts[topic] = counts.get(topic, 0) + 1
        for field in ('heading_good_for_control', 'cs_yaw_align', 'cs_mag_hdg', 'cs_mag_3d',
                      'cs_mag_aligned_in_flight', 'cs_mag_fault', 'cs_mag_field_disturbed',
                      'fs_bad_hdg', 'landed', 'arming_state', 'nav_state', 'failsafe'):
            if field in detail:
                flag_sets.setdefault(field, set()).add(detail[field])
    duration = float(rows[-1]['elapsed_s'])
    flags = latest.get('/fmu/out/estimator_status_flags', {}).get('native_delivered_fields', {})
    return {'source': str(path), 'source_sha256': hashlib.sha256(path.read_bytes()).hexdigest(),
            'duration_monotonic_s': duration, 'message_counts': counts,
            'observed_callback_hz': {k: v / duration for k, v in counts.items()},
            'latest_topic_values': latest, 'observed_flag_values': {k: sorted(v) for k, v in flag_sets.items()},
            'heading_branch_explanation': heading_explanation(flags),
            'receiver_wall_steps': steps, 'dds_analysis': diagnosis,
            'not_mission_or_latency_measurement': True}

old = next((home / 'ros2_ws/baseline_results/phase1_study_36527160a48f/clock_BASE-001').glob('*.csv'))
current = next((audit / 'passive_clock').glob('*.csv'))
for label, path in [('failed_run', old), ('current_passive', current)]:
    data = analyze_probe(path)
    (out / (label + '_analysis.json')).write_text(json.dumps(data, indent=2) + '\n', encoding='utf-8')
    print(label, json.dumps({
        'clock_ratio': data['dds_analysis']['native_to_peer_cumulative_ratio_before_zero'],
        'zero_indices': data['dds_analysis']['zero_transition_indices'],
        'before_count': data['dds_analysis']['before_zero_count'],
        'qualifying_if_converged': data['dds_analysis']['before_zero_qualifying_if_converged'],
        'max_rtt_us': data['dds_analysis']['before_zero_max_rtt_us'],
        'flags': data['observed_flag_values'], 'heading': data['heading_branch_explanation']}, indent=2))

native = home / 'PX4-Autopilot/build/px4_sitl_default/rootfs/log/2026-10-11/18_06_55.ulg'
ulog = ULog(str(native), message_name_filter_list=['vehicle_local_position', 'vehicle_attitude',
            'estimator_status_flags', 'vehicle_status', 'vehicle_land_detected', 'timesync_status'])
summary = {'source': str(native), 'sha256': hashlib.sha256(native.read_bytes()).hexdigest(),
           'ver_sw': ulog.msg_info_dict.get('ver_sw'), 'dropouts': len(ulog.dropouts),
           'topics': {}, 'start_native_us': ulog.start_timestamp, 'end_native_us': ulog.last_timestamp}
for dataset in ulog.data_list:
    data = dataset.data
    timestamp = data['timestamp']
    values = {name: sorted(set(int(v) for v in data[name])) for name in data
              if name in ('heading_good_for_control', 'cs_yaw_align', 'cs_mag_hdg', 'cs_mag_3d',
                          'cs_mag_aligned_in_flight', 'cs_mag_fault', 'cs_mag_field_disturbed',
                          'fs_bad_hdg', 'cs_in_air', 'arming_state', 'landed')}
    counters = {name: sum(int(data[name][i]) != int(data[name][i - 1]) for i in range(1, len(timestamp)))
                for name in data if 'reset_counter' in name}
    summary['topics'][dataset.name + ':' + str(dataset.multi_id)] = {
        'n': len(timestamp), 'native_regressions': sum(int(timestamp[i]) < int(timestamp[i - 1])
                                                     for i in range(1, len(timestamp))),
        'observed_flag_values': values, 'counter_changes_whole_log': counters}
(out / 'native_heading_and_reset_evidence.json').write_text(json.dumps(summary, indent=2) + '\n', encoding='utf-8')
print(json.dumps(summary, indent=2))