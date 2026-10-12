"""Run nonflight verification and retain exact commands in an exclusive evidence directory."""
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import time

from native_timesync_check import run_check

root = Path('/home/kailash/ros2_ws')
package = root / 'src/baseline_measurement'
out = package / 'test-output' / ('continuation_' + time.strftime('%Y%m%d_%H%M%S'))
out.mkdir(parents=True, exist_ok=False)
protected = list((root / 'baseline_results').glob('*'))
protected += list((package / 'heading_fix_backups').rglob('*.py'))
protected += [
    package / 'config/baseline.yaml',
    package / 'baseline_measurement/mission_state.py',
    package / 'tools/vscode_apply_heading_fix.py'
]
protected = [p for p in protected if p.is_file()]


def hashes():
    """Protect raw files, safety policy, configuration and archived source."""
    return {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in protected}


summary = {'protected_before': hashes(), 'flight_commands_sent': 0, 'output': str(out)}


def run(name, command, cwd=package, timeout=180):
    """Retain stdout/stderr and return code without hiding validation failures."""
    print('START ' + name, flush=True)
    try:
        result = (
            subprocess.run(
                command,
                cwd=cwd,
                capture_output=True,
                text=True,
                timeout=timeout,
                env=dict(os.environ, GIT_OPTIONAL_LOCKS='0')
            )
        )
        (out / (name + '.log')).write_text(result.stdout + result.stderr)
        summary[name] = {'command': command, 'returncode': result.returncode}
    except Exception as exc:
        summary[name] = {'command': command, 'error': repr(exc)}
    (out / 'verification.json').write_text(json.dumps(summary, indent=2) + '\n')
    print(name + ': ' + json.dumps(summary[name]), flush=True)


run('git_status', ['git', 'status', '--short', '--branch'], root)
run('git_diff', ['git', 'diff', '--', 'src/baseline_measurement'], root)
run(
    'functional',
    [
        sys.executable,
        '-m',
        'pytest',
        'test',
        '-q',
        '--ignore=test/test_flake8.py',
        '--ignore=test/test_pep257.py',
        '--ignore=test/test_copyright.py',
        '--junitxml=' + str(out / 'functional.xml')
    ]
)
run(
    'full_suite',
    [sys.executable, '-m', 'pytest', 'test', '-q', '--junitxml=' + str(out / 'full_suite.xml')]
)
try:
    summary['native_timesync'] = run_check(out, Path('/home/kailash/PX4-Autopilot'))
except Exception as exc:
    summary['native_timesync'] = {'error': repr(exc)}
run(
    'build',
    [
        'bash',
        '-c',
        'source /opt/ros/jazzy/setup.bash && colcon build --packages-select baseline_measurement'
    ],
    root
)
run(
    'installed_measurement_help',
    ['ros2', 'run', 'baseline_measurement', 'measurement_import', '--help']
)
run(
    'dataset',
    [
        sys.executable,
        '-m',
        'baseline_measurement.dataset',
        '--input',
        str(root / 'baseline_results'),
        '--output',
        str(out / 'dataset')
    ]
)
run(
    'provenance',
    [
        sys.executable,
        '-m',
        'baseline_measurement.provenance',
        '--input',
        str(root / 'baseline_results'),
        '--evidence-dir',
        str(package / 'heading_fix_backups'),
        '--evidence-dir',
        str(package / 'baseline_measurement'),
        '--evidence-dir',
        str(package / 'test-output/continuation_source_before'),
        '--output',
        str(out / 'provenance.json')
    ]
)
run(
    'context',
    [
        sys.executable,
        '-m',
        'baseline_measurement.record_context',
        '--config',
        str(package / 'config/baseline.yaml'),
        '--output',
        str(out)
    ]
)
run(
    'passive_clock',
    [
        sys.executable,
        '-m',
        'baseline_measurement.clock_probe',
        '--seconds',
        '20',
        '--output',
        str(out / 'clock_probe')
    ],
    timeout=45
)
run('loopback_bench', [sys.executable, '-m', 'baseline_measurement.transport_probe',
                       '--output', str(out / 'loopback_bench')])
summary['protected_after'] = hashes()
summary['protected_unchanged'] = summary['protected_before'] == summary['protected_after']
(out / 'verification.json').write_text(json.dumps(summary, indent=2) + '\n')
print('CONTINUATION_OUTPUT=' + str(out), flush=True)
