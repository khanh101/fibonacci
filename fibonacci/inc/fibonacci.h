#ifndef __FIBONACCI__
#define __FIBONACCI__

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

// some example functions for reference
int echo_int(int);
char* echo_string(char*);
void fill_array(int*, int, int);

// fibonacci: return the n-th fibonacci number
uint64_t fibonacci(uint64_t n);

#ifdef __cplusplus
}
#endif


#endif // __FIBONACCI__