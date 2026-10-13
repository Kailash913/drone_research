"""Measure isolated localhost UDP probe timing; never publish vehicle commands."""
import argparse
import csv
import json
from pathlib import Path
import socket
import threading
import time
import uuid

from .measurements import correlated_latency, sequence_loss


def collect(output, count=50):
    """Retain real loopback probe samples separately from UAV baseline experiments."""
    if not 1 <= count <= 10000:
        raise ValueError('Count must be between 1 and 10000')
    output = Path(output)
    output.mkdir(parents=True, exist_ok=False)
    run_id = uuid.uuid4().hex
    server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server.bind(('127.0.0.1', 0))
    server.settimeout(0.1)
    client.settimeout(1.)
    endpoint = server.getsockname()
    done = threading.Event()
    received = []
    faults = []

    def echo():
        while not done.is_set():
            try:
                payload, address = server.recvfrom(4096)
                stamp = time.monotonic_ns() // 1000
                identity, sequence = json.loads(payload)
                if identity != run_id:
                    faults.append('Unexpected identity')
                    continue
                received.append({'event': 'received', 'run_id': identity,
                                 'sequence': sequence, 'monotonic_us': stamp})
                server.sendto(payload, address)
            except socket.timeout:
                continue
            except Exception as exc:
                faults.append(repr(exc))
                break

    worker = threading.Thread(target=echo)
    worker.start()
    sent, pairs = [], []
    try:
        for sequence in range(count):
            payload = json.dumps([run_id, sequence]).encode()
            begin = time.monotonic_ns() // 1000
            client.sendto(payload, endpoint)
            sent.append({'event': 'sent', 'run_id': run_id, 'sequence': sequence,
                         'monotonic_us': begin})
            try:
                response, _ = client.recvfrom(4096)
                end = time.monotonic_ns() // 1000
                if response != payload:
                    faults.append('Mismatched echo')
                    continue
                pairs.append({'request_id': run_id + ':' + str(sequence),
                              'request_us': begin, 'response_us': end,
                              'endpoint_evidence': 'isolated localhost UUID+sequence echo',
                              'clock_validation_evidence': 'same process time.monotonic_ns'})
            except socket.timeout:
                continue
    finally:
        done.set()
        worker.join(timeout=2.)
        client.close()
        server.close()
    if worker.is_alive() or faults:
        raise RuntimeError('Probe observer failure: ' + repr(faults))
    rows = sent + received + [{'event': 'window_closed'}]
    for name, records in [('sequence.csv', rows), ('round_trip.csv', pairs)]:
        fields = sorted({key for record in records for key in record})
        with (output / name).open('x', newline='') as stream:
            writer = csv.DictWriter(stream, fieldnames=fields)
            writer.writeheader()
            writer.writerows(records)
    report = {'mode': 'LOCALHOST_BENCH_ONLY', 'mission_outcome': 'NOT_ATTEMPTED',
              'baseline_experiment_id': None, 'run_id': run_id,
              'sequence_delivery': sequence_loss(rows), 'round_trip': correlated_latency(pairs),
              'limitations': 'Loopback application delivery/RTT only. Does not measure PX4 '
              'telemetry, mission command/E2E latency, wire packet loss or UAV radio bandwidth.'}
    with (output / 'probe.json').open('x') as stream:
        json.dump(report, stream, indent=2)
        stream.write('\n')
    return report


def main(args=None):
    """Run an isolated nonflight transport bench without contacting PX4 endpoints."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', required=True)
    parser.add_argument('--count', type=int, default=50)
    options = parser.parse_args(args)
    report = collect(options.output, options.count)
    print(json.dumps({'output': options.output, 'mode': report['mode'],
                      'transmitted': report['sequence_delivery']['transmitted']}, indent=2))


if __name__ == '__main__':
    main()
