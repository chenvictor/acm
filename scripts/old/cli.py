from abc import ABC, abstractmethod
import werkzeug
werkzeug.cached_property = werkzeug.utils.cached_property
from robobrowser import RoboBrowser
from argparse import ArgumentParser, FileType, ArgumentTypeError
import os
import logging
from getpass import getpass

logger = logging.getLogger('submit-cli')
TICK = .25

class CLI(ABC):
    @abstractmethod
    def get_creds(self):
        pass

    @abstractmethod
    def lang_ok(self, lang):
        pass

    @abstractmethod
    def login(self):
        pass

    # Return error message, or None if success
    @abstractmethod
    def submit(self, contestId, problemId, lang, sourceFile):
        pass

    @abstractmethod
    def get_samples(self, contestId, problemId):
        pass

    # Return (message, done) pair
    def ping(self, contestId, problemId):
        logger.error('Watch not supported!')

    def watch(self, contestId, problemId):
        import spinner
        from time import sleep
        ping_func = self.ping(contestId, problemId)

        while True:
            status, done = next(ping_func)
            spinner.display(status)
            if done:
                break
            sleep(TICK)

    def __init__(self):
        self.username, self.password = self.get_creds()
        while len(self.username or '') == 0:
            self.username = input('Enter username: ')
        while len(self.password or '') == 0:
            self.password = getpass(prompt='Enter password: ')
        self.robo = RoboBrowser(parser='html.parser')
        self.login()
