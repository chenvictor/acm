from enum import Enum

class Status(Enum):
    QUEUE   = False,    'In Queue'
    CPE     = True,     'Compilation Error'
    RUNNING = False,    'Running...'
    AC      = True,     'AC'
    TLE     = True,     'TLE'
    MLE     = True,     'MLE'
    WA      = True,     'WA'
    OTHER   = False,    'Unknown Response'
    def __init__(self, final, message):
        self.final   = final
        self.message = message

def running(testNo = None):
    if testNo is None:
        return 'Running...'
    return 'Running on test {}'.format(testNo)

def rte(testNo = None):
    if testNo is None:
        return 'Runtime error'
    return 'Runtime error on test {}'.format(testNo)

def tle(testNo = None):
    if testNo is None:
        return 'Time limit exceeded'
    return 'Time limit exceeded on test {}'.format(testNo)

def mle(testNo = None):
    if testNo is None:
        return 'Memory limit exceeded'
    return 'Memory limit exceeded on test {}'.format(testNo)

def wa(testNo = None):
    if testNo is None:
        return 'Wrong Answer'
    return 'Wrong Answer on test {}'.format(testNo)

class Format:
    def __init__(self, queue_code = None, cpe_code = None, running_code = None, ac_code = None, rte_code = None, tle_code = None, mle_code = None, wa_code = None):
        self.queue_code     = queue_code
        self.cpe_code       = cpe_code
        self.running_code   = running_code
        self.ac_code        = ac_code
        self.rte_code       = rte_code
        self.tle_code       = tle_code
        self.mle_code       = mle_code
        self.wa_code        = wa_code

    def parse(self, code, testNo = None):
        if code == self.queue_code:
            return 'In Queue', False
        elif code == self.cpe_code:
            return 'Compilation Error', True
        elif code == self.running_code:
            return running(testNo), False
        elif code == self.ac_code:
            return 'Accepted', True
        elif code == self.rte_code:
            return rte(testNo), True
        elif code == self.tle_code:
            return tle(testNo), True
        elif code == self.mle_code:
            return mle(testNo), True
        elif code == self.wa_code:
            return wa(testNo), True
        else:
            return 'Verdict: {}'.format(code), False

