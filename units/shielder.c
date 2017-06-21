/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "syscall.h"
#include "tactics.h"

void task(){

__asm__ (
    "begin:                 \n\t"
);

__asm__ (
    "movw $4096, %cx        \n\t"
    "movl $0x8001000, %ebx  \n\t"
    "copyA:                 \n\t"
    "movb $0x40, (%ebx)     \n\t"
    "inc %eax               \n\t"
    "inc %ebx               \n\t"
    "loop copyA             \n\t"

    "movw $4096, %cx        \n\t"
    "movl $0x8002000, %ebx  \n\t"
    "copyB:                 \n\t"
    "movb $0x40, (%ebx)     \n\t"
    "inc %eax               \n\t"
    "inc %ebx               \n\t"
    "loop copyB             \n\t"

    "movw $4096, %cx        \n\t"
    "movl $0x8003000, %ebx  \n\t"
    "copyC:                 \n\t"
    "movb $0x40, (%ebx)     \n\t"
    "inc %eax               \n\t"
    "inc %ebx               \n\t"
    "loop copyC             \n\t"
);



__asm__ (
    "jmp begin              \n\t"
);