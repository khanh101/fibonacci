#cython: language_level=3
cimport libc.stdlib as stdlib
cimport libc.string as string

cdef extern from "fibonacci.h":
    char* fibonacci(char*)

import time

def int_to_hex_bytes(x: int) -> bytes:
    encoding: str = "utf-8"
    errors: str = "strict"
    x_str: str = hex(x).lstrip("0x") # int to str
    x_bytes: bytes = x_str.encode(encoding=encoding, errors=errors) # str to bytes
    return x_bytes

def hex_bytes_to_int(x_bytes: bytes) -> int:
    encoding: str = "utf-8"
    errors: str = "strict"
    x_str: str = x_bytes.decode(encoding=encoding, errors=errors) # bytes to str
    x: int = int(x_str, 16)
    return x


def fibonacci_py(n: int, encoding: str="utf-8", errors: str="strict") -> int:
    cdef char* m_str_c
    try:
        m_str_c = fibonacci(int_to_hex_bytes(n))
        m_bytes: bytes = m_str_c[:] # copy
        return hex_bytes_to_int(m_bytes)
    finally:
        stdlib.free(m_str_c)
