"""Complete new report artifacts without changing operational code or raw results."""
import csv
import hashlib
import json
from pathlib import Path
import shutil
import sys

home = Path(r'\\wsl.localhost\Ubuntu-24.04\home\kailash')
package = home / 'ros2_ws/src/baseline_measurement'
audit = package / 'test-output/phase1_master_20261011_185629_UTC'
output = Path('outputs/phase1_master_20261011_185629_UTC').resolve()
sys.path.insert(0, str(package))
from baseline_measurement.diagnostic_analysis import dds_deviations


def read(path):
    return json.loads(path.read_text(encoding='utf-8'))


def save(name, value):
    text = json.dumps(value, indent=2) + '\n' if not isinstance(value, str) else value
    for root in (audit, output):
        (root / name).parent.mkdir(exist_ok=True, parents=True)
        (root / name).write_text(text, encoding='utf-8')


references = read(audit / 'source_references.json')
for entry in references:
    if entry.get('missing') and entry['path'].endswith(('VehicleLocalPosition.msg', 'VehicleAttitude.msg')):
        relative = entry['path'].replace('/msg/', '/msg/versioned/')
        path = home / relative
        lines = path.read_text().splitlines()
        entry.clear()
        entry.update(path='/home/kailash/' + relative,
                     sha256=hashlib.sha256(path.read_bytes()).hexdigest(),
                     matches=[{'line': n, 'text': line.strip()} for n, line in enumerate(lines, 1)
                              if any(s in line for s in ['timestamp', 'reset_counter', 'heading_good'])])
save('source_references.json', references)

inventory = read(audit / 'combined_inventory.json')
comparison = []
for cohort in inventory['cohorts']:
    prior_path = package / 'test-output/final_reports_20261011_183812' / cohort['study'] / 'manifest.json'
    previous = read(prior_path)
    current = [r for r in inventory['records'] if r['inventory_study'] == cohort['study']]
    old_ids = {r['sha256']: r['experiment_id'] for r in previous['records']
               if r.get('experiment_id') and r['mode'] == 'SITL_MISSION'}
    actual = {r['sha256']: r['experiment_id'] for r in current}
    mismatches = {h: {'old': value, 'new': actual.get(h)}
                  for h, value in old_ids.items() if actual.get(h) != value}
    assert not mismatches
    comparison.append({'study': cohort['study'], 'prior_manifest': str(prior_path),
                       'assigned_original_or_prior_ids_checked': len(old_ids),
                       'mismatches': mismatches, 'identities_preserved': True})
save('identity_preservation.json', comparison)
recovery = read(audit / 'verification_193155/provenance.json')
save('historical_provenance_findings.json', {
    'records_audited': len(recovery['records']),
    'records_with_at_least_one_retained_source_byte_match': sum(
        any(v['retained_matches'] for v in r['source_identity'].values()) for r in recovery['records']),
    'missing_original_metadata_fields': ['experiment_id', 'run_id', 'config_file',
                                         'config_sha256', 'px4_version', 'simulator_version'],
    'original_yaml_or_environment_backfilled_from_current_files': False,
    'strict_historical_valid': 0,
    'interpretation': 'Source byte identity does not recover execution configuration or environment.'})

metrics = []
for cohort in inventory['cohorts']:
    manifest = read(audit / 'verification_193155' / ('validator_' + cohort['study']) / 'manifest.json')
    metrics.append({'study': cohort['study'], 'definitions': manifest['metric_definitions'],
                    'statistics_by_configuration': manifest['group_statistics'],
                    'metric_provenance_by_raw_sha256': {r['sha256']: r.get('provenance', {})
                                                       for r in manifest['records']},
                    'confidence_intervals': 'WITHHELD: independence and full configuration equivalence unverified'})
save('metric_quality.json', metrics)

probe = next((audit / 'verification_193155/paired_passive').glob('*.csv'))
with probe.open(newline='', encoding='utf-8') as stream:
    rows = list(csv.DictReader(stream))
messages = [r for r in rows if r['record_type'] == 'message']
dds = [{'utc': r['utc'], 'receive_monotonic_s': float(r['local_monotonic_s']),
        **json.loads(r['detail'])} for r in messages if r['topic'] == '/fmu/out/timesync_status']
diagnosis = dds_deviations(dds)
intervals = diagnosis['intervals_before_first_zero']
save('analysis/paired_passive_latest.json', {
    'source': str(probe), 'source_sha256': hashlib.sha256(probe.read_bytes()).hexdigest(),
    'duration_monotonic_s': float(rows[-1]['elapsed_s']),
    'dds': diagnosis,
    'native_midpoint_to_agent_progression_ratio_before_first_zero': (
        sum(r['native_midpoint_delta_us'] for r in intervals) /
        sum(r['peer_delta_us'] for r in intervals) if intervals else None),
    'not_latency_measurement': True, 'not_historical_cause_proof': True})

