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

// fibonacci: return the n-th fibonacci number (n in hex string)
char* fibonacci(char* n_str);

#ifdef __cplusplus
}
#endif


#endif // __FIBONACCI__