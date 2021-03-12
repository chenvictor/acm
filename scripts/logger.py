from sys import stderr
verbose = False

def debug(message):
    if verbose:
        log(message)

def log(message):
    print(message, file=stderr)

def error(message):
    log(message)
    exit(-1)
