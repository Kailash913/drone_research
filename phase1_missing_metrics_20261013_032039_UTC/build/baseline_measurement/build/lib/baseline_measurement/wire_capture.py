"""Capture bounded local UDP traffic with drop evidence; never control PX4."""
import argparse
from datetime import datetime, timezone
import json
import math
from pathlib import Path
import re
import signal
import subprocess
import time

from .dataset import digest
from .measurements import captured_traffic


def capture(output, seconds, interface, port):
    """Keep process window, interface, filter and tcpdump counters with a new PCAP."""
    if not math.isfinite(seconds) or not 1 <= seconds <= 60:
        raise ValueError('Capture duration must be between 1 and 60 seconds')
    if not 1 <= port <= 65535 or not interface or interface.startswith('-'):
        raise ValueError('Explicit interface and valid UDP port required')
    directory = Path(output)
    directory.mkdir(parents=True, exist_ok=False)
    path = directory / 'traffic.pcap'
    args = ['tcpdump', '-i', interface, '-Q', 'inout', '-n', '-s', '0', '-U',
            '-w', str(path), 'udp', 'port', str(port)]
    start_wall, start_ns = time.time(), time.monotonic_ns()
    process = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    try:
        stdout, stderr = process.communicate(timeout=seconds)
    except subprocess.TimeoutExpired:
        process.send_signal(signal.SIGINT)
        try:
            stdout, stderr = process.communicate(timeout=5)
        except subprocess.TimeoutExpired:
            process.terminate()
            stdout, stderr = process.communicate(timeout=5)
    end_ns, end_wall = time.monotonic_ns(), time.time()
    (directory / 'tcpdump.log').write_text(stdout + stderr)
    counters = {}
    for name, suffix in [('captured', 'packets captured'), ('received_by_filter', 'packets '
                                                                                  'received by '
                                                                                  'filter'),
                         ('kernel_dropped', 'packets dropped by kernel')]:
        match = re.search(r'(\d+) ' + suffix, stderr)
        counters[name] = int(match.group(1)) if match else None
    evidence = {'argv': args, 'interface': interface, 'filter': f'udp port {port}',
                'direction': 'both; PX4-to-agent and agent-to-PX4 separated by UDP endpoints '
                             'offline',
                'scope': 'WSL guest captured link-layer frames; not a physical radio link',
                'utc': datetime.now(timezone.utc).isoformat(),
                'start_s': start_wall, 'end_s': end_wall,
                'start_monotonic_ns': start_ns, 'end_monotonic_ns': end_ns,
                'monotonic_window_s': (end_ns - start_ns) / 1e9,
                'timestamp_source': 'libpcap host wall-clock packet timestamps',
                'capture_drops': counters, 'returncode': process.returncode,
                'wire_loss': None, 'loss_reason': 'Capture counts lack independent '
                                                  'sent/received wire IDs'}
    summary = None
    if path.is_file() and path.stat().st_size > 24:
        summary = captured_traffic(path, start_wall, end_wall, evidence)
        evidence['pcap_sha256'] = digest(path)
        summary['monotonic_bits_per_s'] = (
            summary['original_frame_bytes'] * 8 / evidence['monotonic_window_s'])
    validated = bool(summary and process.returncode == 0 and counters['kernel_dropped'] == 0
                     and counters['captured'] == summary['packet_count'])
    report = {'status': 'VALIDATED' if validated else 'MEASURED_UNVALIDATED' if summary
              else 'NOT_MEASURED', 'evidence': evidence, 'traffic': summary,
              'limitations': 'Zero kernel capture drops do not prove absence of network loss; '
              'localhost offered traffic is not physical link capacity. Process window '
              'includes startup.'}
    with (directory / 'capture.json').open('x') as stream:
        json.dump(report, stream, indent=2, allow_nan=False)
    return report


def main(args=None):
    """Require a chosen path; never guess an interface or install capture permissions."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', required=True)
    parser.add_argument('--seconds', type=float, default=15.)
    parser.add_argument('--interface', required=True)
    parser.add_argument('--port', type=int, required=True)
    options = parser.parse_args(args)
    print(json.dumps(capture(options.output, options.seconds, options.interface, options.port),
                     indent=2))


if __name__ == '__main__':
    main()
