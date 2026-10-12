"""Re-run the full nonflight suite after a targeted lifecycle correction."""
import json
from pathlib import Path
import subprocess
import sys
import time

package = Path(__file__).resolve().parents[1]
output = package / 'test-output' / ('final_suite_' + time.strftime('%Y%m%d_%H%M%S'))
output.mkdir(exist_ok=False)
command = [sys.executable, '-m', 'pytest', 'test', '-q',
           '--junitxml=' + str(output / 'full_suite.xml')]
result = subprocess.run(command, cwd=package, capture_output=True, text=True)
(output / 'full_suite.log').write_text(result.stdout + result.stderr)
(output / 'verification.json').write_text(json.dumps({
    'command': command, 'returncode': result.returncode,
    'flight_commands_sent': 0, 'output': str(output)}, indent=2) + '\n')
print(result.stdout + result.stderr, flush=True)
print('FINAL_SUITE_OUTPUT=' + str(output), flush=True)
