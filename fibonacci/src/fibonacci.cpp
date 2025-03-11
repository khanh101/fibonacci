#include "fibonacci.h"

uint64_t fibonacci(uint64_t n) {
  if (n < 2) {
    return 1;
  }
  return fibonacci(n - 1) + fibonacci(n - 2);
}