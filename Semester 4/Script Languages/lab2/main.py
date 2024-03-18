import fileinput
import log_reader
import count_status_codes

def main():
    
    logs = []
    counter = 0
    print("Reading logs...")
    for line in fileinput.input():
        try:
            log = parse_log_line(line)
            logs.append(log)
            counter += 1
            print(counter)
            if counter == 10:
                break
        except ValueError as e:
            print(e, file=sys.stderr)

    status_code_counts = count_status_codes(logs)
    
if __name__ == "__main__":
    main()