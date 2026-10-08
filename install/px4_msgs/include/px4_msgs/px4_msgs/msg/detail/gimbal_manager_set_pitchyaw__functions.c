// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from px4_msgs:msg/GimbalManagerSetPitchyaw.idl
// generated code does not contain a copyright notice
#include "px4_msgs/msg/detail/gimbal_manager_set_pitchyaw__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
px4_msgs__msg__GimbalManagerSetPitchyaw__init(px4_msgs__msg__GimbalManagerSetPitchyaw * msg)
{
  if (!msg) {
    return false;
  }
  // timestamp
  // target_system
  // target_component
  // gimbal_device_id
  // flags
  // pitch
  // yaw
  // pitch_rate
  // yaw_rate
  return true;
}

void
px4_msgs__msg__GimbalManagerSetPitchyaw__fini(px4_msgs__msg__GimbalManagerSetPitchyaw * msg)
{
  if (!msg) {
    return;
  }
  // timestamp
  // target_system
  // target_component
  // gimbal_device_id
  // flags
  // pitch
  // yaw
  // pitch_rate
  // yaw_rate
}

bool
px4_msgs__msg__GimbalManagerSetPitchyaw__are_equal(const px4_msgs__msg__GimbalManagerSetPitchyaw * lhs, const px4_msgs__msg__GimbalManagerSetPitchyaw * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // timestamp
  if (lhs->timestamp != rhs->timestamp) {
    return false;
  }
  // target_system
  if (lhs->target_system != rhs->target_system) {
    return false;
  }
  // target_component
  if (lhs->target_component != rhs->target_component) {
    return false;
  }
  // gimbal_device_id
  if (lhs->gimbal_device_id != rhs->gimbal_device_id) {
    return false;
  }
  // flags
  if (lhs->flags != rhs->flags) {
    return false;
  }
  // pitch
  if (lhs->pitch != rhs->pitch) {
    return false;
  }
  // yaw
  if (lhs->yaw != rhs->yaw) {
    return false;
  }
  // pitch_rate
  if (lhs->pitch_rate != rhs->pitch_rate) {
    return false;
  }
  // yaw_rate
  if (lhs->yaw_rate != rhs->yaw_rate) {
    return false;
  }
  return true;
}

bool
px4_msgs__msg__GimbalManagerSetPitchyaw__copy(
  const px4_msgs__msg__GimbalManagerSetPitchyaw * input,
  px4_msgs__msg__GimbalManagerSetPitchyaw * output)
{
  if (!input || !output) {
    return false;
  }
  // timestamp
  output->timestamp = input->timestamp;
  // target_system
  output->target_system = input->target_system;
  // target_component
  output->target_component = input->target_component;
  // gimbal_device_id
  output->gimbal_device_id = input->gimbal_device_id;
  // flags
  output->flags = input->flags;
  // pitch
  output->pitch = input->pitch;
  // yaw
  output->yaw = input->yaw;
  // pitch_rate
  output->pitch_rate = input->pitch_rate;
  // yaw_rate
  output->yaw_rate = input->yaw_rate;
  return true;
}

px4_msgs__msg__GimbalManagerSetPitchyaw *
px4_msgs__msg__GimbalManagerSetPitchyaw__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__GimbalManagerSetPitchyaw * msg = (px4_msgs__msg__GimbalManagerSetPitchyaw *)allocator.allocate(sizeof(px4_msgs__msg__GimbalManagerSetPitchyaw), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(px4_msgs__msg__GimbalManagerSetPitchyaw));
  bool success = px4_msgs__msg__GimbalManagerSetPitchyaw__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
px4_msgs__msg__GimbalManagerSetPitchyaw__destroy(px4_msgs__msg__GimbalManagerSetPitchyaw * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    px4_msgs__msg__GimbalManagerSetPitchyaw__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence__init(px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__GimbalManagerSetPitchyaw * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(px4_msgs__msg__GimbalManagerSetPitchyaw)) {
      return false;
    }
    data = (px4_msgs__msg__GimbalManagerSetPitchyaw *)allocator.zero_allocate(size, sizeof(px4_msgs__msg__GimbalManagerSetPitchyaw), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = px4_msgs__msg__GimbalManagerSetPitchyaw__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        px4_msgs__msg__GimbalManagerSetPitchyaw__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence__fini(px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      px4_msgs__msg__GimbalManagerSetPitchyaw__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence *
px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence * array = (px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence *)allocator.allocate(sizeof(px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence__destroy(px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence__are_equal(const px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence * lhs, const px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!px4_msgs__msg__GimbalManagerSetPitchyaw__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence__copy(
  const px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence * input,
  px4_msgs__msg__GimbalManagerSetPitchyaw__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(px4_msgs__msg__GimbalManagerSetPitchyaw)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(px4_msgs__msg__GimbalManagerSetPitchyaw);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    px4_msgs__msg__GimbalManagerSetPitchyaw * data =
      (px4_msgs__msg__GimbalManagerSetPitchyaw *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!px4_msgs__msg__GimbalManagerSetPitchyaw__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          px4_msgs__msg__GimbalManagerSetPitchyaw__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!px4_msgs__msg__GimbalManagerSetPitchyaw__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
