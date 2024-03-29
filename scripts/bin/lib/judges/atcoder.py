from ..judge_base import OnlineJudge
from robobrowser import RoboBrowser
from bs4 import BeautifulSoup
import json

LANGS = {
    'cpp': ['4003', '3003'],
    'py': ['4047', '3510'],
}

def get_url(contestId, problemId):
    url = 'https://atcoder.jp/contests/{0}/tasks/{0}_{1}'.format(contestId, problemId)
    return url.format(contestId)

class Judge(OnlineJudge):
    config = '.atconfig.json'

    def do_login(self, username, token):
        self.robo.open('https://atcoder.jp/login')
        form = self.robo.get_form(class_='form-horizontal')
        form['username'] = username
        form['password'] = token
        self.robo.submit_form(form)
        errors = self.robo.select('.alert-danger')
        if len(errors) > 0:
            error = errors[0]
            message = list(filter(lambda y: len(y) > 0, [x.strip() for x in error.findAll(text=True, recursive=False)]))[0]
            return message

    def do_submit(self, contestId, problemId, lang, sourceFile):
        url = get_url(contestId, problemId)
        self.robo.open(url)
        if '404' in self.robo.find('title').get_text():
            logger.error('Problem not found!')

        form = self.robo.get_form(class_='form-code-submit')
        langSet = False
        for code in LANGS[lang]:
            try:
                form['data.LanguageId'] = code
                langSet = True
                break
            except ValueError:
                logger.debug('Lang code {} not available.'.format(code))
        if not langSet:
            logger.error('No known lang code available!')

        form['sourceCode'] = sourceFile.read()
        res = self.robo.submit_form(form)

    def getSubmissionMeta(self, contestId, problemId):
        logger.debug('Fetching submission meta')
        url = 'https://atcoder.jp/contests/{0}/submissions/me?desc=true&f.Task={0}_{1}&orderBy=created'.format(contestId, problemId)
        self.robo.open(url)
        try:
            t = self.robo.select('table')[0]
            frow = t.findChildren('tr')[1]
            cols = frow.findChildren('td')
            name = cols[1].get_text()
            return cols[4]['data-id']
        except:
            logger.error('Error parsing submission meta')

    def ping(self, contestId, problemId):
        pass
#        sId = self.getSubmissionMeta(contestId, problemId)
#        url = 'https://atcoder.jp/contests/{}/submissions/me/status/json?sids[]={}'.format(contestId, sId)
#        logger.debug('pinging url: {}'.format(url))
#        while True:
#            self.robo.open(url)
#            res = json.loads(str(self.robo.parsed))
#            try:
#                res = BeautifulSoup(res['Result'][sId]['Html'], 'html.parser').find('span')
#                code = res['title']
#                msg    = res.get_text().strip()
#            except:
#                logger.error('Error parsing ping response')
#
#            yield format.parse(code, None)

