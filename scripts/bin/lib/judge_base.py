from abc import ABCMeta, abstractmethod
import werkzeug
werkzeug.cached_property = werkzeug.utils.cached_property
from robobrowser import RoboBrowser
import json
from pathlib import Path

class OnlineJudge(metaclass=ABCMeta):

    def __init__(self, logger, contestId):
        self.logger = logger
        self.contestId = contestId
        self.robo = RoboBrowser(parser='html.parser')
        # creds = self.get_creds()
        # self.login(creds['username'], creds['token'])

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
            self.logger.error(f'failed to read ~/{self.config}!')
        for key in ['username', 'token']:
            if key not in creds:
                self.logger.error(f'{self.config} is missing {key}')
        return creds

    @abstractmethod
    def login(self, username, token) -> None:
        pass

    # Return error message, or None if success
    @abstractmethod
    def submit(self, sourceFile, problemId, lang):
        pass

    def setup(self, config):
        pass

    @abstractmethod
    def get_samples(self, contestId, problemId):
        pass

    # Return (message, done) pair
    def ping(self, problemId):
        logger.error('Watch not supported!')

#    def watch(self, contestId, problemId):
#        import spinner
#        from time import sleep
#        ping_func = self.ping(contestId, problemId)
#
#        while True:
#            status, done = next(ping_func)
#            spinner.display(status)
#            if done:
#                break
#            sleep(TICK)

