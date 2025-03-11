#cython: language_level=3
cimport libc.stdlib as stdlib
cimport libc.string as string

cdef extern from "fibonacci.h":
    char* fibonacci(char*)

def fibonacci_py(n: int, encoding: str="utf-8", errors: str="strict") -> int:
    n_str:str = hex(n).lstrip("0x") # int to str
    n_bytes: bytes = n_str.encode(encoding=encoding, errors=errors) # str to bytes
    cdef char* m_str_c
    try:
        m_str_c = fibonacci(n_bytes)
        m_bytes: bytes = m_str_c[:] # copy
        m_str: str = m_bytes.decode(encoding=encoding, errors=errors) # bytes to str
        return int(m_str, 16) # str to int
    finally:
        stdlib.free(m_str_c)
