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

unsigned int sched_proximo_indice(void);

void sched_activar_zombi(unsigned int jugador, unsigned int i);
void sched_desactivar_zombi(unsigned int jugador, unsigned int i);
bool sched_hay_lugar_zombi(unsigned int jugador);
unsigned int sched_indice_libre(unsigned int jugador);

#endif	/* !__SCHED_H__ */
