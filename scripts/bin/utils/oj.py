from argparse import ArgumentParser, FileType
from abc import ABCMeta, abstractmethod
import werkzeug
werkzeug.cached_property = werkzeug.utils.cached_property
from robobrowser import RoboBrowser
import json
from pathlib import Path
from typing import Optional
import sys

def error(msg):
    print(msg, file=sys.stderr)
    exit(-1)

def log(msg):
    print(msg, file=sys.stderr)

DATA_FILE = '.data'

def load_data():
    try:
        with open(DATA_FILE, 'r') as f:
            return json.load(f)
    except:
        error('failed to load {}\nrun init first?'.format(DATA_FILE))

def save_data(data):
    with open(DATA_FILE, 'w') as f:
        json.dump(data, f)


class OnlineJudge(metaclass=ABCMeta):

    def __init__(self):
        self.robo = RoboBrowser(parser='html.parser')
        parser = ArgumentParser()
        subparsers = parser.add_subparsers(dest='cmd', required=True)
        parser_init = subparsers.add_parser('init', aliases=['i'])
        parser_init.add_argument('contest')
        parser_init.set_defaults(func=self.init)

        parser_submit = subparsers.add_parser('submit', aliases=['sm'])
        parser_submit.add_argument('source', type=FileType('r'))
        parser_submit.add_argument('--problem', '-p', required=False)
        parser_submit.set_defaults(func=self.submit)

        args = parser.parse_args()
        args.func(args)

    @property
    @abstractmethod
    def config(self) -> str:
        """
        Path to the .config.json file containing login credentials
        """
        pass

    def get_creds(self):
        path = Path.home() / self.config
        try:
            with open(path, 'r') as f:
                creds = json.load(f)
        except:
            error('failed to read config.json!')
        for key in ['username', 'token']:
            if key not in creds:
                error('{} is missing {}'.format(self.config, key))
        return creds

    @abstractmethod
    def do_login(self, user, token) -> Optional[str]:
        """
        Login to the online judge
        Return error message, or None if success
        """
        pass

    def login(self):
        log('logging in')
        creds = self.get_creds()
        res = self.do_login(creds['username'], creds['token'])
        if res is not None:
            error(res)

    # Return error message, or None if success
    @abstractmethod
    def do_submit(self, contestId, problemId, lang, sourceFile) -> Optional[str]:
        """
        Submit to the online judge
        Return error message, or None if success
        """
        pass

    def init(self, args):
        contest = args.contest
        save_data({
            'contest': contest
        })

    def submit(self, args):
        self.login()
        data = load_data()
        filename = Path(args.source.name)

        problem = args.problem or filename.stem
        lang = filename.suffix
        res = self.do_submit(data['contest'], problem, lang, args.source)
        if res is not None:
            error(res)
        print('submitted', file=sys.stderr)

