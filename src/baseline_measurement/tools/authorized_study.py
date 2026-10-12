"""Collect a human-authorized active SITL study; stop on failure or unsafe preflight."""
import argparse
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import re
import signal
import subprocess
import sys
import time
from types import SimpleNamespace
import uuid

from baseline_measurement.dataset import inspect_csv, validate_dataset, write_report
from baseline_measurement.mission_node import INPUTS, MissionNode, simulation_processes
import psutil
from px4_msgs.msg import VehicleCommand
import rclpy
from rclpy.qos import DurabilityPolicy, HistoryPolicy, QoSProfile, ReliabilityPolicy
import yaml


def sha(path):
    """Hash retained input bytes."""
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def observe(config, output, release_offboard=False):
    """Require current safety checks; optionally release a grounded residual Offboard mode."""
    settings = yaml.safe_load(config.read_text()) or {}
    options = (
        SimpleNamespace(
            execute_sitl=False,
            topics=settings.get('topics', {}),
            output=str(output),
            experiment_id='BASE-001',
            scenario='preflight',
            observe_seconds=12.0,
            sampling_interval=1.0,
            config=str(config)
        )
    )
    rclpy.init(args=[])
    node = MissionNode(options)
    release_sent = False
    until = time.monotonic() + 12.0
    try:
        while time.monotonic() < until and not node.done:
            rclpy.spin_once(node, timeout_sec=0.1)
            now = time.monotonic()
            state = node.telemetry(now)
            if (
                    release_offboard
                    and (not release_sent)
                    and state.connected
                    and state.offboard
                    and state.landed
                    and (not state.armed)
                    and (not state.competition)
                    and (not state.failsafe)
                    and (not state.reset)
            ):
                qos = (
                    QoSProfile(
                        reliability=ReliabilityPolicy.BEST_EFFORT,
                        history=HistoryPolicy.KEEP_LAST,
                        depth=10,
                        durability=DurabilityPolicy.VOLATILE
                    )
                )
                publisher = node.create_publisher(VehicleCommand, INPUTS['command'][0], qos)
                command = VehicleCommand()
                status = node.latest['status']
                command.target_system, command.target_component = (
                    (status.system_id, status.component_id)
                )
                command.source_system, command.source_component = (245, 191)
                command.from_external = True
                command.command = VehicleCommand.VEHICLE_CMD_DO_SET_MODE
                command.param1, command.param2, command.param3 = (1.0, 4.0, 3.0)
                command.timestamp = node.get_clock().now().nanoseconds // 1000
                discovery_deadline = time.monotonic() + 1.0
                while time.monotonic() < discovery_deadline:
                    rclpy.spin_once(node, timeout_sec=0.1)
                current = node.telemetry(time.monotonic())
                if current.landed and not current.armed and not current.failsafe:
                    publisher.publish(command)
                    rclpy.spin_once(node, timeout_sec=0.1)
                release_sent = True
                node.destroy_publisher(publisher)
                print('Grounded residual Offboard release requested: HOLD only', flush=True)
        state = node.telemetry(time.monotonic())
        checks = (
            {
                key: bool(getattr(state, key)) for key in (
                    'connected',
                    'healthy',
                    'valid',
                    'heading_ready',
                    'landed',
                    'armed',
                    'competition',
                    'failsafe',
                    'reset'
                )
            }
        )
        passed = (
            all(
                (
                    checks[key] for key in (
                        'connected',
                        'healthy',
                        'valid',
                        'heading_ready',
                        'landed'
                    )
                )
            ) and (not any((checks[key] for key in ('armed', 'competition', 'failsafe', 'reset'))))
        )
        report = (
            {
                'checks': checks,
                'passed': passed,
                'grounded_hold_requested': release_sent,
                'arming_commands': 0,
                'mission_outcome': 'NOT_ATTEMPTED'
            }
        )
        (output / 'preflight.json').write_text(json.dumps(report, indent=2) + '\n')
        return report
    finally:
        if node.experiment and (not node.experiment.closed):
            node.experiment.finish('not_attempted')
        if not node.log.finished:
            node.log.finish(False, reason='Separate preflight observation, not an active mission')
        node.destroy_node()
        rclpy.shutdown()


