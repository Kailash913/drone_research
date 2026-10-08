// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/NfsUp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/nfs_up.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__NFS_UP__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__NFS_UP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/nfs_up__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_NfsUp_timestamp
{
public:
  Init_NfsUp_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::px4_msgs::msg::NfsUp timestamp(::px4_msgs::msg::NfsUp::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::NfsUp msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::NfsUp>()
{
  return px4_msgs::msg::builder::Init_NfsUp_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__NFS_UP__BUILDER_HPP_
