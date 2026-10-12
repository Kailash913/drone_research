# Reproduce offline verification (no arming or movement)

```bash
source /opt/ros/jazzy/setup.bash
source ~/ros2_ws/install/setup.bash
cd ~/ros2_ws/src/baseline_measurement
python3 -m pytest test -q --junitxml=test-output/reproduced_full_suite.xml
python3 -m pytest test/test_report_analysis.py -q  # actual-source fixtures included
python3 tools/final_report_runner.py
python3 tools/reports_only_verify.py --audit test-output/phase1_master_20261011_185629_UTC
cd ~/ros2_ws
colcon build --packages-select baseline_measurement
```

The actual native fixture compile/run arguments and validator arguments including prior manifests are preserved verbatim in actual_verification.json and verification_*/verification.json. Dataset validators return 2 for incomplete Phase 1; that is a successful rejection, not a crash. final_report_runner returns nonzero for actual test/build/preservation failures. Neither full suite nor these tools publish vehicle commands. reports_only_verify additionally takes a bounded passive DDS/Gazebo capture; requires running SITL but does not restart it.

Use unique new output directories for reanalysis; preserve all historical files. Keep historical/new/empty studies separate. For terminal screenshots, manually display the full test result, build result, validator exit code and study summary, showing commands and output; screenshots are optional supplemental evidence, not substitutes for retained logs. No flight demonstration screenshot was fabricated or claimed. Current source references and configuration hashes are bundled, historical missing metadata remains missing.

Explicit per-study validation, retaining assigned IDs (all currently return 2):

```bash
cd ~/ros2_ws/src/baseline_measurement
validation_dir="test-output/revalidation_$(date -u +%Y%m%d_%H%M%S)"
for study in baseline_results phase1_study_36527160a48f phase1_study_c57f5de2b96a; do
  input="$HOME/ros2_ws/baseline_results"
  if [ "$study" != baseline_results ]; then input="$input/$study"; fi
  python3 -m baseline_measurement.dataset --input "$input" \
    --prior-manifest "test-output/phase1_master_20261011_185629_UTC/verification_193155/validator_$study/manifest.json" \
    --output "$validation_dir/$study"
  printf 'validator %s exit=%s\n' "$study" "$?"
done
```

Native/ROS evidence re-analysis uses the existing pyulog installation (no install required):
```bash
python3 test-output/phase1_master_20261011_185629_UTC/reproduce_timestamp_analysis.py --output test-output/unique_new_clock_analysis
```
