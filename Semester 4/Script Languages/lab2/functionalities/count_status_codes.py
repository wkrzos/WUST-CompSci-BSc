def count_status_codes(logs):
    """
    Counts the occurrences of each HTTP status code in the provided list of Log objects.

    Parameters:
    - logs: List[Log] - A list of Log objects.

    Returns:
    - dict: A dictionary where keys are status codes and values are the counts of each status code.
    """
    status_code_count = {}
    for log in logs:
        # Convert status code to int for uniformity, assuming all status codes are valid integers
        status_code = int(log.status_code)
        if status_code in status_code_count:
            status_code_count[status_code] += 1
        else:
            status_code_count[status_code] = 1
    return status_code_count

# Example usage of the count_status_codes function
# Assuming 'logs' is a list of Log objects
status_code_counts = count_status_codes(logs)

# Print the count of each status code
for status_code, count in status_code_counts.items():
    print(f"Status Code {status_code}: {count} times")