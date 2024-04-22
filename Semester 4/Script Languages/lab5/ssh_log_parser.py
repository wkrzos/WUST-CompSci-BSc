
import argparse
import re
from collections import Counter
import logging
import sys
import random

def parse_log_entry(log_entry):
    pattern = (r"^(?P<date>[A-Za-z]+\s\d+\s\d+:\d+:\d+) "
               r"(?P<host>\S+) "
               r"sshd\[\d+\]: "
               r"(?P<message>.+)$")
    match = re.match(pattern, log_entry)
    if match:
        return match.groupdict()
    return None

def get_ipv4s_from_log(log_entry_dict):
    if log_entry_dict is None:
        return []  # Return an empty list if log_entry_dict is None
    ipv4_pattern = r"\b(?:\d{1,3}\.){3}\d{1,3}\b"
    addresses = re.findall(ipv4_pattern, log_entry_dict.get("message", ""))
    return 

def get_user_from_all_ssh_logs(log_entries):
    """
    Extract usernames from various SSH log entries, handling different message patterns.
    :param log_entries: A list of SSH log entry strings.
    :return: A list of extracted usernames.
    """
    users = []
    # Patterns that might indicate a user action or information
    patterns = [
        r"Invalid user (\S+)",  # Explicit invalid user messages
        r"Failed password for invalid user (\S+)",  # Failed password attempts for invalid users
        r"input_userauth_request: invalid user (\S+)",  # Invalid userauth requests
    ]

    for log_entry in log_entries:
        for pattern in patterns:
            match = re.search(pattern, log_entry)
            if match:
                user = match.group(1)
                if user not in users:  # Avoid duplicates
                    users.append(user)
    return users

# Sample log entries for demonstration
log_entries = [
    "Dec 10 06:55:46 LabSZ sshd[24200]: reverse mapping checking getaddrinfo for ns.marryaldkfaczcz.com [173.234.31.186] failed - POSSIBLE BREAK-IN ATTEMPT!",
    "Dec 10 06:55:46 LabSZ sshd[24200]: Invalid user webmaster from 173.234.31.186",
    "Dec 10 06:55:48 LabSZ sshd[24200]: Failed password for invalid user webmaster from 173.234.31.186 port 38926 ssh2",
    "Dec 10 07:07:38 LabSZ sshd[24206]: Invalid user test9 from 52.80.34.196",
    "Dec 10 07:07:45 LabSZ sshd[24206]: Failed password for invalid user test9 from 52.80.34.196 port 36060 ssh2",
    "Dec 10 07:11:42 LabSZ sshd[24224]: Invalid user chen from 202.100.179.208",
]

# Extract users from the provided log entries
extracted_users = get_user_from_all_ssh_logs(log_entries)
print(extracted_users)


def get_message_type(log_entry_dict):
    if log_entry_dict is None:
        return "other"  # Assume the message type is "other" if log_entry_dict is None
    message = log_entry_dict.get("message", "")
    if "POSSIBLE BREAK-IN ATTEMPT" in message:
        return "break-in attempt"
    elif "Invalid user" in message:
        return "invalid user"
    elif "Failed password" in message:
        return "failed login"
    elif "Connection closed" in message:
        return "connection closed"
    elif "authentication failure" in message:
        return "authentication failure"
    else:
        return "other"

def read_log_file(filepath):
    log_entries = []
    with open(filepath, 'r') as file:
        for line in file:
            log_entries.append(line.strip())
    return log_entries

def random_log_entries_for_user(log_entries, n=1):
    users_logs = {}
    for entry in log_entries:
        parsed_entry = parse_log_entry(entry)
        user = get_user_from_log(parsed_entry)
        if user:
            if user not in users_logs:
                users_logs[user] = []
            users_logs[user].append(entry)
    
    if not users_logs:
        return []
    
    random_user = random.choice(list(users_logs.keys()))
    user_logs = users_logs[random_user]
    return random.sample(user_logs, min(n, len(user_logs)))

def identify_frequent_users(log_entries):
    user_counts = Counter(get_user_from_log(parse_log_entry(entry)) for entry in log_entries if get_user_from_log(parse_log_entry(entry)))
    if not user_counts:
        return None, None
    
    most_frequent = user_counts.most_common(1)[0][0]
    least_frequent = user_counts.most_common()[-1][0]
    return most_frequent, least_frequent

# Function to execute actions based on CLI commands
def execute_cli(args):
    try:
        # Configure logging based on the provided log level
        log_level = getattr(logging, args.log_level.upper(), None)
        if log_level is None:
            raise ValueError(f"Invalid log level: {args.log_level}")
        logging.getLogger().setLevel(log_level)
        
        log_entries = read_log_file(args.log_file)

        if args.command == "ipv4s":
            for entry in log_entries:
                print(get_ipv4s_from_log(parse_log_entry(entry)))
        elif args.command == "user":
            for entry in log_entries:
                print(get_user_from_log(parse_log_entry(entry)))
        elif args.command == "message_type":
            for entry in log_entries:
                print(get_message_type(parse_log_entry(entry)))
        elif args.command == "get_random_logs":
            if args.number < 1:
                raise ValueError("Number of log entries must be at least 1.")
            random_entries = random_log_entries_for_user(log_entries, args.number)
            for entry in random_entries:
                print(entry)
        elif args.command == "most_and_least_frequent_users":
            most_frequent, least_frequent = identify_frequent_users(log_entries)
            if most_frequent and least_frequent:
                print(f"Most Frequent User: {most_frequent}\nLeast Frequent User: {least_frequent}")
            else:
                print("No users found in log entries.")
        else:
            raise ValueError(f"Unknown command: {args.command}")
    except ValueError as e:
        logging.error(str(e))
        sys.exit(1)
    except Exception as e:
        logging.error(f"An unexpected error occurred: {str(e)}")
        sys.exit(1)

# Updating CLI setup to include new functionalities
def setup_cli():
    parser = argparse.ArgumentParser(description="SSH Log Analysis Tool")
    parser.add_argument("log_file", help="Location of the SSH log file", type=str)
    parser.add_argument("-l", "--log_level", help="Minimum logging level (DEBUG, INFO, WARNING, ERROR, CRITICAL)", type=str, choices=["DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"], default="INFO")

    subparsers = parser.add_subparsers(help="Sub-command help", dest="command")

    parser_ipv4s = subparsers.add_parser("ipv4s", help="Extract IPv4 addresses from logs")
    parser_user = subparsers.add_parser("user", help="Extract user information from logs")
    parser_message_type = subparsers.add_parser("message_type", help="Classify log messages")

    parser_random_logs = subparsers.add_parser("get_random_logs", help="Get random log entries for a user")
    parser_random_logs.add_argument("-n", "--number", help="Number of log entries to analyze", type=int, default=1)

    parser_most_least_frequent = subparsers.add_parser("most_and_least_frequent_users", help="Identify most and least frequent users")

    return parser

if __name__ == "__main__":
    parser = setup_cli()
    args = parser.parse_args()
    execute_cli(args)