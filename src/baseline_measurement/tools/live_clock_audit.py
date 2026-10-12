"""Inspect the live stack and native parameters without flight commands."""
import json
from pathlib import Path
import struct
import subprocess
import time

from baseline_measurement.mission_node import simulation_processes
import psutil
from pymavlink import mavutil
from tools.authorized_study import observe

package = Path(__file__).resolve().parents[1]
out = package / 'test-output' / ('live_clock_audit_' + time.strftime('%Y%m%d_%H%M%S'))
out.mkdir()
report = {'flight_commands_sent': 0, 'parameter_writes': 0, 'processes': []}
for p in psutil.process_iter(['pid', 'name', 'cmdline']):
    if any(x in (p.info['name'] or '').lower() for x in ('px4', 'agent', 'gz', 'mission')):
        report['processes'].append(p.info)
report['git'] = subprocess.run(['git', 'status', '--short', '--branch'], cwd=package,
                               capture_output=True, text=True).stdout
(out / 'initial.json').write_text(json.dumps(report, indent=2))
report['preflight'] = observe(package / 'config/baseline.yaml', out, release_offboard=False)
# Verify the observed PX4 socket against the local startup port formula.
px4 = simulation_processes()['px4']
args = psutil.Process(px4[0]).cmdline()
ports = {c.laddr.port for c in psutil.Process(px4[0]).connections(kind='udp')}
report['px4_udp_ports'] = sorted(ports)
if len(px4) != 1 or 14580 not in ports:
    raise RuntimeError('Confirm actual PX4 instance before MAVLink parameter reads')
link = mavutil.mavlink_connection('udpin:127.0.0.1:14540', source_system=246)
hb = None
until = time.monotonic() + 10
while time.monotonic() < until:
    candidate = link.recv_match(type='HEARTBEAT', blocking=True, timeout=0.2)
    if candidate and candidate.autopilot == mavutil.mavlink.MAV_AUTOPILOT_PX4:
        hb = candidate
        link.target_system = hb.get_srcSystem()
        link.target_component = hb.get_srcComponent()
        break
report['mavlink_heartbeat'] = hb.to_dict() if hb else None
report['parameters'] = {}
if hb:
    for name in ('UXRCE_DDS_SYNCT', 'UXRCE_DDS_PRT', 'UXRCE_DDS_DOM_ID'):
        link.mav.param_request_read_send(link.target_system, link.target_component,
                                         name.encode(), -1)
        until = time.monotonic() + 5
        while time.monotonic() < until:
            msg = link.recv_match(type='PARAM_VALUE', blocking=True, timeout=0.2)
            if msg and msg.param_id == name:
                report['parameters'][name] = msg.to_dict()
                if msg.param_type == mavutil.mavlink.MAV_PARAM_TYPE_INT32:
                    report['parameters'][name]['decoded_int32'] = struct.unpack(
                        '<i', struct.pack('<f', msg.param_value))[0]
                break
link.close()
(out / 'report.json').write_text(json.dumps(report, indent=2))
print(json.dumps(report, indent=2), flush=True)
print('LIVE_AUDIT_OUTPUT=' + str(out), flush=True)
