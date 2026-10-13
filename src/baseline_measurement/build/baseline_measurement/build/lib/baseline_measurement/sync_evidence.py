"""Identify DDS synchronizer offset changes independently of estimator reset counters."""


class SyncEvidence:
    """Partition native TimesyncStatus observations by protocol without guessing clock domains."""

    def __init__(self):
        self.previous = {}

    def observe(self, protocol, offset, dds_protocol):
        """Report an observed DDS offset-to-zero transition, not its underlying cause."""
        previous = self.previous.get(protocol)
        self.previous[protocol] = offset
        if protocol == dds_protocol and previous is not None and (previous != 0) and (offset == 0):
            return {
                'previous_offset_us': previous,
                'current_offset_us': offset,
                'interpretation': (
                    'DDS synchronizer offset became zero; correlate native '
                    'timestamps and reset counters before attributing a source '
                    'discontinuity.'
                ),
                'estimator_reset_proven': False
            }
        return None
