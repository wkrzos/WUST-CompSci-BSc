def acronym(words: list[str]) -> str:
    return ''.join(word[0].upper() for word in words)

""" def acronym(list_of_strings: list[str]) -> str:
    return ''.join(map(lambda s: s[0].upper(), filter(bool, list_of_strings))) """

print(acronym(["Ale", "Bajer", "co nie?"]))

def median(numbers: list[float]) -> float:
    sorted_numbers = sorted(numbers)
    n = len(sorted_numbers)
    mid = n // 2
    return sorted_numbers[mid] if n % 2 != 0 else (sorted_numbers[mid - 1] + sorted_numbers[mid]) / 2

print(median([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]))

def root(x: float, epsilon=0.1) -> float:
    def helper(guess):
        next_guess = (guess + x / guess) / 2.0
        return next_guess if abs(next_guess**2 - x) < epsilon else helper(next_guess)
    return helper(x / 2.0)

print(root(9))
print(root(9, 0.0001))

""" def make_alpha_dict(s: str) -> dict:
    words = s.split()
    alpha_dict = {}

    for word in words:
        for char in word:
            if char.isalpha():
                if char not in alpha_dict:
                    alpha_dict[char] = [word]
                elif word not in alpha_dict[char]:
                    alpha_dict[char].append(word)

    return alpha_dict """
    
def make_alpha_dict(string: str) -> dict:
    words = string.split()
    is_alpha = lambda x: x.isalpha()
    return {char: [word for word in words if char in word] for char in set(filter(is_alpha, string))}

print(make_alpha_dict("on i ona"))
print(make_alpha_dict("ala ma kota a kot ma ale"))

""" def flatten(lst: list) -> list:
    flat_list = []
    for item in lst:
        if isinstance(item, (list, tuple)):  # Check if the item is a list or a tuple
            flat_list.extend(flatten(item))  # Recursively flatten and extend the flat list
        else:
            flat_list.append(item)  # Append the non-list item to the flat list
    return flat_list """
    
def flatten(list: list) -> list:
    def helper(item):
        if isinstance(item, (list, tuple)):
            return [element for sublist in item for element in helper(sublist)]
        else:
            return [item]
    return [element for item in list for element in helper(item)]

print(flatten([1, [2, 3], [[4, 5], 6]]))