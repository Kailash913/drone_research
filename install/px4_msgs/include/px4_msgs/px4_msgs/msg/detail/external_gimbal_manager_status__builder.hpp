// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/ExternalGimbalManagerStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/external_gimbal_manager_status.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__EXTERNAL_GIMBAL_MANAGER_STATUS__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__EXTERNAL_GIMBAL_MANAGER_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/external_gimbal_manager_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_ExternalGimbalManagerStatus_secondary_control_compid
{
public:
  explicit Init_ExternalGimbalManagerStatus_secondary_control_compid(::px4_msgs::msg::ExternalGimbalManagerStatus & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::ExternalGimbalManagerStatus secondary_control_compid(::px4_msgs::msg::ExternalGimbalManagerStatus::_secondary_control_compid_type arg)
  {
    msg_.secondary_control_compid = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::ExternalGimbalManagerStatus msg_;
};

class Init_ExternalGimbalManagerStatus_secondary_control_sysid
{
public:
  explicit Init_ExternalGimbalManagerStatus_secondary_control_sysid(::px4_msgs::msg::ExternalGimbalManagerStatus & msg)
  : msg_(msg)
  {}
  Init_ExternalGimbalManagerStatus_secondary_control_compid secondary_control_sysid(::px4_msgs::msg::ExternalGimbalManagerStatus::_secondary_control_sysid_type arg)
  {
    msg_.secondary_control_sysid = std::move(arg);
    return Init_ExternalGimbalManagerStatus_secondary_control_compid(msg_);
  }

private:
  ::px4_msgs::msg::ExternalGimbalManagerStatus msg_;
};

class Init_ExternalGimbalManagerStatus_primary_control_compid
{
public:
  explicit Init_ExternalGimbalManagerStatus_primary_control_compid(::px4_msgs::msg::ExternalGimbalManagerStatus & msg)
  : msg_(msg)
  {}
  Init_ExternalGimbalManagerStatus_secondary_control_sysid primary_control_compid(::px4_msgs::msg::ExternalGimbalManagerStatus::_primary_control_compid_type arg)
  {
    msg_.primary_control_compid = std::move(arg);
    return Init_ExternalGimbalManagerStatus_secondary_control_sysid(msg_);
  }

private:
  ::px4_msgs::msg::ExternalGimbalManagerStatus msg_;
};

class Init_ExternalGimbalManagerStatus_primary_control_sysid
{
public:
  explicit Init_ExternalGimbalManagerStatus_primary_control_sysid(::px4_msgs::msg::ExternalGimbalManagerStatus & msg)
  : msg_(msg)
  {}
  Init_ExternalGimbalManagerStatus_primary_control_compid primary_control_sysid(::px4_msgs::msg::ExternalGimbalManagerStatus::_primary_control_sysid_type arg)
  {
    msg_.primary_control_sysid = std::move(arg);
    return Init_ExternalGimbalManagerStatus_primary_control_compid(msg_);
  }

private:
  ::px4_msgs::msg::ExternalGimbalManagerStatus msg_;
};

class Init_ExternalGimbalManagerStatus_gimbal_device_id
{
public:
  explicit Init_ExternalGimbalManagerStatus_gimbal_device_id(::px4_msgs::msg::ExternalGimbalManagerStatus & msg)
  : msg_(msg)
  {}
  Init_ExternalGimbalManagerStatus_primary_control_sysid gimbal_device_id(::px4_msgs::msg::ExternalGimbalManagerStatus::_gimbal_device_id_type arg)
  {
    msg_.gimbal_device_id = std::move(arg);
    return Init_ExternalGimbalManagerStatus_primary_control_sysid(msg_);
  }

private:
  ::px4_msgs::msg::ExternalGimbalManagerStatus msg_;
};

class Init_ExternalGimbalManagerStatus_flags
{
public:
  explicit Init_ExternalGimbalManagerStatus_flags(::px4_msgs::msg::ExternalGimbalManagerStatus & msg)
  : msg_(msg)
  {}
  Init_ExternalGimbalManagerStatus_gimbal_device_id flags(::px4_msgs::msg::ExternalGimbalManagerStatus::_flags_type arg)
  {
    msg_.flags = std::move(arg);
    return Init_ExternalGimbalManagerStatus_gimbal_device_id(msg_);
  }

private:
  ::px4_msgs::msg::ExternalGimbalManagerStatus msg_;
};

class Init_ExternalGimbalManagerStatus_manager_compid
{
public:
  explicit Init_ExternalGimbalManagerStatus_manager_compid(::px4_msgs::msg::ExternalGimbalManagerStatus & msg)
  : msg_(msg)
  {}
  Init_ExternalGimbalManagerStatus_flags manager_compid(::px4_msgs::msg::ExternalGimbalManagerStatus::_manager_compid_type arg)
  {
    msg_.manager_compid = std::move(arg);
    return Init_ExternalGimbalManagerStatus_flags(msg_);
  }

private:
  ::px4_msgs::msg::ExternalGimbalManagerStatus msg_;
};

class Init_ExternalGimbalManagerStatus_manager_sysid
{
public:
  explicit Init_ExternalGimbalManagerStatus_manager_sysid(::px4_msgs::msg::ExternalGimbalManagerStatus & msg)
  : msg_(msg)
  {}
  Init_ExternalGimbalManagerStatus_manager_compid manager_sysid(::px4_msgs::msg::ExternalGimbalManagerStatus::_manager_sysid_type arg)
  {
    msg_.manager_sysid = std::move(arg);
    return Init_ExternalGimbalManagerStatus_manager_compid(msg_);
  }

private:
  ::px4_msgs::msg::ExternalGimbalManagerStatus msg_;
};

class Init_ExternalGimbalManagerStatus_timestamp
{
public:
  Init_ExternalGimbalManagerStatus_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExternalGimbalManagerStatus_manager_sysid timestamp(::px4_msgs::msg::ExternalGimbalManagerStatus::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_ExternalGimbalManagerStatus_manager_sysid(msg_);
  }

private:
  ::px4_msgs::msg::ExternalGimbalManagerStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::ExternalGimbalManagerStatus>()
{
  return px4_msgs::msg::builder::Init_ExternalGimbalManagerStatus_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__EXTERNAL_GIMBAL_MANAGER_STATUS__BUILDER_HPP_
