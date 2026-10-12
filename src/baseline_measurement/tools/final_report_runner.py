"""Finish Phase 1 reports and verification without publishing vehicle commands."""
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import time

from baseline_measurement.dataset import validate_dataset, write_report
from baseline_measurement.reporting import verification_exit_code

package = Path(__file__).resolve().parents[1]
workspace = package.parents[1]
results = workspace / 'baseline_results'
output = package / 'test-output' / ('final_reports_' + time.strftime('%Y%m%d_%H%M%S'))
output.mkdir(exist_ok=False)
protected = list(results.rglob('*.csv')) + list(results.rglob('*.json'))
protected += [package / 'config/baseline.yaml',
              package / 'baseline_measurement/mission_state.py']


def hashes():
    """Check raw study records and unchanged safety policy."""
    return {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in protected}


report = {'flight_commands_sent': 0, 'parameter_writes': 0,
          'output': str(output), 'protected_before': hashes()}
commands = {
    'full_suite': ([sys.executable, '-m', 'pytest', 'test', '-q',
                    '--junitxml=' + str(output / 'full_suite.xml')], package),
    'build': (['bash', '-c', 'source /opt/ros/jazzy/setup.bash && '
               'colcon build --packages-select baseline_measurement'], workspace),
}
for name, (command, directory) in commands.items():
    completed = subprocess.run(command, cwd=directory, capture_output=True, text=True,
                               timeout=180, env=dict(os.environ, GIT_OPTIONAL_LOCKS='0'))
    (output / (name + '.log')).write_text(completed.stdout + completed.stderr)
    report[name] = {'command': command, 'returncode': completed.returncode}
    print(name + ': ' + json.dumps(report[name]), flush=True)

cohorts = [results] + sorted(results.glob('phase1_study_*'))
report['cohorts'] = []
for directory in cohorts:
    document = validate_dataset(directory)
    destination = output / directory.name
    write_report(document, destination)
    report['cohorts'].append({'input': str(directory), 'output': str(destination),
                              'counts': document['counts'],
                              'phase1': document['overall_phase1']})
    print('DATASET ' + str(directory) + ': ' + json.dumps(document['counts']), flush=True)
report['protected_after'] = hashes()
report['protected_unchanged'] = report['protected_before'] == report['protected_after']
report['verification_exit_code'] = verification_exit_code(
    report['full_suite']['returncode'], report['build']['returncode'],
    report['protected_unchanged'])
(output / 'verification.json').write_text(json.dumps(report, indent=2) + '\n')
print('FINAL_REPORT_OUTPUT=' + str(output), flush=True)
raise SystemExit(report['verification_exit_code'])
