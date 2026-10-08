// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/UavcanFirmwareUpdate.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/uavcan_firmware_update.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__UAVCAN_FIRMWARE_UPDATE__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__UAVCAN_FIRMWARE_UPDATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__UavcanFirmwareUpdate __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__UavcanFirmwareUpdate __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct UavcanFirmwareUpdate_
{
  using Type = UavcanFirmwareUpdate_<ContainerAllocator>;

  explicit UavcanFirmwareUpdate_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->pending_updates = false;
    }
  }

  explicit UavcanFirmwareUpdate_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->pending_updates = false;
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _pending_updates_type =
    bool;
  _pending_updates_type pending_updates;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__pending_updates(
    const bool & _arg)
  {
    this->pending_updates = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    px4_msgs::msg::UavcanFirmwareUpdate_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::UavcanFirmwareUpdate_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::UavcanFirmwareUpdate_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::UavcanFirmwareUpdate_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::UavcanFirmwareUpdate_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::UavcanFirmwareUpdate_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::UavcanFirmwareUpdate_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::UavcanFirmwareUpdate_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::UavcanFirmwareUpdate_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::UavcanFirmwareUpdate_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__UavcanFirmwareUpdate
    std::shared_ptr<px4_msgs::msg::UavcanFirmwareUpdate_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__UavcanFirmwareUpdate
    std::shared_ptr<px4_msgs::msg::UavcanFirmwareUpdate_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const UavcanFirmwareUpdate_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->pending_updates != other.pending_updates) {
      return false;
    }
    return true;
  }
  bool operator!=(const UavcanFirmwareUpdate_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct UavcanFirmwareUpdate_

// alias to use template instance with default allocator
using UavcanFirmwareUpdate =
  px4_msgs::msg::UavcanFirmwareUpdate_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__UAVCAN_FIRMWARE_UPDATE__STRUCT_HPP_
