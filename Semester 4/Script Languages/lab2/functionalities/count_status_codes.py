import sys

def count_status_codes():
    status_code_count = {}
    for line in sys.stdin:
        status_code = int(line.strip())  # Read status code from stdin and convert to int
        if status_code in status_code_count:
            status_code_count[status_code] += 1
        else:
            status_code_count[status_code] = 1
    return status_code_count

status_code_counts = count_status_codes()

for status_code, count in status_code_counts.items():
    print(f"Status Code {status_code}: {count} times")
