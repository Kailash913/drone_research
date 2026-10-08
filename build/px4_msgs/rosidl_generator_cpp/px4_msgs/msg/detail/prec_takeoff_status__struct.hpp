// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/PrecTakeoffStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/prec_takeoff_status.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__PREC_TAKEOFF_STATUS__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__PREC_TAKEOFF_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__PrecTakeoffStatus __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__PrecTakeoffStatus __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PrecTakeoffStatus_
{
  using Type = PrecTakeoffStatus_<ContainerAllocator>;

  explicit PrecTakeoffStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->state = 0;
      this->setpoint_adjusted = false;
    }
  }

  explicit PrecTakeoffStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->state = 0;
      this->setpoint_adjusted = false;
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _state_type =
    uint8_t;
  _state_type state;
  using _setpoint_adjusted_type =
    bool;
  _setpoint_adjusted_type setpoint_adjusted;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__state(
    const uint8_t & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__setpoint_adjusted(
    const bool & _arg)
  {
    this->setpoint_adjusted = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t PREC_TAKEOFF_STATE_STOPPED =
    0u;
  static constexpr uint8_t PREC_TAKEOFF_STATE_ONGOING =
    1u;
  static constexpr uint8_t PREC_TAKEOFF_STATE_DONE =
    2u;

  // pointer types
  using RawPtr =
    px4_msgs::msg::PrecTakeoffStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::PrecTakeoffStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::PrecTakeoffStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::PrecTakeoffStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::PrecTakeoffStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::PrecTakeoffStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::PrecTakeoffStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::PrecTakeoffStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::PrecTakeoffStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::PrecTakeoffStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__PrecTakeoffStatus
    std::shared_ptr<px4_msgs::msg::PrecTakeoffStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__PrecTakeoffStatus
    std::shared_ptr<px4_msgs::msg::PrecTakeoffStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PrecTakeoffStatus_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    if (this->setpoint_adjusted != other.setpoint_adjusted) {
      return false;
    }
    return true;
  }
  bool operator!=(const PrecTakeoffStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PrecTakeoffStatus_

// alias to use template instance with default allocator
using PrecTakeoffStatus =
  px4_msgs::msg::PrecTakeoffStatus_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PrecTakeoffStatus_<ContainerAllocator>::PREC_TAKEOFF_STATE_STOPPED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PrecTakeoffStatus_<ContainerAllocator>::PREC_TAKEOFF_STATE_ONGOING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PrecTakeoffStatus_<ContainerAllocator>::PREC_TAKEOFF_STATE_DONE;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__PREC_TAKEOFF_STATUS__STRUCT_HPP_
