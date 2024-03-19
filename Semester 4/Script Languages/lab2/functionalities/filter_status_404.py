import sys
def filter_status_400():
    for line in sys.stdin:
        try:
            status_code = int(line.strip())  # Convert the read line to an integer
            if status_code == 400:
                print(status_code)  # Print status code if it is 400
        except ValueError:
            print(f"Could not convert {line.strip()} to an integer", file=sys.stderr)
            # Handle the case where the line is not an integer,
            # You might want to print an error or pass silently
            pass
        
filter_status_400()