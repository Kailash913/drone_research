# generated from rosidl_generator_py/resource/_idl.py.em
# with input from px4_msgs:msg/VehicleGnss.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

# Member 'antenna_offset'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_VehicleGnss(type):
    """Metaclass of message 'VehicleGnss'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'CHECK_NSATS': 1,
        'CHECK_PDOP': 2,
        'CHECK_EPH': 4,
        'CHECK_EPV': 8,
        'CHECK_SACC': 16,
        'CHECK_HDRIFT': 32,
        'CHECK_VDRIFT': 64,
        'CHECK_HSPEED': 128,
        'CHECK_VSPEED': 256,
        'CHECK_SPOOFED': 512,
        'CHECK_FIX': 1024,
        'CHECK_JAMMED': 2048,
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
                'px4_msgs.msg.VehicleGnss')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__vehicle_gnss
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__vehicle_gnss
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__vehicle_gnss
            cls._TYPE_SUPPORT = module.type_support_msg__msg__vehicle_gnss
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__vehicle_gnss

            from px4_msgs.msg import SensorGnss
            if SensorGnss.__class__._TYPE_SUPPORT is None:
                SensorGnss.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'CHECK_NSATS': cls.__constants['CHECK_NSATS'],
            'CHECK_PDOP': cls.__constants['CHECK_PDOP'],
            'CHECK_EPH': cls.__constants['CHECK_EPH'],
            'CHECK_EPV': cls.__constants['CHECK_EPV'],
            'CHECK_SACC': cls.__constants['CHECK_SACC'],
            'CHECK_HDRIFT': cls.__constants['CHECK_HDRIFT'],
            'CHECK_VDRIFT': cls.__constants['CHECK_VDRIFT'],
            'CHECK_HSPEED': cls.__constants['CHECK_HSPEED'],
            'CHECK_VSPEED': cls.__constants['CHECK_VSPEED'],
            'CHECK_SPOOFED': cls.__constants['CHECK_SPOOFED'],
            'CHECK_FIX': cls.__constants['CHECK_FIX'],
            'CHECK_JAMMED': cls.__constants['CHECK_JAMMED'],
        }

    @property
    def CHECK_NSATS(self):
        """Message constant 'CHECK_NSATS'."""
        return Metaclass_VehicleGnss.__constants['CHECK_NSATS']

    @property
    def CHECK_PDOP(self):
        """Message constant 'CHECK_PDOP'."""
        return Metaclass_VehicleGnss.__constants['CHECK_PDOP']

    @property
    def CHECK_EPH(self):
        """Message constant 'CHECK_EPH'."""
        return Metaclass_VehicleGnss.__constants['CHECK_EPH']

    @property
    def CHECK_EPV(self):
        """Message constant 'CHECK_EPV'."""
        return Metaclass_VehicleGnss.__constants['CHECK_EPV']

    @property
    def CHECK_SACC(self):
        """Message constant 'CHECK_SACC'."""
        return Metaclass_VehicleGnss.__constants['CHECK_SACC']

    @property
    def CHECK_HDRIFT(self):
        """Message constant 'CHECK_HDRIFT'."""
        return Metaclass_VehicleGnss.__constants['CHECK_HDRIFT']

    @property
    def CHECK_VDRIFT(self):
        """Message constant 'CHECK_VDRIFT'."""
        return Metaclass_VehicleGnss.__constants['CHECK_VDRIFT']

    @property
    def CHECK_HSPEED(self):
        """Message constant 'CHECK_HSPEED'."""
        return Metaclass_VehicleGnss.__constants['CHECK_HSPEED']

    @property
    def CHECK_VSPEED(self):
        """Message constant 'CHECK_VSPEED'."""
        return Metaclass_VehicleGnss.__constants['CHECK_VSPEED']

    @property
    def CHECK_SPOOFED(self):
        """Message constant 'CHECK_SPOOFED'."""
        return Metaclass_VehicleGnss.__constants['CHECK_SPOOFED']

    @property
    def CHECK_FIX(self):
        """Message constant 'CHECK_FIX'."""
        return Metaclass_VehicleGnss.__constants['CHECK_FIX']

    @property
    def CHECK_JAMMED(self):
        """Message constant 'CHECK_JAMMED'."""
        return Metaclass_VehicleGnss.__constants['CHECK_JAMMED']


class VehicleGnss(metaclass=Metaclass_VehicleGnss):
    """
    Message class 'VehicleGnss'.

    Constants:
      CHECK_NSATS
      CHECK_PDOP
      CHECK_EPH
      CHECK_EPV
      CHECK_SACC
      CHECK_HDRIFT
      CHECK_VDRIFT
      CHECK_HSPEED
      CHECK_VSPEED
      CHECK_SPOOFED
      CHECK_FIX
      CHECK_JAMMED
    """

    __slots__ = [
        '_timestamp',
        '_timestamp_sample',
        '_receiver',
        '_antenna_offset',
        '_selected_instance',
        '_selection_count',
        '_usable',
        '_failed_checks',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'timestamp': 'uint64',
        'timestamp_sample': 'uint64',
        'receiver': 'px4_msgs/SensorGnss',
        'antenna_offset': 'float[3]',
        'selected_instance': 'uint8',
        'selection_count': 'uint8',
        'usable': 'boolean',
        'failed_checks': 'uint16',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['px4_msgs', 'msg'], 'SensorGnss'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 3),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
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
        self.timestamp_sample = kwargs.get('timestamp_sample', int())
        from px4_msgs.msg import SensorGnss
        self.receiver = kwargs.get('receiver', SensorGnss())
        if 'antenna_offset' not in kwargs:
            self.antenna_offset = numpy.zeros(3, dtype=numpy.float32)
        else:
            self.antenna_offset = kwargs.get('antenna_offset')
        self.selected_instance = kwargs.get('selected_instance', int())
        self.selection_count = kwargs.get('selection_count', int())
        self.usable = kwargs.get('usable', bool())
        self.failed_checks = kwargs.get('failed_checks', int())

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
        if self.timestamp_sample != other.timestamp_sample:
            return False
        if self.receiver != other.receiver:
            return False
        if any(self.antenna_offset != other.antenna_offset):
            return False
        if self.selected_instance != other.selected_instance:
            return False
        if self.selection_count != other.selection_count:
            return False
        if self.usable != other.usable:
            return False
        if self.failed_checks != other.failed_checks:
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
    def timestamp_sample(self):
        """Message field 'timestamp_sample'."""
        return self._timestamp_sample

    @timestamp_sample.setter
    def timestamp_sample(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'timestamp_sample' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'timestamp_sample' field must be an unsigned integer in [0, 18446744073709551615]"
        self._timestamp_sample = value

    @builtins.property
    def receiver(self):
        """Message field 'receiver'."""
        return self._receiver

    @receiver.setter
    def receiver(self, value):
        if self._check_fields:
            from px4_msgs.msg import SensorGnss
            assert \
                isinstance(value, SensorGnss), \
                "The 'receiver' field must be a sub message of type 'SensorGnss'"
        self._receiver = value

    @builtins.property
    def antenna_offset(self):
        """Message field 'antenna_offset'."""
        return self._antenna_offset

    @antenna_offset.setter
    def antenna_offset(self, value):
        if self._check_fields:
            if isinstance(value, numpy.ndarray):
                assert value.dtype == numpy.float32, \
                    "The 'antenna_offset' numpy.ndarray() must have the dtype of 'numpy.float32'"
                assert value.size == 3, \
                    "The 'antenna_offset' numpy.ndarray() must have a size of 3"
                self._antenna_offset = value
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
                 len(value) == 3 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'antenna_offset' field must be a set or sequence with length 3 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._antenna_offset = numpy.array(value, dtype=numpy.float32)

    @builtins.property
    def selected_instance(self):
        """Message field 'selected_instance'."""
        return self._selected_instance

    @selected_instance.setter
    def selected_instance(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'selected_instance' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'selected_instance' field must be an unsigned integer in [0, 255]"
        self._selected_instance = value

    @builtins.property
    def selection_count(self):
        """Message field 'selection_count'."""
        return self._selection_count

    @selection_count.setter
    def selection_count(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'selection_count' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'selection_count' field must be an unsigned integer in [0, 255]"
        self._selection_count = value

    @builtins.property
    def usable(self):
        """Message field 'usable'."""
        return self._usable

    @usable.setter
    def usable(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'usable' field must be of type 'bool'"
        self._usable = value

    @builtins.property
    def failed_checks(self):
        """Message field 'failed_checks'."""
        return self._failed_checks

    @failed_checks.setter
    def failed_checks(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'failed_checks' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'failed_checks' field must be an unsigned integer in [0, 65535]"
        self._failed_checks = value
