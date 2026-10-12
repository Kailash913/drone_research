# Timestamp findings — production correction NOT APPLIED

The proximate mechanism in diagnostic BASE-001 is strongly supported: the DDS Timesync filter discarded its converged offset, the generated serializer immediately delivered native simulation timestamps, and the controller correctly treated the backwards source timestamps as a discontinuity. It is not proof of an EKF reset. The runtime cause of the qualifying clock deviations remains UNPROVEN.

## Exact clock path

Native uORB `timestamp` and `timestamp_sample` are uint64 microseconds. This SITL build enables lockstep: Gazebo sim time feeds PX4 CLOCK_MONOTONIC; hrt_absolute_time reads the scheduler's simulated time. The XRCE SDK custom PX4 uxr_nanos returns hrt_absolute_time()*1000 nanoseconds. Agent get_epoch_time uses high_resolution_clock; the actual compiled fixture confirms its system_clock alias in this environment. These are independently progressing clocks.

The SDK timestamp-reply callback passes client receive time, Agent receive t1, Agent transmit t2, and client originate t0. PX4's callback parameter names misleadingly identify t2 as agent_receive_timestamp; Timesync actually receives Agent transmit t2. This naming discrepancy is documented, not patched. Offset = (originate/1000 + native_now - 2*Agent_transmit/1000)/2 us; RTT = native_now - originate/1000 us. DDS protocol is 2. Only native-clock RTT <10000 us is accepted; after convergence, deviation >100000 us increments the high-deviation count. Count >10 resets the filter (eleventh qualifying sample). High-RTT rejection does not clear that count; an accepted ordinary sample does. The source comment saying five consecutive is stale.

on_time stores -Timesync.offset()*1000 ns in session.time_offset. The DDS send template converts ns/1000 to us, and generated serializers add it to BOTH timestamp fields. At reset, the offset is zero. px4_msgs delivers the adjusted uint64 fields without normalization. The ROS adapter consumes timestamp for ordering; logging retains it as source_timestamp_us. Receive freshness uses local time.monotonic, with a separate source-progress watchdog so repeated timestamps cannot indefinitely renew validity. The latched airborne guard sends the existing mission to FAILSAFE. Actual reset counters are independent evidence; expected bootstrap yaw-reset handling and guarded grounded completion remain unchanged.

## Correlated evidence

At 2026-10-11 18:07:01.748566 UTC DDS estimated offset changes -1791735387918623 us to 0. Position at 18:07:01.749219 changes 1791742020006623 to 6632104000 us; attitude follows. Native contemporaneous ULog stays ordered, has zero dropouts, and all captured position/velocity/heading/quaternion reset counters remain unchanged across the whole log. The next accepted sample restores a large offset. Actual-source fixtures reproduce the eleven-sample reset, serializer-sized discontinuity, and recovery deterministically using labelled synthetic inputs. No test fixture is an experiment.

Eight captured pre-reset DDS samples qualify if converged, with native RTT <=4000 us. Endpoint progression reconstructed algebraically from remote_timestamp + observed_offset gives cumulative native-midpoint/Agent progression ratio 0.8508925233 before reset. This establishes endpoint progression mismatch, not calibrated telemetry latency; the capture does not contain all eleven triggering samples.

## Hypotheses and uncertainty

Confirmed: serializer conversion switches domains when filter offset resets; native estimator counters do not support a genuine reset in this event. Strongly supported: differing simulation/client and epoch/Agent progression drives the observed offset departures. Unproven alternatives: Gazebo clock pauses/catch-up, WSL scheduling, OS clock rate adjustment, host/guest clock instability, and transport processing delay. Reported native RTT is simulation-time based: small values do NOT exclude real delivery delay while simulation time stalls.

A receiver wall-minus-monotonic step of approximately +1.984 s occurs AFTER failure, so it cannot establish the cause of the earlier event. A later passive Gazebo window has sim/server-real delta ratio approximately 0.999999685 with reported RTF 0.5501–1.8105. This excludes sustained slowdown in that particular window, not historical slowdown. A still later WSL clock sample gives MONOTONIC 14.93265 s and RAW 15.99419 s; REALTIME tracks MONOTONIC. This is evidence of rate disagreement in that later sample, not contemporaneous causal attribution. WSL uses tsc, time synchronization is active; the retained journal does not show a synchronization event at the failure. No clock service or time source was changed.

Source revision, generated serializers, compile definitions, and running binary fingerprints are retained. They provide strong installed identity evidence, not a byte-for-byte reproducible rebuild of the Agent/PX4 binaries. Historical reversals in runs 015/021/043/045 lack synchronized native/offset evidence; do not transfer this diagnosis to each historical failure as proven.

## Closure and safety

Production correction is NOT APPLIED. All current source-ordering, local freshness, actual reset, heading and failsafe checks remain in place. Obtain simultaneous Gazebo sim/server-real, client t0/receive, Agent t1/t2 and OS realtime/monotonic/raw observations spanning a reset to discriminate causes. A future native-clock proposal must coordinate incoming DDS timestamps and outgoing command/setpoint headers, prove native ordering while grounded, and retain genuine-reset/staleness tests. Parameter changes/client restart, live controller changes and flight tests require explicit authorization. See unapplied_clock_proposal.md. Never simply ignore epoch-to-boot reversals.

The final paired passive capture spans 15 seconds and again observes a DDS offset-to-zero transition. Its captured pre-transition native-midpoint/Agent progression ratio is 0.9862905854, demonstrating variable clock disagreement rather than one universal slowdown factor. It does not establish the cause of the earlier flight failure. See analysis/paired_passive_latest.json.
