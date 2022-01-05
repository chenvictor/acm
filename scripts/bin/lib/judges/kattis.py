from ..judge_base import OnlineJudge
from robobrowser import RoboBrowser

LANGS = {
    'cpp': 'C++',
    'py': 'Python 3',
}

def getURL(contestId, problemId, sourceFile):
    # non open problems are prefixed with contestId
    if contestId != 'open':
        problemId = '{}.{}'.format(contestId, problemId)

    url = 'https://{}.kattis.com/problems/{}/submit'
    return url.format(contestId, problemId.lower())

class Judge(OnlineJudge):
    config = '.kaconfig.json'

    def login(self, username, token):
        login_url = 'https://{}.kattis.com/login'.format(self.contestId)
        data = {'user': username, 'token': token, 'script': 'true'}
        headers = {'User-Agent': 'kattis-cli-submit'}
        self.robo.open(login_url, method='post', data=data, headers=headers)
        res = str(self.robo.parsed).strip().replace('\\n', '')
        if res != 'Login successful':
            self.logger.error('Login failed: {}'.format(res))

    def lang_ok(self, lang):
        return lang in LANGS

    def submit(self, sourceFile, problemId, lang):
        self.login(**self.get_creds())
        url = getURL(self.contestId, problemId, sourceFile)
        self.robo.open(url)
        if self.robo.find('404: Not Found') is not None:
            self.logger.error('Problem not found!')
        form = self.robo.get_form(id='submit-solution-form')
        form['sub_file[]'] = sourceFile
        form['language'] = LANGS[lang]
        self.robo.submit_form(form)

