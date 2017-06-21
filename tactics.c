#include "tactics.h"

// ACTIONS +++++++++++++++++++++
// +++++++++++++++++++++++++++++
void destroy() {
    char* ptr;
    for(ptr = (char*)ALREDEDOR; ptr < (char*) ALREDEDOR+ALREDEDOR_SIZE; ptr++) {
      *ptr = 0;
    };
}

void freeze(char* page) {
    char* ptr;
    for(ptr = page; ptr < (char*)page + PAGE_SIZE; ptr++) {
      *ptr = 0xf8; // clear carry flag, 1 bit
    };
    //jmp near to the beginning-ish
    page[PAGE_SIZE-6] = 0xe9;
    page[PAGE_SIZE-5] = 0x36;
    page[PAGE_SIZE-4] = 0xf1;
    page[PAGE_SIZE-3] = 0xff;
    page[PAGE_SIZE-2] = 0xff;
    page[PAGE_SIZE-1] = 0x40;
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