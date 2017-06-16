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


#define INC_INDEX(index) index = (index+1)%8;
unsigned int sched_proximo_indice() {

  short active_tasks_A = 0, active_tasks_B = 0;
  int i;
  for (i = 0; i < 8; i++) {
    active_tasks_A+=short(tasks_A[i]);
    active_tasks_B+=short(tasks_B[i]);
  }

  if ((next_player == player_A || active_tasks_B == 0) && active_tasks_A > 0) {
    INC_INDEX(running_A)
    while(1) {
      if (tasks_A[running_A]) {
        return running_A;
      }
      INC_INDEX(running_A)
    }
  }else if(active_tasks_B > 0){
    INC_INDEX(running_B)
    while(1) {
      if (tasks_B[running_B]) {
        return running_B + 8;
      }
      INC_INDEX(running_B)
  }else{
    return TSS_IDLE_INDEX;
  }
}
