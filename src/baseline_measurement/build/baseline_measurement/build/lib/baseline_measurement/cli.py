"""ROS-independent validation for the mission_node command line."""

import math
import re


def validate_options(observe_seconds, sampling_interval, run_count,
                     experiment_id=None, execute_sitl=False, passive_only=False,
                     topics=None, allowed_topic_keys=()):
    for name, value in (('observe_seconds', observe_seconds),
                        ('sampling_interval', sampling_interval)):
        if not isinstance(value, (int, float)) or not math.isfinite(value) or value <= 0:
            raise ValueError(f'--{name.replace("_", "-")} must be finite and positive')
    if not isinstance(run_count, int) or not 1 <= run_count <= 30:
        raise ValueError('--run-count must be between 1 and 30')
    if experiment_id and not re.fullmatch(r'BASE-(?:00[1-9]|0[12][0-9]|030)', experiment_id):
        raise ValueError('--experiment-id must be BASE-001 through BASE-030')
    if execute_sitl and (passive_only or run_count != 1):
        raise ValueError('--execute-sitl cannot be combined with --passive-only or batch runs')
    if not isinstance(topics, dict) or any(
            key not in allowed_topic_keys or not isinstance(value, str)
            or not value.startswith('/') for key, value in topics.items()):
        raise ValueError('config topics must map known keys to absolute ROS topic names')
