from abc import ABC, abstractmethod
import werkzeug
werkzeug.cached_property = werkzeug.utils.cached_property
from robobrowser import RoboBrowser
from abc import ABCMeta, abstractmethod
import json
from pathlib import Path

class OnlineJudge(metaclass=ABCMeta):

    @property
    @abstractmethod
    def config(self) -> str:
        """
        Path to the .config.json file containing login credentials
        """
        pass
    
    def get_creds(self):
        path = '{}/{}'.format(os.path.self.config)
        print('get creds from', path)
        try:
            with open(path, 'r') as f:
                data = json.load(f)
        except:
            import sys
            print(sys.exc_info())
            print('failed to read config.json!')
            exit(-1)
        print(data)

    @abstractmethod
    def login(user, token, self) -> None:
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

    def __init__(self):
        self.get_creds()
#        self.robo = RoboBrowser(parser='html.parser')
#        self.login()
