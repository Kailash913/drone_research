"""Audit the reports-only workspace and collect subscription-only evidence."""
from datetime import datetime, timezone
import hashlib
import importlib
import json
import os
from pathlib import Path
import platform
import shutil
import subprocess
import sys

import psutil

package = Path(__file__).resolve().parents[1]
workspace = package.parents[1]
px4 = Path.home() / 'PX4-Autopilot'
output = package / 'test-output' / (
    'phase1_master_' + datetime.now(timezone.utc).strftime('%Y%m%d_%H%M%S_UTC'))
output.mkdir(exist_ok=False)
report = {'output': str(output), 'cwd': os.getcwd(), 'python': platform.python_version(),
          'ros_distro': os.environ.get('ROS_DISTRO'), 'flight_commands_sent': 0,
          'parameter_writes': 0, 'component_restarts': 0, 'commands': {}}


def command(name, args, cwd=workspace):
    """Save exact read-only command, result and output without hidden errors."""
    if args[0] == 'rg' and not shutil.which('rg'):
        args = ['grep', '-RnE'] + args[2:]
    result = subprocess.run(args, cwd=cwd, capture_output=True, text=True, timeout=60,
                            env=dict(os.environ, GIT_OPTIONAL_LOCKS='0'))
    (output / (name + '.log')).write_text(result.stdout + result.stderr)
    report['commands'][name] = {'argv': args, 'cwd': str(cwd),
                                'returncode': result.returncode}
    return result.stdout.strip()


report['branch'] = command('branch', ['git', 'branch', '--show-current'])
report['commit'] = command('commit', ['git', 'rev-parse', 'HEAD'])
command('git_status_before', ['git', 'status', '--short', '--branch'])
command('git_diff_before', ['git', 'diff'])
command('git_diff_stat', ['git', 'diff', '--stat'])
command('git_recent_commits', ['git', 'log', '-8', '--oneline'])
command('untracked_before', ['git', 'ls-files', '--others', '--exclude-standard'])
report['px4_commit'] = command('px4_commit', ['git', 'rev-parse', 'HEAD'], px4)
report['px4_version'] = command('px4_version', ['git', 'describe', '--tags', '--always'], px4)
command('px4_git_status', ['git', 'status', '--short', '--branch'], px4)
report['px4_msgs_commit'] = command(
    'px4_msgs_commit', ['git', 'rev-parse', 'HEAD'], workspace / 'src/px4_msgs')
command('px4_msgs_status', ['git', 'status', '--short', '--branch'], workspace / 'src/px4_msgs')
report['gazebo_version'] = command('gazebo_version', ['gz', 'sim', '--versions'], package)
command('timestamp_and_heading_search', [
    'rg', '-n',
    ('isYawFinalAlignComplete|_flt_mag_align_start_time|mag_aligned_in_flight|'
     'time_offset|MAX_CONSECUTIVE_HIGH_DEVIATION|heading_good_for_control'),
    'src/modules/ekf2/EKF', 'src/modules/uxrce_dds_client', 'src/lib/timesync'], px4)
command('agent_clock_search', ['rg', '-n', 'system_clock|TIMESTAMP_REPLY|time_reply|'
        'time_offset|timestamp_reply', 'src', 'include'], Path.home() / 'Micro-XRCE-DDS-Agent')
protected = list((workspace / 'baseline_results').rglob('*.csv'))
protected += list((workspace / 'baseline_results').rglob('*.json'))
protected += list((workspace / 'baseline_results').rglob('*.plan'))
protected += [package / name for name in (
    'baseline_measurement/mission_node.py', 'baseline_measurement/mission_state.py',
    'baseline_measurement/qgc_plan.py', 'baseline_measurement/baseline_node.py',
    'config/baseline.yaml')]
protected += [px4 / name for name in (
    'src/lib/timesync/Timesync.cpp', 'src/lib/timesync/Timesync.hpp',
    'src/modules/uxrce_dds_client/uxrce_dds_client.cpp',
    'src/modules/uxrce_dds_client/dds_topics.h.em',
    'src/modules/uxrce_dds_client/module.yaml',
    'src/modules/ekf2/EKF/ekf.h', 'src/modules/ekf2/EKF2.cpp',
    'Tools/msg/templates/ucdr/msg.h.em',
    'ROMFS/px4fmu_common/init.d-posix/rcS',
    'build/px4_sitl_default/uORB/ucdr/vehicle_local_position.h',
    'build/px4_sitl_default/uORB/ucdr/vehicle_attitude.h')]
report['protected_before'] = {
    str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in protected if p.is_file()}
report['read_only_evidence'] = list(report['protected_before'])
report['editable_scope'] = [
    'offline analysis/fixtures/tests', 'new derived reports',
    'VS Code nonflight launch selection']
report['runtime_processes'] = []
for process in psutil.process_iter(['pid', 'name', 'cmdline']):
    if process.info['name'] in ('px4', 'MicroXRCEAgent'):
        item = process.info
        path = Path(process.exe())
        item['exe'] = str(path)
        item['exe_sha256'] = hashlib.sha256(path.read_bytes()).hexdigest()
        report['runtime_processes'].append(item)
report['installed_message_types'] = {}
for name in ('VehicleLocalPosition', 'VehicleAttitude', 'EstimatorStatusFlags', 'TimesyncStatus'):
    module = importlib.import_module('px4_msgs.msg')
    cls = getattr(module, name)
    loaded = importlib.import_module(cls.__module__)
    path = Path(loaded.__file__)
    report['installed_message_types'][name] = {
        'file': str(path), 'sha256': hashlib.sha256(path.read_bytes()).hexdigest(),
        'fields': cls.get_fields_and_field_types()}
(output / 'audit_state.json').write_text(json.dumps(report, indent=2) + '\n')
display_fields = ('output', 'branch', 'commit', 'px4_commit', 'px4_version', 'gazebo_version')
print(json.dumps({k: report[k] for k in display_fields}, indent=2), flush=True)
if report['commit'] != '5affc1548a85c081b8c37e068a0ea9ffca9081ef':
    raise RuntimeError('Workspace revision changed; reconcile before further work')
if report['px4_commit'] != '43cccdea0e57cf92a58562d2d7a1cba0854395f7':
    raise RuntimeError('PX4 revision changed; reconcile before further work')
command('passive_clock', [
    sys.executable, '-m', 'baseline_measurement.clock_probe',
    '--seconds', '25', '--output', str(output / 'passive_clock')], package)
(output / 'audit_state.json').write_text(json.dumps(report, indent=2) + '\n')
print('MASTER_AUDIT_OUTPUT=' + str(output), flush=True)
