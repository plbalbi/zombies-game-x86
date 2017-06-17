/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"

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
    INC_INDEX(running_A);
    while(1) {
      if (tasks_A[running_A]) {
        return GDT_IDX_TSS_ZOMBIS_A + running_A;
      }
      INC_INDEX(running_A);
    }
  }else if(active_tasks_B > 0){
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
