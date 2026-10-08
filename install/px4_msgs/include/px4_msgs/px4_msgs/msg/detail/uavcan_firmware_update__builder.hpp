// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/UavcanFirmwareUpdate.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/uavcan_firmware_update.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__UAVCAN_FIRMWARE_UPDATE__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__UAVCAN_FIRMWARE_UPDATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/uavcan_firmware_update__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_UavcanFirmwareUpdate_pending_updates
{
public:
  explicit Init_UavcanFirmwareUpdate_pending_updates(::px4_msgs::msg::UavcanFirmwareUpdate & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::UavcanFirmwareUpdate pending_updates(::px4_msgs::msg::UavcanFirmwareUpdate::_pending_updates_type arg)
  {
    msg_.pending_updates = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::UavcanFirmwareUpdate msg_;
};

class Init_UavcanFirmwareUpdate_timestamp
{
public:
  Init_UavcanFirmwareUpdate_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_UavcanFirmwareUpdate_pending_updates timestamp(::px4_msgs::msg::UavcanFirmwareUpdate::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_UavcanFirmwareUpdate_pending_updates(msg_);
  }

private:
  ::px4_msgs::msg::UavcanFirmwareUpdate msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::UavcanFirmwareUpdate>()
{
  return px4_msgs::msg::builder::Init_UavcanFirmwareUpdate_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__UAVCAN_FIRMWARE_UPDATE__BUILDER_HPP_
