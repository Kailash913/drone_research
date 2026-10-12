/****************************************************************************
 *
 *   Copyright (c) 2018-2022 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file Timesync.cpp
 * timesync implementation.
 *
 * @author Mohammed Kabir <mhkabir98@gmail.com>
 */


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
using namespace time_literals;

static constexpr time_t PX4_EPOCH_SECS = 1234567890ULL;

// Filter gains
//
// Alpha : Used to smooth the overall clock offset estimate. Smaller values will lead
// to a smoother estimate, but track time drift more slowly, introducing a bias
// in the estimate. Larger values will cause low-amplitude oscillations.
//
// Beta : Used to smooth the clock skew estimate. Smaller values will lead to a
// tighter estimation of the skew (derivative), but will negatively affect how fast the
// filter reacts to clock skewing (e.g cause by temperature changes to the oscillator).
// Larger values will cause large-amplitude oscillations.
static constexpr double ALPHA_GAIN_INITIAL = 0.05;
static constexpr double BETA_GAIN_INITIAL = 0.05;
static constexpr double ALPHA_GAIN_FINAL = 0.003;
static constexpr double BETA_GAIN_FINAL = 0.003;

// Filter gain scheduling
//
// The filter interpolates between the INITIAL and FINAL gains while the number of
// exhanged timesync packets is less than CONVERGENCE_WINDOW. A lower value will
// allow the timesync to converge faster, but with potentially less accurate initial
// offset and skew estimates.
static constexpr uint32_t CONVERGENCE_WINDOW = 500;

// Outlier rejection and filter reset
//
// Samples with round-trip time higher than MAX_RTT_SAMPLE are not used to update the filter.
// More than MAX_CONSECUTIVE_HIGH_RTT number of such events in a row will throw a debug message
// but not reset the filter.
// Samples whose calculated clock offset is more than MAX_DEVIATION_SAMPLE off from the current
// estimate are not used to update the filter. More than MAX_CONSECUTIVE_HIGH_DEVIATION number
// of such events in a row will reset the filter. This usually happens only due to a time jump
// on the remote system.
// TODO : automatically determine these using ping statistics?
static constexpr uint64_t MAX_RTT_SAMPLE = 10_ms;
static constexpr uint64_t MAX_DEVIATION_SAMPLE = 100_ms;
static constexpr uint32_t MAX_CONSECUTIVE_HIGH_RTT = 10;
static constexpr uint32_t MAX_CONSECUTIVE_HIGH_DEVIATION = 10;

class Timesync
{
public:
	Timesync(uint8_t source = timesync_status_s::SOURCE_PROTOCOL_UNKNOWN) : _source(source) {};
	~Timesync() = default;

	void update(const uint64_t now_us, const int64_t remote_timestamp_ns, int64_t originate_timestamp_ns);

	/**
	 * Convert remote timestamp to local hrt time (usec)
	 * Use synchronised time if available, monotonic boot time otherwise
	 */
	uint64_t sync_stamp(uint64_t usec);

	int64_t offset() const { return (int64_t)_time_offset; }

	/**
	 * Return true if the timesync algorithm converged to a good estimate,
	 * return false otherwise
	 */
	bool sync_converged() const { return _sequence >= CONVERGENCE_WINDOW; }

	/**
	 * Reset the exponential filter and its states
	 */
	void reset_filter();


private:

	/**
	 * Online exponential filter to smooth time offset
	 */
	void add_sample(int64_t offset_us);
	uORB::PublicationMulti<timesync_status_s>  _timesync_status_pub{ORB_ID(timesync_status)};

	uint32_t _sequence{0};

	// Timesync statistics
	double _time_offset{0};
	double _time_skew{0};

	// Filter parameters
	double _filter_alpha{ALPHA_GAIN_INITIAL};
	double _filter_beta{BETA_GAIN_INITIAL};

	// Outlier rejection and filter reset
	uint32_t _high_deviation_count{0};
	uint32_t _high_rtt_count{0};

