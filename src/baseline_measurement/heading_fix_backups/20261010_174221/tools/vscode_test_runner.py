"""Run the functional tests using VS Code's Linux debugger, without flight."""

import json
from pathlib import Path
import sys
import unittest

project = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(project))
sys.path.insert(0, str(project / 'test'))
names = ['test_phase1', 'test_baseline_new', 'test_preflight', 'test_auto_takeoff',
         'test_auto_takeoff_adapter', 'test_qgc_plan']
suite = unittest.defaultTestLoader.loadTestsFromNames(names)
directory = project / 'test-output'
directory.mkdir(exist_ok=True)
with (directory / 'heading_fix_tests.log').open('w', encoding='utf-8') as stream:
    result = unittest.TextTestRunner(stream=stream, verbosity=2).run(suite)
summary = {'tests': result.testsRun, 'failures': len(result.failures),
           'errors': len(result.errors), 'skipped': len(result.skipped),
           'passed': result.wasSuccessful()}
(directory / 'heading_fix_tests.json').write_text(json.dumps(summary, indent=2) + '\n')
print(json.dumps(summary, indent=2), flush=True)
if not result.wasSuccessful():
    print((directory / 'heading_fix_tests.log').read_text(), flush=True)
    raise SystemExit(1)
