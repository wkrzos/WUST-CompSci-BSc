import sys
import re
from datetime import datetime

def parse_apache_log(log_line):
    log_pattern = r'(\S+) - - \[(.*?)\] "(.*?)" (\d{3}) (\d+|-)'
    match = re.match(log_pattern, log_line)
    if match is None:
        raise ValueError("Invalid log line")
    groups = match.groups()
    
    # Convert timestamp to datetime.datetime
    timestamp_format = "%d/%b/%Y:%H:%M:%S %z"
    timestamp = datetime.strptime(groups[1], timestamp_format)
    
    # Convert status code to int and response size to int, handling '-' as 0
    status_code = int(groups[3])
    response_size = int(groups[4]) if groups[4].isdigit() else 0
    
    return (groups[0], timestamp, groups[2], status_code, response_size)

def read_log():
    log_entries = []
    for line in sys.stdin:
        line = line.strip()
        if line:  # Ensure the line is not empty
            try:
                log_entry = parse_apache_log(line)
                log_entries.append(log_entry)
            except ValueError as e:
                print(f"Error parsing log line: {e}", file=sys.stderr)
    return log_entries
        
def sort_log(log_entries, tuple_index):
    """
    Sorts log entries based on the specified tuple index.

    Parameters:
    - log_entries: A list of tuples, each representing a log entry.
    - tuple_index: The index of the tuple element to sort by.

    Returns:
    - A list of tuples sorted based on the specified tuple element.
    """
    try:
        return sorted(log_entries, key=lambda entry: entry[tuple_index])
    except IndexError:
        print(f"Error: The specified index ({tuple_index}) is out of bounds for the log entry tuples.")
        return []
    except TypeError:
        print(f"Error: The specified index must be an integer.")
        return []
    
def get_entries_by_addr(log_entries, address):
    """
    Filters log entries by the given IP address or hostname.

    Parameters:
    - log_entries: A list of tuples, each representing a log entry.
    - address: A string representing the IP address or hostname to filter by.

    Returns:
    - A list of tuples representing log entries that match the given address.
    """
    filtered_entries = [entry for entry in log_entries if entry[0] == address]
    return filtered_entries

if __name__ == "__main__":
    # Test the log parsing
    log_entries = read_log()
    for entry in log_entries:
        print(entry)
        
    # Sort by status code (index 3)
    sorted_log = sort_log(log_entries, 3)
    for entry in sorted_log:
        print(entry)
        
    # Filter by a specific IP address
    address = "unicomp6.unicomp.net"
    entries_by_addr = get_entries_by_addr(log_entries, address)
    for entry in entries_by_addr:
        print(entry)