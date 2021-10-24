#!/bin/env python3
from argparse import ArgumentParser
import pathlib

def init(args):
    print('init', args.path)

def submit(args):
    print('submit', args)

parser = ArgumentParser()
subparsers = parser.add_subparsers(dest='cmd', required=True)
parser_init = subparsers.add_parser('init', aliases=['i'])
parser_init.add_argument('path', type=pathlib.Path)
parser_init.add_argument('contest', nargs='?')
parser_init.set_defaults(func=init)

parser_submit = subparsers.add_parser('submit', aliases=['sm'])
parser_submit.set_defaults(func=submit)

args = parser.parse_args()
args.func(args)
