/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "tactics.h"
#include "syscall.h"

void task() {
    while(1){
        freeze(ADELANTE);
        freeze(DIAG_ADE_DER);
        freeze(DIAG_ADE_IZQ);
    };
}

#include "tactics.c"