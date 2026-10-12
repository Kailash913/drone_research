"""Validate explicit native-clock evidence without altering the mission controller."""


def native_header(source_timestamp_us):
    """Retain an observed positive PX4 timestamp without conversion or extrapolation."""
    if (isinstance(source_timestamp_us, bool)
            or not isinstance(source_timestamp_us, int) or source_timestamp_us <= 0):
        raise ValueError('A positive observed native timestamp is required')
    return source_timestamp_us


def verify_native_pairs(pairs, synchronized, maximum_difference_us=100000):
    """Check bounded ROS/MAVLink boot-clock agreement; never interpret it as latency."""
    if synchronized != 0:
        raise ValueError('DDS native mode requires verified UXRCE_DDS_SYNCT=0')
    if not isinstance(maximum_difference_us, int) or maximum_difference_us <= 0:
        raise ValueError('An explicit positive comparison bound is required')
    if len(pairs) < 10:
        raise ValueError('At least ten independent native clock observations are required')
    previous = None
    for pair in pairs:
        source = native_header(pair['ros_timestamp_us'])
        boot_ms = pair['mavlink_time_boot_ms']
        if isinstance(boot_ms, bool) or not isinstance(boot_ms, int) or boot_ms <= 0:
            raise ValueError('A positive MAVLink native boot timestamp is required')
        if abs(source - boot_ms * 1000) > maximum_difference_us:
            raise ValueError('ROS and independently observed native clocks disagree')
        if previous is not None and (source <= previous[0] or boot_ms <= previous[1]):
            raise ValueError('Repeated or reversed observations cannot validate ordering')
        previous = (source, boot_ms)
    return {'clock_domain': 'px4_boot_us', 'observations': len(pairs),
            'maximum_difference_us': maximum_difference_us,
            'latency_measured': False, 'flight_authorized': False}
