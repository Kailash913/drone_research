"""Read-only Linux inventory and baseline tests; never creates ROS publishers."""
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import time
root = Path('/home/kailash/ros2_ws')
package = root / 'src/baseline_measurement'
out = package / 'test-output' / ('phase1_audit_' + time.strftime('%Y%m%d_%H%M%S'))
out.mkdir(parents=True, exist_ok=False)


def run(name, argv, cwd=root, timeout=120):
    try:
        result = (
            subprocess.run(
                argv,
                cwd=cwd,
                capture_output=True,
                text=True,
                timeout=timeout,
                env=dict(os.environ, GIT_OPTIONAL_LOCKS='0')
            )
        )
        text = result.stdout + result.stderr
        (out / (name + '.log')).write_text(text)
        return {'argv': argv, 'returncode': result.returncode, 'log': name + '.log'}
    except Exception as exc:
        return {'argv': argv, 'error': repr(exc)}


inventory = {'started_utc': time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime())}
for name, argv in [
    ('git_status', ['git', 'status', '--short', '--branch']),
    ('git_commit', ['git', 'rev-parse', 'HEAD']),
    ('git_diff', ['git', 'diff', '--', 'src/baseline_measurement']),
    ('git_cached_diff', ['git', 'diff', '--cached', '--', 'src/baseline_measurement']),
    ('colcon_list', ['colcon', 'list']),
    ('installed_executables', ['ros2', 'pkg', 'executables', 'baseline_measurement']),
    ('installed_prefix', ['ros2', 'pkg', 'prefix', 'baseline_measurement']),
    ('cli_help', ['ros2', 'run', 'baseline_measurement', 'mission_node', '--help']),
    ('topics', ['ros2', 'topic', 'list', '-t']),
    ('nodes', ['ros2', 'node', 'list']),
    ('processes', ['ps', '-eo', 'pid,comm,args']),
    ('ubuntu', ['cat', '/etc/os-release']),
    (
        'px4_version',
        ['git', '-C', '/home/kailash/PX4-Autopilot', 'describe', '--always', '--dirty']
    ),
    ('px4_status', ['git', '-C', '/home/kailash/PX4-Autopilot', 'status', '--short', '--branch']),
    ('gz_version', ['gz', 'sim', '--versions']),
    ('ros_version', ['dpkg-query', '-W', 'ros-jazzy-ros2cli', 'ros-jazzy-rclpy'])
]:
    inventory[name] = run(name, argv)
inventory['source_hashes'] = (
    {
        str(p.relative_to(package)): hashlib.sha256(p.read_bytes()).hexdigest()
        for p in package.rglob('*') if p.is_file() and (
            not any(
                (
                    x in p.parts for x in (
                        '__pycache__',
                        '.pytest_cache',
                        'test-output',
                        'heading_fix_backups'
                    )
                )
            )
        )
    }
)
inventory['baseline_pytest'] = (
    run(
        'baseline_pytest',
        [
            sys.executable,
            '-m',
            'pytest',
            'test',
            '-q',
            '--junitxml=' + str(out / 'baseline_pytest.xml')
        ],
        package,
        180
    )
)
(out / 'inventory.json').write_text(json.dumps(inventory, indent=2) + '\n')
print('AUDIT_OUTPUT=' + str(out), flush=True)
print(json.dumps(inventory['baseline_pytest']), flush=True)
