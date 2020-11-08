#!/usr/bin/env python3
from argparse import ArgumentParser
import os, sys

# Logging

import logging
logger = logging.getLogger('submit-cli')
logging.basicConfig(level=logging.INFO, stream=sys.stderr, format='%(message)s')

# https://gist.github.com/gothma/2459959b58b8af895574
class ShutdownHandler(logging.Handler):
    def emit(self, record):
        print(record.msg, file=sys.stderr)
        exit(1)

logger.addHandler(ShutdownHandler(level=logging.ERROR))
logger.setLevel(logging.INFO)

# Judges

import cf
import at

JUDGES = {
    'cf': lambda *args: cf.cf(*args),
    'at': lambda *args: at.at(*args)
}

# Arguments

def arg_source(src):
    return src, os.path.abspath(src)

def arg_judge(j):
    if j not in JUDGES:
        logger.error('Invalid judge: {} is not one of {}'.format(j, JUDGES.keys()))

    return j

def guess_judge():
    path = os.getcwd()
    logger.debug('Guessing judge with path: {}'.format(path))

    dirs = path.split('/')
    dirs = [x.split('-') for x in filter(len, dirs)]
    for dir in sum(dirs, []):
        if dir in JUDGES:
            return dir

    return None

def guess_meta(path):
    logger.debug('Guessing meta with path: {}'.format(path))
    try:
        dirs = path.split('/')
        file, ext = os.path.splitext(dirs[-1])
        ext = ext[1:] if len(ext) else None
        dirs[-1] = file.split('_')[0]
        dirs = [x.split('-') for x in filter(len, dirs)]
        dirs = sum(dirs, [None, None, None])
        meta = dirs[-3:] + [ext]
        if not meta[0] in JUDGES:
            meta[0] = None
        logger.debug('Meta is {}'.format(meta))
        return meta
    except:
        logger.debug('Failed to guess meta')
        return [None]*4

def guess_test(lang, source):
    if lang == 'py':
        return ['python3', source]
    elif lang == 'cpp':
        return ['./{}'.format(source[:-4])]
    else:
        return None

def confirm(judge, contestId, problemId, lang, source, force):
    line = '='*20
    print(
'''{0}
Confirm submission
judge:      {1}
contest:    {2}
problem:    {3}
file:       {4}
language:   {5}
{0}'''.format(line, judge, contestId, problemId, source, lang), file=sys.stderr
    )
    return True if force else (input('Submit? [y/n] ').strip() == 'y')

def do_test(runner, cId, pId, command):
    logger.debug('Testing with command: {}'.format(command))
    ins, outs = runner.get_samples(cId, pId)
    logger.debug('Inputs: {}\nOutputs: {}'.format(ins, outs))

    if len(ins) != len(outs):
        return logger.info('Error fetching test cases')
    if len(ins) == 0:
        return logger.info('No test cases found!')

    logger.info('{} test case(s) found.'.format(len(ins)))
    from subprocess import run, PIPE, TimeoutExpired
    for i in range(len(ins)):
        try:
            p = run(command, stdout=PIPE, stderr=PIPE, input=ins[i], encoding='ascii', timeout=2)
        except TimeoutExpired:
            return logger.info('Timed out on test {}'.format(i+1))
        except:
            logger.error('Error running test command: {}'.format(command))
        if p.returncode:
            return logger.info('Failed test {} with exit code {}'.format(i+1, p.returncode))
        output = p.stdout.strip()
        if output != outs[i]:
            logger.info('Input:')
            logger.info(ins[i])
            logger.info('Output:')
            logger.info(output)
            logger.info('Expected:')
            logger.info(outs[i])
            return logger.info('Output differed on test {}'.format(i+1))
    
    logger.info('Passed sample')

def do_submit(args):
    source, path    = args.source
    meta            = [args.judge, args.contestId, args.problemId, args.language]
    force           = args.force

    guess = guess_meta(path)
    judge, cId, pId, lang = [x or guess[i] for i, x in enumerate(meta)]

    if judge is None:
        logger.error('Could not guess judge: specify with -j')

    if cId is None:
        logger.error('Could not guess contest: specify with -c')

    if pId is None:
        logger.error('Could not guess problem: specify with -p')

    runner = JUDGES[judge]()

    # Validation
    logger.debug('Checking language')
    if not runner.lang_ok(lang):
        logger.error('Language not supported: {}'.format(lang))
    logger.debug('Ok')

    if args.test is not None:
        if len(args.test) == 0:
            args.test = guess_test(lang, source)

        if args.test:
            do_test(runner, cId, pId, args.test)
        else:
            logger.error('Could not guess test: specify with -t {command}')

    if not confirm(judge, cId, pId, lang, source, force):
        logger.error('Aborted')

    if args.skip:
        logger.info('Skipping submit')
    else:
        logger.info('Submitting')
        err = runner.submit(cId, pId, lang, source)
        logger.info('Submitted')

    if args.watch:
        runner.watch(cId, pId)

if __name__ == '__main__':
    try:
        parser = ArgumentParser(description='CLI Submit')

        parser.add_argument('source', type=arg_source)
        parser.add_argument('-j', '--judge', type=arg_judge)
        parser.add_argument('-c', '--contestId')
        parser.add_argument('-p', '--problemId')
        parser.add_argument('-l', '--language')
        parser.add_argument('-v', '--verbose', action='store_true')
        parser.add_argument('-f', '--force', action='store_true', help='skip confirmation')
        parser.add_argument('-w', '--watch', action='store_true', help='watch after submitting')
        parser.add_argument('-s', '--skip', action='store_true', help='skip submission step')
        parser.add_argument('-t', '--test', nargs='*', help='test before submitting')

        args, _ = parser.parse_known_args()

        if args.verbose:
            logger.setLevel(logging.DEBUG)
            logger.debug('Verbose logging')

        do_submit(args)

    except KeyboardInterrupt:
        print()
        exit(1)
