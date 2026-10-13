"""Plot actual revalidated historical runs; no synthetic observations are included."""
import json
from pathlib import Path

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

output = Path(__file__).parent / 'final_report'
runs = json.loads((output / 'active_runs.json').read_text())
labels = [Path(r['source_file']).parent.name.rsplit('_', 1)[1] for r in runs]
fig, axes = plt.subplots(1, 3, figsize=(12, 3.7), constrained_layout=True)
for axis, key, title, unit in zip(
    axes, ('mission_completion_s', 'node_cpu_pct', 'node_rss_mib'),
    ('Mission duration including preflight', 'Mission process CPU', 'Mission process RSS'),
    ('seconds', '% of one logical CPU', 'MiB')
):
    axis.bar(labels, [r['metrics'][key] for r in runs], color='#3269a8')
    axis.set_title(title, fontsize=10)
    axis.set_xlabel('Active run')
    axis.set_ylabel(unit)
    axis.grid(axis='y', alpha=.25)
fig.suptitle('Five historical active SITL missions — raw evidence revalidated', fontsize=12)
fig.savefig(output / 'active_duration_resources.png', dpi=180)
plt.close(fig)
fig, axis = plt.subplots(figsize=(7, 4), constrained_layout=True)
positions = list(range(len(runs)))
axis.bar([i - .18 for i in positions], [r['metrics']['rx_payload_mbps'] for r in runs],
         width=.36, label='Received CDR payload')
axis.bar([i + .18 for i in positions], [r['metrics']['tx_payload_mbps'] for r in runs],
         width=.36, label='Publish-call CDR payload')
axis.set_xticks(positions, labels)
axis.set_xlabel('Active run')
axis.set_ylabel('Mbit/s over whole monotonic run')
axis.set_title('Serialized ROS payload throughput — excludes transport headers')
axis.legend()
axis.grid(axis='y', alpha=.25)
fig.savefig(output / 'active_payload_throughput.png', dpi=180)
plt.close(fig)
