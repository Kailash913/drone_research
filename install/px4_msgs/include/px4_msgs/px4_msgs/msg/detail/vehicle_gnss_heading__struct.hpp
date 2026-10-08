// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/VehicleGnssHeading.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/vehicle_gnss_heading.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS_HEADING__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS_HEADING__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__VehicleGnssHeading __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__VehicleGnssHeading __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VehicleGnssHeading_
{
  using Type = VehicleGnssHeading_<ContainerAllocator>;

  explicit VehicleGnssHeading_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->timestamp_sample = 0ull;
      this->device_id = 0ul;
      this->heading = 0.0f;
      this->heading_accuracy = 0.0f;
      this->heading_offset = 0.0f;
      this->baseline_length = 0.0f;
      this->jamming_state = 0;
      this->spoofing_state = 0;
      this->usable = false;
    }
  }

  explicit VehicleGnssHeading_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->timestamp_sample = 0ull;
      this->device_id = 0ul;
      this->heading = 0.0f;
      this->heading_accuracy = 0.0f;
      this->heading_offset = 0.0f;
      this->baseline_length = 0.0f;
      this->jamming_state = 0;
      this->spoofing_state = 0;
      this->usable = false;
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _timestamp_sample_type =
    uint64_t;
  _timestamp_sample_type timestamp_sample;
  using _device_id_type =
    uint32_t;
  _device_id_type device_id;
  using _heading_type =
    float;
  _heading_type heading;
  using _heading_accuracy_type =
    float;
  _heading_accuracy_type heading_accuracy;
  using _heading_offset_type =
    float;
  _heading_offset_type heading_offset;
  using _baseline_length_type =
    float;
  _baseline_length_type baseline_length;
  using _jamming_state_type =
    uint8_t;
  _jamming_state_type jamming_state;
  using _spoofing_state_type =
    uint8_t;
  _spoofing_state_type spoofing_state;
  using _usable_type =
    bool;
  _usable_type usable;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__timestamp_sample(
    const uint64_t & _arg)
  {
    this->timestamp_sample = _arg;
    return *this;
  }
  Type & set__device_id(
    const uint32_t & _arg)
  {
    this->device_id = _arg;
    return *this;
  }
  Type & set__heading(
    const float & _arg)
  {
    this->heading = _arg;
    return *this;
  }
  Type & set__heading_accuracy(
    const float & _arg)
  {
    this->heading_accuracy = _arg;
    return *this;
  }
  Type & set__heading_offset(
    const float & _arg)
  {
    this->heading_offset = _arg;
    return *this;
  }
  Type & set__baseline_length(
    const float & _arg)
  {
    this->baseline_length = _arg;
    return *this;
  }
  Type & set__jamming_state(
    const uint8_t & _arg)
  {
    this->jamming_state = _arg;
    return *this;
  }
  Type & set__spoofing_state(
    const uint8_t & _arg)
  {
    this->spoofing_state = _arg;
    return *this;
  }
  Type & set__usable(
    const bool & _arg)
  {
    this->usable = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    px4_msgs::msg::VehicleGnssHeading_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::VehicleGnssHeading_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::VehicleGnssHeading_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::VehicleGnssHeading_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::VehicleGnssHeading_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::VehicleGnssHeading_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::VehicleGnssHeading_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::VehicleGnssHeading_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::VehicleGnssHeading_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::VehicleGnssHeading_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__VehicleGnssHeading
    std::shared_ptr<px4_msgs::msg::VehicleGnssHeading_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__VehicleGnssHeading
    std::shared_ptr<px4_msgs::msg::VehicleGnssHeading_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VehicleGnssHeading_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->timestamp_sample != other.timestamp_sample) {
      return false;
    }
    if (this->device_id != other.device_id) {
      return false;
    }
    if (this->heading != other.heading) {
      return false;
    }
    if (this->heading_accuracy != other.heading_accuracy) {
      return false;
    }
    if (this->heading_offset != other.heading_offset) {
      return false;
    }
    if (this->baseline_length != other.baseline_length) {
      return false;
    }
    if (this->jamming_state != other.jamming_state) {
      return false;
    }
    if (this->spoofing_state != other.spoofing_state) {
      return false;
    }
    if (this->usable != other.usable) {
      return false;
    }
    return true;
  }
  bool operator!=(const VehicleGnssHeading_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VehicleGnssHeading_

// alias to use template instance with default allocator
using VehicleGnssHeading =
  px4_msgs::msg::VehicleGnssHeading_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS_HEADING__STRUCT_HPP_
