import time
from fibonacci import fibonacci
import sys

sys.set_int_max_str_digits(0) # no conversion limit

def fibonacci_py(n: int) -> int:
    if n <= 1:
        return n
    l, r = 0, 1
    for _ in range(n-1):
        l, r = r, l + r
    return r

n = int(sys.argv[1])

t1 = time.perf_counter()
x = fibonacci(n)
t2 = time.perf_counter()
# y = fibonacci_py(n)
t3 = time.perf_counter()
# assert x == y, f"wrong result"
print(f"c time: {t2-t1}")
# print(f"py time: {t3-t2}")