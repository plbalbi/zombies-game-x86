/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "colors.h"
#include "defines.h"
#include "game.h"
#include "syscall.h"

#define PRIME1 104743
#define PRIME2 105871
#define PRIME3 1117

void task() {
    int xn;
    __asm __volatile("rdtsc");
    __asm __volatile("\t movl %%eax,%0" : "=r"(xn));
    if(xn%100 < 33){
        while (1) {
            xn = (PRIME1*xn + PRIME2) % PRIME3;
            int r = xn%5;
            if (r==0) {
                syscall_mover(ADE);
            }else if(r<2){
                syscall_mover(IZQ);
            }else{
                syscall_mover(DER);
            }
        }
    }else if(xn%100<66){
        while (1) {
            xn = (PRIME1*xn + PRIME2) % PRIME3;
            int r = xn%5;
            if (r==0) {
                syscall_mover(ADE);
            }else if(r<4){
                syscall_mover(DER);
            }else{
                syscall_mover(IZQ);
            }
        }
    }else{
        int c = 0;
        syscall_mover(ADE);
        syscall_mover(ADE);
        syscall_mover(ADE);
        syscall_mover(ADE);
        syscall_mover(ADE);
        syscall_mover(ADE);
        while (1) {
            xn = (PRIME1*xn + PRIME2) % PRIME3;
            int r = xn%7;
            if (r==0 && c>0) {
                syscall_mover(ATR);
            }else if(r<3){
                syscall_mover(IZQ);
            }else if(r<5){
                syscall_mover(DER);
            }else{
                syscall_mover(ADE);
                c++;
            }
        }
    }
    __asm __volatile("xchg %%bx, %%bx" : :);
    /* Tarea */
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
