#!/usr/bin/env python3
from cli import CLI

def login():
    USERNAME = 'chenvictor1999'
    from creds import PASSWORD

    from getpass import getpass
    from robobrowser import RoboBrowser

    browser = RoboBrowser(parser='html.parser')
    browser.open('https://codeforces.com/enter')

    form = browser.get_form(id='enterForm')
    while len(USERNAME) == 0:
        USERNAME = input('CF Handle: ')
    form['handleOrEmail'].value = USERNAME
    while len(PASSWORD) == 0:
        PASSWORD = getpass('Password: ')
    form['password'].value = PASSWORD
    browser.submit_form(form)

    if (len(browser.select('span.error.for__password')) > 0):
        print('Login Failed.')
        exit(-1)

    print('Logged in as {}'.format(USERNAME))
    return browser

LANGS = {
    'cpp': '54',
    'py': '41',
}

class CF(CLI):
    def supported(self, ext):
        return ext in LANGS

    def submit(self, contestId, problemId, sourceFile):
        print('submitting {} to problem {} of contest {}'.format(sourceFile, problemId, contestId))
        cf = login()
        url = 'https://codeforces.com/problemset/problem/{}/{}'.format(contestId, problemId.upper())
        cf.open(url)
        if cf.url != url:
            print('Problem not found!')
            exit(-1)
        form = cf.get_form(class_='submitForm')
        if form is None:
            print('Error finding form')
            exit(-1)
        form['programTypeId'] = LANGS[sourceFile.split('.')[-1]]
        form['sourceFile'] = sourceFile
        cf.submit_form(form)
        print('submitted')

CF()
