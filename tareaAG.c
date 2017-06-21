/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "syscall.h"
#include "tactics.h"

// TIENE 4K-4BYTES, NO LO TOQUEN QUE EXPLOTA


__asm__ (
    "begin:                 \n\t"

    "movw $4096, %cx        \n\t"
    "movl $0x8001000, %ebx  \n\t"
    "copyFirstA:            \n\t"
    "movb $0xf8, (%ebx)     \n\t"
    "inc %ebx               \n\t"
    "loop copyFirstA        \n\t"

    "movw $2000, %cx        \n\t"
    "movl $0x8000500, %eax  \n\t"
    "movl $0x8001500, %ebx  \n\t"
    "copyLastA:             \n\t"
    "movb (%eax), %dl       \n\t"
    "movb %dl, (%ebx)       \n\t"
    "inc %eax               \n\t"
    "inc %ebx               \n\t"
    "loop copyLastA         \n\t"


    "movw $4096, %cx        \n\t"
    "movl $0x8002000, %ebx  \n\t"
    "copyFirstB:            \n\t"
    "movb $0xf8, (%ebx)     \n\t"
    "inc %ebx               \n\t"
    "loop copyFirstB        \n\t"

    "movw $2000, %cx        \n\t"
    "movl $0x8000500, %eax  \n\t"
    "movl $0x8002500, %ebx  \n\t"
    "copyLastB:             \n\t"
    "movb (%eax), %dl       \n\t"
    "movb %dl, (%ebx)       \n\t"
    "inc %eax               \n\t"
    "inc %ebx               \n\t"
    "loop copyLastB         \n\t"


    "movw $4096, %cx        \n\t"
    "movl $0x8003000, %ebx  \n\t"
    "copyFirstC:            \n\t"
    "movb $0xf8, (%ebx)     \n\t"
    "inc %ebx               \n\t"
    "loop copyFirstC        \n\t"

    "movw $2000, %cx        \n\t"
    "movl $0x8000500, %eax  \n\t"
    "movl $0x8003500, %ebx  \n\t"
    "copyLastC:             \n\t"
    "movb (%eax), %dl       \n\t"
    "movb %dl, (%ebx)       \n\t"
    "inc %eax               \n\t"
    "inc %ebx               \n\t"
    "loop copyLastC         \n\t"

    "jmp begin              \n\t"
);

WALL
WALL
WALL

__asm__ (
    "beginI:                \n\t"

    "movw $4096, %cx        \n\t"
    "movl $0x8000000, %eax  \n\t"
    "movl $0x8006000, %ebx  \n\t"
    "copyAI:                \n\t"
    "movb (%eax), %dl      \n\t"
    "movb %dl, (%ebx)      \n\t"
    "inc %eax               \n\t"
    "inc %ebx               \n\t"
    "loop copyAI            \n\t"

    "movw $4096, %cx        \n\t"
    "movl $0x8000000, %eax  \n\t"
    "movl $0x8007000, %ebx  \n\t"
    "copyBI:                \n\t"
    "movb (%eax), %dl      \n\t"
    "movb %dl, (%ebx)      \n\t"
    "inc %eax               \n\t"
    "inc %ebx               \n\t"
    "loop copyBI            \n\t"

    "movw $4096, %cx        \n\t"
    "movl $0x8000000, %eax  \n\t"
    "movl $0x8008000, %ebx  \n\t"
    "copyCI:                \n\t"
    "movb (%eax), %dl      \n\t"
    "movb %dl, (%ebx)      \n\t"
    "inc %eax               \n\t"
    "inc %ebx               \n\t"
    "loop copyCI            \n\t"

    "jmp beginI             \n\t"
);

WALL

__asm__ (
    "jmp begin \n\t"
);