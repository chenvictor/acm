from math import *
from sys import stdout, stderr
def fprintf(fs, s, *argv):
    fs.write(s.format(*argv))

def printf(s, *argv):
    fprintf(stdout, s, *argv)

def gets(type=int, sep=' '):
    return list(map(type, input().split(sep)))

def main(): # Emily <3
    

main()
