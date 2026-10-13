import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/kailash/ros2_ws/src/baseline_measurement/install/baseline_measurement'
