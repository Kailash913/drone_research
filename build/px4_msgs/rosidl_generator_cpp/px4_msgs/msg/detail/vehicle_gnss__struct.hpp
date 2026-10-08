// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/VehicleGnss.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/vehicle_gnss.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'receiver'
#include "px4_msgs/msg/detail/sensor_gnss__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__VehicleGnss __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__VehicleGnss __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VehicleGnss_
{
  using Type = VehicleGnss_<ContainerAllocator>;

  explicit VehicleGnss_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : receiver(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->timestamp_sample = 0ull;
      std::fill<typename std::array<float, 3>::iterator, float>(this->antenna_offset.begin(), this->antenna_offset.end(), 0.0f);
      this->selected_instance = 0;
      this->selection_count = 0;
      this->usable = false;
      this->failed_checks = 0;
    }
  }

  explicit VehicleGnss_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : receiver(_alloc, _init),
    antenna_offset(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->timestamp_sample = 0ull;
      std::fill<typename std::array<float, 3>::iterator, float>(this->antenna_offset.begin(), this->antenna_offset.end(), 0.0f);
      this->selected_instance = 0;
      this->selection_count = 0;
      this->usable = false;
      this->failed_checks = 0;
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _timestamp_sample_type =
    uint64_t;
  _timestamp_sample_type timestamp_sample;
  using _receiver_type =
    px4_msgs::msg::SensorGnss_<ContainerAllocator>;
  _receiver_type receiver;
  using _antenna_offset_type =
    std::array<float, 3>;
  _antenna_offset_type antenna_offset;
  using _selected_instance_type =
    uint8_t;
  _selected_instance_type selected_instance;
  using _selection_count_type =
    uint8_t;
  _selection_count_type selection_count;
  using _usable_type =
    bool;
  _usable_type usable;
  using _failed_checks_type =
    uint16_t;
  _failed_checks_type failed_checks;

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
  Type & set__receiver(
    const px4_msgs::msg::SensorGnss_<ContainerAllocator> & _arg)
  {
    this->receiver = _arg;
    return *this;
  }
  Type & set__antenna_offset(
    const std::array<float, 3> & _arg)
  {
    this->antenna_offset = _arg;
    return *this;
  }
  Type & set__selected_instance(
    const uint8_t & _arg)
  {
    this->selected_instance = _arg;
    return *this;
  }
  Type & set__selection_count(
    const uint8_t & _arg)
  {
    this->selection_count = _arg;
    return *this;
  }
  Type & set__usable(
    const bool & _arg)
  {
    this->usable = _arg;
    return *this;
  }
  Type & set__failed_checks(
    const uint16_t & _arg)
  {
    this->failed_checks = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t CHECK_NSATS =
    1u;
  static constexpr uint16_t CHECK_PDOP =
    2u;
  static constexpr uint16_t CHECK_EPH =
    4u;
  static constexpr uint16_t CHECK_EPV =
    8u;
  static constexpr uint16_t CHECK_SACC =
    16u;
  static constexpr uint16_t CHECK_HDRIFT =
    32u;
  static constexpr uint16_t CHECK_VDRIFT =
    64u;
  static constexpr uint16_t CHECK_HSPEED =
    128u;
  static constexpr uint16_t CHECK_VSPEED =
    256u;
  static constexpr uint16_t CHECK_SPOOFED =
    512u;
  static constexpr uint16_t CHECK_FIX =
    1024u;
  static constexpr uint16_t CHECK_JAMMED =
    2048u;

  // pointer types
  using RawPtr =
    px4_msgs::msg::VehicleGnss_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::VehicleGnss_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::VehicleGnss_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::VehicleGnss_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::VehicleGnss_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::VehicleGnss_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::VehicleGnss_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::VehicleGnss_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::VehicleGnss_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::VehicleGnss_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__VehicleGnss
    std::shared_ptr<px4_msgs::msg::VehicleGnss_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__VehicleGnss
    std::shared_ptr<px4_msgs::msg::VehicleGnss_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VehicleGnss_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->timestamp_sample != other.timestamp_sample) {
      return false;
    }
    if (this->receiver != other.receiver) {
      return false;
    }
    if (this->antenna_offset != other.antenna_offset) {
      return false;
    }
    if (this->selected_instance != other.selected_instance) {
      return false;
    }
    if (this->selection_count != other.selection_count) {
      return false;
    }
    if (this->usable != other.usable) {
      return false;
    }
    if (this->failed_checks != other.failed_checks) {
      return false;
    }
    return true;
  }
  bool operator!=(const VehicleGnss_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VehicleGnss_

// alias to use template instance with default allocator
using VehicleGnss =
  px4_msgs::msg::VehicleGnss_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VehicleGnss_<ContainerAllocator>::CHECK_NSATS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VehicleGnss_<ContainerAllocator>::CHECK_PDOP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VehicleGnss_<ContainerAllocator>::CHECK_EPH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VehicleGnss_<ContainerAllocator>::CHECK_EPV;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VehicleGnss_<ContainerAllocator>::CHECK_SACC;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VehicleGnss_<ContainerAllocator>::CHECK_HDRIFT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VehicleGnss_<ContainerAllocator>::CHECK_VDRIFT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VehicleGnss_<ContainerAllocator>::CHECK_HSPEED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VehicleGnss_<ContainerAllocator>::CHECK_VSPEED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VehicleGnss_<ContainerAllocator>::CHECK_SPOOFED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VehicleGnss_<ContainerAllocator>::CHECK_FIX;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t VehicleGnss_<ContainerAllocator>::CHECK_JAMMED;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_GNSS__STRUCT_HPP_
