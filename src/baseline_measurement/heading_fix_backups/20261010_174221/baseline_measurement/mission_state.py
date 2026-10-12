"""Deterministic, ROS-independent SITL mission policy (all time is monotonic)."""

from dataclasses import dataclass, field
import math


STAGES = ('TAKEOFF', 'WAYPOINT_1', 'WAYPOINT_2', 'WAYPOINT_3', 'RETURN_HOME')
TIMEOUTS = {
    'WAIT_FOR_PX4': 30., 'WAIT_FOR_HEALTH': 30., 'WAIT_FOR_HEADING': 30.,
    'PREFLIGHT_SETPOINT': 10.,
    'AUTO_TAKEOFF_REQUEST': 10., 'AUTO_ARM': 10.,
    'OFFBOARD': 10., 'ARM': 10., **dict.fromkeys(STAGES, 60.),
    'LAND': 90., 'DISARM': 15., 'FAILSAFE': 90.,
}


@dataclass
class Telemetry:
    """Latest validated telemetry; adapter supplies freshness and graph checks."""

    connected: bool = False
    healthy: bool = False
    valid: bool = False
    heading_ready: bool = False
    auto_takeoff_ready: bool = False
    taking_off: bool = False
    holding: bool = False
    armed: bool = False
    offboard: bool = False
    landing: bool = False
    landed: bool = False
    failsafe: bool = False
    competition: bool = False
    reset: bool = False
    position: tuple = (0., 0., 0.)
    velocity: tuple = (0., 0., 0.)


