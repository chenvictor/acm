#!/usr/bin/env python3
from cli import CLI
import werkzeug
werkzeug.cached_property = werkzeug.utils.cached_property
from robobrowser import RoboBrowser
from bs4 import BeautifulSoup
import json
import logging
from format import Format
logger = logging.getLogger('submit-cli')

LANGS = {
    'cpp': ['4003', '3003'],
    'py': ['4047', '3510'],
}

def get_url(contestId, problemId):
    url = 'https://atcoder.jp/contests/{0}/tasks/{0}_{1}'.format(contestId, problemId)
    return url.format(contestId)

class at(CLI):
    def get_creds(self):
        from creds import AT_USER, AT_PASS
        return AT_USER, AT_PASS

    def lang_ok(self, lang):
        return lang in LANGS

    def login(self):
        self.robo.open('https://atcoder.jp/login')
        form = self.robo.get_form(class_='form-horizontal')
        form['username'] = self.username
        form['password'] = self.password
        self.robo.submit_form(form)
        errors = self.robo.select('.alert-danger')
        if len(errors) > 0:
            error = errors[0]
            message = list(filter(lambda y: len(y) > 0, [x.strip() for x in error.findAll(text=True, recursive=False)]))[0]
            logger.error('Login failed: {}'.format(message))

    def get_samples(self, contestId, problemId):
        url = get_url(contestId, problemId)
        self.robo.open(url)
        if '404' in self.robo.find('title').get_text():
            logger.error('Problem not found!')

        import re
        def _find(text):
            res = self.robo.find_all(text=re.compile(text))
            return [x.parent.parent.pre.text.strip() for x in res]

        inputs = _find('Sample Input')
        outputs = _find('Sample Output')

        return inputs, outputs

    def submit(self, contestId, problemId, lang, sourceFile):
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
        
        with open(sourceFile, mode='r') as f:
            form['sourceCode'] = f.read()
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
        from format import Format
        format = Format(
            queue_code      = 'Waiting for Judging',
            cpe_code        = 'Compilation Error',
            running_code    = 'Judging',
            ac_code         = 'Accepted',
            tle_code        = 'Time Limit Exceeded'
        )

        sId = self.getSubmissionMeta(contestId, problemId)
        url = 'https://atcoder.jp/contests/{}/submissions/me/status/json?sids[]={}'.format(contestId, sId)
        logger.debug('pinging url: {}'.format(url))
        while True:
            self.robo.open(url)
            res = json.loads(str(self.robo.parsed))
            try:
                res = BeautifulSoup(res['Result'][sId]['Html'], 'html.parser').find('span')
                code = res['title']
                msg    = res.get_text().strip()
            except:
                logger.error('Error parsing ping response')

            yield format.parse(code, None)

