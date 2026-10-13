"""Snapshot provenance for a human-authorized run; never launch a mission."""
import argparse
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import platform
import subprocess
import uuid


def command(argv):
    """Retain actual bounded inventory output with return code."""
    try:
        result = (
            subprocess.run(
                argv,
                capture_output=True,
                text=True,
                timeout=10,
                env=dict(os.environ, GIT_OPTIONAL_LOCKS='0')
            )
        )
        return {
            'argv': argv,
            'returncode': result.returncode,
            'stdout': result.stdout,
            'stderr': result.stderr
        }
    except (OSError, subprocess.TimeoutExpired) as exc:
        return {'argv': argv, 'unavailable': str(exc)}


def main(args=None):
    """Preserve config and current versions; label any attachment retrospective."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--config', required=True)
    parser.add_argument('--output', required=True)
    parser.add_argument(
        '--run-csv',
        help='Attach context by raw SHA; current snapshot is not proof of historical environment'
    )
    options = parser.parse_args(args)
    config = Path(options.config).expanduser().resolve()
    package = Path(__file__).resolve().parents[1]
    workspace = package.parents[1]
    output = Path(options.output).expanduser() / ('context_' + uuid.uuid4().hex)
    output.mkdir(parents=True, exist_ok=False)
    content = config.read_bytes()
    (output / 'config_original.yaml').write_bytes(content)
    document = (
        {
            'schema_version': 1,
            'captured_utc': datetime.now(timezone.utc).isoformat(),
            'context_id': output.name,
            'config_file': str(config),
            'config_sha256': hashlib.sha256(content).hexdigest(),
            'python': platform.python_version(),
            'ros_distro': os.environ.get('ROS_DISTRO'),
            'source_sha256': {
                p.name: hashlib.sha256(p.read_bytes()).hexdigest()
                for p in (package / 'baseline_measurement').glob('*.py')
            },
            'mission_outcome': 'NOT_ATTEMPTED',
            'commands_sent': 0,
            'scope': ('current WSL environment snapshot, '
                      'not a flight or historical-version attestation'),
            'inventory': {
                name: command(argv) for name,
                argv in {
                    'workspace_commit': ['git', '-C', str(workspace), 'rev-parse', 'HEAD'],
                    'workspace_status': [
                        'git',
                        '-C',
                        str(workspace),
                        'status',
                        '--short',
                        '--branch'
                    ],
                    'px4_revision': [
                        'git',
                        '-C',
                        str(Path.home() / 'PX4-Autopilot'),
                        'describe',
                        '--always',
                        '--dirty'
                    ],
                    'gazebo_version': ['gz', 'sim', '--versions'],
                    'ros_packages': ['dpkg-query', '-W', 'ros-jazzy-rclpy', 'ros-jazzy-ros2cli'],
                    'installed_baseline': ['ros2', 'pkg', 'prefix', 'baseline_measurement']
                }.items()
            }
        }
    )
    if options.run_csv:
        raw = Path(options.run_csv).expanduser().resolve()
        document['retrospective_attachment'] = (
            {
                'file': str(raw),
                'sha256': hashlib.sha256(raw.read_bytes()).hexdigest(),
                'warning': ('Snapshot captured now; cannot fill missing '
                            'versions/configuration at historical run time.')
            }
        )
    (output / 'context.json').write_text(json.dumps(document, indent=2, allow_nan=False) + '\n')
    print(str(output))


if __name__ == '__main__':
    main()
