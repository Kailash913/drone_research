"""Export retained native ULog evidence without guessing cross-domain clock calibration."""
import argparse
from datetime import datetime, timezone
import json
import math
from pathlib import Path

from .dataset import digest
from .measurements import battery_energy

TOPICS = ('vehicle_local_position', 'vehicle_local_position_groundtruth', 'timesync_status',
          'vehicle_land_detected', 'vehicle_status', 'battery_status')
FIELDS = ('timestamp', 'timestamp_sample', 'x', 'y', 'z', 'ref_lat', 'ref_lon', 'ref_alt',
          'xy_valid', 'z_valid', 'xy_global', 'z_global', 'dead_reckoning',
          'xy_reset_counter', 'z_reset_counter', 'heading_reset_counter',
          'arming_state', 'landed', 'voltage_v', 'current_a', 'connected',
          'estimated_offset', 'observed_offset', 'remote_timestamp', 'source_protocol',
          'round_trip_time')


def export_logs(paths, output):
    """Retain actual logged versions/parameters as sidecars, never rewrite historical CSVs."""
    from pyulog import ULog

    output = Path(output)
    output.mkdir(parents=True, exist_ok=False)
    results = []
    for path in paths:
        path = Path(path)
        before = digest(path)
        log = ULog(str(path), message_name_filter_list=list(TOPICS))
        exported = output / (path.parent.name + '_' + path.stem + '.jsonl')
        counts = {}
        batteries = []
        reset_values = {}
        references = {}
        with exported.open('x') as stream:
            for topic in log.data_list:
                count = len(topic.data['timestamp'])
                counts[f'{topic.name}:{topic.multi_id}'] = count
                if topic.name == 'vehicle_local_position':
                    reset_values = {k: sorted({int(v) for v in topic.data[k]}) for k in
                                    ('xy_reset_counter', 'z_reset_counter',
                                     'heading_reset_counter')}
                if topic.name in ('vehicle_local_position', 'vehicle_local_position_groundtruth'):
                    references[topic.name] = {
                        k: [float(topic.data[k][0]), float(topic.data[k][-1])]
                        for k in ('ref_lat', 'ref_lon', 'ref_alt')}
                for i in range(count):
                    row = {k: topic.data[k][i].item() for k in FIELDS if k in topic.data}
                    # Invalid native floats remain null; they are never measured zeros.
                    row = {k: None if isinstance(v, float) and not math.isfinite(v) else v
                           for k, v in row.items()}
                    row.update(topic=topic.name, multi_id=topic.multi_id,
                               source_domain='px4_native_boot_us',
                               host_receive_monotonic_ns=None)
                    stream.write(json.dumps(row, allow_nan=False) + '\n')
                    if topic.name == 'battery_status':
                        batteries.append(dict(row, monotonic_s=row['timestamp'] / 1e6))
        after = digest(path)
        if before != after:
            raise ValueError('Native log changed during analysis; cannot use a moving input')
        results.append({'raw_file': str(path), 'sha256': before,
                        'exported_file': str(exported), 'exported_sha256': digest(exported),
                        'native_start_us': log.start_timestamp,
                        'native_end_us': log.last_timestamp, 'topics': counts,
                        'recorded_firmware_hash': log.msg_info_dict.get('ver_sw'),
                        'recorded_release': log.msg_info_dict.get('ver_sw_release'),
                        'recorded_system_uuid': log.msg_info_dict.get('sys_uuid'),
                        'recorded_dds_sync_parameter': log.initial_parameters.get(
                            'UXRCE_DDS_SYNCT'),
                        'reset_counter_values': reset_values, 'position_references': references,
                        'battery': battery_energy(batteries, 2.),
                        'observed_current_values': sorted({r['current_a'] for r in batteries
                                                          if r.get('current_a') is not None}),
                        'clock_calibration_validated': False,
                        'trajectory_rmse_status': 'NOT_MEASURED',
                        'limitations': 'Groundtruth is Gazebo world pose exported by GZBridge, '
                        'timestamped with native hrt at callback entry. Pose acquisition '
                        'timestamp '
                        'and transport-age uncertainty were not logged. Reference altitude '
                        'differs '
                        'from world origin; independent frame/origin validation is required. UTC '
                        'filename overlap alone is a candidate run association, '
                        'not unique proof.'})
    document = {'created_utc': datetime.now(timezone.utc).isoformat(), 'logs': results,
                'status': 'MEASURED_UNVALIDATED', 'historical_files_modified': False}
    with (output / 'native_log_audit.json').open('x') as stream:
        json.dump(document, stream, indent=2, allow_nan=False)
    return document


def main(args=None):
    """Audit explicit closed log paths only; no PX4 connections or parameter writes."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--input', action='append', required=True)
    parser.add_argument('--output', required=True)
    options = parser.parse_args(args)
    print(json.dumps({'logs': len(export_logs(options.input, options.output)['logs'])}))


if __name__ == '__main__':
    main()
