/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
#include "screen.h"
#include "debug.h"
#include "tss.h"

bool tasks_A[8] = {};
bool tasks_B[8] = {};
unsigned short running_A = 0;
unsigned short running_B = 0;
unsigned int next_player = player_A;


unsigned int sched_proximo_indice() {
  unsigned int active_tasks_A = 0, active_tasks_B = 0;
  int i;
  for (i = 0; i < 8; i++) {
    active_tasks_A+=tasks_A[i];
    active_tasks_B+=tasks_B[i];
  }

  if ((next_player == player_A || active_tasks_B == 0) && active_tasks_A > 0) {
    next_player = player_B;
    INC_INDEX(running_A);
    while(1) {
      if (tasks_A[running_A]) {
        return GDT_IDX_TSS_ZOMBIS_A + running_A;
      }
      INC_INDEX(running_A);
    }
  }else if(active_tasks_B > 0){
    next_player = player_A;
    INC_INDEX(running_B);
    while(1) {
      if (tasks_B[running_B]) {
        return GDT_IDX_TSS_ZOMBIS_B + running_B;
      }
      INC_INDEX(running_B);
    }
  }else{
    return GDT_IDX_TSS_IDLE;
  }
}

void sched_activar_zombi(unsigned int jugador, unsigned int i) {
  if (jugador == player_A) {
    tasks_A[i] = 1;
  } else {
    tasks_B[i] = 1;
  }
}

void sched_desactivar_zombi(unsigned int jugador, unsigned int i) {
  if (jugador == player_A) {
    tasks_A[i] = 0;
  } else {
    tasks_B[i] = 0;
  }
}

bool sched_hay_lugar_zombi(unsigned int jugador) {
  int i;
  if (jugador == player_A) {
    for (i = 0; i < 8; i++) {
      if (tasks_A[i] == 0) return true;
    }
  } else {
    for (i = 0; i < 8; i++) {
      if (tasks_B[i] == 0) return true;
    }
  }
  return false;
}

unsigned int sched_indice_libre(unsigned int jugador) {
  // REQ: sched_hay_lugar_zombi(jugador) == true
  int i;
  if (jugador == player_A) {
    for (i = 0; i < 8; i++) {
      if (tasks_A[i] == 0) return i;
    }
  } else {
    for (i = 0; i < 8; i++) {
      if (tasks_B[i] == 0) return i;
    }
  }
  error("ASSERT ERROR: No hay zombi libre (sched_indice_libre)");
  return 0xDEAD;
}
