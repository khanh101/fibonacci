import time
from fibonacci import *
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
    t1 = time.perf_counter()
    x = fibonacci(n)
    t2 = time.perf_counter()
    y = fibonacci_faster(n)
    t3 = time.perf_counter()
    print(y-x)
    print((t3-t2)/(t2-t1))