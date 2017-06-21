/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "colors.h"
#include "defines.h"
#include "game.h"
#include "syscall.h"
#include "task_functions.h"

#define MAGIC_NUM_OFF PAGE_SIZE/2
#define MAGIC_NUM 0x7D1A


void task() {
  int *magic_mark = (int*)(DIR_INICIO_ZOMBI_VISION + MAGIC_NUM_OFF);
  *magic_mark = MAGIC_NUM;
  char* ptr;
  char* src;
  char* ptr1;
  direccion side = DER;

  int forward = get_random(2, 15);
  for (; forward > 0; forward--) {
    syscall_mover(ADE);
  }
  if (get_random_bool()) {
    side = IZQ;
  }
  int side_count = 0;
  while (1) {
    for(ptr = (char*)ALREDEDOR; ptr < (char*) ALREDEDOR+ALREDEDOR_SIZE; ptr+=PAGE_SIZE) {
      if (*((int*)(ptr + MAGIC_NUM_OFF)) != MAGIC_NUM) {
        src = (char *)DIR_INICIO_ZOMBI_VISION;
        for (ptr1 = ptr; ptr1 - ptr < PAGE_SIZE; ptr1++) {
           *ptr1 = *src;
           src++;
        }
        magic_mark = ((int*)(ptr + MAGIC_NUM_OFF));
        *magic_mark = MAGIC_NUM;
      }
    }
    if (side_count >= 80) {
      syscall_mover(ADE);
      side_count = 0;
    }else{
      syscall_mover(side);
      side_count++;
    }
  }
}