@dataclass
class Mission:
    """One bounded mission; returns commands as intents, never publishes itself."""

    start: float
    state: str = 'WAIT_FOR_PX4'
    entered: float = field(init=False)
    failure_state: str = ''
    failure_reason: str = ''
    reached: list = field(default_factory=list)
    home: tuple = None
    segment_start: tuple = None
    target: tuple = None
    hold_since: float = None
    last_tick: float = None
    stream_since: float = None
    last_command: float = -math.inf
    command_count: int = 0
    done: bool = False
    passed: bool = False
    events: list = field(default_factory=list)
    intents: list = field(default_factory=list)
    owned: bool = False
    auto_takeoff: bool = False

    def __post_init__(self):
        self.entered = self.start
        self.events.append(('INIT', self.start))

    def transition(self, state, now):
        self.state, self.entered = state, now
        self.hold_since = None
        self.last_command, self.command_count = -math.inf, 0
        self.events.append((state, now))

    def fail(self, reason, now):
        if self.failure_reason or self.done:
            return
        self.failure_state, self.failure_reason = self.state, reason
        self.transition('FAILSAFE', now)

    def command(self, name, now):
        # No retries: avoid ambiguous ACK matching and repeated arm/disarm actions.
        if self.command_count == 0:
            self.intents.append(name)
            self.command_count = 1
            self.last_command = now
            if name == 'ARM':
                self.owned = True

    def begin_stage(self, stage, now):
        self.segment_start = self.target or self.home
        offsets = ((0., 0.), (20., 0.), (20., 20.), (0., 20.), (0., 0.))
        x, y = offsets[STAGES.index(stage)]
        self.target = (self.home[0] + x, self.home[1] + y, self.home[2] - 10.)
        self.transition(stage, now)

    def setpoint(self, now):
        if self.state in ('PREFLIGHT_SETPOINT', 'OFFBOARD', 'ARM'):
            return self.target if self.auto_takeoff else self.home
        if self.auto_takeoff and self.state == 'TAKEOFF':
            return None  # PX4 Auto owns takeoff and handles its yaw alignment.
        if self.state not in STAGES:
            return None
        # Quintic position profile: zero velocity/acceleration at endpoints.
        # PX4 tracks position; velocity and acceleration feedforward remain NaN.
        u = min(1., max(0., (now - self.entered) / 15.))
        blend = 10*u**3 - 15*u**4 + 6*u**5
        return tuple(a + (b-a)*blend for a, b in zip(self.segment_start, self.target))

    def tick(self, now, t):
        self.intents = []
        if self.done:
            return []
        gap = 0. if self.last_tick is None else now - self.last_tick
        self.last_tick = now
        active = self.state not in ('WAIT_FOR_PX4', 'WAIT_FOR_HEALTH', 'FAILSAFE')
        if active:
            if not t.connected:
                self.fail('Telemetry stale or PX4 input subscribers absent', now)
            elif t.competition:
                self.fail('Another ROS publisher is controlling PX4', now)
            elif t.reset:
                self.fail('Estimator or source clock reset', now)
            elif t.failsafe:
                self.fail('PX4 reports failsafe', now)
            elif not t.valid:
                self.fail('Position or velocity invalid', now)
            elif not t.healthy:
                self.fail('PX4 health checks failed', now)
            elif (self.auto_takeoff and self.state in
                  ('AUTO_TAKEOFF_REQUEST', 'AUTO_ARM', 'TAKEOFF', 'WAIT_FOR_HEADING')
                  and not t.auto_takeoff_ready):
                self.fail('Auto takeoff estimator readiness lost', now)
            elif (self.state in ('PREFLIGHT_SETPOINT', 'OFFBOARD', 'ARM', *STAGES)
                  and not (self.auto_takeoff and self.state == 'TAKEOFF')
                  and not t.heading_ready):
                self.fail('Heading readiness lost during yaw control', now)
            elif gap > .25:
                self.fail('Control scheduling gap exceeded 250 ms', now)
        if self.state != 'FAILSAFE' and now - self.start > 480.:
            self.fail('Mission timeout', now)
        if now - self.entered > TIMEOUTS.get(self.state, math.inf):
            if self.state == 'FAILSAFE':
                self.done = True
                self.events.append(('FAILSAFE_UNCONFIRMED', now))
                return []
            self.fail('State timeout', now)
        if self.state == 'FAILSAFE':
            # Stop the normal heartbeat and trajectory. Never disarm in air.
            # A single land request is best effort; PX4 owns link-loss response.
            if self.owned and not (t.connected and not t.armed and t.landed):
                self.command('LAND', now)
            if not self.owned or (t.connected and t.landed and not t.armed):
                self.done = True
                self.events.append(('MISSION_FAIL', now))
            return list(self.intents)
        if self.state == 'WAIT_FOR_PX4':
            if t.connected:
                self.transition('WAIT_FOR_HEALTH', now)
        elif self.state == 'WAIT_FOR_HEALTH':
            if t.armed:
                self.fail('Vehicle already armed; refusing takeover', now)
            elif t.competition:
                self.fail('Competing controller detected', now)
            elif t.connected and t.healthy and t.valid and t.landed and not t.failsafe:
                self.hold_since = now if self.hold_since is None else self.hold_since
                if now - self.hold_since >= 2.:
                    self.transition('WAIT_FOR_HEADING', now)
            else:
                self.hold_since = None
        elif self.state == 'WAIT_FOR_HEADING':
            if self.auto_takeoff:
                if not t.armed or t.landed or not (t.taking_off or t.holding):
                    self.fail('PX4 Auto state lost while aligning heading', now)
                elif t.heading_ready:
                    self.hold_since = now if self.hold_since is None else self.hold_since
                    if now - self.hold_since >= 2.:
                        self.transition('PREFLIGHT_SETPOINT', now)
                        self.stream_since = now
                else:
                    self.hold_since = None
            elif t.armed or not t.landed:
                self.fail('Unsafe vehicle state while waiting for heading', now)
            elif t.heading_ready:
                self.home = tuple(t.position)
                self.target = self.home
                self.transition('PREFLIGHT_SETPOINT', now)
                self.stream_since = now
            elif t.auto_takeoff_ready:
                # This PX4 build completes magnetic alignment after takeoff.
                # Auto suppresses absolute yaw until ready; Offboard does not.
                self.auto_takeoff = True
                self.home = tuple(t.position)
                self.target = self.home
                self.transition('AUTO_TAKEOFF_REQUEST', now)
        elif self.state == 'AUTO_TAKEOFF_REQUEST':
            if t.armed or not t.landed:
                self.fail('Unsafe state before automatic takeoff', now)
            elif t.taking_off:
                self.transition('AUTO_ARM', now)
            else:
                self.command('AUTO_TAKEOFF', now)
        elif self.state == 'AUTO_ARM':
            if not t.taking_off:
                self.fail('Auto takeoff mode lost before arming', now)
            elif t.armed:
                self.begin_stage('TAKEOFF', now)
            elif not t.landed:
                self.fail('Unexpected flight before arming', now)
            else:
                self.command('ARM', now)
        elif self.state == 'PREFLIGHT_SETPOINT':
            unsafe = ((not t.armed or t.landed or not (t.taking_off or t.holding))
                      if self.auto_takeoff else (t.armed or not t.landed))
            if unsafe or not t.healthy:
                self.fail('Preflight state changed', now)
            elif now - self.stream_since >= 2.:
                self.transition('OFFBOARD', now)
        elif self.state == 'OFFBOARD':
            unsafe = ((not t.armed or t.landed or
                       not (t.offboard or t.taking_off or t.holding))
                      if self.auto_takeoff else (t.armed or not t.landed))
            if unsafe or not t.healthy:
                self.fail('Unsafe state before arming', now)
            elif t.offboard:
                if self.auto_takeoff:
                    self.begin_stage('WAYPOINT_1', now)
                else:
                    self.transition('ARM', now)
            else:
                self.command('OFFBOARD', now)
        elif self.state == 'ARM':
            if not t.offboard:
                self.fail('Offboard mode lost before arming', now)
            elif t.armed:
                self.begin_stage('TAKEOFF', now)
            elif not t.healthy or not t.landed:
                self.fail('Health changed before arming', now)
            else:
                self.command('ARM', now)
        elif self.state in STAGES:
            mode_ok = ((t.taking_off or t.holding)
                       if self.auto_takeoff and self.state == 'TAKEOFF' else t.offboard)
            if not t.armed or not mode_ok:
                self.fail('Armed/offboard state lost in flight', now)
            else:
                error = math.dist(t.position, self.target)
                speed = math.sqrt(sum(v*v for v in t.velocity))
                settled = error <= .7 and speed <= .5 and not t.landed
                if now - self.entered >= 15. and settled:
                    self.hold_since = now if self.hold_since is None else self.hold_since
                    if now - self.hold_since >= 2.:
                        stage = self.state
                        self.reached.append(stage)
                        self.events.append((stage + '_REACHED', now))
                        i = STAGES.index(stage)
                        if i == len(STAGES)-1:
                            self.transition('LAND', now)
                        elif self.auto_takeoff and stage == 'TAKEOFF':
                            self.transition('WAIT_FOR_HEADING', now)
                        else:
                            self.begin_stage(STAGES[i+1], now)
                else:
                    self.hold_since = None
        elif self.state == 'LAND':
            if t.landed:
                self.hold_since = now if self.hold_since is None else self.hold_since
                if now - self.hold_since >= 2.:
                    self.events.append(('LANDED', now))
                    self.transition('DISARM', now)
            elif not t.armed:
                self.fail('Disarmed without confirmed landing', now)
            else:
                self.hold_since = None
                self.command('LAND', now)
                if now - self.entered > 8. and not t.landing:
                    self.fail('Auto land mode not observed', now)
        elif self.state == 'DISARM':
            if not t.landed:
                self.fail('Landing confirmation lost', now)
            elif not t.armed:
                if self.reached != list(STAGES) or self.failure_reason:
                    self.fail('Required mission stages missing', now)
                else:
                    self.passed = True
                    self.done = True
                    self.transition('COMPLETE', now)
            else:
                self.command('DISARM', now)
        return list(self.intents)