	uint8_t _source{};
};
void Timesync::update(const uint64_t now_us, const int64_t remote_timestamp_ns, const int64_t originate_timestamp_ns)
{
	// Message originating from this system, compute time offset from it
	if (remote_timestamp_ns > 0) {
		// Calculate time offset between this system and the remote system, assuming RTT for
		// the timesync packet is roughly equal both ways.
		int64_t offset_us = (int64_t)((originate_timestamp_ns / 1000ULL) + now_us - (remote_timestamp_ns / 1000ULL) * 2) / 2 ;

		// Calculate the round trip time (RTT) it took the timesync packet to bounce back to us from remote system
		uint64_t rtt_us = now_us - (originate_timestamp_ns / 1000ULL);

		// Calculate the difference of this sample from the current estimate
		uint64_t deviation = llabs((int64_t)_time_offset - offset_us);

		if (rtt_us < MAX_RTT_SAMPLE) {	// Only use samples with low RTT

			if (sync_converged() && (deviation > MAX_DEVIATION_SAMPLE)) {

				// Increment the counter if we have a good estimate and are getting samples far from the estimate
				_high_deviation_count++;

				// We reset the filter if we received 5 consecutive samples which violate our present estimate.
				// This is most likely due to a time jump on the offboard system.
				if (_high_deviation_count > MAX_CONSECUTIVE_HIGH_DEVIATION) {
					PX4_DEBUG("time jump detected. Resetting time synchroniser.");
					// Reset the filter
					reset_filter();
				}

			} else {

				// Filter gain scheduling
				if (!sync_converged()) {
					// Interpolate with a sigmoid function
					const float progress = (float) _sequence / (float) CONVERGENCE_WINDOW;
					double p = (double)(1.f - expf(0.5f * (1.f - 1.f / (1.f - progress))));
					_filter_alpha = p * ALPHA_GAIN_FINAL + (1.0 - p) * ALPHA_GAIN_INITIAL;
					_filter_beta = p * BETA_GAIN_FINAL + (1.0 - p) * BETA_GAIN_INITIAL;

				} else {
					_filter_alpha = ALPHA_GAIN_FINAL;
					_filter_beta = BETA_GAIN_FINAL;
				}

				// Perform filter update
				add_sample(offset_us);

				// Increment sequence counter after filter update
				_sequence++;

				// Reset high deviation count after filter update
				_high_deviation_count = 0;

				// Reset high RTT count after filter update
				_high_rtt_count = 0;
			}

		} else {
			// Increment counter if round trip time is too high for accurate timesync
			_high_rtt_count++;

			if (_high_rtt_count == MAX_CONSECUTIVE_HIGH_RTT) {
				PX4_DEBUG("RTT too high for timesync: %llu ms", rtt_us / 1000ULL);
			}
		}

		// Publish status message
		timesync_status_s tsync_status{};
		tsync_status.source_protocol = _source;
		tsync_status.remote_timestamp = remote_timestamp_ns / 1000ULL;
		tsync_status.observed_offset = offset_us;
		tsync_status.estimated_offset = (int64_t)_time_offset;
		tsync_status.round_trip_time = rtt_us;
		tsync_status.timestamp = hrt_absolute_time();

		_timesync_status_pub.publish(tsync_status);
	}
}

uint64_t Timesync::sync_stamp(uint64_t usec)
{
	// Only return synchronised stamp if we have converged to a good value
	if (sync_converged()) {
		return usec + (int64_t)_time_offset;

	} else {
		return hrt_absolute_time();
	}
}

void Timesync::add_sample(int64_t offset_us)
{
	// Online exponential smoothing filter. The derivative of the estimate is also
	// estimated in order to produce an estimate without steady state lag:
	// https://en.wikipedia.org/wiki/Exponential_smoothing#Double_exponential_smoothing
	double time_offset_prev = _time_offset;

	if (_sequence == 0) {
		// First offset sample
		_time_offset = offset_us;

	} else {
		// Update the clock offset estimate
		_time_offset = _filter_alpha * offset_us + (1.0 - _filter_alpha) * (_time_offset + _time_skew);

		// Update the clock skew estimate
		_time_skew = _filter_beta * (_time_offset - time_offset_prev) + (1.0 - _filter_beta) * _time_skew;
	}
}

void Timesync::reset_filter()
{
	// Do a full reset of all statistics and parameters
	_sequence = 0;
	_time_offset = 0.0;
	_time_skew = 0.0;
	_filter_alpha = ALPHA_GAIN_INITIAL;
	_filter_beta = BETA_GAIN_INITIAL;
	_high_deviation_count = 0;
	_high_rtt_count = 0;
}
static void on_time(uxrSession *session, int64_t current_time, int64_t client_transmit_timestamp,
		    int64_t agent_receive_timestamp, int64_t originate_timestamp, void *args)
{
	if (args) {
		Timesync *timesync = static_cast<Timesync *>(args);
		timesync->update(current_time / 1000, agent_receive_timestamp, originate_timestamp);

		session->time_offset = -timesync->offset() * 1000; // us -> ns
	}
}


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
