"""Verify an authorized batch cannot launch a mission after failed preflight."""
import importlib.util
from pathlib import Path
import tempfile
import unittest
from unittest import mock


class AuthorizedStudyTests(unittest.TestCase):
    """Exercise the batch gate with all flight process creation mocked."""

    def test_failed_preflight_never_starts_active_process(self):
        tool = Path(__file__).resolve().parents[1] / 'tools/authorized_study.py'
        spec = importlib.util.spec_from_file_location('authorized_study_tested', tool)
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            package = root / 'src/baseline_measurement'
            (package / 'tools').mkdir(parents=True)
            (root / 'baseline_results').mkdir()
            config = root / 'config.yaml'
            config.write_text('topics: {}\n')
            module.__file__ = str(package / 'tools/authorized_study.py')
            with mock.patch.object(
                module,
                'observe',
                return_value={'passed': False}
            ), mock.patch.object(module.subprocess, 'Popen') as start:
                module.main(
                    ['--human-authorized-active-sitl', '--count', '30', '--config', str(config)]
                )
                start.assert_not_called()
            self.assertEqual(len(list((root / 'baseline_results').glob('phase1_study_*'))), 1)

    def test_completed_passive_capture_cannot_spin_callbacks_into_closed_log(self):
        tool = Path(__file__).resolve().parents[1] / 'tools/authorized_study.py'
        spec = importlib.util.spec_from_file_location('authorized_study_lifecycle', tool)
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        from types import SimpleNamespace
        state = (
            SimpleNamespace(
                connected=True,
                healthy=True,
                valid=True,
                heading_ready=True,
                landed=True,
                armed=False,
                competition=False,
                failsafe=False,
                reset=False
            )
        )
        node = mock.Mock(done=False, experiment=None)
        node.log.finished = True
        node.telemetry.return_value = state

        def finish_capture(*args, **kwargs):
            if node.done:
                raise AssertionError('Callback attempted after CSV closed')
            node.done = True
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            config = root / 'config.yaml'
            config.write_text('topics: {}\n')
            with (
                mock.patch.object(module, 'MissionNode', return_value=node),
                mock.patch.object(module.rclpy, 'init'),
                mock.patch.object(module.rclpy, 'shutdown'),
                mock.patch.object(module.rclpy, 'spin_once', side_effect=finish_capture) as spin,
                mock.patch.object(module.time, 'monotonic', return_value=1.0),
            ):
                result = module.observe(config, root)
                self.assertTrue(result['passed'])
                self.assertEqual(spin.call_count, 1)
                node.log.finish.assert_not_called()
