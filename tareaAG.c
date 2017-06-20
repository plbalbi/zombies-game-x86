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
  char* ptr;
  while (1) {
    syscall_mover(ADE);
    for(ptr = (char*)ALREDEDOR; ptr < (char*) ALREDEDOR+ALREDEDOR_SIZE; ptr++) {
      *ptr = 0;
    };
  };
}
