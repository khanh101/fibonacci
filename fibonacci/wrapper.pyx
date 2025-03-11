#cython: language_level=3
from libc.stdint cimport *


cdef extern from "fibonacci.h":
    int echo_int(int)
    char* echo_string(int)
    void fill_array(int*, int, int)
    uint64_t fibonacci(uint64_t)

def fibonacci_py(n: int) -> int:
    cdef uint64_t n_c = n
    cdef uint64_t m_c = fibonacci(n_c)
    return int(m_c)
