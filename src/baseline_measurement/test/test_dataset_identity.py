"""Reject identity conflicts and retain study boundaries in synthetic import fixtures."""
import csv
import json
from pathlib import Path

from baseline_measurement.dataset import validate_dataset, write_report
import pytest
import test_dataset


def fixture(directory, name='baseline_run_001.csv', identity=None):
    """Generate synthetic temporary test rows, never historical evidence."""
    helper = test_dataset.DatasetTests()
    helper.directory = directory
    path = helper.make_csv(name=name, cpu='1' if name.endswith('003.csv') else '0')
    if identity:
        with path.open(newline='') as stream:
            reader = csv.DictReader(stream)
            fields = reader.fieldnames
            rows = list(reader)
        metadata = json.loads(rows[0]['detail'])
        metadata.update(experiment_id=identity, run_id='original-fixture-run-' + identity)
        rows[0]['detail'] = json.dumps(metadata)
        with path.open('w', newline='') as stream:
            writer = csv.DictWriter(stream, fieldnames=fields)
            writer.writeheader()
            writer.writerows(rows)
    return path


def test_original_identity_is_not_replaced_by_import_hash(tmp_path):
    """Retain recorded IDs even when its BASE slot is not the first available slot."""
    original = fixture(tmp_path, identity='BASE-007').read_bytes()
    record = validate_dataset(tmp_path)['records'][0]
    assert record['experiment_id'] == 'BASE-007'
    assert record['run_id'] == 'original-fixture-run-BASE-007'
    assert record['original_run_id'] == record['run_id']
    assert record['id_provenance'] == 'Recorded original experiment ID'
    assert Path(record['source_file']).read_bytes() == original
    assert not record['strict_experiment_valid']


def test_empty_study_has_no_slots_or_successes(tmp_path):
    """Exclude empty preflight-error studies from the experiment denominator."""
    report = validate_dataset(tmp_path)
    assert report['counts']['active_attempts'] == 0
    assert report['counts']['study_slots_assigned'] == 0
    assert report['counts']['active_pass'] == 0


def test_conflicting_source_ids_rejected(tmp_path):
    """Do not let different raw attempts silently occupy the same original BASE slot."""
    fixture(tmp_path, identity='BASE-007')
    path = fixture(tmp_path, name='baseline_run_002.csv', identity='BASE-007')
    # Make a distinct raw attempt without changing its claimed experiment identity.
    path.write_text(path.read_text().replace('original-fixture-run-', 'second-fixture-run-'))
    with pytest.raises(ValueError, match='Conflicting original experiment IDs'):
        validate_dataset(tmp_path)


def test_added_records_preserve_original_and_prior_ids(tmp_path):
    """Preserve recorded IDs and prior retrospective assignments when files are added."""
    fixture(tmp_path, identity='BASE-007')
    fixture(tmp_path, name='baseline_run_002.csv')
    first = validate_dataset(tmp_path)
    output = tmp_path / 'first'
    write_report(first, output)
    fixture(tmp_path, name='baseline_run_003.csv')
    second = validate_dataset(tmp_path, output / 'manifest.json')
    ids = {r['sha256']: r['experiment_id'] for r in second['records']}
    assert all(ids[r['sha256']] == r['experiment_id'] for r in first['records'])


def test_same_base_id_in_different_studies_is_separate(tmp_path):
    """Study-scoped identity prevents pooling unrelated BASE-001 records."""
    a, b = tmp_path / 'historical', tmp_path / 'diagnostic'
    a.mkdir()
    b.mkdir()
    fixture(a, identity='BASE-001')
    fixture(b, identity='BASE-001')
    first, second = validate_dataset(a), validate_dataset(b)
    assert first['records'][0]['study_id'] != second['records'][0]['study_id']
    assert first['counts']['active_attempts'] == second['counts']['active_attempts'] == 1


def test_prior_cannot_relabel_recorded_original_id(tmp_path):
    """Reject incompatible prior derived metadata instead of silently rewriting identity."""
    fixture(tmp_path, identity='BASE-007')
    report = validate_dataset(tmp_path)
    output = tmp_path / 'first'
    write_report(report, output)
    path = output / 'manifest.json'
    manifest = json.loads(path.read_text())
    manifest['records'][0]['experiment_id'] = 'BASE-001'
    path.write_text(json.dumps(manifest))
    with pytest.raises(ValueError, match='conflicts with recorded original'):
        validate_dataset(tmp_path, path)


@pytest.mark.parametrize('field,first_value,second_value', [
    ('config_sha256', 'a' * 64, 'b' * 64),
    ('px4_version', 'fixture-revision-A', 'fixture-revision-B'),
    ('simulator_version', 'fixture-simulator-A', 'fixture-simulator-B')])
def test_recorded_context_differences_are_not_pooled(tmp_path, field, first_value, second_value):
    """Keep metrics from materially different known configurations separate."""
    for index, value in enumerate((first_value, second_value), 1):
        path = fixture(tmp_path, name=f'baseline_run_{index:03d}.csv',
                       identity=f'BASE-{index:03d}')
        with path.open(newline='') as stream:
            reader = csv.DictReader(stream)
            fields = reader.fieldnames
            rows = list(reader)
        metadata = json.loads(rows[0]['detail'])
        metadata[field] = value
        rows[0]['detail'] = json.dumps(metadata)
        with path.open('w', newline='') as stream:
            writer = csv.DictWriter(stream, fieldnames=fields)
            writer.writeheader()
            writer.writerows(rows)
    report = validate_dataset(tmp_path)
    assert len(report['group_statistics']) == 2
    assert report['counts']['active_attempts'] == 2
    assert {r['experiment_id'] for r in report['records']} == {'BASE-001', 'BASE-002'}
