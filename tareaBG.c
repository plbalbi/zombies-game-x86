/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "syscall.h"
#include "tactics.h"

void task() {
    int i;
    unsigned int dir = random() % 100;
    unsigned int length = (random() % 20) + 5;

    for (i = 0; i < 1000; i++) {
        destroy();
        __asm__ volatile ("xchg %bx, %bx");
        syscall_mover(ADE);
    }

    if (dir > 50) {
        for (i = 0; i < length; i++) {
            destroy();
            syscall_mover(DER);
        }
    } else {
        for (i = 0; i < length; i++) {
            destroy();
            syscall_mover(IZQ);
        }
    }

    while(1){
        destroy();
        syscall_mover(ADE); 
    };
}

#include "tactics.c"