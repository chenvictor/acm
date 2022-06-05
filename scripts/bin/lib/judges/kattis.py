from ..judge_base import OnlineJudge
from robobrowser import RoboBrowser

LANGS = {
    'cpp': 'C++',
    'py': 'Python 3',
}

_HEADERS = {'User-Agent': 'kattis-cli-submit'}

def getURL(contestId):
    url = 'https://{}.kattis.com/submit'
    return url.format(contestId)

class Judge(OnlineJudge):
    config = '.kaconfig.json'

    def login(self, username, token):
        login_url = 'https://{}.kattis.com/login'.format(self.contestId)
        data = {'user': username, 'token': token, 'script': 'true'}
        headers = {'User-Agent': 'kattis-cli-submit'}
        self.robo.open(login_url, method='post', data=data, headers=_HEADERS)
        res = str(self.robo.parsed).strip().replace('\\n', '')
        if res != 'Login successful':
            self.logger.error('Login failed: {}'.format(res))

    def lang_ok(self, lang):
        return lang in LANGS

    def submit(self, sourceFile, problemId, lang):
        self.login(**self.get_creds())
        submit_url = getURL(self.contestId)
        data = {'submit': 'true',
                'submit_ctr': 2,
                'language': LANGS[lang],
                #'mainclass': mainclass,
                'problem': problemId,
                #'tag': tag,
                'script': 'true'}
        sub_files = []
        sub_files.append(('sub_file[]',
                          (sourceFile.name,
                           sourceFile.read(),
                           'application/octet-stream')))
        self.robo.open(submit_url, method='post', data=data, files=sub_files, headers=_HEADERS)
        print(self.robo.parsed)

