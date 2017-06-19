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
  while(1) {
    char* ptr;
    for(ptr = (char*)ALREDEDOR; ptr < (char*) ALREDEDOR_SIZE; ptr++) {
      *ptr = 0xDE;
    };
    syscall_mover(ADE);
    syscall_mover(DER);
    syscall_mover(ADE);
    syscall_mover(IZQ);
  }
}
