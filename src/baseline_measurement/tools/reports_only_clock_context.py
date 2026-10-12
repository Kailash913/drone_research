"""Read host/guest clock and service evidence without modifying settings."""
import argparse
import csv
from datetime import datetime, timezone
import json
from pathlib import Path
import shutil
import subprocess
import time

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--audit', required=True)
options = parser.parse_args()
output = Path(options.audit) / (
    'clock_context_' + datetime.now(timezone.utc).strftime('%H%M%S'))
output.mkdir(exist_ok=False)
report = {'scope': 'PASSIVE_CLOCK_DIAGNOSTIC_ONLY', 'flight_commands_sent': 0,
          'parameter_writes': 0, 'component_restarts': 0, 'commands': {},
          'output': str(output)}
for name in ('/proc/version', '/etc/wsl.conf', '/etc/systemd/timesyncd.conf',
             '/sys/devices/system/clocksource/clocksource0/current_clocksource',
             '/sys/devices/system/clocksource/clocksource0/available_clocksource'):
    path = Path(name)
    if path.is_file():
        report[name] = path.read_text()
commands = {
    'timedatectl': ['timedatectl', 'show'],
    'timesync_service': ['systemctl', 'show', 'systemd-timesyncd.service',
                         '-p', 'ActiveState', '-p', 'SubState', '-p', 'MainPID'],
    'time_service_journal': ['journalctl', '--utc', '-u', 'systemd-timesyncd',
                             '-n', '100', '--no-pager'],
    'chrony_tracking': ['chronyc', 'tracking'],
}
for name, command in commands.items():
    if not shutil.which(command[0]):
        report['commands'][name] = {'status': 'NOT AVAILABLE'}
        continue
    result = subprocess.run(command, capture_output=True, text=True, timeout=10)
    (output / (name + '.log')).write_text(result.stdout + result.stderr)
    report['commands'][name] = {'argv': command, 'returncode': result.returncode}
clock_names = ('CLOCK_REALTIME', 'CLOCK_MONOTONIC', 'CLOCK_MONOTONIC_RAW', 'CLOCK_BOOTTIME')
rows = []
start = time.monotonic()
while time.monotonic() - start < 15:
    row = {'receive_monotonic_ns': time.monotonic_ns()}
    for name in clock_names:
        row[name] = time.clock_gettime_ns(getattr(time, name))
    row['read_span_ns'] = time.monotonic_ns() - row['receive_monotonic_ns']
    rows.append(row)
    time.sleep(0.1)
with (output / 'clock_samples.csv').open('x', newline='') as stream:
    writer = csv.DictWriter(stream, fieldnames=list(rows[0]))
    writer.writeheader()
    writer.writerows(rows)
report['sample_count'] = len(rows)
report['clock_deltas_s'] = {
    name: (rows[-1][name] - rows[0][name]) / 1e9 for name in clock_names}
report['realtime_to_monotonic_progression_ratio'] = (
    report['clock_deltas_s']['CLOCK_REALTIME'] / report['clock_deltas_s']['CLOCK_MONOTONIC'])
report['latency_or_baseline_experiment'] = False
(output / 'clock_context.json').write_text(json.dumps(report, indent=2) + '\n')
print('CLOCK_CONTEXT_OUTPUT=' + str(output), flush=True)
print(json.dumps(report['clock_deltas_s']), flush=True)
