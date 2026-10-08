// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/FixedWingTakeoffStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/fixed_wing_takeoff_status.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__FIXED_WING_TAKEOFF_STATUS__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__FIXED_WING_TAKEOFF_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/fixed_wing_takeoff_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_FixedWingTakeoffStatus_climbout_completed
{
public:
  explicit Init_FixedWingTakeoffStatus_climbout_completed(::px4_msgs::msg::FixedWingTakeoffStatus & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::FixedWingTakeoffStatus climbout_completed(::px4_msgs::msg::FixedWingTakeoffStatus::_climbout_completed_type arg)
  {
    msg_.climbout_completed = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::FixedWingTakeoffStatus msg_;
};

class Init_FixedWingTakeoffStatus_timestamp
{
public:
  Init_FixedWingTakeoffStatus_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FixedWingTakeoffStatus_climbout_completed timestamp(::px4_msgs::msg::FixedWingTakeoffStatus::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_FixedWingTakeoffStatus_climbout_completed(msg_);
  }

private:
  ::px4_msgs::msg::FixedWingTakeoffStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::FixedWingTakeoffStatus>()
{
  return px4_msgs::msg::builder::Init_FixedWingTakeoffStatus_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__FIXED_WING_TAKEOFF_STATUS__BUILDER_HPP_