repro = (audit / 'REPRODUCE.md').read_text(encoding='utf-8')
repro = repro.replace('python3 tools/native_timesync_check.py --help\npython3 tools/native_heading_check.py --help',
                     'python3 -m pytest test/test_report_analysis.py -q  # actual-source fixtures included')
repro += '''
Explicit per-study validation, retaining assigned IDs (all currently return 2):

```bash
cd ~/ros2_ws/src/baseline_measurement
validation_dir="test-output/revalidation_$(date -u +%Y%m%d_%H%M%S)"
for study in baseline_results phase1_study_36527160a48f phase1_study_c57f5de2b96a; do
  input="$HOME/ros2_ws/baseline_results"
  if [ "$study" != baseline_results ]; then input="$input/$study"; fi
  python3 -m baseline_measurement.dataset --input "$input" \\
    --prior-manifest "test-output/phase1_master_20261011_185629_UTC/verification_193155/validator_$study/manifest.json" \\
    --output "$validation_dir/$study"
  printf 'validator %s exit=%s\\n' "$study" "$?"
done
```
'''
save('REPRODUCE.md', repro)
for name in ['FINAL_PHASE1_REPORT.md', 'metric_definitions_and_quality.md']:
    text = (audit / name).read_text(encoding='utf-8')
    text = text.replace('including defensible intervals.',
                        'with 95% confidence intervals explicitly withheld because independence and full configuration equivalence are unverified.')
    text = text.replace('and 95% intervals where supported are in the cohort manifests.',
                        'are in the cohort manifests. 95% confidence intervals are withheld because independence and full configuration equivalence are unverified.')
    save(name, text)
qgc = '''# QGroundControl plan path — inspection finding

The baseline ROS mission drives OFFBOARD setpoints through XRCE-DDS. qgc_plan.py generates a .plan file for inspection from the retained home/reference and route. Exporting that file is not a MAVLink mission upload. This code path does not implement MISSION_COUNT / MISSION_ITEM_INT / MISSION_ACK transfer into the PX4 mission store. Therefore absence of a QGC onboard Plan is not demonstrated to be caused by missing ROS telemetry, and a successful OFFBOARD flight would not by itself prove QGC mission upload.

Existing raw .plan exports are preserved. No upload, QGC flight control or new mission was performed. Current QGC/MAVLink mission-transfer acceptance remains BLOCKED pending explicit Plan load/upload and matching MAVLink acknowledgment/read-back evidence, if the roadmap requires an onboard MAVLink mission rather than ROS OFFBOARD control. A screen read was occluded by VS Code and is not counted as verified QGC connection evidence. Do not silently replace the existing controller with QGC AUTO mission behavior.
'''
save('qgc_plan_findings.md', qgc)
save('metric_definitions_and_quality.md', (audit / 'metric_definitions_and_quality.md').read_text(encoding='utf-8') +
     '\nDiagnostic resource capture contains 18 retained valid samples with 17 observed intervals: mean 1.023586 s, range 0.994792–1.057056 s. Per-run sample lines and intervals are retained in metric_quality.json. Configuration groups use known recorded fields; unknown historical environment equivalence remains a limitation.\n')

# Provide portable re-analysis source as evidence, outside the operational package.
portable = Path('work/phase1_continuation/analyze_master.py').read_text(encoding='utf-8')
portable = portable.replace("home = Path(r'\\\\wsl.localhost\\Ubuntu-24.04\\home\\kailash')", 'home = Path.home()')
portable = portable.replace("out = audit / 'analysis'", "import argparse\nparser = argparse.ArgumentParser()\nparser.add_argument('--output', required=True, help='New destination for regenerated analysis')\nargs = parser.parse_args()\nout = Path(args.output)\nassert not out.exists(), 'Use a new evidence destination'")
portable = portable.replace("sys.path.insert(0, str(Path('work').resolve()))\n", '')
save('reproduce_timestamp_analysis.py', portable)
save('REPRODUCE.md', (audit / 'REPRODUCE.md').read_text(encoding='utf-8') +
     '\nNative/ROS evidence re-analysis uses the existing pyulog installation (no install required):\n```bash\npython3 test-output/phase1_master_20261011_185629_UTC/reproduce_timestamp_analysis.py --output test-output/unique_new_clock_analysis\n```\n')
shutil.copy2(Path(__file__), audit / 'finish_master_evidence.py')
shutil.copy2(Path(__file__), output / 'finish_master_evidence.py')
print(json.dumps({'identities': comparison, 'paired_capture': str(probe),
                  'paired_pre_zero_ratio': read(audit / 'analysis/paired_passive_latest.json')['native_midpoint_to_agent_progression_ratio_before_first_zero']}, indent=2))
