from importlib import import_module

ALIASES = {
    'cf': 'codeforces',
    'at': 'atcoder',
}

def get_judge(raw, contestId, logger):
    try:
        name = ALIASES[raw]
    except:
        name = raw
    logger.debug(f'judge alias: {raw} => {name}')
    try:
        return import_module('lib.judges.{}'.format(name)).Judge(logger, contestId)
    except:
        logger.error(f'invalid judge: {name}')

