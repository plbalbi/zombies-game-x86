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
    int i;
    unsigned long* p = (unsigned long*) (0x8000000+(2<<13));
    while(1){
        for(i=0; i<5; i++){
            *p = 0;
            p++;
            syscall_mover(ADE);
            syscall_mover(ADE);
            syscall_mover(DER);
        }
        for(i=0; i<5; i++){
            *p = 0;
            p++;
            syscall_mover(DER);
            syscall_mover(ATR);
            syscall_mover(IZQ);
            syscall_mover(IZQ);
            syscall_mover(ADE);
            syscall_mover(ADE);
            syscall_mover(ADE);
        }
        for(i=0; i<5; i++){
            *p = 0;
            p++;
            syscall_mover(ADE);
            syscall_mover(DER);
            syscall_mover(ATR);
            syscall_mover(ADE);
            syscall_mover(IZQ);
            syscall_mover(ATR);
            syscall_mover(ADE);
            syscall_mover(IZQ);
        }
        for(i=0; i<5; i++){
            *p = 0;
            p++;
            syscall_mover(ADE);
            syscall_mover(ADE);
            syscall_mover(DER);
            syscall_mover(DER);
            syscall_mover(DER);
        }
    }

   while(1) { __asm __volatile("mov $2, %%eax":::"eax"); }
}
