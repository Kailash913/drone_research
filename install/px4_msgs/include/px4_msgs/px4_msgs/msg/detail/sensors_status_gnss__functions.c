// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from px4_msgs:msg/SensorsStatusGnss.idl
// generated code does not contain a copyright notice
#include "px4_msgs/msg/detail/sensors_status_gnss__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
px4_msgs__msg__SensorsStatusGnss__init(px4_msgs__msg__SensorsStatusGnss * msg)
{
  if (!msg) {
    return false;
  }
  // timestamp
  // device_id_selected
  // device_ids
  // order
  // healthy
  // failed_checks
  // strict
  // drift_rate_horizontal
  // drift_rate_vertical
  // speed_horizontal_filtered
  return true;
}

void
px4_msgs__msg__SensorsStatusGnss__fini(px4_msgs__msg__SensorsStatusGnss * msg)
{
  if (!msg) {
    return;
  }
  // timestamp
  // device_id_selected
  // device_ids
  // order
  // healthy
  // failed_checks
  // strict
  // drift_rate_horizontal
  // drift_rate_vertical
  // speed_horizontal_filtered
}

bool
px4_msgs__msg__SensorsStatusGnss__are_equal(const px4_msgs__msg__SensorsStatusGnss * lhs, const px4_msgs__msg__SensorsStatusGnss * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // timestamp
  if (lhs->timestamp != rhs->timestamp) {
    return false;
  }
  // device_id_selected
  if (lhs->device_id_selected != rhs->device_id_selected) {
    return false;
  }
  // device_ids
  for (size_t i = 0; i < 4; ++i) {
    if (lhs->device_ids[i] != rhs->device_ids[i]) {
      return false;
    }
  }
  // order
  for (size_t i = 0; i < 4; ++i) {
    if (lhs->order[i] != rhs->order[i]) {
      return false;
    }
  }
  // healthy
  for (size_t i = 0; i < 4; ++i) {
    if (lhs->healthy[i] != rhs->healthy[i]) {
      return false;
    }
  }
  // failed_checks
  for (size_t i = 0; i < 4; ++i) {
    if (lhs->failed_checks[i] != rhs->failed_checks[i]) {
      return false;
    }
  }
  // strict
  for (size_t i = 0; i < 4; ++i) {
    if (lhs->strict[i] != rhs->strict[i]) {
      return false;
    }
  }
  // drift_rate_horizontal
  for (size_t i = 0; i < 4; ++i) {
    if (lhs->drift_rate_horizontal[i] != rhs->drift_rate_horizontal[i]) {
      return false;
    }
  }
  // drift_rate_vertical
  for (size_t i = 0; i < 4; ++i) {
    if (lhs->drift_rate_vertical[i] != rhs->drift_rate_vertical[i]) {
      return false;
    }
  }
  // speed_horizontal_filtered
  for (size_t i = 0; i < 4; ++i) {
    if (lhs->speed_horizontal_filtered[i] != rhs->speed_horizontal_filtered[i]) {
      return false;
    }
  }
  return true;
}

bool
px4_msgs__msg__SensorsStatusGnss__copy(
  const px4_msgs__msg__SensorsStatusGnss * input,
  px4_msgs__msg__SensorsStatusGnss * output)
{
  if (!input || !output) {
    return false;
  }
  // timestamp
  output->timestamp = input->timestamp;
  // device_id_selected
  output->device_id_selected = input->device_id_selected;
  // device_ids
  for (size_t i = 0; i < 4; ++i) {
    output->device_ids[i] = input->device_ids[i];
  }
  // order
  for (size_t i = 0; i < 4; ++i) {
    output->order[i] = input->order[i];
  }
  // healthy
  for (size_t i = 0; i < 4; ++i) {
    output->healthy[i] = input->healthy[i];
  }
  // failed_checks
  for (size_t i = 0; i < 4; ++i) {
    output->failed_checks[i] = input->failed_checks[i];
  }
  // strict
  for (size_t i = 0; i < 4; ++i) {
    output->strict[i] = input->strict[i];
  }
  // drift_rate_horizontal
  for (size_t i = 0; i < 4; ++i) {
    output->drift_rate_horizontal[i] = input->drift_rate_horizontal[i];
  }
  // drift_rate_vertical
  for (size_t i = 0; i < 4; ++i) {
    output->drift_rate_vertical[i] = input->drift_rate_vertical[i];
  }
  // speed_horizontal_filtered
  for (size_t i = 0; i < 4; ++i) {
    output->speed_horizontal_filtered[i] = input->speed_horizontal_filtered[i];
  }
  return true;
}

px4_msgs__msg__SensorsStatusGnss *
px4_msgs__msg__SensorsStatusGnss__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__SensorsStatusGnss * msg = (px4_msgs__msg__SensorsStatusGnss *)allocator.allocate(sizeof(px4_msgs__msg__SensorsStatusGnss), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(px4_msgs__msg__SensorsStatusGnss));
  bool success = px4_msgs__msg__SensorsStatusGnss__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
px4_msgs__msg__SensorsStatusGnss__destroy(px4_msgs__msg__SensorsStatusGnss * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    px4_msgs__msg__SensorsStatusGnss__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
px4_msgs__msg__SensorsStatusGnss__Sequence__init(px4_msgs__msg__SensorsStatusGnss__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__SensorsStatusGnss * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(px4_msgs__msg__SensorsStatusGnss)) {
      return false;
    }
    data = (px4_msgs__msg__SensorsStatusGnss *)allocator.zero_allocate(size, sizeof(px4_msgs__msg__SensorsStatusGnss), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = px4_msgs__msg__SensorsStatusGnss__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        px4_msgs__msg__SensorsStatusGnss__fini(&data[i - 1]);
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
px4_msgs__msg__SensorsStatusGnss__Sequence__fini(px4_msgs__msg__SensorsStatusGnss__Sequence * array)
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
      px4_msgs__msg__SensorsStatusGnss__fini(&array->data[i]);
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

px4_msgs__msg__SensorsStatusGnss__Sequence *
px4_msgs__msg__SensorsStatusGnss__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__SensorsStatusGnss__Sequence * array = (px4_msgs__msg__SensorsStatusGnss__Sequence *)allocator.allocate(sizeof(px4_msgs__msg__SensorsStatusGnss__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = px4_msgs__msg__SensorsStatusGnss__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
px4_msgs__msg__SensorsStatusGnss__Sequence__destroy(px4_msgs__msg__SensorsStatusGnss__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    px4_msgs__msg__SensorsStatusGnss__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
px4_msgs__msg__SensorsStatusGnss__Sequence__are_equal(const px4_msgs__msg__SensorsStatusGnss__Sequence * lhs, const px4_msgs__msg__SensorsStatusGnss__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!px4_msgs__msg__SensorsStatusGnss__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
px4_msgs__msg__SensorsStatusGnss__Sequence__copy(
  const px4_msgs__msg__SensorsStatusGnss__Sequence * input,
  px4_msgs__msg__SensorsStatusGnss__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(px4_msgs__msg__SensorsStatusGnss)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(px4_msgs__msg__SensorsStatusGnss);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    px4_msgs__msg__SensorsStatusGnss * data =
      (px4_msgs__msg__SensorsStatusGnss *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!px4_msgs__msg__SensorsStatusGnss__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          px4_msgs__msg__SensorsStatusGnss__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!px4_msgs__msg__SensorsStatusGnss__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
