#!/usr/bin/env python3
from argparse import ArgumentParser, FileType
import os.path
import logger
import importlib

def parse_path(path):
    parsed = path.replace('-', '/').split('/')
    return list(reversed(parsed))

def guess(parsed, idx, param):
    if len(parsed) > idx:
        return parsed[idx]
    logger.error('Could not guess {}: specify with -{}'.format(param, param[0]))

def main():
    parser = ArgumentParser(prog='CLI submit', description='Submit a solution to an online judge')

    parser.add_argument('file', type=FileType())
    flags = parser.add_argument_group(title='flags')
    parser.add_argument('-j', '--judge')
    parser.add_argument('-c', '--contest')
    parser.add_argument('-p', '--problem')
    parser.add_argument('-l', '--language')
    flags.add_argument('-v', '--verbose', action='store_true')
    flags.add_argument('-s', '--skip', action='store_true', help='skip submission step')

    args = parser.parse_args()

    logger.verbose = args.verbose;
    filename = args.file.name;
    path, ext = os.path.splitext(os.path.abspath(filename))
    parsed = parse_path(path)

    judge = args.judge or guess(parsed, 2, 'judge')
    contest = args.contest or guess(parsed, 1, 'contest')
    problem = args.problem or guess(parsed, 0, 'problem')

    try:
        judge = importlib.import_module('oj.{}'.format(judge)).export()
    except ModuleNotFoundError:
        logger.error('Invalid judge: {}'.format(judge))

    print(judge)

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print()
        exit(1)
