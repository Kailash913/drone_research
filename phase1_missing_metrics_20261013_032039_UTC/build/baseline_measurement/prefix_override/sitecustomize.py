import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/kailash/ros2_ws/phase1_missing_metrics_20261013_032039_UTC/install/baseline_measurement'
