from sys import stderr
import logging
logger = logging.getLogger('submit-cli')

state = '◴◷◶◵'
cur = 0

def display(message):
    global cur
    if cur and logger.getEffectiveLevel() == logging.INFO:
        print('\033[F\033[2K', end='', file=stderr)
    print('{} {}'.format(state[cur % len(state)], message), file=stderr)
    cur += 1

