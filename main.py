import time
from fibonacci import fibonacci
import sys


def fibonacci_py(n: int) -> int:
    if n <= 1:
        return n
    l, r = 0, 1
    for _ in range(n-1):
        l, r = r, l + r
    return r
if __name__ == "__main__":
    sys.set_int_max_str_digits(0) # no conversion limit
    n = int(sys.argv[1])
    x = fibonacci(n)
    print(x, file=sys.stdout)