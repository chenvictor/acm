from abc import ABC, abstractmethod

class OJ(ABC):
    """
        Login, return cookies
    """
    @abstractmethod
    def login(self):
        pass

    """
        Validate the contest and problem
    """
    @abstractmethod
    def validate(self):
        pass

    """
        Submit a file
    """
    @abstractmethod
    def submit(self, file):
        pass

    def __init__(self, contest, problem): 
        self.contest = contest
        self.problem = problem

