#log_reader.py
import sys
import re
import fileinput

# Define a Log class
class Log:
    def __init__(self, host, datetime, method, path, http_version, status_code, size):
        self.host = host
        self.datetime = datetime
        self.method = method
        self.path = path
        self.http_version = http_version
        self.status_code = status_code
        self.size = size

    def __repr__(self):
        return f"Log(host={self.host}, datetime={self.datetime}, method={self.method}, path={self.path}, http_version={self.http_version}, status_code={self.status_code}, size={self.size})"

# Regex pattern remains the same
log_pattern = re.compile(r'^([\w\.:-]+) - - \[([^\]]+)\] "(GET|POST|HEAD) ([^ ]+) HTTP/(\d\.\d)" (\d+) (\d+|-)')

def parse_log_line(line):
    match = log_pattern.match(line)
    if match:
        return Log(
            host=match.group(1),
            datetime=match.group(2),
            method=match.group(3),
            path=match.group(4),
            http_version=match.group(5),
            status_code=match.group(6),
            size=match.group(7),
        )
    else:
        raise ValueError("Line does not match log format")

for line in fileinput.input():
    try:
        log = parse_log_line(line)
        print(log.status_code)  # Change here: print only the status code
    except ValueError as e:
        print(e, file=sys.stderr)