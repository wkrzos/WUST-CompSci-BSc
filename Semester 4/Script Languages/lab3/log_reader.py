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

def get_entries_by_code(log_entries, status_code):
    """
    Filters log entries by HTTP status code.

    Parameters:
    - log_entries: A list of tuples, each representing a log entry.
    - status_code: An integer representing the HTTP status code to filter by.

    Returns:
    - A list of tuples representing log entries with the given status code.
    """
    try:
        code = int(status_code)
        if code < 100 or code > 599:
            raise ValueError("Invalid HTTP status code.")
        return [entry for entry in log_entries if entry[3] == code]
    except ValueError as e:
        print(f"Error: {e}")
        return []

def get_failed_reads(log_entries, combined=False):
    """
    Returns lists of log entries with HTTP status codes 4xx and 5xx.

    Parameters:
    - log_entries: A list of tuples representing log entries.
    - combined: A boolean indicating whether to return a combined list or separate lists.

    Returns:
    - Either two separate lists (4xx and 5xx) or a combined list of tuples, based on the 'combined' parameter.
    """
    client_errors = [entry for entry in log_entries if 400 <= entry[3] < 500]
    server_errors = [entry for entry in log_entries if 500 <= entry[3] < 600]
    
    if combined:
        return client_errors + server_errors
    else:
        return client_errors, server_errors
    
def get_entries_by_extension(log_entries, extension):
    extension = extension.lower()
    return [entry for entry in log_entries if entry[2].lower().endswith(f".{extension}")]

def entry_to_dict(entry):
    return {
        "address": entry[0],
        "timestamp": entry[1],
        "request": entry[2],
        "status_code": entry[3],
        "response_size": entry[4]
    }
    
def log_to_dict(log_entries):
    """
    Converts a list of log entry tuples into a dictionary, grouping entries by IP address or domain name.

    Parameters:
    - log_entries: A list of tuples, each representing a log entry.

    Returns:
    - A dictionary with IP addresses or domain names as keys and lists of dictionary-formatted entries as values.
    """
    log_dict = {}
    for entry in log_entries:
        entry_dict = entry_to_dict(entry)
        address = entry_dict["address"]
        if address not in log_dict:
            log_dict[address] = []
        log_dict[address].append(entry_dict)
    return log_dict
    
def get_addrs(entries_dict):
    """
    Extracts IP addresses or domain names from the dictionary keys.

    Parameters:
    - entries_dict: A dictionary with IP addresses or domain names as keys.

    Returns:
    - A list of IP addresses or domain names.
    """
    return list(entries_dict.keys())

def print_dict_entry_dates(entries_dict):
    """
    Prints detailed information for each host from the log entries dictionary, including
    the number of requests, dates of the first and last requests, and the ratio of successful
    requests (status code 200) to the total number of requests.

    Parameters:
    - entries_dict: A dictionary where each key is an IP address or domain name, and the value
                    is a list of dictionaries representing log entries for that host.
    """
    for addr, entries in entries_dict.items():
        # Extract dates and status codes from entries
        dates = [entry['timestamp'] for entry in entries]
        status_codes = [entry['status_code'] for entry in entries]
        
        # Calculate required metrics
        num_requests = len(entries)
        first_request = min(dates) if dates else "N/A"
        last_request = max(dates) if dates else "N/A"
        success_ratio = status_codes.count(200) / num_requests if num_requests > 0 else 0
        
        # Print the gathered information
        print(f"Host: {addr}")
        print(f"  Number of requests: {num_requests}")
        print(f"  Date of first request: {first_request}")
        print(f"  Date of last request: {last_request}")
        print(f"  Ratio of 200 responses: {success_ratio:.2f}")
        print("----------")



def print_entries(entries):
    for entry in entries:
        print(entry)
    print("---------- End of Entries ----------\n")      
    
if __name__ == "__main__":
    
    ### Excersise 1
    # Test the log parsing
    log_entries = read_log()
    print_entries(log_entries)
        
    ### Excersise 2
    # Sort by status code (index 3)
    sorted_log = sort_log(log_entries, 3)
    print_entries(sorted_log)
        
    # Filter by a specific IP address
    address = "unicomp6.unicomp.net"
    entries_by_addr = get_entries_by_addr(log_entries, address)
    print_entries(entries_by_addr)
    
    # Filter by a specfic code
    code = 200
    entries_by_code = get_entries_by_code(log_entries, 200)
    print_entries(entries_by_code)
        
    # Get failed reads
    failed_reads = get_failed_reads(log_entries)
    print_entries(failed_reads)
        
    # Get entries by extension
    extension = "txt"
    entries_by_extension = get_entries_by_extension(log_entries, extension)
    print_entries(entries_by_extension)
    
    ### Exercise 3
    
    # Convert the log entries to a dictionary grouped by IP or domain, with dictionary-formatted entries
    entries_dict = log_to_dict(log_entries)

    # Test get_addrs to extract and print all unique IP addresses or domain names from the log entries
    print("Testing get_addrs")
    addresses = get_addrs(entries_dict)
    print(addresses)
    print("---------- End of get_addrs Test ----------\n")
    
    # Test print_dict_entry_dates to print detailed information for each IP address or domain
    print("Testing print_dict_entry_dates")
    print_dict_entry_dates(entries_dict)
    print("---------- End of print_dict_entry_dates Test ----------\n")