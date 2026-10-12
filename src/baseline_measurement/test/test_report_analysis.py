"""Test reports-only clock/heading inference using clearly synthetic fixtures."""
from pathlib import Path

from baseline_measurement.diagnostic_analysis import dds_deviations, heading_explanation
import pytest
from tools.native_heading_check import run_check as heading_check
from tools.native_timesync_check import run_check as timesync_check


def sample(remote=1000000, observed=0, estimated=0, rtt=0, protocol=2):
    """Build a synthetic diagnostic input, never a baseline experiment."""
    return {'remote_timestamp': remote, 'observed_offset': observed,
            'estimated_offset': estimated, 'round_trip_time': rtt,
            'source_protocol': protocol}


def test_clock_rate_difference_precedes_zero_transition():
    """Distinguish endpoint clock progression from a claimed physical/OS cause."""
    rows = [sample(1000000, -100000, -100000),
            sample(2000000, -250000, -100000), sample(3000000, -400000, 0)]
    result = dds_deviations(rows)
    assert result['zero_transition_indices'] == [2]
    assert result['intervals_before_first_zero'][0]['native_to_peer_progression_ratio'] == 0.85
    assert result['samples'][1]['qualifying_if_filter_converged']
    assert not result['filter_convergence_observed']
    assert not result['underlying_os_cause_proven']
    assert not result['latency_measured']


@pytest.mark.parametrize('rtt,deviation,qualifies', [
    (9999, 100001, True), (10000, 100001, False), (0, 100000, False)])
def test_exact_source_thresholds(rtt, deviation, qualifies):
    """Keep strict source inequalities and native microsecond units."""
    result = dds_deviations([sample(observed=deviation, rtt=rtt)])
    assert result['samples'][0]['qualifying_if_filter_converged'] is qualifies


def test_protocol_one_is_not_dds_evidence():
    """Do not conflate MAVLink timesync and DDS offset transitions."""
    assert not dds_deviations([sample(protocol=1)])['samples']


@pytest.mark.parametrize('bad', [None, 1.5, True, '1000'])
def test_no_arbitrary_unit_conversion(bad):
    """Reject invalid native fields instead of silently guessing units/domains."""
    row = sample()
    row['observed_offset'] = bad
    with pytest.raises(ValueError):
        dds_deviations([row])


def test_repeated_or_reversed_clock_interval_rejected():
    """Do not claim a clock-rate observation from repeated source evidence."""
    with pytest.raises(ValueError):
        dds_deviations([sample(), sample()])


@pytest.mark.parametrize('yaw,mag,aligned,expected', [
    (0, 0, 0, False), (1, 0, 0, True), (1, 1, 0, False), (1, 1, 1, None)])
def test_final_heading_and_initial_yaw_are_distinct(yaw, mag, aligned, expected):
    """Retain missing private elapsed-time uncertainty rather than force readiness."""
    result = heading_explanation({'cs_yaw_align': yaw, 'cs_mag_hdg': mag,
                                  'cs_mag_3d': 0, 'cs_mag_aligned_in_flight': aligned})
    assert result['expected_ready'] is expected


def test_missing_heading_flags_are_unknown():
    """Do not diagnose alignment from absent evidence."""
    assert heading_explanation({})['expected_ready'] is None


def test_actual_native_timesync_and_callback_fixture(tmp_path):
    """Compile actual local PX4 code; platform and samples are synthetic only."""
    px4 = Path.home() / 'PX4-Autopilot'
    result = timesync_check(tmp_path, px4)
    assert result['compile_returncode'] == 0, result['compile_output']
    assert result['run_returncode'] == 0, result['run_output']


def test_actual_final_heading_predicate_fixture(tmp_path):
    """Verify both actual compiled predicate branches and the strict one-second boundary."""
    result = heading_check(tmp_path, Path.home() / 'PX4-Autopilot')
    for variant in result['results']:
        assert variant['compile_returncode'] == 0, variant['compile_output']
        assert variant['run_returncode'] == 0, variant['run_output']
