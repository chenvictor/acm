from ..judge_base import OnlineJudge
from robobrowser import RoboBrowser
import requests
import json

LANGS = {
    'cpp': '54',
    'py': '41',
}

# Return array of errors
def getErrors(robo):
    return list(filter(lambda x: len(x) > 2, [err.get_text() for err in robo.select('span.error')]))

class Judge(OnlineJudge):
    config = '.cfconfig.json'

    def get_url(self):
        URL = 'https://codeforces.com/contest/{}'
        GYM = 'https://codeforces.com/gym/{}'
        if (len(self.contestId) <= 4):
            self.logger.debug('Contest URL')
            url = URL
        else:
            self.logger.debug('Gym URL')
            url = GYM
        return url.format(self.contestId)

    def get_submit_url(self):
        return f'{self.get_url()}/submit'

    def get_problem_url(self, problemId):
        return f'{self.get_url()}/problem/{problemId.upper()}'

    def lang_ok(self, lang):
        return lang in LANGS

    def login(self, username, token) -> None:
        self.robo.open('https://codeforces.com/enter')
        form = self.robo.get_form(id='enterForm')
        if form is None:
            self.logger.error('Login form not found')
            exit(-1)
        form['handleOrEmail'].value = username
        form['password'].value      = token
        self.robo.submit_form(form)
        errs = getErrors(self.robo)
        if len(errs) > 0:
            self.logger.debug(errs)
            self.logger.error('Login error: {}'.format(errs[0]))

    def get_samples(self, problemId):
        url = self.get_problem_url(problemId)
        self.logger.debug('Problem url: {}'.format(url))
        def _get(class_):
            r = self.robo.find_all(class_=class_)
            return [x.pre.text.strip() for x in r]

        try:
            self.robo.open(url)
            ins = _get('input')
            outs = _get('output')
            return ins, outs
        except:
            self.logger.debug('Error getting samples')
            return [], []

    def submit(self, sourceFile, problemId, lang):
        self.login(**self.get_creds())
        url = self.get_submit_url()
        self.logger.debug('Submit url: {}'.format(url))
        self.robo.open(url)
        form = self.robo.get_form(class_='submit-form')
        if form is None:
            self.logger.error('Submit form not found!')
            exit(-1)
        form['submittedProblemIndex'] = problemId.upper()
        form['programTypeId'] = LANGS[lang]
        form['sourceFile'] = sourceFile

        res = self.robo.submit_form(form)
        errs = getErrors(self.robo)
        if len(errs) > 0:
            self.logger.debug(errs)
            self.logger.error('Submission error: {}'.format(errs[0]))
            exit(-1)

    def ping(self, problemId):
        from format import Format
        format = Format(
            queue_code      = 'queue',
            cpe_code        = 'COMPILATION_ERROR',
            running_code    = 'TESTING',
            ac_code         = 'OK',
            wa_code         = 'WRONG_ANSWER',
            rte_code        = 'RUNTIME_ERROR'
        )

        url = 'https://codeforces.com/api/contest.status?contestId={}&from=1&count=1&handle={}'.format(self.contestId, self.username)

        while True:
            self.robo.open(url)
            res = self.robo.response
            if not res.ok or res.status_code != 200:
               logger.error('Response error')
               logger.debug(res.error)
            res = json.loads(str(self.robo.parsed))
            try:
                res = res['result'][0]
                #problem     = res['problem']['name']
                verdict     = res.get('verdict', 'queue')
                passedTests = res.get('passedTestCount', 0)
            except:
                logger.error('error parsing: {}'.format(res))

            yield format.parse(verdict, passedTests+1)

