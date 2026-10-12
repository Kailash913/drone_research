"""Run Phase 1 offline tests, build, immutable import and passive diagnostics."""
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import time
root = Path('/home/kailash/ros2_ws')
package = root / 'src/baseline_measurement'
results = root / 'baseline_results'
out = package / 'test-output' / ('phase1_verify_' + time.strftime('%Y%m%d_%H%M%S'))
out.mkdir(parents=True, exist_ok=False)
protected = (
    [
        package / 'baseline_measurement/mission_node.py',
        package / 'baseline_measurement/mission_state.py',
        package / 'config/baseline.yaml'
    ]
)
raw = [p for p in results.iterdir() if p.is_file()]


def hashes(paths):
    return {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in paths}


before = hashes(raw + protected)
summary = (
    {
        'started_utc': time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime()),
        'flight_commands_sent_by_this_runner': 0,
        'protected_hashes_before': before
    }
)


def run(name, argv, cwd=package, timeout=180):
    print('START ' + name, flush=True)
    try:
        p = (
            subprocess.run(
                argv,
                cwd=cwd,
                capture_output=True,
                text=True,
                timeout=timeout,
                env=dict(os.environ, GIT_OPTIONAL_LOCKS='0')
            )
        )
        (out / (name + '.log')).write_text(p.stdout + p.stderr)
        result = {'argv': argv, 'returncode': p.returncode, 'log': name + '.log'}
    except Exception as exc:
        result = {'argv': argv, 'error': repr(exc)}
    summary[name] = result
    (out / 'verification.json').write_text(json.dumps(summary, indent=2) + '\n')
    print(name + ' ' + json.dumps(result), flush=True)
    return result


run(
    'functional_tests',
    [
        sys.executable,
        '-m',
        'pytest',
        'test',
        '-q',
        '--ignore=test/test_flake8.py',
        '--ignore=test/test_pep257.py',
        '--ignore=test/test_copyright.py',
        '--junitxml=' + str(out / 'functional_tests.xml')
    ]
)
run(
    'build',
    [
        'bash',
        '-c',
        'source /opt/ros/jazzy/setup.bash && colcon build --packages-select baseline_measurement'
    ],
    root
)
style_files = [
    'baseline_measurement/dataset.py', 'baseline_measurement/clock_probe.py',
    'baseline_measurement/record_context.py', 'test/test_dataset.py',
    'test/test_clock_guard.py', 'tools/phase1_inspect.py', 'tools/phase1_verify.py',
    'tools/phase1_lint_tools.py']
style_code = (
    'import sys; from ament_flake8.main import main_with_errors; '
    'rc, errors = main_with_errors(argv=sys.argv[1:]); '
    'print("\\n".join(errors)); sys.exit(rc)')
run('new_file_style', [sys.executable, '-c', style_code] + style_files)
run('installed_help', ['ros2', 'run', 'baseline_measurement', 'baseline_dataset', '--help'])
run(
    'dataset',
    [
        'ros2',
        'run',
        'baseline_measurement',
        'baseline_dataset',
        '--input',
        str(results),
        '--output',
        str(out / 'dataset')
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
    'passive_clock_probe',
    [
        sys.executable,
        '-m',
        'baseline_measurement.clock_probe',
        '--seconds',
        '20',
        '--config',
        str(package / 'config/baseline.yaml'),
        '--output',
        str(out / 'clock_probe')
    ],
    timeout=45
)
run(
    'full_suite',
    [sys.executable, '-m', 'pytest', 'test', '-q', '--junitxml=' + str(out / 'full_suite.xml')]
)
run('git_status_after', ['git', 'status', '--short', '--branch'], root)
summary['protected_hashes_after'] = hashes(raw + protected)
summary['protected_files_unchanged'] = before == summary['protected_hashes_after']
summary['output_directory'] = str(out)
(out / 'verification.json').write_text(json.dumps(summary, indent=2) + '\n')
print('VERIFY_OUTPUT=' + str(out), flush=True)
print('PROTECTED_FILES_UNCHANGED=' + str(summary['protected_files_unchanged']), flush=True)
