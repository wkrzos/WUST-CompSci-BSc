import logging
from functools import wraps
from time import time

logging.basicConfig(level=logging.DEBUG, format='%(asctime)s - %(levelname)s - %(message)s')

def log(level='INFO'):
    def decorator(obj):
        if isinstance(obj, type):
            # To jest dekorator klasy
            class Wrapper(obj):
                def __init__(self, *args, **kwargs):
                    logging.log(getattr(logging, level), f'Creating instance of {obj.__name__} with args={args}, kwargs={kwargs}')
                    super().__init__(*args, **kwargs)
            return Wrapper
        else:
            # To jest dekorator funkcji
            @wraps(obj)
            def wrapper(*args, **kwargs):
                logging.log(getattr(logging, level), f'Calling {obj.__name__} with args={args}, kwargs={kwargs}')
                start_time = time()
                result = obj(*args, **kwargs)
                end_time = time()
                logging.log(getattr(logging, level), f'Finished {obj.__name__} in {end_time - start_time:.4f} sec with result {result}')
                return result
            return wrapper
    return decorator

# Przykłady użycia dekoratora
@log('DEBUG')
def test_function(a, b):
    return a + b

@log('INFO')
class TestClass:
    def __init__(self, value):
        self.value = value

test_function(3, 4)
test_instance = TestClass(10)
