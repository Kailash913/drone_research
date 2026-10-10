"""Read-only process accounting for WSL simulation components."""

import os

import psutil


def role_for(name, cmdline, own_pid):
    name = (name or '').lower()
    command = ' '.join(cmdline or []).lower()
    if own_pid:
        return 'measurement_node'
    if name == 'px4' and 'px4_sitl' in command:
        return 'px4_sitl'
    if 'microxrceagent' in name or 'microxrceagent' in command:
        return 'xrce_agent'
    if name.startswith('gz') and ('sim' in command or 'server' in name):
        return 'gazebo_sim'
    return None


class ResourceMonitor:
    """Re-scan each interval to tolerate missing or restarted processes."""

    def __init__(self):
        self.primed = set()

    def sample(self):
        result = []
        seen = set()
        for process in psutil.process_iter(['pid', 'name', 'cmdline']):
            try:
                pid = process.info['pid']
                role = role_for(process.info['name'], process.info['cmdline'], pid == os.getpid())
                if role is None:
                    continue
                seen.add(pid)
                cpu = process.cpu_percent(None)
                if pid not in self.primed:
                    self.primed.add(pid)
                    cpu = None  # first call is a primer, not a measurement
                rss = process.memory_info().rss / (1024**2)
                result.append((role, pid, cpu, rss))
            except (psutil.NoSuchProcess, psutil.AccessDenied, psutil.ZombieProcess):
                continue
        self.primed.intersection_update(seen)
        return result
