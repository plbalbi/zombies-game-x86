/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"

int y_a = 22, y_b = 22;
unsigned short tipo_a = 1, tipo_b = 1; // Tipo de zombi: 1,2 o 3
unsigned short restantes_a = 20, restantes_b = 20;
unsigned short puntaje_a = 0, puntaje_b = 0;
posicion zombis_pos_a[8] = {};
posicion zombis_pos_b[8] = {};
unsigned short zombis_tipo_a[8] = {};
unsigned short zombis_tipo_b[8] = {};

void game_jugador_mover(unsigned int jugador, unsigned int value) {
}
void game_lanzar_zombi(unsigned int jugador) {
}
void game_move_current_zombi(direccion dir) {
}

bool hay_lugar_zombi(unsigned int jugador) {
  int i;
  if (jugador == player_A) {
    for (i = 0; i < 8; i++) {
      if (zombis_tipo_a[i] == 0) return true;
    }
  } else {
    for (i = 0; i < 8; i++) {
      if (zombis_tipo_b[i] == 0) return true;
    }
  }
  return false;
}

unsigned int slot_zombi_libre(unsigned int jugador) {
  int i;
  if (jugador == player_A) {
    for (i = 0; i < 8; i++) {
      if (zombis_tipo_a[i] == 0) return i;
    }
  } else {
    for (i = 0; i < 8; i++) {
      if (zombis_tipo_b[i] == 0) return i;
    }
  }
  error("ASSERT ERROR: No hay zombi libre (slot_zombi_libre)");
  return 0xDEAD;
}