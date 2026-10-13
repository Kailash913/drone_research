"""Validate explicit measurement evidence without controlling a vehicle."""
import argparse
import csv
import hashlib
import json
import math
from pathlib import Path
import struct


def finite(value):
    """Reject missing and nonfinite observations instead of substituting zero."""
    number = float(value)
    if not math.isfinite(number):
        raise ValueError('Nonfinite observation')
    return number


def clock_latency(rows, calibration):
    """Map native source time only using externally validated clock calibration."""
    required = ('validation_evidence', 'source_domain', 'receiver_domain')
    if not all((calibration.get(key) for key in required)):
        raise ValueError('Independent clock validation and explicit domains required')
    scale = finite(calibration['scale'])
    offset = finite(calibration['offset_us'])
    uncertainty = finite(calibration['uncertainty_us'])
    lower = finite(calibration['valid_source_min_us'])
    upper = finite(calibration['valid_source_max_us'])
    if scale <= 0 or uncertainty < 0 or lower > upper:
        raise ValueError('Invalid calibration')
    samples = []
    for row in rows:
        source = finite(row['native_source_us'])
        receive = finite(row['receive_us'])
        if (
                row['source_domain'] != calibration['source_domain']
                or row['receiver_domain'] != calibration['receiver_domain']
                or (not lower <= source <= upper)
        ):
            raise ValueError('Clock domain or calibration validity mismatch')
        latency = receive - (source * scale + offset)
        if latency < -uncertainty:
            raise ValueError('Latency outside calibration uncertainty')
        samples.append({'latency_us': latency, 'uncertainty_us': uncertainty})
    return {
        'method': 'validated source-event to receive-event clock mapping',
        'samples': samples,
        'calibration': calibration
    }


def correlated_latency(rows):
    """Accept request timing only with unique IDs and an independently evidenced endpoint."""
    seen = set()
    samples = []
    for row in rows:
        identity = row['request_id']
        if (
                not identity
                or identity in seen
                or (not row['endpoint_evidence'])
                or (not row['clock_validation_evidence'])
        ):
            raise ValueError('Unique correlation and endpoint/clock evidence required')
        seen.add(identity)
        value = finite(row['response_us']) - finite(row['request_us'])
        if value < 0:
            raise ValueError('Response precedes request')
        samples.append({'request_id': identity, 'latency_us': value})
    return {'method': 'evidenced correlated request/response interval', 'samples': samples}


def sequence_loss(rows):
    """Count exact transmitted IDs against received IDs in a completed observation window."""
    sent, received = (set(), set())
    duplicates = 0
    window_closed = False
    for row in rows:
        if window_closed:
            raise ValueError('Events after observation window closure')
        if row['event'] == 'window_closed':
            window_closed = True
            continue
        raw_sequence = row['sequence']
        if isinstance(raw_sequence, bool) or not str(raw_sequence).isdigit():
            raise ValueError('Sequence must be an exact nonnegative integer')
        identity = (row['run_id'], int(raw_sequence))
        if not identity[0] or identity[1] < 0:
            raise ValueError('Invalid sequence identity')
        if row['event'] == 'sent':
            if identity in sent:
                raise ValueError('Duplicate transmitted ID')
            sent.add(identity)
        elif row['event'] == 'received':
            duplicates += identity in received
            received.add(identity)
        else:
            raise ValueError('Unknown sequence event')
    if not window_closed or not sent or received - sent:
        raise ValueError('Complete sender/receiver evidence and closed window required')
    missing = len(sent - received)
    return {
        'method': 'application sequence delivery, not wire packet loss',
        'transmitted': len(sent),
        'unique_received': len(received),
        'duplicate_received': duplicates,
        'missing': missing,
        'loss_fraction': missing / len(sent)
    }


def captured_traffic(path, start_s, end_s, capture_evidence):
    """Count original frame lengths in a classic PCAP with an explicit observation window."""
    start_s, end_s = (finite(start_s), finite(end_s))
    if end_s <= start_s or not capture_evidence:
        raise ValueError('Capture scope/drop evidence and positive window required')
    formats = (
        {
            b'\xd4\xc3\xb2\xa1': ('<', 1000000.0),
            b'\xa1\xb2\xc3\xd4': ('>', 1000000.0),
            b'M<\xb2\xa1': ('<', 1000000000.0),
            b'\xa1\xb2<M': ('>', 1000000000.0)
        }
    )
    count = total = 0
    with Path(path).open('rb') as stream:
        header = stream.read(24)
        if len(header) != 24 or header[:4] not in formats:
            raise ValueError('Classic PCAP required')
        endian, divisor = formats[header[:4]]
        major, minor, _, _, snaplen, _ = struct.unpack(endian + 'HHIIII', header[4:])
        if (major, minor) != (2, 4) or snaplen <= 0:
            raise ValueError('Invalid PCAP version or snapshot length')
        captured_bytes = truncated_packets = 0
        first_stamp = last_stamp = previous_stamp = None
        link_type = struct.unpack(endian + 'I', header[20:24])[0]
        while True:
            record = stream.read(16)
            if not record:
                break
            if len(record) != 16:
                raise ValueError('Truncated packet header')
            seconds, fraction, included, original = struct.unpack(endian + 'IIII', record)
            if included > original or included > snaplen or included > 16 * 1024 * 1024:
                raise ValueError('Invalid captured length')
            if len(stream.read(included)) != included:
                raise ValueError('Truncated packet')
            if fraction >= divisor:
                raise ValueError('Invalid timestamp fraction')
            stamp = seconds + fraction / divisor
            if previous_stamp is not None and stamp < previous_stamp:
                raise ValueError('Reversed capture timestamps')
            previous_stamp = stamp
            if start_s <= stamp < end_s:
                count += 1
                total += original
                captured_bytes += included
                truncated_packets += included < original
                first_stamp = stamp if first_stamp is None else first_stamp
                last_stamp = stamp
    return {
        'method': 'captured frame offered traffic; excludes uncaptured overhead',
        'capture_evidence': capture_evidence,
        'link_type': link_type,
        'window_s': end_s - start_s,
        'packet_count': count,
        'original_frame_bytes': total,
        'captured_bytes': captured_bytes,
        'truncated_packets': truncated_packets,
        'first_packet_s': first_stamp,
        'last_packet_s': last_stamp,
        'packets_per_s': count / (end_s - start_s),
        'bytes_per_s': total / (end_s - start_s),
        'bits_per_s': total * 8 / (end_s - start_s),
        'capacity_bandwidth': None,
        'wire_packet_loss': None
    }


