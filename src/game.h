/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "defines.h"

int y_a, y_b;
unsigned short tipo_a, tipo_b; // Tipo de zombi
unsigned short restantes_a, restantes_b;
unsigned short puntaje_a, puntaje_b;
posicion zombis_pos_a[8];
posicion zombis_pos_b[8];
unsigned short zombis_tipo_a[8];
unsigned short zombis_tipo_b[8];

bool debug;
bool debug_hubo_excepcion;

typedef enum direccion_e { IZQ = 0xAAA, DER = 0x441, ADE = 0x83D, ATR = 0x732 } direccion;

void game_mover_jugador(unsigned int jugador, unsigned int value);

void game_cambiar_tipo(unsigned int jugador, unsigned int value);

void game_lanzar_zombi(unsigned int jugador);

void game_move_current_zombi(direccion dir);

bool game_hay_lugar_zombi(unsigned int jugador);

unsigned int game_slot_zombi_libre(unsigned int jugador);

#endif  /* !__GAME_H__ */
