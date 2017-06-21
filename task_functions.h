#ifndef __TASK_FUNC__
#define __TASK_FUNC__

#include "defines.h"
#define RDTSC(var)                                   \
{                                                    \
    __asm__ __volatile__ (                           \
        "xor %%eax, %%eax\n\t"                       \
        "rdtsc\n\t"                                  \
        "mov %%eax, %0\n\t"                         \
        : "=r" (var)                                 \
        : /* no input */                             \
        : "%eax"                             \
    );                                               \
}



unsigned int get_random(unsigned int min, unsigned int max);
bool get_random_bool();

#endif
