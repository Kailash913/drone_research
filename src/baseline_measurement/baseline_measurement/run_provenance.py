"""Attach contemporaneous provenance to future runs without filling historical gaps."""
import hashlib
import json
from pathlib import Path
import uuid


def run_metadata(options):
    """Generate a unique identity and retain the actual supplied configuration bytes."""
    config = getattr(options, 'config', None)
    result = (
        {
            'run_id': uuid.uuid4().hex,
            'experiment_id': getattr(options, 'experiment_id', None),
            'config_file': None,
            'config_sha256': None
        }
    )
    if config:
        path = Path(config).expanduser().resolve()
        result.update(
            config_file=str(path),
            config_sha256=hashlib.sha256(path.read_bytes()).hexdigest()
        )
    context = getattr(options, 'provenance_json', None)
    if context:
        path = Path(context).expanduser().resolve()
        document = json.loads(path.read_text())
        if (
                document['config_sha256'] != result['config_sha256']
                or document['experiment_id'] != result['experiment_id']
        ):
            raise ValueError('Run provenance identity/configuration mismatch')
        source = Path(__file__).parent
        for name, digest in document['source_sha256'].items():
            if hashlib.sha256((source / name).read_bytes()).hexdigest() != digest:
                raise ValueError('Run provenance source mismatch: ' + name)
        result.update(
            provenance_file=str(path),
            provenance_sha256=hashlib.sha256(path.read_bytes()).hexdigest(),
            px4_version=document.get('px4_version'),
            simulator_version=document.get('simulator_version'),
            provenance_method=document.get('version_evidence')
        )
    return result
