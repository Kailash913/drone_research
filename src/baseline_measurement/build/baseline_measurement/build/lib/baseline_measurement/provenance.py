"""Recover retained source identity from recorded hashes without inventing historical metadata."""
import argparse
import csv
import hashlib
import json
from pathlib import Path


def recover(input_dir, evidence_dirs):
    """Match recorded source hashes to retained bytes; keep other historical unknowns explicit."""
    inventory = {}
    for directory in evidence_dirs:
        for path in Path(directory).rglob('*.py'):
            digest = hashlib.sha256(path.read_bytes()).hexdigest()
            inventory.setdefault((path.name, digest), []).append(str(path.resolve()))
    records = []
    for path in sorted(Path(input_dir).glob('baseline_run_*.csv')):
        with path.open(newline='', encoding='utf-8') as stream:
            metadata_rows = (
                [row for row in csv.DictReader(stream) if row['record_type'] == 'metadata']
            )
        if len(metadata_rows) != 1:
            records.append({'source_file': str(path), 'error': 'Metadata count is not one'})
            continue
        metadata = json.loads(metadata_rows[0]['detail'])
        matches = (
            {
                name: {
                    'recorded_sha256': digest,
                    'retained_matches': inventory.get((name, digest), [])
                } for name,
                digest in metadata.get('source_sha256', {}).items()
            }
        )
        records.append(
            {
                'source_file': str(path.resolve()),
                'raw_sha256': hashlib.sha256(path.read_bytes()).hexdigest(),
                'source_identity': matches,
                'historical_config_file': metadata.get('config_file'),
                'historical_config_sha256': metadata.get('config_sha256'),
                'historical_px4_version': metadata.get('px4_version'),
                'interpretation': (
                    'Retained byte matches support source identity only; current '
                    'versions/configuration cannot establish historical provenance.'
                )
            }
        )
    return {'records': records, 'historical_raw_files_modified': False}


def main(args=None):
    """Write an exclusive recovery sidecar without rewriting raw records or manifests."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--input', required=True)
    parser.add_argument('--evidence-dir', action='append', required=True)
    parser.add_argument('--output', required=True)
    options = parser.parse_args(args)
    result = recover(options.input, options.evidence_dir)
    with Path(options.output).open('x', encoding='utf-8') as stream:
        json.dump(result, stream, indent=2)
        stream.write('\n')


if __name__ == '__main__':
    main()
