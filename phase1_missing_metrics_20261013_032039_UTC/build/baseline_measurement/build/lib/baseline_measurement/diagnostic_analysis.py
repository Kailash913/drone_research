"""Interpret diagnostic observations without publishing or changing flight decisions."""


def dds_deviations(samples):
    """Measure conditional deviations and clock intervals; do not infer an OS cause."""
    rows = []
    for sample in samples:
        if sample.get('source_protocol') != 2:
            continue
        fields = ('remote_timestamp', 'observed_offset', 'estimated_offset', 'round_trip_time')
        if any(isinstance(sample.get(k), bool) or not isinstance(sample.get(k), int)
               for k in fields):
            raise ValueError('DDS fields must retain native integer units')
        if sample['remote_timestamp'] <= 0 or sample['round_trip_time'] < 0:
            raise ValueError('Invalid native DDS clock observation')
        deviation = abs(sample['observed_offset'] - sample['estimated_offset'])
        rows.append({**sample, 'deviation_us': deviation,
                     'qualifying_if_filter_converged': (
                         sample['round_trip_time'] < 10000 and deviation > 100000),
                     'native_midpoint_us': sample['remote_timestamp'] + sample['observed_offset']})
    transitions = [i for i in range(1, len(rows))
                   if rows[i - 1]['estimated_offset'] != 0 and rows[i]['estimated_offset'] == 0]
    before = rows[:transitions[0]] if transitions else rows
    intervals = []
    for previous, current in zip(before, before[1:]):
        peer_delta = current['remote_timestamp'] - previous['remote_timestamp']
        native_delta = current['native_midpoint_us'] - previous['native_midpoint_us']
        if peer_delta <= 0 or native_delta <= 0:
            raise ValueError('Clock interval evidence is repeated or reversed')
        intervals.append({'peer_delta_us': peer_delta, 'native_midpoint_delta_us': native_delta,
                          'native_to_peer_progression_ratio': native_delta / peer_delta})
    return {'samples': rows, 'zero_transition_indices': transitions,
            'intervals_before_first_zero': intervals, 'filter_convergence_observed': False,
            'latency_measured': False, 'underlying_os_cause_proven': False,
            'method': 'native midpoint=(originate+receive)/2 from observed+remote fields; '
                      'integer division has <=1 us rounding, not a calibrated clock mapping'}


def heading_explanation(flags, magnetometer_compiled=True):
    """Explain observable branches while retaining uncertainty about private elapsed time."""
    keys = ('cs_yaw_align', 'cs_mag_hdg', 'cs_mag_3d', 'cs_mag_aligned_in_flight')
    if any(flags.get(k) not in (0, 1, False, True) for k in keys):
        return {'expected_ready': None, 'reason': 'Missing readiness evidence'}
    if not flags['cs_yaw_align']:
        return {'expected_ready': False, 'reason': 'Initial yaw alignment absent'}
    if not magnetometer_compiled or not (flags['cs_mag_hdg'] or flags['cs_mag_3d']):
        return {'expected_ready': True, 'reason': 'Yaw aligned without active magnetic heading'}
    if not flags['cs_mag_aligned_in_flight']:
        return {'expected_ready': False, 'reason': 'Magnetic in-flight alignment incomplete'}
    return {'expected_ready': None,
            'reason': 'Native private alignment start and delayed time needed for >1 s check'}
