"""Compile the actual PX4 final-heading predicate with mocked state only."""
import hashlib
import json
import subprocess


def run_check(output, px4):
    """Verify magnetic and nonmagnetic branches without modifying PX4 or flying."""
    path = px4 / 'src/modules/ekf2/EKF/ekf.h'
    source = path.read_text()
    start = source.index('bool isYawFinalAlignComplete() const')
    end = source.index('\n\t}', start) + 3
    method = source[start:end]
    prefix = r"""
#include <cstdint>
#include <cassert>
#include <chrono>
#include <iostream>
#include <type_traits>
struct Flags { bool mag_3D{}, mag_hdg{}, mag_aligned_in_flight{}, yaw_align{}; };
struct Predicate {
struct { Flags flags; } _control_status;
uint64_t _time_delayed_us{}, _flt_mag_align_start_time{};
"""
    main = r"""
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
"""
    output.mkdir(parents=True, exist_ok=True)
    cpp = output / 'native_heading_fixture.cpp'
    cpp.write_text(prefix + method + main)
    results = []
    for magnetic in (True, False):
        binary = output / ('heading_mag' if magnetic else 'heading_nonmag')
        args = ['g++', '-std=c++17']
        if magnetic:
            args.append('-DCONFIG_EKF2_MAGNETOMETER=1')
        args.extend([str(cpp), '-o', str(binary)])
        built = subprocess.run(args, capture_output=True, text=True)
        run = (subprocess.run([str(binary)], capture_output=True, text=True)
               if not built.returncode else None)
        results.append({'magnetometer_compiled': magnetic, 'compile_command': args,
                        'compile_returncode': built.returncode,
                        'compile_output': built.stdout + built.stderr,
                        'run_returncode': run.returncode if run else None,
                        'run_output': run.stdout + run.stderr if run else None})
    report = {'source': str(path), 'source_sha256': hashlib.sha256(path.read_bytes()).hexdigest(),
              'source_method': method, 'results': results,
              'scope': 'Actual source predicate with synthetic mocked state, never a mission'}
    (output / 'native_heading_check.json').write_text(json.dumps(report, indent=2) + '\n')
    return report
