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
    /* Ok, el problema es que el clérico se sigue moviendo
      forever and ever. Seguí esto con el bochs, y por alguna
      razón, el lugar de la memoria en la que está guardado
      la variable 'i', que es '[rbp-4] (0x8000fcc-4)' cada
      vez que se ejecuta 'syscall', se vuelve 0. En la siguiente
      linea se le resta 1, queda -1, y por eso nunca se rompe
      la guarda del while (Los registros generales quedan iguales).
    */

    /* Tarea */
    //__asm __volatile("xchg %%bx, %%bx" : :);
    int i = 10;
    while (i != 0) {
        syscall_mover(ADE);
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
