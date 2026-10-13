"""Offline independent trajectory comparison requiring explicit clock/frame evidence."""
from bisect import bisect_left
from collections import Counter
from decimal import Decimal
import math

from .measurements import finite
from .metrics import describe


def vector(values):
    """Require a finite three-dimensional coordinate."""
    if len(values) != 3:
        raise ValueError('Three coordinates required')
    return [finite(x) for x in values]


def transform(position, frame):
    """Apply an evidenced rigid rotation and two independently established origins."""
    if not frame.get('validation_evidence'):
        raise ValueError('Independent frame/origin evidence required')
    rotation = [vector(row) for row in frame['rotation']]
    if len(rotation) != 3:
        raise ValueError('Three rotation rows required')
    for i in range(3):
        for j in range(3):
            dot = sum(rotation[i][k] * rotation[j][k] for k in range(3))
            if not math.isclose(dot, float(i == j), abs_tol=1e-9):
                raise ValueError('Rotation must be orthonormal')
    determinant = sum(rotation[0][i] * (
        rotation[1][(i + 1) % 3] * rotation[2][(i + 2) % 3]
        - rotation[1][(i + 2) % 3] * rotation[2][(i + 1) % 3]) for i in range(3))
    if not math.isclose(determinant, 1., abs_tol=1e-9):
        raise ValueError('Rotation must preserve handedness')
    origin = vector(frame['gazebo_origin'])
    local = vector(frame['px4_origin'])
    point = vector(position)
    return [sum(rotation[i][k] * (point[k] - origin[k]) for k in range(3)) + local[i]
            for i in range(3)]


def trajectory_rmse(estimates, truth, calibration, frame):
    """Pair once within a validated time bound; exclude ground, resets and bad samples."""
    for key in ('validation_evidence', 'source_domain', 'receiver_domain'):
        if not calibration.get(key):
            raise ValueError('Independent clock evidence and explicit domains required')
    if calibration['receiver_domain'] != 'gazebo_sim_ns':
        raise ValueError('Ground truth must use Gazebo simulation nanoseconds')
    scale = finite(calibration['scale_ns_per_source_unit'])
    offset = finite(calibration['offset_ns'])
    uncertainty = finite(calibration['uncertainty_ns'])
    bound = finite(calibration['maximum_pair_error_ns'])
    lower = finite(calibration['valid_source_min'])
    upper = finite(calibration['valid_source_max'])
    if scale <= 0 or uncertainty < 0 or bound <= 0 or uncertainty > bound or lower > upper:
        raise ValueError('Invalid clock calibration or alignment bound')
    transform([0., 0., 0.], frame)
    previous = None
    for row in truth:
        finite(row['source_timestamp'])
        stamp = Decimal(str(row['source_timestamp']))
        if row['source_domain'] != calibration['receiver_domain']:
            raise ValueError('Ground truth clock domain mismatch')
        if previous is not None and stamp <= previous:
            raise ValueError('Truth timestamps must increase strictly')
        vector(row['position'])
        previous = stamp
    times = [Decimal(str(row['source_timestamp'])) for row in truth]
    rejected = Counter()
    matched = []
    used = set()
    counters = None
    previous = None
    reset_latched = False
    for index, row in enumerate(estimates):
        if row['source_domain'] != calibration['source_domain']:
            raise ValueError('Estimate clock domain mismatch')
        finite(row['source_timestamp'])
        stamp = Decimal(str(row['source_timestamp']))
        if previous is not None and stamp <= previous:
            rejected['source_order'] += 1
            continue
        previous = stamp
        current = row.get('reset_counters')
        if not current or not all(k in current for k in
                                  ('xy_reset_counter', 'z_reset_counter',
                                   'heading_reset_counter')):
            rejected['missing_reset_counters'] += 1
            continue
        if counters is not None and current != counters:
            reset_latched = True
        counters = current
        if reset_latched:
            rejected['reset_boundary_requires_new_calibration'] += 1
            continue
        if row.get('airborne') is not True:
            rejected['grounded_or_unknown_flight_state'] += 1
            continue
        if row.get('position_valid') is not True:
            rejected['invalid_estimator_position'] += 1
            continue
        if not lower <= stamp <= upper:
            rejected['outside_calibration_interval'] += 1
            continue
        target = (stamp * Decimal(str(calibration['scale_ns_per_source_unit']))
                  + Decimal(str(calibration['offset_ns'])))
        slot = bisect_left(times, target)
        options = [i for i in (slot - 1, slot) if 0 <= i < len(times)]
        if not options:
            rejected['no_truth'] += 1
            continue
        nearest = min(options, key=lambda i: abs(times[i] - target))
        delta = float(times[nearest] - target)
        if abs(delta) + uncertainty > bound:
            rejected['alignment_bound'] += 1
            continue
        if nearest in used:
            rejected['truth_already_used'] += 1
            continue
        try:
            position = vector(row['position'])
        except ValueError:
            rejected['nonfinite_position'] += 1
            continue
        gt = transform(truth[nearest]['position'], frame)
        error = [position[k] - gt[k] for k in range(3)]
        used.add(nearest)
        matched.append({'estimate_index': index, 'truth_index': nearest,
                        'error_ned_m': error, 'alignment_error_ns': delta})
    n = len(matched)
    axis = [math.sqrt(sum(p['error_ned_m'][k] ** 2 for p in matched) / n)
            if n else None for k in range(3)]
    return {'status': 'MEASURED_UNVALIDATED' if n else 'NOT_MEASURED',
            'validation_scope': 'Calculation validated; supplied calibration/frame evidence '
            'requires independent review before experimental acceptance',
            'matched_count': n, 'rejected': dict(rejected), 'pairs': matched,
            'axis_rmse_m': axis,
            'horizontal_rmse_m': math.hypot(axis[0], axis[1]) if n else None,
            'vertical_rmse_m': axis[2],
            'rmse_3d_m': math.sqrt(sum(x * x for x in axis)) if n else None,
            'alignment_error_ns': describe([abs(p['alignment_error_ns']) for p in matched]),
            'calibration': calibration, 'frame': frame}
