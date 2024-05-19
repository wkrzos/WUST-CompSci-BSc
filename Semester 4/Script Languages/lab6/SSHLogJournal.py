import datetime
from ipaddress import IPv4Address
from typing import Union, Iterator, Callable
from SSHLogEntry import MessageType, OtherSSHLogEntry, SSHAcceptedPassword, SSHErrorLogEntry, SSHLogEntry, SSHRejectedPassword

class SSHLogJournal:
    def __init__(self):
        self._ssh_log_entries: list[SSHLogEntry] = []

    def __getitem__(self, key: Union[int, slice, datetime.datetime, IPv4Address]) -> Union[SSHLogEntry, list[SSHLogEntry], Iterator[SSHLogEntry]]:
        if isinstance(key, (int, slice)):
            return self._ssh_log_entries[key]
        elif isinstance(key, datetime.datetime):
            return (
                log
                for log in self._ssh_log_entries
                if log.timestamp_with_current_year == key
            )
        elif isinstance(key, IPv4Address):
            return (
                log
                for log in self._ssh_log_entries
                if log.has_ipv4 and log.extract_ipv4() == key
            )
        else:
            raise TypeError("Invalid key type")

    def __len__(self) -> int:
        return len(self._ssh_log_entries)

    def __iter__(self) -> Iterator[SSHLogEntry]:
        return iter(self._ssh_log_entries)

    def __contains__(self, value: SSHLogEntry) -> bool:
        return value in self._ssh_log_entries

    def filter(self, predicate: Callable[[SSHLogEntry], bool]) -> Iterator[SSHLogEntry]:
        return filter(predicate, self._ssh_log_entries)

    def append(self, log: str) -> None:
        ssh_entry = self._create_ssh_entry(log)

        if not ssh_entry.validate():
            raise ValueError(f"Invalid log entry: {log}")

        self._ssh_log_entries.append(ssh_entry)

    @staticmethod
    def _create_ssh_entry(log: str) -> SSHLogEntry:
        if "Failed password for invalid user" in log:
            return SSHRejectedPassword(log)
        elif "Accepted password for" in log:
            return SSHAcceptedPassword(log)
        elif "error" in log:
            return SSHErrorLogEntry(log)
        else:
            return OtherSSHLogEntry(log)

    def get_logs_by_type(self, message_type: MessageType) -> list[SSHLogEntry]:
        return [log for log in self._ssh_log_entries if log.type == message_type]
