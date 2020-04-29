#!/usr/bin/env python3
from cli import CLI
from robobrowser import RoboBrowser

def getURL(contestId, problemId, sourceFile):
    URL = 'https://codeforces.com/problemset/problem/{}/{}'
    GYM = 'https://codeforces.com/problemset/gymProblem/{}/{}'
    if (len(contestId) <= 4):
        print('submitting {} to problem {} of contest {}'.format(sourceFile, problemId, contestId))
        url = URL
    else:
        print('submitting {} to problem {} of gym {}'.format(sourceFile, problemId, contestId))
        url = GYM
    return url.format(contestId, problemId.upper())

# Return array of errors
def getErrors(robo): 
    return list(filter(lambda x: len(x) > 2, [err.get_text() for err in robo.select('span.error')]))

def login():
    from creds import CF_USER, CF_PASS

    robo = RoboBrowser(parser='html.parser')
    robo.open('https://codeforces.com/enter')

    form = robo.get_form(id='enterForm')
    form['handleOrEmail'].value = CF_USER
    form['password'].value = CF_PASS
    robo.submit_form(form)

    errs = getErrors(robo)
    if len(errs) > 0:
        print('Login failed:')
        for err in errs:
            print('> {}'.format(err))
        exit(-1)

    print('CF logged in as {}'.format(CF_USER))
    return robo

LANGS = {
    'cpp': '54',
    'py': '41',
}

class CF(CLI):
    def supported(self, ext):
        return ext in LANGS

    def submit(self, contestId, problemId, sourceFile, ext):
        robo = login()
        url = getURL(contestId, problemId, sourceFile)
        robo.open(url)
        if robo.url != url:
            print('Problem not found!')
            return True
        form = robo.get_form(class_='submitForm')
        if form is None:
            print('Error finding form')
            return True
        form['programTypeId'] = LANGS[ext]
        form['sourceFile'] = sourceFile
        res = robo.submit_form(form)
        errs = getErrors(robo)
        if len(errs) > 0:
            print('Submit failed:')
            for err in errs:
                print('> {}'.format(err))
            return True

CF()
