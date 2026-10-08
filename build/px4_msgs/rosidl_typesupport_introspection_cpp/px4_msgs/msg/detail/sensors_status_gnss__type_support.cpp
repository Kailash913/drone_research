// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from px4_msgs:msg/SensorsStatusGnss.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "px4_msgs/msg/detail/sensors_status_gnss__functions.h"
#include "px4_msgs/msg/detail/sensors_status_gnss__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace px4_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void SensorsStatusGnss_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) px4_msgs::msg::SensorsStatusGnss(_init);
}

void SensorsStatusGnss_fini_function(void * message_memory)
{
  auto typed_message = static_cast<px4_msgs::msg::SensorsStatusGnss *>(message_memory);
  typed_message->~SensorsStatusGnss();
}

size_t size_function__SensorsStatusGnss__device_ids(const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * get_const_function__SensorsStatusGnss__device_ids(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<uint32_t, 4> *>(untyped_member);
  return &member[index];
}

void * get_function__SensorsStatusGnss__device_ids(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<uint32_t, 4> *>(untyped_member);
  return &member[index];
}

void fetch_function__SensorsStatusGnss__device_ids(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint32_t *>(
    get_const_function__SensorsStatusGnss__device_ids(untyped_member, index));
  auto & value = *reinterpret_cast<uint32_t *>(untyped_value);
  value = item;
}

void assign_function__SensorsStatusGnss__device_ids(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint32_t *>(
    get_function__SensorsStatusGnss__device_ids(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint32_t *>(untyped_value);
  item = value;
}

size_t size_function__SensorsStatusGnss__order(const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * get_const_function__SensorsStatusGnss__order(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int8_t, 4> *>(untyped_member);
  return &member[index];
}

void * get_function__SensorsStatusGnss__order(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int8_t, 4> *>(untyped_member);
  return &member[index];
}

void fetch_function__SensorsStatusGnss__order(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const int8_t *>(
    get_const_function__SensorsStatusGnss__order(untyped_member, index));
  auto & value = *reinterpret_cast<int8_t *>(untyped_value);
  value = item;
}

void assign_function__SensorsStatusGnss__order(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<int8_t *>(
    get_function__SensorsStatusGnss__order(untyped_member, index));
  const auto & value = *reinterpret_cast<const int8_t *>(untyped_value);
  item = value;
}

size_t size_function__SensorsStatusGnss__healthy(const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * get_const_function__SensorsStatusGnss__healthy(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<bool, 4> *>(untyped_member);
  return &member[index];
}

void * get_function__SensorsStatusGnss__healthy(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<bool, 4> *>(untyped_member);
  return &member[index];
}

void fetch_function__SensorsStatusGnss__healthy(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const bool *>(
    get_const_function__SensorsStatusGnss__healthy(untyped_member, index));
  auto & value = *reinterpret_cast<bool *>(untyped_value);
  value = item;
}

void assign_function__SensorsStatusGnss__healthy(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<bool *>(
    get_function__SensorsStatusGnss__healthy(untyped_member, index));
  const auto & value = *reinterpret_cast<const bool *>(untyped_value);
  item = value;
}

size_t size_function__SensorsStatusGnss__failed_checks(const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * get_const_function__SensorsStatusGnss__failed_checks(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<uint16_t, 4> *>(untyped_member);
  return &member[index];
}

void * get_function__SensorsStatusGnss__failed_checks(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<uint16_t, 4> *>(untyped_member);
  return &member[index];
}

void fetch_function__SensorsStatusGnss__failed_checks(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint16_t *>(
    get_const_function__SensorsStatusGnss__failed_checks(untyped_member, index));
  auto & value = *reinterpret_cast<uint16_t *>(untyped_value);
  value = item;
}

void assign_function__SensorsStatusGnss__failed_checks(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint16_t *>(
    get_function__SensorsStatusGnss__failed_checks(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint16_t *>(untyped_value);
  item = value;
}

size_t size_function__SensorsStatusGnss__strict(const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * get_const_function__SensorsStatusGnss__strict(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<bool, 4> *>(untyped_member);
  return &member[index];
}

void * get_function__SensorsStatusGnss__strict(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<bool, 4> *>(untyped_member);
  return &member[index];
}

void fetch_function__SensorsStatusGnss__strict(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const bool *>(
    get_const_function__SensorsStatusGnss__strict(untyped_member, index));
  auto & value = *reinterpret_cast<bool *>(untyped_value);
  value = item;
}

void assign_function__SensorsStatusGnss__strict(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<bool *>(
    get_function__SensorsStatusGnss__strict(untyped_member, index));
  const auto & value = *reinterpret_cast<const bool *>(untyped_value);
  item = value;
}

size_t size_function__SensorsStatusGnss__drift_rate_horizontal(const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * get_const_function__SensorsStatusGnss__drift_rate_horizontal(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 4> *>(untyped_member);
  return &member[index];
}

void * get_function__SensorsStatusGnss__drift_rate_horizontal(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 4> *>(untyped_member);
  return &member[index];
}

void fetch_function__SensorsStatusGnss__drift_rate_horizontal(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__SensorsStatusGnss__drift_rate_horizontal(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__SensorsStatusGnss__drift_rate_horizontal(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__SensorsStatusGnss__drift_rate_horizontal(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

size_t size_function__SensorsStatusGnss__drift_rate_vertical(const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * get_const_function__SensorsStatusGnss__drift_rate_vertical(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 4> *>(untyped_member);
  return &member[index];
}

void * get_function__SensorsStatusGnss__drift_rate_vertical(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 4> *>(untyped_member);
  return &member[index];
}

void fetch_function__SensorsStatusGnss__drift_rate_vertical(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__SensorsStatusGnss__drift_rate_vertical(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__SensorsStatusGnss__drift_rate_vertical(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__SensorsStatusGnss__drift_rate_vertical(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

size_t size_function__SensorsStatusGnss__speed_horizontal_filtered(const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * get_const_function__SensorsStatusGnss__speed_horizontal_filtered(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 4> *>(untyped_member);
  return &member[index];
}

void * get_function__SensorsStatusGnss__speed_horizontal_filtered(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 4> *>(untyped_member);
  return &member[index];
}

void fetch_function__SensorsStatusGnss__speed_horizontal_filtered(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__SensorsStatusGnss__speed_horizontal_filtered(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__SensorsStatusGnss__speed_horizontal_filtered(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__SensorsStatusGnss__speed_horizontal_filtered(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember SensorsStatusGnss_message_member_array[10] = {
  {
    "timestamp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::SensorsStatusGnss, timestamp),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "device_id_selected",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::SensorsStatusGnss, device_id_selected),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "device_ids",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::SensorsStatusGnss, device_ids),  // bytes offset in struct
    nullptr,  // default value
    size_function__SensorsStatusGnss__device_ids,  // size() function pointer
    get_const_function__SensorsStatusGnss__device_ids,  // get_const(index) function pointer
    get_function__SensorsStatusGnss__device_ids,  // get(index) function pointer
    fetch_function__SensorsStatusGnss__device_ids,  // fetch(index, &value) function pointer
    assign_function__SensorsStatusGnss__device_ids,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "order",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::SensorsStatusGnss, order),  // bytes offset in struct
    nullptr,  // default value
    size_function__SensorsStatusGnss__order,  // size() function pointer
    get_const_function__SensorsStatusGnss__order,  // get_const(index) function pointer
    get_function__SensorsStatusGnss__order,  // get(index) function pointer
    fetch_function__SensorsStatusGnss__order,  // fetch(index, &value) function pointer
    assign_function__SensorsStatusGnss__order,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "healthy",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::SensorsStatusGnss, healthy),  // bytes offset in struct
    nullptr,  // default value
    size_function__SensorsStatusGnss__healthy,  // size() function pointer
    get_const_function__SensorsStatusGnss__healthy,  // get_const(index) function pointer
    get_function__SensorsStatusGnss__healthy,  // get(index) function pointer
    fetch_function__SensorsStatusGnss__healthy,  // fetch(index, &value) function pointer
    assign_function__SensorsStatusGnss__healthy,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "failed_checks",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::SensorsStatusGnss, failed_checks),  // bytes offset in struct
    nullptr,  // default value
    size_function__SensorsStatusGnss__failed_checks,  // size() function pointer
    get_const_function__SensorsStatusGnss__failed_checks,  // get_const(index) function pointer
    get_function__SensorsStatusGnss__failed_checks,  // get(index) function pointer
    fetch_function__SensorsStatusGnss__failed_checks,  // fetch(index, &value) function pointer
    assign_function__SensorsStatusGnss__failed_checks,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "strict",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::SensorsStatusGnss, strict),  // bytes offset in struct
    nullptr,  // default value
    size_function__SensorsStatusGnss__strict,  // size() function pointer
    get_const_function__SensorsStatusGnss__strict,  // get_const(index) function pointer
    get_function__SensorsStatusGnss__strict,  // get(index) function pointer
    fetch_function__SensorsStatusGnss__strict,  // fetch(index, &value) function pointer
    assign_function__SensorsStatusGnss__strict,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "drift_rate_horizontal",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::SensorsStatusGnss, drift_rate_horizontal),  // bytes offset in struct
    nullptr,  // default value
    size_function__SensorsStatusGnss__drift_rate_horizontal,  // size() function pointer
    get_const_function__SensorsStatusGnss__drift_rate_horizontal,  // get_const(index) function pointer
    get_function__SensorsStatusGnss__drift_rate_horizontal,  // get(index) function pointer
    fetch_function__SensorsStatusGnss__drift_rate_horizontal,  // fetch(index, &value) function pointer
    assign_function__SensorsStatusGnss__drift_rate_horizontal,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "drift_rate_vertical",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::SensorsStatusGnss, drift_rate_vertical),  // bytes offset in struct
    nullptr,  // default value
    size_function__SensorsStatusGnss__drift_rate_vertical,  // size() function pointer
    get_const_function__SensorsStatusGnss__drift_rate_vertical,  // get_const(index) function pointer
    get_function__SensorsStatusGnss__drift_rate_vertical,  // get(index) function pointer
    fetch_function__SensorsStatusGnss__drift_rate_vertical,  // fetch(index, &value) function pointer
    assign_function__SensorsStatusGnss__drift_rate_vertical,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "speed_horizontal_filtered",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::SensorsStatusGnss, speed_horizontal_filtered),  // bytes offset in struct
    nullptr,  // default value
    size_function__SensorsStatusGnss__speed_horizontal_filtered,  // size() function pointer
    get_const_function__SensorsStatusGnss__speed_horizontal_filtered,  // get_const(index) function pointer
    get_function__SensorsStatusGnss__speed_horizontal_filtered,  // get(index) function pointer
    fetch_function__SensorsStatusGnss__speed_horizontal_filtered,  // fetch(index, &value) function pointer
    assign_function__SensorsStatusGnss__speed_horizontal_filtered,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers SensorsStatusGnss_message_members = {
  "px4_msgs::msg",  // message namespace
  "SensorsStatusGnss",  // message name
  10,  // number of fields
  sizeof(px4_msgs::msg::SensorsStatusGnss),
  false,  // has_any_key_member_
  SensorsStatusGnss_message_member_array,  // message members
  SensorsStatusGnss_init_function,  // function to initialize message memory (memory has to be allocated)
  SensorsStatusGnss_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t SensorsStatusGnss_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &SensorsStatusGnss_message_members,
  get_message_typesupport_handle_function,
  &px4_msgs__msg__SensorsStatusGnss__get_type_hash,
  &px4_msgs__msg__SensorsStatusGnss__get_type_description,
  &px4_msgs__msg__SensorsStatusGnss__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace px4_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<px4_msgs::msg::SensorsStatusGnss>()
{
  return &::px4_msgs::msg::rosidl_typesupport_introspection_cpp::SensorsStatusGnss_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, px4_msgs, msg, SensorsStatusGnss)() {
  return &::px4_msgs::msg::rosidl_typesupport_introspection_cpp::SensorsStatusGnss_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