def power_energy(rows, instrument):
    """Integrate calibrated physical power samples with bounded gaps using trapezoids."""
    if (
            instrument.get('scope') != 'physical_uav'
            or not instrument.get('calibration_evidence')
            or (not instrument.get('device_id'))
    ):
        raise ValueError('Calibrated physical UAV instrument required')
    gap = finite(instrument['max_gap_s'])
    if gap <= 0:
        raise ValueError('Positive gap bound required')
    samples = [(finite(row['monotonic_s']), finite(row['power_w'])) for row in rows]
    if len(samples) < 2 or any((power < 0 for _, power in samples)):
        raise ValueError('At least two nonnegative power samples required')
    energy = 0.0
    for (before, previous), (now, power) in zip(samples, samples[1:]):
        if not 0 < now - before <= gap:
            raise ValueError('Unordered or missing power samples')
        energy += (previous + power) * 0.5 * (now - before)
    duration = samples[-1][0] - samples[0][0]
    return {
        'method': 'calibrated physical power, trapezoidal integration',
        'duration_s': duration,
        'energy_j': energy,
        'mean_power_w': energy / duration,
        'instrument': instrument
    }


def main(args=None):
    """Import evidence to a new report; never invent measurements or overwrite results."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        'kind',
        choices=['telemetry', 'correlated', 'sequence', 'traffic', 'power']
    )
    parser.add_argument('--input', required=True)
    parser.add_argument('--metadata', required=True)
    parser.add_argument('--output', required=True)
    options = parser.parse_args(args)
    source = Path(options.input)
    metadata_path = Path(options.metadata)
    metadata = json.loads(metadata_path.read_text())
    if options.kind == 'traffic':
        result = captured_traffic(source, metadata['start_s'], metadata['end_s'], metadata)
    else:
        with source.open(newline='') as stream:
            rows = list(csv.DictReader(stream))
        if options.kind == 'telemetry':
            result = clock_latency(rows, metadata)
        elif options.kind == 'correlated':
            result = correlated_latency(rows)
        elif options.kind == 'sequence':
            result = sequence_loss(rows)
        else:
            result = power_energy(rows, metadata)
    result['source_sha256'] = hashlib.sha256(source.read_bytes()).hexdigest()
    result['metadata_sha256'] = hashlib.sha256(metadata_path.read_bytes()).hexdigest()
    result['validation_scope'] = (
        'schema/method validation; supplied evidence requires human review'
    )
    with Path(options.output).open('x') as stream:
        json.dump(result, stream, indent=2, allow_nan=False)
        stream.write('\n')


if __name__ == '__main__':
    main()


def battery_power(voltage_v, current_a, connected):
    """Reject disconnected, nonfinite and invalid-sentinel simulated battery readings."""
    if connected is not True:
        raise ValueError('Battery disconnected or connection state unknown')
    voltage, current = finite(voltage_v), finite(current_a)
    if voltage <= 0 or current < 0:
        raise ValueError('Invalid voltage/current; negative current is not measured power')
    power = voltage * current
    if not math.isfinite(power):
        raise ValueError('Nonfinite power')
    return power


def battery_energy(rows, max_gap_s):
    """Integrate only consecutive valid simulated readings; never bridge invalid data."""
    gap = finite(max_gap_s)
    if gap <= 0:
        raise ValueError('Positive maximum power sample gap required')
    previous = None
    power = []
    energy = 0.
    integrated_s = 0.
    intervals = 0
    rejected = []
    for index, row in enumerate(rows):
        try:
            when = finite(row['monotonic_s'])
            watts = battery_power(row['voltage_v'], row['current_a'], row['connected'])
        except (KeyError, TypeError, ValueError) as exc:
            rejected.append({'index': index, 'reason': str(exc)})
            previous = None
            continue
        power.append(watts)
        if previous is not None:
            delta = when - previous[0]
            if 0 < delta <= gap:
                energy += (watts + previous[1]) * .5 * delta
                integrated_s += delta
                intervals += 1
            else:
                rejected.append({'index': index, 'reason': 'Nonpositive or excessive sample gap'})
        previous = (when, watts)
    return {'scope': 'PX4 simulated battery estimate; not physical UAV consumption',
            'status': 'MEASURED_UNVALIDATED' if power else 'UNAVAILABLE_IN_CURRENT_SETUP',
            'power_w': power, 'valid_sample_count': len(power), 'rejected': rejected,
            'energy_j': energy if intervals else None,
            'energy_wh': energy / 3600 if intervals else None,
            'integrated_duration_s': integrated_s, 'integrated_interval_count': intervals,
            'method': 'Trapezoids across consecutive valid samples with bounded positive gaps',
            'limitation': 'A credible electrical model or physical calibrated sensor is required'}
