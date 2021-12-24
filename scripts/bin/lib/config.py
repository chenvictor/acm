import json

CONFIG_FILE = '.contest.json'

def read_config(return_defaults=True):
    try:
        with open(CONFIG_FILE) as f:
            return json.load(f)
    except FileNotFoundError as e:
        if return_defaults:
            return {'judge': None, 'contest': None}
        else:
            return None

def write_config(config):
    with open(CONFIG_FILE, 'w') as f:
        f.write(json.dumps(config))

