"""Keep verification failures separate from incomplete experiment acceptance."""


def verification_exit_code(full_suite_code, build_code, protected_unchanged):
    """Fail the runner on test/build/integrity errors, independently of dataset count."""
    return 0 if full_suite_code == 0 and build_code == 0 and protected_unchanged else 1
