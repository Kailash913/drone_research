import importlib.util
import json
from pathlib import Path
modules = ('black', 'autopep8', 'yapf', 'ruff', 'isort')
result = {name: bool(importlib.util.find_spec(name)) for name in modules}
Path(
    '/home/kailash/ros2_ws/src/baseline_measurement/test-output/lint_tools.json'
).write_text(json.dumps(result))
print(result, flush=True)
