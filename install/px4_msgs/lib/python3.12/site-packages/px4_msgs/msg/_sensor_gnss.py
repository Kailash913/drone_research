# generated from rosidl_generator_py/resource/_idl.py.em
# with input from px4_msgs:msg/SensorGnss.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SensorGnss(type):
    """Metaclass of message 'SensorGnss'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'FIX_TYPE_NONE': 1,
        'FIX_TYPE_2D': 2,
        'FIX_TYPE_3D': 3,
        'FIX_TYPE_RTCM_CODE_DIFFERENTIAL': 4,
        'FIX_TYPE_RTK_FLOAT': 5,
        'FIX_TYPE_RTK_FIXED': 6,
        'FIX_TYPE_EXTRAPOLATED': 8,
        'JAMMING_STATE_UNKNOWN': 0,
        'JAMMING_STATE_OK': 1,
        'JAMMING_STATE_MITIGATED': 2,
        'JAMMING_STATE_DETECTED': 3,
        'SPOOFING_STATE_UNKNOWN': 0,
        'SPOOFING_STATE_OK': 1,
        'SPOOFING_STATE_MITIGATED': 2,
        'SPOOFING_STATE_DETECTED': 3,
        'AUTHENTICATION_STATE_UNKNOWN': 0,
        'AUTHENTICATION_STATE_INITIALIZING': 1,
        'AUTHENTICATION_STATE_ERROR': 2,
        'AUTHENTICATION_STATE_OK': 3,
        'AUTHENTICATION_STATE_DISABLED': 4,
        'SYSTEM_ERROR_OK': 0,
        'SYSTEM_ERROR_INCOMING_CORRECTIONS': 1,
        'SYSTEM_ERROR_CONFIGURATION': 2,
        'SYSTEM_ERROR_SOFTWARE': 4,
        'SYSTEM_ERROR_ANTENNA': 8,
        'SYSTEM_ERROR_EVENT_CONGESTION': 16,
        'SYSTEM_ERROR_CPU_OVERLOAD': 32,
        'SYSTEM_ERROR_OUTPUT_CONGESTION': 64,
        'CORRECTIONS_PROTOCOL_UNKNOWN': 0,
        'CORRECTIONS_PROTOCOL_RTCM3': 1,
        'CORRECTIONS_PROTOCOL_SPARTN': 2,
        'CORRECTIONS_PROTOCOL_HAS': 3,
        'CORRECTIONS_PROTOCOL_PMP': 4,
        'CORRECTIONS_PROTOCOL_QZSS_L6': 5,
        'CORRECTIONS_MSG_USED_UNKNOWN': 0,
        'CORRECTIONS_MSG_USED_NOT_USED': 1,
        'CORRECTIONS_MSG_USED_USED': 2,
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
                'px4_msgs.msg.SensorGnss')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__sensor_gnss
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__sensor_gnss
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__sensor_gnss
            cls._TYPE_SUPPORT = module.type_support_msg__msg__sensor_gnss
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__sensor_gnss

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'FIX_TYPE_NONE': cls.__constants['FIX_TYPE_NONE'],
            'FIX_TYPE_2D': cls.__constants['FIX_TYPE_2D'],
            'FIX_TYPE_3D': cls.__constants['FIX_TYPE_3D'],
            'FIX_TYPE_RTCM_CODE_DIFFERENTIAL': cls.__constants['FIX_TYPE_RTCM_CODE_DIFFERENTIAL'],
            'FIX_TYPE_RTK_FLOAT': cls.__constants['FIX_TYPE_RTK_FLOAT'],
            'FIX_TYPE_RTK_FIXED': cls.__constants['FIX_TYPE_RTK_FIXED'],
            'FIX_TYPE_EXTRAPOLATED': cls.__constants['FIX_TYPE_EXTRAPOLATED'],
            'JAMMING_STATE_UNKNOWN': cls.__constants['JAMMING_STATE_UNKNOWN'],
            'JAMMING_STATE_OK': cls.__constants['JAMMING_STATE_OK'],
            'JAMMING_STATE_MITIGATED': cls.__constants['JAMMING_STATE_MITIGATED'],
            'JAMMING_STATE_DETECTED': cls.__constants['JAMMING_STATE_DETECTED'],
            'SPOOFING_STATE_UNKNOWN': cls.__constants['SPOOFING_STATE_UNKNOWN'],
            'SPOOFING_STATE_OK': cls.__constants['SPOOFING_STATE_OK'],
            'SPOOFING_STATE_MITIGATED': cls.__constants['SPOOFING_STATE_MITIGATED'],
            'SPOOFING_STATE_DETECTED': cls.__constants['SPOOFING_STATE_DETECTED'],
            'AUTHENTICATION_STATE_UNKNOWN': cls.__constants['AUTHENTICATION_STATE_UNKNOWN'],
            'AUTHENTICATION_STATE_INITIALIZING': cls.__constants['AUTHENTICATION_STATE_INITIALIZING'],
            'AUTHENTICATION_STATE_ERROR': cls.__constants['AUTHENTICATION_STATE_ERROR'],
            'AUTHENTICATION_STATE_OK': cls.__constants['AUTHENTICATION_STATE_OK'],
            'AUTHENTICATION_STATE_DISABLED': cls.__constants['AUTHENTICATION_STATE_DISABLED'],
            'SYSTEM_ERROR_OK': cls.__constants['SYSTEM_ERROR_OK'],
            'SYSTEM_ERROR_INCOMING_CORRECTIONS': cls.__constants['SYSTEM_ERROR_INCOMING_CORRECTIONS'],
            'SYSTEM_ERROR_CONFIGURATION': cls.__constants['SYSTEM_ERROR_CONFIGURATION'],
            'SYSTEM_ERROR_SOFTWARE': cls.__constants['SYSTEM_ERROR_SOFTWARE'],
            'SYSTEM_ERROR_ANTENNA': cls.__constants['SYSTEM_ERROR_ANTENNA'],
            'SYSTEM_ERROR_EVENT_CONGESTION': cls.__constants['SYSTEM_ERROR_EVENT_CONGESTION'],
            'SYSTEM_ERROR_CPU_OVERLOAD': cls.__constants['SYSTEM_ERROR_CPU_OVERLOAD'],
            'SYSTEM_ERROR_OUTPUT_CONGESTION': cls.__constants['SYSTEM_ERROR_OUTPUT_CONGESTION'],
            'CORRECTIONS_PROTOCOL_UNKNOWN': cls.__constants['CORRECTIONS_PROTOCOL_UNKNOWN'],
            'CORRECTIONS_PROTOCOL_RTCM3': cls.__constants['CORRECTIONS_PROTOCOL_RTCM3'],
            'CORRECTIONS_PROTOCOL_SPARTN': cls.__constants['CORRECTIONS_PROTOCOL_SPARTN'],
            'CORRECTIONS_PROTOCOL_HAS': cls.__constants['CORRECTIONS_PROTOCOL_HAS'],
            'CORRECTIONS_PROTOCOL_PMP': cls.__constants['CORRECTIONS_PROTOCOL_PMP'],
            'CORRECTIONS_PROTOCOL_QZSS_L6': cls.__constants['CORRECTIONS_PROTOCOL_QZSS_L6'],
            'CORRECTIONS_MSG_USED_UNKNOWN': cls.__constants['CORRECTIONS_MSG_USED_UNKNOWN'],
            'CORRECTIONS_MSG_USED_NOT_USED': cls.__constants['CORRECTIONS_MSG_USED_NOT_USED'],
            'CORRECTIONS_MSG_USED_USED': cls.__constants['CORRECTIONS_MSG_USED_USED'],
        }

    @property
    def FIX_TYPE_NONE(self):
        """Message constant 'FIX_TYPE_NONE'."""
        return Metaclass_SensorGnss.__constants['FIX_TYPE_NONE']

    @property
    def FIX_TYPE_2D(self):
        """Message constant 'FIX_TYPE_2D'."""
        return Metaclass_SensorGnss.__constants['FIX_TYPE_2D']

    @property
    def FIX_TYPE_3D(self):
        """Message constant 'FIX_TYPE_3D'."""
        return Metaclass_SensorGnss.__constants['FIX_TYPE_3D']

    @property
    def FIX_TYPE_RTCM_CODE_DIFFERENTIAL(self):
        """Message constant 'FIX_TYPE_RTCM_CODE_DIFFERENTIAL'."""
        return Metaclass_SensorGnss.__constants['FIX_TYPE_RTCM_CODE_DIFFERENTIAL']

    @property
    def FIX_TYPE_RTK_FLOAT(self):
        """Message constant 'FIX_TYPE_RTK_FLOAT'."""
        return Metaclass_SensorGnss.__constants['FIX_TYPE_RTK_FLOAT']

    @property
    def FIX_TYPE_RTK_FIXED(self):
        """Message constant 'FIX_TYPE_RTK_FIXED'."""
        return Metaclass_SensorGnss.__constants['FIX_TYPE_RTK_FIXED']

    @property
    def FIX_TYPE_EXTRAPOLATED(self):
        """Message constant 'FIX_TYPE_EXTRAPOLATED'."""
        return Metaclass_SensorGnss.__constants['FIX_TYPE_EXTRAPOLATED']

    @property
    def JAMMING_STATE_UNKNOWN(self):
        """Message constant 'JAMMING_STATE_UNKNOWN'."""
        return Metaclass_SensorGnss.__constants['JAMMING_STATE_UNKNOWN']

    @property
    def JAMMING_STATE_OK(self):
        """Message constant 'JAMMING_STATE_OK'."""
        return Metaclass_SensorGnss.__constants['JAMMING_STATE_OK']

    @property
    def JAMMING_STATE_MITIGATED(self):
        """Message constant 'JAMMING_STATE_MITIGATED'."""
        return Metaclass_SensorGnss.__constants['JAMMING_STATE_MITIGATED']

    @property
    def JAMMING_STATE_DETECTED(self):
        """Message constant 'JAMMING_STATE_DETECTED'."""
        return Metaclass_SensorGnss.__constants['JAMMING_STATE_DETECTED']

    @property
    def SPOOFING_STATE_UNKNOWN(self):
        """Message constant 'SPOOFING_STATE_UNKNOWN'."""
        return Metaclass_SensorGnss.__constants['SPOOFING_STATE_UNKNOWN']

    @property
    def SPOOFING_STATE_OK(self):
        """Message constant 'SPOOFING_STATE_OK'."""
        return Metaclass_SensorGnss.__constants['SPOOFING_STATE_OK']

    @property
    def SPOOFING_STATE_MITIGATED(self):
        """Message constant 'SPOOFING_STATE_MITIGATED'."""
        return Metaclass_SensorGnss.__constants['SPOOFING_STATE_MITIGATED']

    @property
    def SPOOFING_STATE_DETECTED(self):
        """Message constant 'SPOOFING_STATE_DETECTED'."""
        return Metaclass_SensorGnss.__constants['SPOOFING_STATE_DETECTED']

    @property
    def AUTHENTICATION_STATE_UNKNOWN(self):
        """Message constant 'AUTHENTICATION_STATE_UNKNOWN'."""
        return Metaclass_SensorGnss.__constants['AUTHENTICATION_STATE_UNKNOWN']

    @property
    def AUTHENTICATION_STATE_INITIALIZING(self):
        """Message constant 'AUTHENTICATION_STATE_INITIALIZING'."""
        return Metaclass_SensorGnss.__constants['AUTHENTICATION_STATE_INITIALIZING']

    @property
    def AUTHENTICATION_STATE_ERROR(self):
        """Message constant 'AUTHENTICATION_STATE_ERROR'."""
        return Metaclass_SensorGnss.__constants['AUTHENTICATION_STATE_ERROR']

    @property
    def AUTHENTICATION_STATE_OK(self):
        """Message constant 'AUTHENTICATION_STATE_OK'."""
        return Metaclass_SensorGnss.__constants['AUTHENTICATION_STATE_OK']

    @property
    def AUTHENTICATION_STATE_DISABLED(self):
        """Message constant 'AUTHENTICATION_STATE_DISABLED'."""
        return Metaclass_SensorGnss.__constants['AUTHENTICATION_STATE_DISABLED']

    @property
    def SYSTEM_ERROR_OK(self):
        """Message constant 'SYSTEM_ERROR_OK'."""
        return Metaclass_SensorGnss.__constants['SYSTEM_ERROR_OK']

    @property
    def SYSTEM_ERROR_INCOMING_CORRECTIONS(self):
        """Message constant 'SYSTEM_ERROR_INCOMING_CORRECTIONS'."""
        return Metaclass_SensorGnss.__constants['SYSTEM_ERROR_INCOMING_CORRECTIONS']

    @property
    def SYSTEM_ERROR_CONFIGURATION(self):
        """Message constant 'SYSTEM_ERROR_CONFIGURATION'."""
        return Metaclass_SensorGnss.__constants['SYSTEM_ERROR_CONFIGURATION']

    @property
    def SYSTEM_ERROR_SOFTWARE(self):
        """Message constant 'SYSTEM_ERROR_SOFTWARE'."""
        return Metaclass_SensorGnss.__constants['SYSTEM_ERROR_SOFTWARE']

    @property
    def SYSTEM_ERROR_ANTENNA(self):
        """Message constant 'SYSTEM_ERROR_ANTENNA'."""
        return Metaclass_SensorGnss.__constants['SYSTEM_ERROR_ANTENNA']

    @property
    def SYSTEM_ERROR_EVENT_CONGESTION(self):
        """Message constant 'SYSTEM_ERROR_EVENT_CONGESTION'."""
        return Metaclass_SensorGnss.__constants['SYSTEM_ERROR_EVENT_CONGESTION']

    @property
    def SYSTEM_ERROR_CPU_OVERLOAD(self):
        """Message constant 'SYSTEM_ERROR_CPU_OVERLOAD'."""
        return Metaclass_SensorGnss.__constants['SYSTEM_ERROR_CPU_OVERLOAD']

    @property
    def SYSTEM_ERROR_OUTPUT_CONGESTION(self):
        """Message constant 'SYSTEM_ERROR_OUTPUT_CONGESTION'."""
        return Metaclass_SensorGnss.__constants['SYSTEM_ERROR_OUTPUT_CONGESTION']

    @property
    def CORRECTIONS_PROTOCOL_UNKNOWN(self):
        """Message constant 'CORRECTIONS_PROTOCOL_UNKNOWN'."""
        return Metaclass_SensorGnss.__constants['CORRECTIONS_PROTOCOL_UNKNOWN']

    @property
    def CORRECTIONS_PROTOCOL_RTCM3(self):
        """Message constant 'CORRECTIONS_PROTOCOL_RTCM3'."""
        return Metaclass_SensorGnss.__constants['CORRECTIONS_PROTOCOL_RTCM3']

    @property
    def CORRECTIONS_PROTOCOL_SPARTN(self):
        """Message constant 'CORRECTIONS_PROTOCOL_SPARTN'."""
        return Metaclass_SensorGnss.__constants['CORRECTIONS_PROTOCOL_SPARTN']

    @property
    def CORRECTIONS_PROTOCOL_HAS(self):
        """Message constant 'CORRECTIONS_PROTOCOL_HAS'."""
        return Metaclass_SensorGnss.__constants['CORRECTIONS_PROTOCOL_HAS']

    @property
    def CORRECTIONS_PROTOCOL_PMP(self):
        """Message constant 'CORRECTIONS_PROTOCOL_PMP'."""
        return Metaclass_SensorGnss.__constants['CORRECTIONS_PROTOCOL_PMP']

    @property
    def CORRECTIONS_PROTOCOL_QZSS_L6(self):
        """Message constant 'CORRECTIONS_PROTOCOL_QZSS_L6'."""
        return Metaclass_SensorGnss.__constants['CORRECTIONS_PROTOCOL_QZSS_L6']

    @property
    def CORRECTIONS_MSG_USED_UNKNOWN(self):
        """Message constant 'CORRECTIONS_MSG_USED_UNKNOWN'."""
        return Metaclass_SensorGnss.__constants['CORRECTIONS_MSG_USED_UNKNOWN']

    @property
    def CORRECTIONS_MSG_USED_NOT_USED(self):
        """Message constant 'CORRECTIONS_MSG_USED_NOT_USED'."""
        return Metaclass_SensorGnss.__constants['CORRECTIONS_MSG_USED_NOT_USED']

    @property
    def CORRECTIONS_MSG_USED_USED(self):
        """Message constant 'CORRECTIONS_MSG_USED_USED'."""
        return Metaclass_SensorGnss.__constants['CORRECTIONS_MSG_USED_USED']


class SensorGnss(metaclass=Metaclass_SensorGnss):
    """
    Message class 'SensorGnss'.

    Constants:
      FIX_TYPE_NONE
      FIX_TYPE_2D
      FIX_TYPE_3D
      FIX_TYPE_RTCM_CODE_DIFFERENTIAL
      FIX_TYPE_RTK_FLOAT
      FIX_TYPE_RTK_FIXED
      FIX_TYPE_EXTRAPOLATED
      JAMMING_STATE_UNKNOWN
      JAMMING_STATE_OK
      JAMMING_STATE_MITIGATED
      JAMMING_STATE_DETECTED
      SPOOFING_STATE_UNKNOWN
      SPOOFING_STATE_OK
      SPOOFING_STATE_MITIGATED
      SPOOFING_STATE_DETECTED
      AUTHENTICATION_STATE_UNKNOWN
      AUTHENTICATION_STATE_INITIALIZING
      AUTHENTICATION_STATE_ERROR
      AUTHENTICATION_STATE_OK
      AUTHENTICATION_STATE_DISABLED
      SYSTEM_ERROR_OK
      SYSTEM_ERROR_INCOMING_CORRECTIONS
      SYSTEM_ERROR_CONFIGURATION
      SYSTEM_ERROR_SOFTWARE
      SYSTEM_ERROR_ANTENNA
      SYSTEM_ERROR_EVENT_CONGESTION
      SYSTEM_ERROR_CPU_OVERLOAD
      SYSTEM_ERROR_OUTPUT_CONGESTION
      CORRECTIONS_PROTOCOL_UNKNOWN
      CORRECTIONS_PROTOCOL_RTCM3
      CORRECTIONS_PROTOCOL_SPARTN
      CORRECTIONS_PROTOCOL_HAS
      CORRECTIONS_PROTOCOL_PMP
      CORRECTIONS_PROTOCOL_QZSS_L6
      CORRECTIONS_MSG_USED_UNKNOWN
      CORRECTIONS_MSG_USED_NOT_USED
      CORRECTIONS_MSG_USED_USED
    """

    __slots__ = [
        '_timestamp',
        '_timestamp_sample',
        '_device_id',
        '_latitude',
        '_longitude',
        '_altitude_msl',
        '_altitude_ellipsoid',
        '_speed_accuracy',
        '_course_accuracy',
        '_fix_type',
        '_eph',
        '_epv',
        '_hdop',
        '_vdop',
        '_noise',
        '_automatic_gain_control',
        '_jamming_state',
        '_jamming_indicator',
        '_spoofing_state',
        '_authentication_state',
        '_ground_speed',
        '_vel_north',
        '_vel_east',
        '_vel_down',
        '_course',
        '_vel_ned_valid',
        '_timestamp_time_relative',
        '_time_utc_usec',
        '_satellites_used',
        '_system_error',
        '_rtcm_injection_rate',
        '_selected_rtcm_instance',
        '_corrections_protocol',
        '_corrections_crc_failed',
        '_corrections_msg_used',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'timestamp': 'uint64',
        'timestamp_sample': 'uint64',
        'device_id': 'uint32',
        'latitude': 'double',
        'longitude': 'double',
        'altitude_msl': 'double',
        'altitude_ellipsoid': 'double',
        'speed_accuracy': 'float',
        'course_accuracy': 'float',
        'fix_type': 'uint8',
        'eph': 'float',
        'epv': 'float',
        'hdop': 'float',
        'vdop': 'float',
        'noise': 'int32',
        'automatic_gain_control': 'uint16',
        'jamming_state': 'uint8',
        'jamming_indicator': 'int32',
        'spoofing_state': 'uint8',
        'authentication_state': 'uint8',
        'ground_speed': 'float',
        'vel_north': 'float',
        'vel_east': 'float',
        'vel_down': 'float',
        'course': 'float',
        'vel_ned_valid': 'boolean',
        'timestamp_time_relative': 'int32',
        'time_utc_usec': 'uint64',
        'satellites_used': 'uint8',
        'system_error': 'uint32',
        'rtcm_injection_rate': 'float',
        'selected_rtcm_instance': 'uint8',
        'corrections_protocol': 'uint8',
        'corrections_crc_failed': 'boolean',
        'corrections_msg_used': 'uint8',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
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
        self.device_id = kwargs.get('device_id', int())
        self.latitude = kwargs.get('latitude', float())
        self.longitude = kwargs.get('longitude', float())
        self.altitude_msl = kwargs.get('altitude_msl', float())
        self.altitude_ellipsoid = kwargs.get('altitude_ellipsoid', float())
        self.speed_accuracy = kwargs.get('speed_accuracy', float())
        self.course_accuracy = kwargs.get('course_accuracy', float())
        self.fix_type = kwargs.get('fix_type', int())
        self.eph = kwargs.get('eph', float())
        self.epv = kwargs.get('epv', float())
        self.hdop = kwargs.get('hdop', float())
        self.vdop = kwargs.get('vdop', float())
        self.noise = kwargs.get('noise', int())
        self.automatic_gain_control = kwargs.get('automatic_gain_control', int())
        self.jamming_state = kwargs.get('jamming_state', int())
        self.jamming_indicator = kwargs.get('jamming_indicator', int())
        self.spoofing_state = kwargs.get('spoofing_state', int())
        self.authentication_state = kwargs.get('authentication_state', int())
        self.ground_speed = kwargs.get('ground_speed', float())
        self.vel_north = kwargs.get('vel_north', float())
        self.vel_east = kwargs.get('vel_east', float())
        self.vel_down = kwargs.get('vel_down', float())
        self.course = kwargs.get('course', float())
        self.vel_ned_valid = kwargs.get('vel_ned_valid', bool())
        self.timestamp_time_relative = kwargs.get('timestamp_time_relative', int())
        self.time_utc_usec = kwargs.get('time_utc_usec', int())
        self.satellites_used = kwargs.get('satellites_used', int())
        self.system_error = kwargs.get('system_error', int())
        self.rtcm_injection_rate = kwargs.get('rtcm_injection_rate', float())
        self.selected_rtcm_instance = kwargs.get('selected_rtcm_instance', int())
        self.corrections_protocol = kwargs.get('corrections_protocol', int())
        self.corrections_crc_failed = kwargs.get('corrections_crc_failed', bool())
        self.corrections_msg_used = kwargs.get('corrections_msg_used', int())

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
        if self.device_id != other.device_id:
            return False
        if self.latitude != other.latitude:
            return False
        if self.longitude != other.longitude:
            return False
        if self.altitude_msl != other.altitude_msl:
            return False
        if self.altitude_ellipsoid != other.altitude_ellipsoid:
            return False
        if self.speed_accuracy != other.speed_accuracy:
            return False
        if self.course_accuracy != other.course_accuracy:
            return False
        if self.fix_type != other.fix_type:
            return False
        if self.eph != other.eph:
            return False
        if self.epv != other.epv:
            return False
        if self.hdop != other.hdop:
            return False
        if self.vdop != other.vdop:
            return False
        if self.noise != other.noise:
            return False
        if self.automatic_gain_control != other.automatic_gain_control:
            return False
        if self.jamming_state != other.jamming_state:
            return False
        if self.jamming_indicator != other.jamming_indicator:
            return False
        if self.spoofing_state != other.spoofing_state:
            return False
        if self.authentication_state != other.authentication_state:
            return False
        if self.ground_speed != other.ground_speed:
            return False
        if self.vel_north != other.vel_north:
            return False
        if self.vel_east != other.vel_east:
            return False
        if self.vel_down != other.vel_down:
            return False
        if self.course != other.course:
            return False
        if self.vel_ned_valid != other.vel_ned_valid:
            return False
        if self.timestamp_time_relative != other.timestamp_time_relative:
            return False
        if self.time_utc_usec != other.time_utc_usec:
            return False
        if self.satellites_used != other.satellites_used:
            return False
        if self.system_error != other.system_error:
            return False
        if self.rtcm_injection_rate != other.rtcm_injection_rate:
            return False
        if self.selected_rtcm_instance != other.selected_rtcm_instance:
            return False
        if self.corrections_protocol != other.corrections_protocol:
            return False
        if self.corrections_crc_failed != other.corrections_crc_failed:
            return False
        if self.corrections_msg_used != other.corrections_msg_used:
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
    def device_id(self):
        """Message field 'device_id'."""
        return self._device_id

    @device_id.setter
    def device_id(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'device_id' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'device_id' field must be an unsigned integer in [0, 4294967295]"
        self._device_id = value

    @builtins.property
    def latitude(self):
        """Message field 'latitude'."""
        return self._latitude

    @latitude.setter
    def latitude(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'latitude' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'latitude' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._latitude = value

    @builtins.property
    def longitude(self):
        """Message field 'longitude'."""
        return self._longitude

    @longitude.setter
    def longitude(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'longitude' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'longitude' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._longitude = value

    @builtins.property
    def altitude_msl(self):
        """Message field 'altitude_msl'."""
        return self._altitude_msl

    @altitude_msl.setter
    def altitude_msl(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'altitude_msl' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'altitude_msl' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._altitude_msl = value

    @builtins.property
    def altitude_ellipsoid(self):
        """Message field 'altitude_ellipsoid'."""
        return self._altitude_ellipsoid

    @altitude_ellipsoid.setter
    def altitude_ellipsoid(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'altitude_ellipsoid' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'altitude_ellipsoid' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._altitude_ellipsoid = value

    @builtins.property
    def speed_accuracy(self):
        """Message field 'speed_accuracy'."""
        return self._speed_accuracy

    @speed_accuracy.setter
    def speed_accuracy(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'speed_accuracy' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'speed_accuracy' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._speed_accuracy = value

    @builtins.property
    def course_accuracy(self):
        """Message field 'course_accuracy'."""
        return self._course_accuracy

    @course_accuracy.setter
    def course_accuracy(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'course_accuracy' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'course_accuracy' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._course_accuracy = value

    @builtins.property
    def fix_type(self):
        """Message field 'fix_type'."""
        return self._fix_type

    @fix_type.setter
    def fix_type(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'fix_type' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'fix_type' field must be an unsigned integer in [0, 255]"
        self._fix_type = value

    @builtins.property
    def eph(self):
        """Message field 'eph'."""
        return self._eph

    @eph.setter
    def eph(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'eph' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'eph' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._eph = value

    @builtins.property
    def epv(self):
        """Message field 'epv'."""
        return self._epv

    @epv.setter
    def epv(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'epv' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'epv' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._epv = value

    @builtins.property
    def hdop(self):
        """Message field 'hdop'."""
        return self._hdop

    @hdop.setter
    def hdop(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'hdop' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'hdop' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._hdop = value

    @builtins.property
    def vdop(self):
        """Message field 'vdop'."""
        return self._vdop

    @vdop.setter
    def vdop(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'vdop' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'vdop' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._vdop = value

    @builtins.property
    def noise(self):
        """Message field 'noise'."""
        return self._noise

    @noise.setter
    def noise(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'noise' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'noise' field must be an integer in [-2147483648, 2147483647]"
        self._noise = value

    @builtins.property
    def automatic_gain_control(self):
        """Message field 'automatic_gain_control'."""
        return self._automatic_gain_control

    @automatic_gain_control.setter
    def automatic_gain_control(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'automatic_gain_control' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'automatic_gain_control' field must be an unsigned integer in [0, 65535]"
        self._automatic_gain_control = value

    @builtins.property
    def jamming_state(self):
        """Message field 'jamming_state'."""
        return self._jamming_state

    @jamming_state.setter
    def jamming_state(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'jamming_state' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'jamming_state' field must be an unsigned integer in [0, 255]"
        self._jamming_state = value

    @builtins.property
    def jamming_indicator(self):
        """Message field 'jamming_indicator'."""
        return self._jamming_indicator

    @jamming_indicator.setter
    def jamming_indicator(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'jamming_indicator' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'jamming_indicator' field must be an integer in [-2147483648, 2147483647]"
        self._jamming_indicator = value

    @builtins.property
    def spoofing_state(self):
        """Message field 'spoofing_state'."""
        return self._spoofing_state

    @spoofing_state.setter
    def spoofing_state(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'spoofing_state' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'spoofing_state' field must be an unsigned integer in [0, 255]"
        self._spoofing_state = value

    @builtins.property
    def authentication_state(self):
        """Message field 'authentication_state'."""
        return self._authentication_state

    @authentication_state.setter
    def authentication_state(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'authentication_state' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'authentication_state' field must be an unsigned integer in [0, 255]"
        self._authentication_state = value

    @builtins.property
    def ground_speed(self):
        """Message field 'ground_speed'."""
        return self._ground_speed

    @ground_speed.setter
    def ground_speed(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'ground_speed' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'ground_speed' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._ground_speed = value

    @builtins.property
    def vel_north(self):
        """Message field 'vel_north'."""
        return self._vel_north

    @vel_north.setter
    def vel_north(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'vel_north' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'vel_north' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._vel_north = value

    @builtins.property
    def vel_east(self):
        """Message field 'vel_east'."""
        return self._vel_east

    @vel_east.setter
    def vel_east(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'vel_east' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'vel_east' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._vel_east = value

    @builtins.property
    def vel_down(self):
        """Message field 'vel_down'."""
        return self._vel_down

    @vel_down.setter
    def vel_down(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'vel_down' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'vel_down' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._vel_down = value

    @builtins.property
    def course(self):
        """Message field 'course'."""
        return self._course

    @course.setter
    def course(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'course' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'course' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._course = value

    @builtins.property
    def vel_ned_valid(self):
        """Message field 'vel_ned_valid'."""
        return self._vel_ned_valid

    @vel_ned_valid.setter
    def vel_ned_valid(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'vel_ned_valid' field must be of type 'bool'"
        self._vel_ned_valid = value

    @builtins.property
    def timestamp_time_relative(self):
        """Message field 'timestamp_time_relative'."""
        return self._timestamp_time_relative

    @timestamp_time_relative.setter
    def timestamp_time_relative(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'timestamp_time_relative' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'timestamp_time_relative' field must be an integer in [-2147483648, 2147483647]"
        self._timestamp_time_relative = value

    @builtins.property
    def time_utc_usec(self):
        """Message field 'time_utc_usec'."""
        return self._time_utc_usec

    @time_utc_usec.setter
    def time_utc_usec(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'time_utc_usec' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'time_utc_usec' field must be an unsigned integer in [0, 18446744073709551615]"
        self._time_utc_usec = value

    @builtins.property
    def satellites_used(self):
        """Message field 'satellites_used'."""
        return self._satellites_used

    @satellites_used.setter
    def satellites_used(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'satellites_used' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'satellites_used' field must be an unsigned integer in [0, 255]"
        self._satellites_used = value

    @builtins.property
    def system_error(self):
        """Message field 'system_error'."""
        return self._system_error

    @system_error.setter
    def system_error(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'system_error' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'system_error' field must be an unsigned integer in [0, 4294967295]"
        self._system_error = value

    @builtins.property
    def rtcm_injection_rate(self):
        """Message field 'rtcm_injection_rate'."""
        return self._rtcm_injection_rate

    @rtcm_injection_rate.setter
    def rtcm_injection_rate(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'rtcm_injection_rate' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'rtcm_injection_rate' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._rtcm_injection_rate = value

    @builtins.property
    def selected_rtcm_instance(self):
        """Message field 'selected_rtcm_instance'."""
        return self._selected_rtcm_instance

    @selected_rtcm_instance.setter
    def selected_rtcm_instance(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'selected_rtcm_instance' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'selected_rtcm_instance' field must be an unsigned integer in [0, 255]"
        self._selected_rtcm_instance = value

    @builtins.property
    def corrections_protocol(self):
        """Message field 'corrections_protocol'."""
        return self._corrections_protocol

    @corrections_protocol.setter
    def corrections_protocol(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'corrections_protocol' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'corrections_protocol' field must be an unsigned integer in [0, 255]"
        self._corrections_protocol = value

    @builtins.property
    def corrections_crc_failed(self):
        """Message field 'corrections_crc_failed'."""
        return self._corrections_crc_failed

    @corrections_crc_failed.setter
    def corrections_crc_failed(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'corrections_crc_failed' field must be of type 'bool'"
        self._corrections_crc_failed = value

    @builtins.property
    def corrections_msg_used(self):
        """Message field 'corrections_msg_used'."""
        return self._corrections_msg_used

    @corrections_msg_used.setter
    def corrections_msg_used(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'corrections_msg_used' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'corrections_msg_used' field must be an unsigned integer in [0, 255]"
        self._corrections_msg_used = value
