
#!/usr/bin/env python3

import asyncio
import math

import rclpy
from rclpy.node import Node
from nav_msgs.msg import Path
from geometry_msgs.msg import PoseStamped

from mavsdk import System
from mavsdk.mission import MissionItem, MissionPlan


class Ros2QgcMission(Node):
    def __init__(self):
        super().__init__("ros2_qgc_mission")

        self.path_pub = self.create_publisher(
            Path, "/mission/path", 10
        )

    def publish_path(self, offsets):
        path = Path()
        path.header.frame_id = "map"
        path.header.stamp = self.get_clock().now().to_msg()

        for east, north in offsets:
            pose = PoseStamped()
            pose.header = path.header
            pose.pose.position.x = float(east)
            pose.pose.position.y = float(north)
            pose.pose.position.z = 5.0
            pose.pose.orientation.w = 1.0
            path.poses.append(pose)

        self.path_pub.publish(path)
        self.get_logger().info(
            f"Published ROS 2 path with {len(offsets)} waypoints"
        )


async def wait_for_connection(drone):
    async for state in drone.core.connection_state():
        if state.is_connected:
            return


async def get_position(drone):
    async for position in drone.telemetry.position():
        if (
            math.isfinite(position.latitude_deg)
            and math.isfinite(position.longitude_deg)
            and abs(position.latitude_deg) <= 90
            and abs(position.longitude_deg) <= 180
        ):
            return position


async def main():
    rclpy.init()
    node = Ros2QgcMission()

    try:
        drone = System()

        # PX4 SITL offboard/MAVSDK UDP endpoint.
        await drone.connect(
            system_address="udp://0.0.0.0:14540"
        )

        node.get_logger().info("Waiting for PX4 MAVLink...")
        await asyncio.wait_for(
            wait_for_connection(drone), timeout=30
        )

        node.get_logger().info("PX4 MAVLink connected")

        position = await asyncio.wait_for(
            get_position(drone), timeout=30
        )

        lat0 = position.latitude_deg
        lon0 = position.longitude_deg

        node.get_logger().info(
            f"Reference GPS: {lat0:.7f}, {lon0:.7f}"
        )

        # Small 5 m square around the current simulated position.
        # East/north offsets in metres.
        offsets = [
            (0.0, 0.0),
            (5.0, 0.0),
            (5.0, 5.0),
            (0.0, 5.0),
        ]

        # Convert local offsets to approximate GPS coordinates.
        metres_per_degree_lat = 111111.0
        metres_per_degree_lon = (
            111111.0 * max(
                abs(math.cos(math.radians(lat0))), 1e-6
            )
        )

        mission_items = []

        for east, north in offsets:
            lat = lat0 + north / metres_per_degree_lat
            lon = lon0 + east / metres_per_degree_lon

            mission_items.append(
                MissionItem(
                    lat,
                    lon,
                    5.0,                  # Relative altitude (m)
                    2.0,                  # Speed (m/s)
                    False,                # Stop at each waypoint
                    float("nan"),         # Gimbal pitch
                    float("nan"),         # Gimbal yaw
                    MissionItem.CameraAction.NONE,
                    0.0,                  # Loiter time
                    0.0,                  # Photo interval
                    1.0,                  # Acceptance radius
                    float("nan"),         # Yaw
                    float("nan"),         # Photo distance
                    MissionItem.VehicleAction.NONE,
                )
            )

        # Publish the corresponding local ROS 2 path.
        node.publish_path(offsets)

        # Upload only: do NOT arm or start the mission.
        plan = MissionPlan(mission_items)

        node.get_logger().info(
            "Uploading mission to PX4; vehicle will remain disarmed"
        )
        await drone.mission.upload_mission(plan)

        node.get_logger().info(
            "MISSION UPLOAD ACKNOWLEDGED BY MAVSDK"
        )
        node.get_logger().info(
            "Next: download the vehicle mission in QGC Plan view"
        )

        # Keep the ROS 2 node alive briefly for path publication.
        await asyncio.sleep(2)

    except asyncio.TimeoutError:
        node.get_logger().error(
            "Timed out waiting for PX4 connection or GPS position"
        )
    except Exception as exc:
        node.get_logger().error(f"Mission upload failed: {exc}")
        raise
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    asyncio.run(main())