def provenance(config, package, experiment_id, directory):
    """Capture actual running PX4 binary identity and retained build/version evidence."""
    directory.mkdir(parents=True, exist_ok=False)
    processes = simulation_processes()
    if len(processes['px4']) != 1 or len(processes['agent']) != 1 or (not processes['gazebo']):
        raise RuntimeError('Single SITL stack required')
    px4 = Path.home() / 'PX4-Autopilot'
    header = px4 / 'build/px4_sitl_default/src/lib/version/build_git_version.h'
    text = header.read_text()
    revision = re.search('PX4_GIT_VERSION_STR "([^"]+)"', text).group(1)
    version = re.search('PX4_GIT_TAG_STR "([^"]+)"', text).group(1)
    binary = Path(psutil.Process(processes['px4'][0]).exe())
    content = binary.read_bytes()
    if revision.encode() not in content or version.encode() not in content:
        raise RuntimeError('Running binary version is not evidenced by retained build header')
    gz = (
        subprocess.run(
            ['gz', 'sim', '--versions'],
            capture_output=True,
            text=True,
            check=True
        ).stdout.strip()
    )
    document = (
        {
            'captured_utc': datetime.now(timezone.utc).isoformat(),
            'experiment_id': experiment_id,
            'config_file': str(config),
            'config_sha256': sha(config),
            'px4_version': version,
            'simulator_version': gz,
            'px4_running_pid': processes['px4'][0],
            'px4_running_binary': str(binary),
            'px4_binary_sha256': hashlib.sha256(content).hexdigest(),
            'px4_build_version_header_sha256': sha(header),
            'source_sha256': {
                p.name: sha(p) for p in (package / 'baseline_measurement').glob('*.py')
            },
            'ros_distro': 'jazzy',
            'processes': processes,
            'version_evidence': (
                'PX4 process executable contains retained full revision and tag; '
                'binary/header hashes retained. Gazebo version command output is '
                'installed-version evidence, alongside live process inventory; not '
                'physical UAV firmware evidence.'
            ),
            'unmeasured': [
                'end_to_end_latency',
                'telemetry_latency',
                'command_latency',
                'packet_loss',
                'wire_bandwidth',
                'physical_power_energy'
            ]
        }
    )
    (directory / 'config.yaml').write_bytes(config.read_bytes())
    (directory / 'build_git_version.h').write_bytes(header.read_bytes())
    source_copy = directory / 'source'
    source_copy.mkdir()
    for p in (package / 'baseline_measurement').glob('*.py'):
        (source_copy / p.name).write_bytes(p.read_bytes())
    path = directory / 'provenance.json'
    path.write_text(json.dumps(document, indent=2) + '\n')
    return path


def main(args=None):
    """Run only when an explicit human flight authorization is supplied."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--human-authorized-active-sitl', action='store_true', required=True)
    parser.add_argument('--config', required=True)
    parser.add_argument('--count', type=int, default=30)
    options = parser.parse_args(args)
    if not 1 <= options.count <= 30:
        parser.error('--count must be 1..30')
    package = Path(__file__).resolve().parents[1]
    config = Path(options.config).expanduser().resolve()
    study = package.parents[1] / 'baseline_results' / ('phase1_study_' + uuid.uuid4().hex[:12])
    study.mkdir(exist_ok=False)
    progress = (
        {
            'study': str(study),
            'authorized_limit': options.count,
            'attempts': [],
            'status': 'PREFLIGHT',
            'unmeasured_metrics_are_not_zero': True
        }
    )

    def save():
        (study / 'study_progress.json').write_text(json.dumps(progress, indent=2) + '\n')
    save()
    print('STUDY_OUTPUT=' + str(study), flush=True)
    for number in range(1, options.count + 1):
        experiment_id = f'BASE-{number:03d}'
        preflight = observe(config, study / ('preflight_' + experiment_id), release_offboard=True)
        progress['last_preflight'] = preflight
        if not preflight['passed']:
            progress['status'] = 'BLOCKED_PREFLIGHT'
            save()
            print('STOP: preflight failed ' + json.dumps(preflight), flush=True)
            break
        context = provenance(config, package, experiment_id, study / ('context_' + experiment_id))
        command = (
            [
                sys.executable,
                '-m',
                'baseline_measurement.mission_node',
                '--execute-sitl',
                '--config',
                str(config),
                '--experiment-id',
                experiment_id,
                '--provenance-json',
                str(context),
                '--output',
                str(study)
            ]
        )
        progress['status'] = 'ACTIVE_' + experiment_id
        progress['active_command'] = command
        save()
        before = set(study.glob('baseline_run_*.csv'))
        probe_stream = (study / (experiment_id + '_clock_console.log')).open('x')
        probe = subprocess.Popen(
            [sys.executable, '-m', 'baseline_measurement.clock_probe', '--seconds', '240',
             '--config', str(config), '--output', str(study / ('clock_' + experiment_id))],
            cwd=package, stdout=probe_stream, stderr=subprocess.STDOUT)
        with (study / (experiment_id + '_console.log')).open('x') as stream:
            process = (
                subprocess.Popen(command, cwd=package, stdout=stream, stderr=subprocess.STDOUT)
            )
            next_notice = 0.
            while process.poll() is None:
                if time.monotonic() >= next_notice:
                    print('ACTIVE ' + experiment_id, flush=True)
                    next_notice = time.monotonic() + 30.
                time.sleep(1.)
        if probe.poll() is None:
            probe.send_signal(signal.SIGINT)
        probe.wait(timeout=10)
        probe_stream.close()
        created = set(study.glob('baseline_run_*.csv')) - before
        if len(created) != 1:
            progress['status'] = 'BLOCKED_RECORD_IDENTITY'
            save()
            break
        record = inspect_csv(created.pop())
        progress['attempts'].append(
            {
                'experiment_id': experiment_id,
                'source_file': record['source_file'],
                'outcome': record['mission_outcome'],
                'strict_provenance_valid': record['strict_experiment_valid'],
                'failure_reason': record.get('failure_reason'),
                'process_returncode': process.returncode
            }
        )
        progress['status'] = 'VALIDATING'
        save()
        document = validate_dataset(study)
        write_report(document, study / ('validation_after_' + experiment_id))
        if record['mission_outcome'] != 'PASS' or not record['strict_experiment_valid']:
            progress['status'] = 'STOPPED_FAILURE_OR_INVALID_RECORD'
            save()
            break
    else:
        progress['status'] = 'REQUESTED_ATTEMPTS_COLLECTED'
        save()
    print(json.dumps(progress, indent=2), flush=True)


if __name__ == '__main__':
    main()
# This is the existing WAIT_FOR_HEALTH residual-mode HOLD action, while grounded.
