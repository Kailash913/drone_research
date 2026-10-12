import csv
import time
import psutil

from datetime import datetime

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy

from px4_msgs.msg import VehicleStatus
from px4_msgs.msg import VehicleAttitude
from px4_msgs.msg import OffboardControlMode

class BaselineMeasurement(Node):

    def __init__(self):
        super().__init__('baseline_measurement')
        self.process = psutil.Process()
        self.process.cpu_percent(interval=None)
        # Message counters
        self.status_count = 0
        self.attitude_count = 0
        self.offboard_count = 0

        # Start time
        self.start_time = time.monotonic()
        px4_qos = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=10
        )
        # PX4 -> ROS 2
        self.status_sub = self.create_subscription(
            VehicleStatus,
            '/fmu/out/vehicle_status_v4',
            self.status_callback,
            px4_qos
        )

        self.attitude_sub = self.create_subscription(
            VehicleAttitude,
            '/fmu/out/vehicle_attitude',
            self.attitude_callback,
            px4_qos
        )

        # ROS 2 -> PX4
        self.offboard_pub = self.create_publisher(
            OffboardControlMode,
            '/fmu/in/offboard_control_mode',
            10
        )

        # Measure every 0.5 seconds
        self.timer = self.create_timer(
            0.5,
            self.measurement_callback
        )

        # Previous counters
        self.last_status_count = 0
        self.last_attitude_count = 0
        self.last_offboard_count = 0

        # CSV file
        self.csv_file = 'baseline_measurements.csv'

        self.csv = open(
            self.csv_file,
            'w',
            newline=''
        )

        self.writer = csv.writer(self.csv)

        self.writer.writerow([
            'timestamp',
            'elapsed_seconds',
            'cpu_percent',
            'memory_kb',
            'vehicle_status_count',
            'vehicle_attitude_count',
            'offboard_messages_sent',
            'status_rate_hz',
            'attitude_rate_hz',
            'offboard_rate_hz'
        ])

        self.get_logger().info(
            'Baseline measurement node started.'
        )

    def status_callback(self, msg):
        self.status_count += 1

    def attitude_callback(self, msg):
        self.attitude_count += 1

    def publish_offboard(self):

        msg = OffboardControlMode()

        msg.timestamp = int(
            self.get_clock().now().nanoseconds / 1000
        )

        msg.position = False
        msg.velocity = False
        msg.acceleration = False
        msg.attitude = False
        msg.body_rate = False
        msg.thrust_and_torque = False
        msg.direct_actuator = False

        self.offboard_pub.publish(msg)

        self.offboard_count += 1

    def measurement_callback(self):

        # Send one OffboardControlMode message
        self.publish_offboard()

        now = time.monotonic()
        elapsed = now - self.start_time

        # Messages received during the last 0.5 seconds
        status_delta = (
            self.status_count -
            self.last_status_count
        )

        attitude_delta = (
            self.attitude_count -
            self.last_attitude_count
        )

        offboard_delta = (
            self.offboard_count -
            self.last_offboard_count
        )

        interval = 0.5

        status_rate = status_delta / interval
        attitude_rate = attitude_delta / interval
        offboard_rate = offboard_delta / interval

        # Save current counters
        self.last_status_count = self.status_count
        self.last_attitude_count = self.attitude_count
        self.last_offboard_count = self.offboard_count

        # CPU and memory
        cpu_percent = psutil.cpu_percent(interval=None)

        memory_kb = (
            self.process.memory_info().rss // 1024
        )

        timestamp = datetime.now().isoformat()

        # Write CSV row
        self.writer.writerow([
            timestamp,
            round(elapsed, 3),
            round(cpu_percent, 3),
            memory_kb,
            self.status_count,
            self.attitude_count,
            self.offboard_count,
            round(status_rate, 3),
            round(attitude_rate, 3),
            round(offboard_rate, 3)
        ])

        self.csv.flush()

        self.get_logger().info(
            f'Elapsed={elapsed:.1f}s | '
            f'Status={status_rate:.2f} Hz | '
            f'Attitude={attitude_rate:.2f} Hz | '
            f'Offboard={offboard_rate:.2f} Hz | '
            f'CPU={cpu_percent:.2f}% | '
            f'Memory={memory_kb} KB'
        )


def main(args=None):

    rclpy.init(args=args)

    node = BaselineMeasurement()

    try:
        rclpy.spin(node)

    except KeyboardInterrupt:
        pass

    finally:
        node.csv.close()

        if rclpy.ok():
            node.destroy_node()
            rclpy.shutdown()


if __name__ == '__main__':
    main()
