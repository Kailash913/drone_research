"""Run the requested reports-only verification; never publish or restart components."""
import argparse
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

from native_heading_check import run_check as heading_check
from native_timesync_check import run_check as timesync_check

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--audit', required=True)
options = parser.parse_args()
audit = Path(options.audit)
initial = json.loads((audit / 'audit_state.json').read_text())
package = Path(__file__).resolve().parents[1]
workspace = package.parents[1]
output = audit / ('verification_' + datetime.now(timezone.utc).strftime('%H%M%S'))
output.mkdir(exist_ok=False)
report = {'output': str(output), 'flight_commands_sent': 0, 'parameter_writes': 0,
          'component_restarts': 0, 'commands': {}}


def run(name, args, cwd=package, timeout=180):
    """Preserve exact command results, including dataset completeness rejection."""
    result = subprocess.run(args, cwd=cwd, capture_output=True, text=True, timeout=timeout,
                            env=dict(os.environ, GIT_OPTIONAL_LOCKS='0'))
    (output / (name + '.log')).write_text(result.stdout + result.stderr)
    report['commands'][name] = {'argv': args, 'cwd': str(cwd), 'returncode': result.returncode}
    (output / 'verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(name + ': ' + json.dumps(report['commands'][name]), flush=True)
    return result


groups = {
    'timestamp_tests': ['test/test_clock_guard.py', 'test/test_report_analysis.py',
                        'test/test_native_clock.py'],
    'heading_tests': ['test/test_preflight.py', 'test/test_auto_takeoff.py',
                      'test/test_auto_takeoff_adapter.py', 'test/test_heading_reports.py'],
    'dataset_tests': ['test/test_dataset.py', 'test/test_dataset_identity.py',
                      'test/test_acceptance.py', 'test/test_reporting_status.py'],
    'measurement_tests': ['test/test_measurements.py', 'test/test_run_provenance.py'],
}
for name, files in groups.items():
    run(name, [sys.executable, '-m', 'pytest', '-q', *files,
               '--junitxml=' + str(output / (name + '.xml'))])
fixture = output / 'source_fixtures'
fixture.mkdir()
report['native_timesync'] = timesync_check(fixture, Path.home() / 'PX4-Autopilot')
report['native_heading'] = heading_check(fixture, Path.home() / 'PX4-Autopilot')
final = run('final_report_runner', [sys.executable, 'tools/final_report_runner.py'])
line = next((s for s in final.stdout.splitlines() if s.startswith('FINAL_REPORT_OUTPUT=')), None)
report['final_report_directory'] = line.split('=', 1)[1] if line else None
cohorts = [workspace / 'baseline_results']
cohorts += sorted((workspace / 'baseline_results').glob('phase1_study_*'))
for index, directory in enumerate(cohorts):
    args = [sys.executable, '-m', 'baseline_measurement.dataset', '--input', str(directory),
            '--output', str(output / ('validator_' + directory.name))]
    prior = (package / 'test-output/final_reports_20261011_183812'
             / directory.name / 'manifest.json')
    if prior.is_file():
        args += ['--prior-manifest', str(prior)]
    run('validator_' + str(index), args)
run('provenance_recovery', [sys.executable, '-m', 'baseline_measurement.provenance',
    '--input', str(workspace / 'baseline_results'), '--evidence-dir', 'heading_fix_backups',
    '--evidence-dir', 'test-output/continuation_source_before',
    '--evidence-dir', 'baseline_measurement', '--output', str(output / 'provenance.json')])
run('px4_clock_source', ['grep', '-RnE', 'ENABLE_LOCKSTEP_SCHEDULER|px4_clock_settime|'
    'px4_clock_gettime', 'platforms/posix/src/px4/common', 'platforms/common/include'],
    Path.home() / 'PX4-Autopilot')
help_result = run('gz_topic_help', ['gz', 'topic', '--help'])
topics_result = run('gz_topic_list', ['gz', 'topic', '-l'])
stats_topics = [line.strip() for line in topics_result.stdout.splitlines()
                if line.strip().startswith('/world/') and line.strip().endswith('/stats')]
if len(stats_topics) == 1:
    passive_args = [sys.executable, '-m', 'baseline_measurement.clock_probe',
                    '--seconds', '15', '--output', str(output / 'paired_passive')]
    with (output / 'paired_passive.log').open('x') as stream:
        subscriber = subprocess.Popen(passive_args, stdout=stream, stderr=subprocess.STDOUT)
        capture_args = ['timeout', '-s', 'INT', '12', 'gz', 'topic', '-e', '-t', stats_topics[0]]
        if '--json-output' in help_result.stdout:
            capture_args.append('--json-output')
        run('gz_stats_passive', capture_args, timeout=30)
        code = subscriber.wait(timeout=30)
    report['paired_passive'] = {'argv': passive_args, 'returncode': code,
                                'publishers_created': 0, 'flight_commands_sent': 0}
else:
    report['paired_passive'] = {'status': 'No unique published world statistics topic'}
run('final_git_status', ['git', 'status', '--short', '--branch'], workspace)
run('final_git_diff', ['git', 'diff'], workspace)
report['protected_before'] = initial['protected_before']
report['protected_after'] = {
    name: hashlib.sha256(Path(name).read_bytes()).hexdigest()
    for name in initial['protected_before']}
report['protected_unchanged'] = report['protected_before'] == report['protected_after']
required = ('timestamp_tests', 'heading_tests', 'dataset_tests',
            'measurement_tests', 'final_report_runner')
report['verification_exit_code'] = 0 if (
    all(report['commands'][name]['returncode'] == 0 for name in required)
    and report['protected_unchanged']) else 1
(output / 'verification.json').write_text(json.dumps(report, indent=2) + '\n')
print('MASTER_VERIFICATION_OUTPUT=' + str(output), flush=True)
raise SystemExit(report['verification_exit_code'])
