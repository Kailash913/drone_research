"""Test native clock contract rejection without publishing or arming a vehicle."""
from baseline_measurement.native_clock import native_header, verify_native_pairs
import pytest


@pytest.mark.parametrize('value', [None, 0, -1, 1.5, True])
def test_invalid_native_header(value):
    """Reject missing or guessed timestamps."""
    with pytest.raises(ValueError):
        native_header(value)


def test_header_is_exact():
    """Preserve observed bytes numerically without applying a clock estimate."""
    assert native_header(6632104000) == 6632104000


def pairs():
    """Return fixture observations that are never experimental measurements."""
    return [{'ros_timestamp_us': 1000000 + i * 100000,
             'mavlink_time_boot_ms': 1000 + i * 100} for i in range(10)]


def test_explicit_native_contract():
    """Validate domain agreement without claiming latency or flight authorization."""
    result = verify_native_pairs(pairs(), synchronized=0)
    assert result['clock_domain'] == 'px4_boot_us'
    assert not result['latency_measured']
    assert not result['flight_authorized']


def test_synchronized_mode_rejected():
    """Require actual configuration evidence instead of selecting a guessed domain."""
    with pytest.raises(ValueError):
        verify_native_pairs(pairs(), synchronized=1)


def test_epoch_boot_mismatch_rejected():
    """Reject an epoch/native mismatch rather than normalizing arbitrary values."""
    samples = pairs()
    samples[4]['ros_timestamp_us'] = 1791742020006623
    with pytest.raises(ValueError):
        verify_native_pairs(samples, synchronized=0)


@pytest.mark.parametrize('change', ['reverse', 'repeat', 'missing', 'insufficient'])
def test_bad_clock_evidence(change):
    """Reject evidence that cannot establish native ordering."""
    samples = pairs()
    if change == 'reverse':
        samples[4]['ros_timestamp_us'] = 900000
    elif change == 'repeat':
        samples[4] = samples[3].copy()
    elif change == 'missing':
        samples[4]['ros_timestamp_us'] = 0
    else:
        samples = samples[:2]
    with pytest.raises(ValueError):
        verify_native_pairs(samples, synchronized=0)
