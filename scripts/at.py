#!/usr/bin/env python3
from cli import CLI
from robobrowser import RoboBrowser

def getURL(contestId, problemId, sourceFile):
    url = 'https://atcoder.jp/contests/{0}/tasks/{0}_{1}'.format(contestId, problemId)
    print('submitting {} to problem {} of contest {}'.format(sourceFile, problemId, contestId))
    return url.format(contestId)

def login():
    from creds import AT_USER, AT_PASS

    browser = RoboBrowser(parser='html.parser')
    browser.open('https://atcoder.jp/login')

    form = browser.get_form(class_='form-horizontal')
    form['username'] = AT_USER
    form['password'] = AT_PASS
    browser.submit_form(form)
    errors = browser.select('.alert-danger')
    if len(errors) > 0:
        error = errors[0]
        message = list(filter(lambda y: len(y) > 0, [x.strip() for x in error.findAll(text=True, recursive=False)]))[0]
        print('Login failed: {}'.format(message))
        exit(-1)

    return browser

LANGS = {
    'cpp': '4003',
    'py': '4047',
}

class AT(CLI):
    def supported(self, ext):
        return ext in LANGS

    def submit(self, contestId, problemId, sourceFile, ext):
        robo = login()
        url = getURL(contestId, problemId, sourceFile)
        robo.open(url)
        if '404' in robo.find('title').get_text():
            print('Problem not found!')
            return True
        form = robo.get_form(class_='form-code-submit')
        form['data.LanguageId'] = LANGS[ext]
        with open(sourceFile, mode='r') as f:
            form['sourceCode'] = f.read()
        robo.submit_form(form)

AT()
