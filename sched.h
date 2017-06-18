/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "screen.h"
#include "tss.h"

#define INC_INDEX(index) index = (index+1)%8

bool tasks_A[8];
bool tasks_B[8];
unsigned short running_A;
unsigned short running_B;
unsigned int next_player;

unsigned int sched_proximo_indice();


#endif	/* !__SCHED_H__ */
