
#include <cstdint>
#include <cassert>
#include <chrono>
#include <iostream>
#include <type_traits>
struct Flags { bool mag_3D{}, mag_hdg{}, mag_aligned_in_flight{}, yaw_align{}; };
struct Predicate {
struct { Flags flags; } _control_status;
uint64_t _time_delayed_us{}, _flt_mag_align_start_time{};
bool isYawFinalAlignComplete() const
	{
#if defined(CONFIG_EKF2_MAGNETOMETER)
		const bool is_using_mag = (_control_status.flags.mag_3D || _control_status.flags.mag_hdg);
		const bool is_mag_alignment_in_flight_complete = is_using_mag
				&& _control_status.flags.mag_aligned_in_flight
				&& ((_time_delayed_us - _flt_mag_align_start_time) > (uint64_t)1e6);
		return _control_status.flags.yaw_align
		       && (is_mag_alignment_in_flight_complete || !is_using_mag);
#else
		return _control_status.flags.yaw_align;
#endif
	}
};
int main() {
Predicate p;
assert(!p.isYawFinalAlignComplete());
p._control_status.flags.yaw_align = true;
assert(p.isYawFinalAlignComplete());
#ifdef CONFIG_EKF2_MAGNETOMETER
p._control_status.flags.mag_hdg = true;
assert(!p.isYawFinalAlignComplete());
p._control_status.flags.mag_aligned_in_flight = true;
p._flt_mag_align_start_time = 1000000;
p._time_delayed_us = 2000000;
assert(!p.isYawFinalAlignComplete());
p._time_delayed_us = 2000001;
assert(p.isYawFinalAlignComplete());
p._control_status.flags.yaw_align = false;
assert(!p.isYawFinalAlignComplete());
p._control_status.flags.yaw_align = true;
p._control_status.flags.mag_hdg = false;
p._control_status.flags.mag_3D = true;
p._control_status.flags.mag_aligned_in_flight = false;
assert(!p.isYawFinalAlignComplete());
#endif
std::cout << "PASS actual heading predicate; high_resolution_clock steady="
<< std::chrono::high_resolution_clock::is_steady << "; alias_system_clock="
<< std::is_same<std::chrono::high_resolution_clock, std::chrono::system_clock>::value
<< "\n";
}
