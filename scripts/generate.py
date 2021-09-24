from argparse import ArgumentParser, FileType
import re, sys, subprocess

MARKER_BOOK_CODE = '// BOOK CODE'
MARKER_REAL_CODE = '// REAL CODE'
MARKER_MAIN = '// MAIN'
REGEX_DEP = '// dep: (.+)'

def log(s):
  print(s, file=sys.stderr)

def find(filename):
  path = subprocess.check_output('find . -name {}'.format(filename), shell=True).decode().strip()
  if path:
    return open(path)

def extract_dependencies(test):
  files = [];
  for line in test:
    # match file
    filename = re.search(REGEX_DEP, line)
    if filename:
      filename = filename.group(1)
      file = find(filename)
      if file:
        files.append(file)
      else:
        log('Error - dependency: "{}" not found'.format(filename))
        sys.exit(1)
  test.seek(0)
  return files

if __name__ == '__main__':
  parser = ArgumentParser(description='Generate a test file')
  parser.add_argument('template', type=FileType('r'))
  parser.add_argument('test', type=FileType('r'))
  args = parser.parse_args()
  files = extract_dependencies(args.test)
  if len(files) == 0:
    log('Warning - no dependencies')

  # read until BOOK_CODE
  for line in args.template:
    print(line.rstrip())
    if line.startswith(MARKER_BOOK_CODE):
      break
  print()
  for file in files:
    print(file.read().rstrip())
  print()
  for line in args.template:
    if line.startswith(MARKER_REAL_CODE):
      print(line.rstrip())
      break
  print()
  print(args.test.read().rstrip())
  print()
  for line in args.template:
    if line.startswith(MARKER_MAIN):
      print(line.rstrip())
      break
  for line in args.template:
    print(line.rstrip())

