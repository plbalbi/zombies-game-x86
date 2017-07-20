/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "tactics.h"
#include "syscall.h"

void task() {
    //__asm__("jmp next+4096*6"); // move ip back

    __asm__("next:");

    //    __asm__("mov 0x8000000, %eax"); //init dir
    __asm__("mov 1024*4, %eax"); // byte count
    //  __asm__("cmp %ebx, 0");
    //  __asm__("je loop");

    __asm__("loop:");
    __asm__("jmp loop");

}

#include "tactics.c"

