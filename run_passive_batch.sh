#!/usr/bin/env bash
set -uo pipefail

cd "$HOME/ros2_ws"
set +u
source /opt/ros/jazzy/setup.bash
set -u
set +u
source ~/ros2_ws/install/setup.bash
set -u
BASE="$HOME/uav_research/baseline"
BATCH="$BASE/batch_30"
mkdir -p "$BATCH"

# Start from the two already-confirmed 16-second PASS captures.
PASS=2
ATTEMPT=0
MAX_ATTEMPTS=45

printf 'trial,csv,decision,report\n' > "$BATCH/results.csv"
printf '018,%s,PASS,previously-validated\n' \
  "$BASE/preflight_018.csv" >> "$BATCH/results.csv"
printf '020,%s,PASS,previously-validated\n' \
  "$BASE/preflight_020.csv" >> "$BATCH/results.csv"

echo "Target: 30 accepted captures; already accepted: $PASS"

while (( PASS < 30 && ATTEMPT < MAX_ATTEMPTS )); do
    ATTEMPT=$((ATTEMPT + 1))
    LOG="$BATCH/attempt_$(printf '%02d' "$ATTEMPT").log"

    echo
    echo "Attempt $ATTEMPT/$MAX_ATTEMPTS — accepted $PASS/30"

    if ! timeout 30s ros2 run baseline_measurement mission_node \
        --config "$HOME/ros2_ws/src/baseline_measurement/config/baseline.yaml" \
        --passive-only --observe-seconds 16 2>&1 | tee "$LOG"; then
        echo "Capture command failed; preserving log."
        printf '%s,,FAIL,command_failed\n' "$ATTEMPT" \
          >> "$BATCH/results.csv"
        continue
    fi

    CSV=$(sed -n \
      's/.*CSV: \(.*\); execute_sitl=False.*/\1/p' "$LOG" | head -n 1)

    if [[ -z "$CSV" || ! -f "$CSV" ]]; then
        echo "Could not identify the capture CSV; preserving log."
        printf '%s,,FAIL,csv_missing\n' "$ATTEMPT" \
          >> "$BATCH/results.csv"
        continue
    fi

    NAME=$(basename "$CSV" .csv)
    REPORT="$BATCH/${NAME}.json"
    VLOG="$BATCH/${NAME}_validation.log"

    if ros2 run baseline_measurement phase1_acceptance \
        --output "$REPORT" "$CSV" > "$VLOG" 2>&1; then
        PASS=$((PASS + 1))
        DECISION=PASS
        echo "PASS: $CSV ($PASS/30)"
    else
        DECISION=FAIL
        echo "FAIL: $CSV — see $VLOG"
    fi

    printf '%s,%s,%s,%s\n' \
      "$ATTEMPT" "$CSV" "$DECISION" "$REPORT" \
      >> "$BATCH/results.csv"
done

echo
echo "Accepted captures: $PASS/30"
echo "Results: $BATCH/results.csv"
echo "Logs and reports: $BATCH/"

if (( PASS == 30 )); then
    echo "PASS: 30 accepted passive captures collected."
    exit 0
else
    echo "INCOMPLETE: attempt limit reached."
    exit 1
fi
