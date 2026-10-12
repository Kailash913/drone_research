"""Exercise retained PX4 Timesync methods with mocked publication/hrt, never flight hardware."""
import hashlib
import json
import subprocess


def run_check(output, px4):
    """Compile actual local filter methods and assert offset reset/recovery behavior."""
    source = px4 / 'src/lib/timesync/Timesync.cpp'
    header = px4 / 'src/lib/timesync/Timesync.hpp'
    client = px4 / 'src/modules/uxrce_dds_client/uxrce_dds_client.cpp'
    client_text = client.read_text()
    callback = client_text[client_text.index('static void on_time('):
                           client_text.index('static void on_time_no_sync(')]
    cpp = source.read_text()
    hpp = header.read_text()
    prefix = r"""
#include <cstdint>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
namespace time_literals {
constexpr uint64_t operator""_ms(unsigned long long value) { return value * 1000; }
}
#define PX4_DEBUG(...) do {} while (0)
#define ORB_ID(x) 0
uint64_t hrt_absolute_time() { return 1234; }
struct timesync_status_s {
static constexpr uint8_t SOURCE_PROTOCOL_UNKNOWN = 0;
uint8_t source_protocol{};
uint64_t remote_timestamp{}, round_trip_time{}, timestamp{};
int64_t observed_offset{}, estimated_offset{};
};
struct uxrSession { int64_t time_offset{}; };
timesync_status_s latest;
namespace uORB {
template<typename T> class PublicationMulti {
public: PublicationMulti(int) {} void publish(const T &value) { latest = value; }
};
}
"""
    # Preserve original license and filter code; substitute platform dependencies only.
    platform_header = hpp[hpp.index('using namespace time_literals;'):]
    filter_body = cpp[cpp.index('void Timesync::update'):]
    main = r"""
int main() {
constexpr int64_t epoch = 1790000000000000LL;
Timesync filter(2);
uxrSession session;
auto sample = [&](Timesync &f, uxrSession &s, int n, int64_t jump, int64_t rtt=100) {
uint64_t now = 1000000ULL + n * 1000ULL;
on_time(&s, now * 1000LL, 0, (now - rtt/2 + epoch + jump) * 1000LL,
        (now - rtt) * 1000LL, &f);
return now;
};
for (int n=0; n<500; ++n) sample(filter, session, n, 0);
assert(filter.sync_converged()); assert(filter.offset() == -epoch);
assert(session.time_offset == epoch * 1000LL);
uint64_t old_native = 0;
for (int n=500; n<510; ++n) old_native = sample(filter, session, n, 200000);
assert(filter.offset() == -epoch);
int64_t old_adjusted = old_native + session.time_offset / 1000;
uint64_t new_native = sample(filter, session, 510, 200000);
assert(filter.offset() == 0); assert(latest.estimated_offset == 0);
assert(session.time_offset == 0); assert(!filter.sync_converged());
assert(new_native > old_native);
assert((int64_t)new_native + session.time_offset / 1000 < old_adjusted);
sample(filter, session, 511, 200000);
assert(filter.offset() == -(epoch + 200000));
assert(session.time_offset / 1000 == epoch + 200000);
Timesync delayed(2); uxrSession delayed_session;
for (int n=0; n<500; ++n) sample(delayed, delayed_session, n, 0);
for (int n=500; n<530; ++n) sample(delayed, delayed_session, n, 200000, 20000);
assert(delayed.offset() == -epoch); assert(delayed.sync_converged());
Timesync boundary(2); uxrSession boundary_session;
for (int n=0; n<500; ++n) sample(boundary, boundary_session, n, 0);
sample(boundary, boundary_session, 500, 100000);
assert(boundary.offset() != 0); assert(boundary.sync_converged());
Timesync ramp(2); uxrSession ramp_session;
for (int n=0; n<500; ++n) sample(ramp, ramp_session, n, 0);
for (int n=500; n<511; ++n) sample(ramp, ramp_session, n, 200000 + (n-500)*10000);
assert(ramp.offset() == 0);
std::cout << "PASS actual PX4 filter and on_time callback: convergence, ns/us conversion, "
             "11 deviations, zero offset, ordered native/adjusted regression, recovery, "
             "high-RTT rejection, exact-threshold and synthetic clock ramp\n";
}
"""
    fixture = output / 'native_timesync_fixture.cpp'
    fixture.write_text(
        cpp[:cpp.index('#include')] + prefix + platform_header + filter_body + callback + main)
    binary = output / 'native_timesync_fixture'
    compiled = subprocess.run(['g++', '-std=c++17', str(fixture), '-o', str(binary)],
                              capture_output=True, text=True)
    executed = (subprocess.run([str(binary)], capture_output=True, text=True)
                if not compiled.returncode else None)
    report = {'client_callback_sha256': hashlib.sha256(callback.encode()).hexdigest(),
              'client_source_sha256': hashlib.sha256(client.read_bytes()).hexdigest(),
              'source_sha256': hashlib.sha256(source.read_bytes()).hexdigest(),
              'header_sha256': hashlib.sha256(header.read_bytes()).hexdigest(),
              'compile_returncode': compiled.returncode,
              'compile_output': compiled.stdout + compiled.stderr,
              'run_returncode': executed.returncode if executed else None,
              'run_output': executed.stdout + executed.stderr if executed else None,
              'scope': 'Actual retained filter methods, mocked platform, diagnostic fixture only; '
              'does not prove historical filter reset or cause of clock deviation.'}
    (output / 'native_timesync_check.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2), flush=True)
    return report
