/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "defines.h"
#include "screen.h"
#include "mmu.h"

int y_a, y_b;
unsigned short tipo_a, tipo_b; // Tipo de zombi
unsigned short restantes_a, restantes_b;
unsigned short puntaje_a, puntaje_b;
posicion zombis_pos_a[];
posicion zombis_pos_b[];

typedef enum direccion_e { IZQ = 0xAAA, DER = 0x441, ADE = 0x83D, ATR = 0x732 } direccion;

void game_jugador_mover(unsigned int jugador, unsigned int value);

void game_lanzar_zombi(unsigned int jugador);

void game_move_current_zombi(direccion dir);


#endif  /* !__GAME_H__ */
