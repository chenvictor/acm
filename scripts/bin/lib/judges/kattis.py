from ..judge_base import OnlineJudge
from cli import CLI
from robobrowser import RoboBrowser

def getURL(contestId, problemId, sourceFile):
    # non open problems are prefixed with contestId
    if contestId != 'open':
        problemId = '{}.{}'.format(contestId, problemId)

    url = 'https://{}.kattis.com/problems/{}/submit'
    return url.format(contestId, problemId.lower())

LANGS = {
    'cpp': 'C++',
    'py': 'Python 3',
}

class Judge(OnlineJudge):
    config = '.kaconfig.json'

    def login(self, user, token):
        robo = RoboBrowser(parser='html.parser')
        login_url = 'https://{}.kattis.com/login'.format(contestId)
        data = {'user': KA_USER, 'token': KA_AUTH, 'script': 'true'}
        headers = {'User-Agent': 'kattis-cli-submit'}
        robo.open(login_url, method='post', data=data, headers=headers)
        res = str(robo.parsed).strip().replace('\\n', '')
        if res != 'Login successful':
            print('Login failed: {}'.format(res))
            exit(-1)

        print('KA logged in as {}'.format(KA_USER))
        return robo

    def lang_ok(self, lang):
        return lang in LANGS

    def get_samples(self, contestId, problemId):
        return [], []

    def submit(self, contestId, problemId, sourceFile, ext):
        robo = login(contestId)
        url = getURL(contestId, problemId, sourceFile)
        robo.open(url)
        if robo.find('404: Not Found') is not None:
            print('Problem not found!')
            return True
        form = robo.get_form(id='submit-solution-form')
        form['sub_file[]'] = sourceFile
        form['language'] = LANGS[ext]
        robo.submit_form(form)

