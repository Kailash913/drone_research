"""Ensure nonflight report commands never hide test, build or preservation failures."""
from baseline_measurement.reporting import verification_exit_code
import pytest


@pytest.mark.parametrize('suite,build,preserved', [
    (1, 0, True), (0, 1, True), (None, 0, True), (0, 0, False)])
def test_failure_is_not_masked(suite, build, preserved):
    """Reject a false successful command exit despite a generated report."""
    assert verification_exit_code(suite, build, preserved) == 1


def test_dataset_rejection_is_distinct_from_verification_failure():
    """Permit working tooling with passing checks while experiment acceptance is blocked."""
    assert verification_exit_code(0, 0, True) == 0
