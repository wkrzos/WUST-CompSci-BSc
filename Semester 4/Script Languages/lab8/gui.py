import sys
import re
from datetime import datetime
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QVBoxLayout, QListWidget, QLabel, QHBoxLayout, QPushButton, QFileDialog, QFormLayout, QDateEdit
from PyQt5.QtCore import QDate, Qt

def parse_apache_log(log_line):
    log_pattern = r'(\S+) - - \[(.*?)\] "(.*?)" (\d{3}) (\d+|-)'
    match = re.match(log_pattern, log_line)
    if match is None:
        raise ValueError("Invalid log line")
    groups = match.groups()

    timestamp_format = "%d/%b/%Y:%H:%M:%S %z"
    timestamp = datetime.strptime(groups[1], timestamp_format)
    method, resource = groups[2].split(' ')[0], groups[2].split(' ')[1]

    status_code = int(groups[3])
    response_size = int(groups[4]) if groups[4].isdigit() else 0

    return {
        'remote_host': groups[0],
        'date': timestamp.strftime('%Y-%m-%d'),
        'time': timestamp.strftime('%H:%M:%S'),
        'timezone': timestamp.strftime('%z'),
        'method': method,
        'resource': resource,
        'status_code': status_code,
        'response_size': response_size
    }

class LogBrowserApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Log Browser')
        self.setGeometry(100, 100, 800, 600)
        self.all_log_entries = []
        self.current_index = -1
        self.initUI()

    def initUI(self):
        central_widget = QWidget(self)
        self.setCentralWidget(central_widget)
        main_layout = QVBoxLayout(central_widget)

        self.log_list = QListWidget()
        self.log_list.itemSelectionChanged.connect(self.update_detail_view)
        main_layout.addWidget(self.log_list)

        self.setup_detail_view(main_layout)
        self.setup_controls(main_layout)

    def setup_detail_view(self, layout):
        detail_layout = QFormLayout()
        self.remote_host_label = QLabel()
        self.date_label = QLabel()
        self.time_label = QLabel()
        self.timezone_label = QLabel()
        self.method_label = QLabel()
        self.resource_label = QLabel()
        self.status_code_label = QLabel()
        self.response_size_label = QLabel()

        self.remote_host_label.setTextInteractionFlags(Qt.TextSelectableByMouse)
        self.date_label.setTextInteractionFlags(Qt.TextSelectableByMouse)
        self.time_label.setTextInteractionFlags(Qt.TextSelectableByMouse)
        self.timezone_label.setTextInteractionFlags(Qt.TextSelectableByMouse)
        self.method_label.setTextInteractionFlags(Qt.TextSelectableByMouse)
        self.resource_label.setTextInteractionFlags(Qt.TextSelectableByMouse)
        self.status_code_label.setTextInteractionFlags(Qt.TextSelectableByMouse)
        self.response_size_label.setTextInteractionFlags(Qt.TextSelectableByMouse)

        detail_layout.addRow("Remote host:", self.remote_host_label)
        detail_layout.addRow("Date:", self.date_label)
        detail_layout.addRow("Time:", self.time_label)
        detail_layout.addRow("Timezone:", self.timezone_label)
        detail_layout.addRow("Method:", self.method_label)
        detail_layout.addRow("Resource:", self.resource_label)
        detail_layout.addRow("Status code:", self.status_code_label)
        detail_layout.addRow("Response size (B):", self.response_size_label)

        layout.addLayout(detail_layout)

    def setup_controls(self, layout):
        controls_layout = QHBoxLayout()

        self.load_button = QPushButton("Load Log File")
        self.load_button.clicked.connect(self.load_log_file)
        controls_layout.addWidget(self.load_button)

        self.from_date = QDateEdit(calendarPopup=True)
        self.from_date.setDate(QDate.currentDate().addDays(-1))
        self.from_date.setDisplayFormat("yyyy-MM-dd")
        controls_layout.addWidget(self.from_date)

        self.to_date = QDateEdit(calendarPopup=True)
        self.to_date.setDate(QDate.currentDate())
        self.to_date.setDisplayFormat("yyyy-MM-dd")
        controls_layout.addWidget(self.to_date)

        self.filter_button = QPushButton("Filter Logs")
        self.filter_button.clicked.connect(self.filter_logs)
        controls_layout.addWidget(self.filter_button)

        self.reset_button = QPushButton("Reset Filter")
        self.reset_button.clicked.connect(self.reset_filter)
        controls_layout.addWidget(self.reset_button)

        self.prev_button = QPushButton("Previous")
        self.prev_button.clicked.connect(self.show_previous_log)
        self.prev_button.setEnabled(False)
        controls_layout.addWidget(self.prev_button)

        self.next_button = QPushButton("Next")
        self.next_button.clicked.connect(self.show_next_log)
        self.next_button.setEnabled(False)
        controls_layout.addWidget(self.next_button)

        layout.addLayout(controls_layout)

    def load_log_file(self):
        options = QFileDialog.Options()
        file_path, _ = QFileDialog.getOpenFileName(self, "Open Log File", "", "Log Files (*.log);;All Files (*)", options=options)
        if file_path:
            self.read_log_file(file_path)

    def read_log_file(self, file_path):
        with open(file_path, 'r') as file:
            self.all_log_entries = [parse_apache_log(line.strip()) for line in file if line.strip()]
            self.display_logs(self.all_log_entries)
            self.update_navigation_buttons()

    def display_logs(self, log_entries):
        self.log_list.clear()
        for entry in log_entries:
            display_text = f"{entry['date']} - {entry['remote_host']} - {entry['status_code']}"
            self.log_list.addItem(display_text)

    def update_detail_view(self):
        self.current_index = self.log_list.currentRow()
        log_details = self.all_log_entries[self.current_index]
        self.display_log_details(log_details)
        self.update_navigation_buttons()

    def display_log_details(self, log_details):
        self.remote_host_label.setText(log_details['remote_host'])
        self.date_label.setText(log_details['date'])
        self.time_label.setText(log_details['time'])
        self.timezone_label.setText(log_details['timezone'])
        self.method_label.setText(log_details['method'])
        self.resource_label.setText(log_details['resource'])
        self.status_code_label.setText(str(log_details['status_code']))
        self.response_size_label.setText(f"{log_details['response_size']} B")

    def filter_logs(self):
        from_date = self.from_date.date().toPyDate()
        to_date = self.to_date.date().toPyDate()
        filtered_logs = [entry for entry in self.all_log_entries if from_date <= datetime.strptime(entry['date'], '%Y-%m-%d').date() <= to_date]
        self.display_logs(filtered_logs)
        self.update_navigation_buttons()

    def reset_filter(self):
        self.display_logs(self.all_log_entries)
        self.update_navigation_buttons()

    def show_previous_log(self):
        if self.current_index > 0:
            self.log_list.setCurrentRow(self.current_index - 1)

    def show_next_log(self):
        if self.current_index < len(self.all_log_entries) - 1:
            self.log_list.setCurrentRow(self.current_index + 1)

    def update_navigation_buttons(self):
        self.prev_button.setEnabled(self.current_index > 0)
        self.next_button.setEnabled(self.current_index < len(self.all_log_entries) - 1)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = LogBrowserApp()
    ex.show()
    sys.exit(app.exec_())
