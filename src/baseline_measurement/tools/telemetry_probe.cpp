// Read-only bounded C++ demonstration. No flight-input publishers.
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include <px4_msgs/msg/vehicle_status.hpp>
#include <rclcpp/rclcpp.hpp>

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("phase1_cpp_telemetry_probe");
  unsigned count = 0;
  px4_msgs::msg::VehicleStatus last;
  auto sub = node->create_subscription<px4_msgs::msg::VehicleStatus>(
    "/fmu/out/vehicle_status_v4", rclcpp::SensorDataQoS(),
    [&](px4_msgs::msg::VehicleStatus::ConstSharedPtr msg) {
      ++count;
      last = *msg;
    });
  const auto end = std::chrono::steady_clock::now() + std::chrono::seconds(5);
  while (rclcpp::ok() && std::chrono::steady_clock::now() < end) {
    rclcpp::spin_some(node);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  std::cout << "received=" << count << " timestamp_us=" << last.timestamp
            << " arming_state=" << unsigned(last.arming_state)
            << " checks_pass=" << last.pre_flight_checks_pass
            << " failsafe=" << last.failsafe
            << " gcs_connection_lost=" << last.gcs_connection_lost << std::endl;
  rclcpp::shutdown();
  return count >= 2 && last.pre_flight_checks_pass && !last.failsafe ? 0 : 1;
}
