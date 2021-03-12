from oj import OJ

class KA(OJ):
    """
        Login, return cookies
    """
    def login(self):
        username, token
        data = { 'user': username, 'token': token, 'script': 'true' }
        headers = { 'User-Agent': 'kattis-cli-submit' }

        pass

    """
        Validate the contest and problem
    """
    def validate(self):
        pass

    """
        Submit a file
    """
    def submit(self, file):
        pass

export = KA
