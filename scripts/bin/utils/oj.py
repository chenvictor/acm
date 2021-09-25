from abc import ABC, abstractmethod
import werkzeug
werkzeug.cached_property = werkzeug.utils.cached_property
from robobrowser import RoboBrowser
from abc import ABCMeta, abstractmethod
import json
from pathlib import Path

class OnlineJudge(metaclass=ABCMeta):

    def __init__(self):
        creds = self.get_creds()
        self.robo = RoboBrowser(parser='html.parser')
        self.login(creds['username'], creds['token'])

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
            print('failed to read config.json!')
            exit(-1)
        for key in ['username', 'token']:
            if key not in creds:
                print('{} is missing {}'.format(self.config, key))
                exit(-1)
        return creds

    @abstractmethod
    def login(self, user, token) -> None:
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

