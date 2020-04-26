from abc import ABC, abstractmethod
from argparse import ArgumentParser, FileType, ArgumentTypeError
from string import ascii_lowercase, ascii_uppercase
import os

def letter(value):
    if not value in ascii_lowercase:
        raise ArgumentTypeError('problem must be a single lowercase letter')
    return value

class CLI(ABC):
    @abstractmethod
    def supported(self, extension):
        pass

    @abstractmethod
    def submit(self, contestId, problemId, sourceFile):
        pass

    def valid_file(self, name):
        ext = name.split('.')[-1]
        if not self.supported(ext):
            raise ArgumentTypeError('extension {} not supported'.format(ext))
        if not os.path.exists(name):
            raise ArgumentTypeError('source file doesn\'t exist')
        return name

    def guess_problem(self, sourceFile):
        p = sourceFile.split('.')[0]
        if p in ascii_lowercase:
            return sourceFile[0]
        if p in ascii_uppercase:
            return p.lower()
        print('could not guess problemId, specify using -p flag')
        exit(-1)

    def __init__(self):
        parser = ArgumentParser(description='CLI Submit')
        parser.add_argument('contestId')
        parser.add_argument('source', type=self.valid_file)
        parser.add_argument('-p', '--problem', type=letter)
        args = parser.parse_args()

        problem = args.problem
        if problem is None:
            problem = self.guess_problem(args.source)
        self.submit(args.contestId, problem, args.source)

