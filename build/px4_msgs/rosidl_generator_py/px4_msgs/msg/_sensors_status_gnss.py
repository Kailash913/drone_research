# generated from rosidl_generator_py/resource/_idl.py.em
# with input from px4_msgs:msg/SensorsStatusGnss.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

# Member 'device_ids'
# Member 'order'
# Member 'failed_checks'
# Member 'drift_rate_horizontal'
# Member 'drift_rate_vertical'
# Member 'speed_horizontal_filtered'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SensorsStatusGnss(type):
    """Metaclass of message 'SensorsStatusGnss'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'MAX_RECEIVERS': 4,
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('px4_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'px4_msgs.msg.SensorsStatusGnss')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__sensors_status_gnss
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__sensors_status_gnss
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__sensors_status_gnss
            cls._TYPE_SUPPORT = module.type_support_msg__msg__sensors_status_gnss
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__sensors_status_gnss

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'MAX_RECEIVERS': cls.__constants['MAX_RECEIVERS'],
        }

    @property
    def MAX_RECEIVERS(self):
        """Message constant 'MAX_RECEIVERS'."""
        return Metaclass_SensorsStatusGnss.__constants['MAX_RECEIVERS']


class SensorsStatusGnss(metaclass=Metaclass_SensorsStatusGnss):
    """
    Message class 'SensorsStatusGnss'.

    Constants:
      MAX_RECEIVERS
    """

    __slots__ = [
        '_timestamp',
        '_device_id_selected',
        '_device_ids',
        '_order',
        '_healthy',
        '_failed_checks',
        '_strict',
        '_drift_rate_horizontal',
        '_drift_rate_vertical',
        '_speed_horizontal_filtered',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'timestamp': 'uint64',
        'device_id_selected': 'uint32',
        'device_ids': 'uint32[4]',
        'order': 'int8[4]',
        'healthy': 'boolean[4]',
        'failed_checks': 'uint16[4]',
        'strict': 'boolean[4]',
        'drift_rate_horizontal': 'float[4]',
        'drift_rate_vertical': 'float[4]',
        'speed_horizontal_filtered': 'float[4]',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('uint32'), 4),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int8'), 4),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('boolean'), 4),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('uint16'), 4),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('boolean'), 4),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 4),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 4),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 4),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.timestamp = kwargs.get('timestamp', int())
        self.device_id_selected = kwargs.get('device_id_selected', int())
        if 'device_ids' not in kwargs:
            self.device_ids = numpy.zeros(4, dtype=numpy.uint32)
        else:
            self.device_ids = kwargs.get('device_ids')
        if 'order' not in kwargs:
            self.order = numpy.zeros(4, dtype=numpy.int8)
        else:
            self.order = kwargs.get('order')
        self.healthy = kwargs.get(
            'healthy',
            [bool() for x in range(4)]
        )
        if 'failed_checks' not in kwargs:
            self.failed_checks = numpy.zeros(4, dtype=numpy.uint16)
        else:
            self.failed_checks = kwargs.get('failed_checks')
        self.strict = kwargs.get(
            'strict',
            [bool() for x in range(4)]
        )
        if 'drift_rate_horizontal' not in kwargs:
            self.drift_rate_horizontal = numpy.zeros(4, dtype=numpy.float32)
        else:
            self.drift_rate_horizontal = kwargs.get('drift_rate_horizontal')
        if 'drift_rate_vertical' not in kwargs:
            self.drift_rate_vertical = numpy.zeros(4, dtype=numpy.float32)
        else:
            self.drift_rate_vertical = kwargs.get('drift_rate_vertical')
        if 'speed_horizontal_filtered' not in kwargs:
            self.speed_horizontal_filtered = numpy.zeros(4, dtype=numpy.float32)
        else:
            self.speed_horizontal_filtered = kwargs.get('speed_horizontal_filtered')

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.timestamp != other.timestamp:
            return False
        if self.device_id_selected != other.device_id_selected:
            return False
        if any(self.device_ids != other.device_ids):
            return False
        if any(self.order != other.order):
            return False
        if self.healthy != other.healthy:
            return False
        if any(self.failed_checks != other.failed_checks):
            return False
        if self.strict != other.strict:
            return False
        if any(self.drift_rate_horizontal != other.drift_rate_horizontal):
            return False
        if any(self.drift_rate_vertical != other.drift_rate_vertical):
            return False
        if any(self.speed_horizontal_filtered != other.speed_horizontal_filtered):
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def timestamp(self):
        """Message field 'timestamp'."""
        return self._timestamp

    @timestamp.setter
    def timestamp(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'timestamp' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'timestamp' field must be an unsigned integer in [0, 18446744073709551615]"
        self._timestamp = value

    @builtins.property
    def device_id_selected(self):
        """Message field 'device_id_selected'."""
        return self._device_id_selected

    @device_id_selected.setter
    def device_id_selected(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'device_id_selected' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'device_id_selected' field must be an unsigned integer in [0, 4294967295]"
        self._device_id_selected = value

    @builtins.property
    def device_ids(self):
        """Message field 'device_ids'."""
        return self._device_ids

    @device_ids.setter
    def device_ids(self, value):
        if self._check_fields:
            if isinstance(value, numpy.ndarray):
                assert value.dtype == numpy.uint32, \
                    "The 'device_ids' numpy.ndarray() must have the dtype of 'numpy.uint32'"
                assert value.size == 4, \
                    "The 'device_ids' numpy.ndarray() must have a size of 4"
                self._device_ids = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 4 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 4294967296 for val in value)), \
                "The 'device_ids' field must be a set or sequence with length 4 and each value of type 'int' and each unsigned integer in [0, 4294967295]"
        self._device_ids = numpy.array(value, dtype=numpy.uint32)

    @builtins.property
    def order(self):
        """Message field 'order'."""
        return self._order

    @order.setter
    def order(self, value):
        if self._check_fields:
            if isinstance(value, numpy.ndarray):
                assert value.dtype == numpy.int8, \
                    "The 'order' numpy.ndarray() must have the dtype of 'numpy.int8'"
                assert value.size == 4, \
                    "The 'order' numpy.ndarray() must have a size of 4"
                self._order = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 4 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -128 and val < 128 for val in value)), \
                "The 'order' field must be a set or sequence with length 4 and each value of type 'int' and each integer in [-128, 127]"
        self._order = numpy.array(value, dtype=numpy.int8)

    @builtins.property
    def healthy(self):
        """Message field 'healthy'."""
        return self._healthy

    @healthy.setter
    def healthy(self, value):
        if self._check_fields:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 4 and
                 all(isinstance(v, bool) for v in value) and
                 True), \
                "The 'healthy' field must be a set or sequence with length 4 and each value of type 'bool'"
        self._healthy = value

    @builtins.property
    def failed_checks(self):
        """Message field 'failed_checks'."""
        return self._failed_checks

    @failed_checks.setter
    def failed_checks(self, value):
        if self._check_fields:
            if isinstance(value, numpy.ndarray):
                assert value.dtype == numpy.uint16, \
                    "The 'failed_checks' numpy.ndarray() must have the dtype of 'numpy.uint16'"
                assert value.size == 4, \
                    "The 'failed_checks' numpy.ndarray() must have a size of 4"
                self._failed_checks = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 4 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 65536 for val in value)), \
                "The 'failed_checks' field must be a set or sequence with length 4 and each value of type 'int' and each unsigned integer in [0, 65535]"
        self._failed_checks = numpy.array(value, dtype=numpy.uint16)

    @builtins.property
    def strict(self):
        """Message field 'strict'."""
        return self._strict

    @strict.setter
    def strict(self, value):
        if self._check_fields:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 4 and
                 all(isinstance(v, bool) for v in value) and
                 True), \
                "The 'strict' field must be a set or sequence with length 4 and each value of type 'bool'"
        self._strict = value

    @builtins.property
    def drift_rate_horizontal(self):
        """Message field 'drift_rate_horizontal'."""
        return self._drift_rate_horizontal

    @drift_rate_horizontal.setter
    def drift_rate_horizontal(self, value):
        if self._check_fields:
            if isinstance(value, numpy.ndarray):
                assert value.dtype == numpy.float32, \
                    "The 'drift_rate_horizontal' numpy.ndarray() must have the dtype of 'numpy.float32'"
                assert value.size == 4, \
                    "The 'drift_rate_horizontal' numpy.ndarray() must have a size of 4"
                self._drift_rate_horizontal = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 4 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'drift_rate_horizontal' field must be a set or sequence with length 4 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._drift_rate_horizontal = numpy.array(value, dtype=numpy.float32)

    @builtins.property
    def drift_rate_vertical(self):
        """Message field 'drift_rate_vertical'."""
        return self._drift_rate_vertical

    @drift_rate_vertical.setter
    def drift_rate_vertical(self, value):
        if self._check_fields:
            if isinstance(value, numpy.ndarray):
                assert value.dtype == numpy.float32, \
                    "The 'drift_rate_vertical' numpy.ndarray() must have the dtype of 'numpy.float32'"
                assert value.size == 4, \
                    "The 'drift_rate_vertical' numpy.ndarray() must have a size of 4"
                self._drift_rate_vertical = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 4 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'drift_rate_vertical' field must be a set or sequence with length 4 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._drift_rate_vertical = numpy.array(value, dtype=numpy.float32)

    @builtins.property
    def speed_horizontal_filtered(self):
        """Message field 'speed_horizontal_filtered'."""
        return self._speed_horizontal_filtered

    @speed_horizontal_filtered.setter
    def speed_horizontal_filtered(self, value):
        if self._check_fields:
            if isinstance(value, numpy.ndarray):
                assert value.dtype == numpy.float32, \
                    "The 'speed_horizontal_filtered' numpy.ndarray() must have the dtype of 'numpy.float32'"
                assert value.size == 4, \
                    "The 'speed_horizontal_filtered' numpy.ndarray() must have a size of 4"
                self._speed_horizontal_filtered = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 4 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'speed_horizontal_filtered' field must be a set or sequence with length 4 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._speed_horizontal_filtered = numpy.array(value, dtype=numpy.float32)
