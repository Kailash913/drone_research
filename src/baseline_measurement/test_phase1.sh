#!/usr/bin/env bash
# Functional acceptance tests only; package linters remain in colcon test.
set -eo pipefail
cd "$(dirname "$0")/../.."
source /opt/ros/jazzy/setup.bash
source install/setup.bash
python3 -m pytest src/baseline_measurement/test/test_phase1.py \
    src/baseline_measurement/test/test_baseline_new.py \
    src/baseline_measurement/test/test_preflight.py \
    src/baseline_measurement/test/test_acceptance.py -q
