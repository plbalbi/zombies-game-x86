/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "syscall.h"
#include "tactics.h"

void task() {
    __asm__ ("mov $1, %%eax");
    __asm__ ("mov $20, %%eax");
}

#include "tactics.c"