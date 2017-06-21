#include "tactics.h"

// ACTIONS +++++++++++++++++++++
// +++++++++++++++++++++++++++++
void destroy() {
    char* ptr;
    for(ptr = (char*)ALREDEDOR; ptr < (char*) ALREDEDOR+ALREDEDOR_SIZE; ptr++) {
      *ptr = 0;
    };
}


// ROUTINES ++++++++++++++++++++
// +++++++++++++++++++++++++++++
unsigned int random() {
    unsigned int n;
    __asm__ volatile (
        "rdtsc \n\t"
        "movl %%eax, %0 \n\t"
        : "=r"(n) // outputs
    );
    return n;
}