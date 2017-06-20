/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "colors.h"
#include "defines.h"
#include "game.h"
#include "syscall.h"

void task() {
    /* Tarea */
    //__asm __volatile("xchg %%bx, %%bx" : :);
    int i = 10;
    while (i != 0) {
        syscall_mover(DER);
        i--;
    }
    // syscall_mover(DER);
    // for(i=0;i<5;i++)
    // syscall_mover(ATR);
    // for(i=0;i<5;i++)
    // syscall_mover(IZQ);
    // for(i=0;i<500;i++)
    // syscall_mover(ATR);

    while(1) { __asm __volatile("mov $2, %%eax":::"eax"); }
}
