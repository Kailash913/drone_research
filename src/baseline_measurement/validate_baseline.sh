#!/usr/bin/env bash
# Read-only ROS preflight after building ONLY baseline_measurement.
# Does not start PX4, Gazebo, MicroXRCEAgent, or a flight controller.
set -eo pipefail
cd "$HOME/ros2_ws"
source /opt/ros/jazzy/setup.bash
source install/setup.bash
python3 -c 'import psutil, rclpy, px4_msgs; print("Dependencies import successfully")'
colcon build --packages-select baseline_measurement
source install/setup.bash
python3 -m unittest discover -s src/baseline_measurement/test -p test_phase1.py -v
for name in VehicleCommand TrajectorySetpoint OffboardControlMode VehicleStatus VehicleLocalPosition VehicleLandDetected VehicleCommandAck; do
    ros2 interface show "px4_msgs/msg/$name"
done
ros2 node list
ros2 topic list -t
for topic in /fmu/in/offboard_control_mode /fmu/in/trajectory_setpoint /fmu/in/vehicle_command; do
    ros2 topic info "$topic" --verbose
done
ros2 run baseline_measurement mission_node --observe-seconds 15
