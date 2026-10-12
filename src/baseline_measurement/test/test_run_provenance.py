"""Prevent prospective provenance from claiming mismatched configurations."""
import hashlib
import json
from pathlib import Path
import tempfile
from types import SimpleNamespace
import unittest

from baseline_measurement.run_provenance import run_metadata


class RunProvenanceTests(unittest.TestCase):
    """Retain real input bytes and generate distinct run identities."""

    def test_ids_are_unique_and_absent_config_is_not_fabricated(self):
        options = SimpleNamespace(experiment_id='BASE-001')
        first, second = (run_metadata(options), run_metadata(options))
        self.assertNotEqual(first['run_id'], second['run_id'])
        self.assertIsNone(first['config_sha256'])

    def test_actual_config_hash_and_mismatched_context(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'config.yaml'
            path.write_bytes(b'observe_seconds: 15\n')
            context = Path(directory) / 'context.json'
            context.write_text(json.dumps({'config_sha256': 'wrong', 'experiment_id': 'BASE-001'}))
            options = SimpleNamespace(config=str(path), experiment_id='BASE-001')
            self.assertEqual(
                run_metadata(options)['config_sha256'],
                hashlib.sha256(path.read_bytes()).hexdigest()
            )
            options.provenance_json = str(context)
            with self.assertRaises(ValueError):
                run_metadata(options)
