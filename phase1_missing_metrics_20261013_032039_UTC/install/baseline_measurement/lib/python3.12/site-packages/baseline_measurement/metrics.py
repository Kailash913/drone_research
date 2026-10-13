"""ROS-independent calculations for the unsecured baseline."""

import math
import random
import statistics


_T95 = (None, 12.706, 4.303, 3.182, 2.776, 2.571, 2.447, 2.365,
        2.306, 2.262, 2.228, 2.201, 2.179, 2.160, 2.145, 2.131,
        2.120, 2.110, 2.101, 2.093, 2.086, 2.080, 2.074, 2.069,
        2.064, 2.060, 2.056, 2.052, 2.048, 2.045)


def describe(values, independent=False):
    """Describe finite samples; CI requires independent observations."""
    data = [float(x) for x in values if x is not None and math.isfinite(x)]
    if not data:
        return {'count': 0, 'mean': None, 'median': None, 'std': None,
                'min': None, 'max': None, 'ci95_lower': None, 'ci95_upper': None}
    n = len(data)
    mean = statistics.mean(data)
    sd = statistics.stdev(data) if n > 1 else None
    result = {'count': n, 'mean': mean, 'median': statistics.median(data),
              'std': sd, 'min': min(data), 'max': max(data),
              'ci95_lower': None, 'ci95_upper': None}
    if independent and n > 1:
        critical = _T95[n - 1] if n <= 30 else 1.96
        half = critical * sd / math.sqrt(n)
        result.update(ci95_lower=mean - half, ci95_upper=mean + half)
    return result


def throughput_mbps(delivered_bytes, elapsed_s):
    if delivered_bytes < 0 or elapsed_s <= 0:
        return None
    return delivered_bytes * 8 / elapsed_s / 1_000_000


def packet_loss_pct(sent, received):
    if sent <= 0 or received < 0 or received > sent:
        return None
    return 100 * (sent - received) / sent


def integrate_energy_wh(samples):
    """Trapezoidal integration of (monotonic seconds, valid watts)."""
    result = 0.0
    previous = None
    for when, watts in samples:
        if not math.isfinite(when) or not math.isfinite(watts) or watts < 0:
            continue
        if previous is not None and when > previous[0]:
            result += (watts + previous[1]) * (when - previous[0]) / 7200
        previous = (when, watts)
    return result if previous is not None else None


class OnlineStats:
    """Exact mean/variance/extrema; bounded reservoir for approximate median."""

    def __init__(self, capacity=4096):
        self.n = 0
        self.mean = self.m2 = 0.0
        self.minimum = self.maximum = None
        self.samples = []
        self.capacity = capacity
        self.random = random.Random(0)

    def add(self, value):
        if value is None or not math.isfinite(value):
            return
        value = float(value)
        self.n += 1
        delta = value - self.mean
        self.mean += delta / self.n
        self.m2 += delta * (value - self.mean)
        self.minimum = value if self.minimum is None else min(self.minimum, value)
        self.maximum = value if self.maximum is None else max(self.maximum, value)
        if len(self.samples) < self.capacity:
            self.samples.append(value)
        else:
            slot = self.random.randrange(self.n)
            if slot < self.capacity:
                self.samples[slot] = value

    def summary(self):
        return {'count': self.n, 'mean': self.mean if self.n else None,
                'median': statistics.median(self.samples) if self.samples else None,
                'median_approximate': self.n > self.capacity,
                'std': math.sqrt(max(self.m2, 0) / (self.n - 1)) if self.n > 1 else None,
                'min': self.minimum, 'max': self.maximum,
                'ci95_lower': None, 'ci95_upper': None}
