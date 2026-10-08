// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/SensorsStatusGnss.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "px4_msgs/msg/sensors_status_gnss.hpp"


#ifndef PX4_MSGS__MSG__DETAIL__SENSORS_STATUS_GNSS__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__SENSORS_STATUS_GNSS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__SensorsStatusGnss __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__SensorsStatusGnss __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SensorsStatusGnss_
{
  using Type = SensorsStatusGnss_<ContainerAllocator>;

  explicit SensorsStatusGnss_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->device_id_selected = 0ul;
      std::fill<typename std::array<uint32_t, 4>::iterator, uint32_t>(this->device_ids.begin(), this->device_ids.end(), 0ul);
      std::fill<typename std::array<int8_t, 4>::iterator, int8_t>(this->order.begin(), this->order.end(), 0);
      std::fill<typename std::array<bool, 4>::iterator, bool>(this->healthy.begin(), this->healthy.end(), false);
      std::fill<typename std::array<uint16_t, 4>::iterator, uint16_t>(this->failed_checks.begin(), this->failed_checks.end(), 0);
      std::fill<typename std::array<bool, 4>::iterator, bool>(this->strict.begin(), this->strict.end(), false);
      std::fill<typename std::array<float, 4>::iterator, float>(this->drift_rate_horizontal.begin(), this->drift_rate_horizontal.end(), 0.0f);
      std::fill<typename std::array<float, 4>::iterator, float>(this->drift_rate_vertical.begin(), this->drift_rate_vertical.end(), 0.0f);
      std::fill<typename std::array<float, 4>::iterator, float>(this->speed_horizontal_filtered.begin(), this->speed_horizontal_filtered.end(), 0.0f);
    }
  }

  explicit SensorsStatusGnss_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : device_ids(_alloc),
    order(_alloc),
    healthy(_alloc),
    failed_checks(_alloc),
    strict(_alloc),
    drift_rate_horizontal(_alloc),
    drift_rate_vertical(_alloc),
    speed_horizontal_filtered(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->device_id_selected = 0ul;
      std::fill<typename std::array<uint32_t, 4>::iterator, uint32_t>(this->device_ids.begin(), this->device_ids.end(), 0ul);
      std::fill<typename std::array<int8_t, 4>::iterator, int8_t>(this->order.begin(), this->order.end(), 0);
      std::fill<typename std::array<bool, 4>::iterator, bool>(this->healthy.begin(), this->healthy.end(), false);
      std::fill<typename std::array<uint16_t, 4>::iterator, uint16_t>(this->failed_checks.begin(), this->failed_checks.end(), 0);
      std::fill<typename std::array<bool, 4>::iterator, bool>(this->strict.begin(), this->strict.end(), false);
      std::fill<typename std::array<float, 4>::iterator, float>(this->drift_rate_horizontal.begin(), this->drift_rate_horizontal.end(), 0.0f);
      std::fill<typename std::array<float, 4>::iterator, float>(this->drift_rate_vertical.begin(), this->drift_rate_vertical.end(), 0.0f);
      std::fill<typename std::array<float, 4>::iterator, float>(this->speed_horizontal_filtered.begin(), this->speed_horizontal_filtered.end(), 0.0f);
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _device_id_selected_type =
    uint32_t;
  _device_id_selected_type device_id_selected;
  using _device_ids_type =
    std::array<uint32_t, 4>;
  _device_ids_type device_ids;
  using _order_type =
    std::array<int8_t, 4>;
  _order_type order;
  using _healthy_type =
    std::array<bool, 4>;
  _healthy_type healthy;
  using _failed_checks_type =
    std::array<uint16_t, 4>;
  _failed_checks_type failed_checks;
  using _strict_type =
    std::array<bool, 4>;
  _strict_type strict;
  using _drift_rate_horizontal_type =
    std::array<float, 4>;
  _drift_rate_horizontal_type drift_rate_horizontal;
  using _drift_rate_vertical_type =
    std::array<float, 4>;
  _drift_rate_vertical_type drift_rate_vertical;
  using _speed_horizontal_filtered_type =
    std::array<float, 4>;
  _speed_horizontal_filtered_type speed_horizontal_filtered;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__device_id_selected(
    const uint32_t & _arg)
  {
    this->device_id_selected = _arg;
    return *this;
  }
  Type & set__device_ids(
    const std::array<uint32_t, 4> & _arg)
  {
    this->device_ids = _arg;
    return *this;
  }
  Type & set__order(
    const std::array<int8_t, 4> & _arg)
  {
    this->order = _arg;
    return *this;
  }
  Type & set__healthy(
    const std::array<bool, 4> & _arg)
  {
    this->healthy = _arg;
    return *this;
  }
  Type & set__failed_checks(
    const std::array<uint16_t, 4> & _arg)
  {
    this->failed_checks = _arg;
    return *this;
  }
  Type & set__strict(
    const std::array<bool, 4> & _arg)
  {
    this->strict = _arg;
    return *this;
  }
  Type & set__drift_rate_horizontal(
    const std::array<float, 4> & _arg)
  {
    this->drift_rate_horizontal = _arg;
    return *this;
  }
  Type & set__drift_rate_vertical(
    const std::array<float, 4> & _arg)
  {
    this->drift_rate_vertical = _arg;
    return *this;
  }
  Type & set__speed_horizontal_filtered(
    const std::array<float, 4> & _arg)
  {
    this->speed_horizontal_filtered = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t MAX_RECEIVERS =
    4u;

  // pointer types
  using RawPtr =
    px4_msgs::msg::SensorsStatusGnss_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::SensorsStatusGnss_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::SensorsStatusGnss_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::SensorsStatusGnss_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::SensorsStatusGnss_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::SensorsStatusGnss_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::SensorsStatusGnss_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::SensorsStatusGnss_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::SensorsStatusGnss_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::SensorsStatusGnss_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__SensorsStatusGnss
    std::shared_ptr<px4_msgs::msg::SensorsStatusGnss_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__SensorsStatusGnss
    std::shared_ptr<px4_msgs::msg::SensorsStatusGnss_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SensorsStatusGnss_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->device_id_selected != other.device_id_selected) {
      return false;
    }
    if (this->device_ids != other.device_ids) {
      return false;
    }
    if (this->order != other.order) {
      return false;
    }
    if (this->healthy != other.healthy) {
      return false;
    }
    if (this->failed_checks != other.failed_checks) {
      return false;
    }
    if (this->strict != other.strict) {
      return false;
    }
    if (this->drift_rate_horizontal != other.drift_rate_horizontal) {
      return false;
    }
    if (this->drift_rate_vertical != other.drift_rate_vertical) {
      return false;
    }
    if (this->speed_horizontal_filtered != other.speed_horizontal_filtered) {
      return false;
    }
    return true;
  }
  bool operator!=(const SensorsStatusGnss_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SensorsStatusGnss_

// alias to use template instance with default allocator
using SensorsStatusGnss =
  px4_msgs::msg::SensorsStatusGnss_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SensorsStatusGnss_<ContainerAllocator>::MAX_RECEIVERS;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__SENSORS_STATUS_GNSS__STRUCT_HPP_
