import random
import string

class PasswordGenerator:
    def __init__(self, length, charset=string.ascii_letters + string.digits, count=1):
        self.length = length
        self.charset = charset
        self.count = count
        self.generated_count = 0

    def __iter__(self):
        return self

    def __next__(self):
        if self.generated_count >= self.count:
            raise StopIteration
        self.generated_count += 1
        return ''.join(random.choice(self.charset) for _ in range(self.length))

# Generate 5, 8-character passwords
password_gen = PasswordGenerator(8, count=5)

print(next(password_gen))
print(next(password_gen))

for password in password_gen:
    print(password)
