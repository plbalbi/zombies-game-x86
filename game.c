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


// JUGADORES
// --------------------------

void game_mover_jugador(unsigned int jugador, unsigned int value) {
  int* ptr_y =  jugador == player_A ? &y_a : &y_b;
  unsigned short* ptr_tipo =  jugador == player_A ? &tipo_a : &tipo_b;
  unsigned short color =  jugador == player_A ? BG_RED : BG_BLUE;
  int x =  jugador == player_A ? 0 : 79;

  if (value == UP && (*ptr_y) > 0) {
    (*ptr_y)--;
    print_jugador(jugador, (*ptr_tipo), (*ptr_y));
    print(" ", x, ((*ptr_y)+1)+1, color);
  } else if (value == DOWN && (*ptr_y) < MAP_HEIGHT-1) {
    (*ptr_y)++;
    print_jugador(jugador, (*ptr_tipo), (*ptr_y));
    print(" ", x, ((*ptr_y)-1)+1, color);
  }
}

void game_cambiar_tipo(unsigned int jugador, unsigned int value) {
  int* ptr_y =  jugador == player_A ? &y_a : &y_b;
  unsigned short* ptr_tipo =  jugador == player_A ? &tipo_a : &tipo_b;

  if (value == UP && (*ptr_tipo) < 3) {
    (*ptr_tipo)++;
    print_jugador(jugador, (*ptr_tipo), (*ptr_y));
  } else if (value == DOWN && (*ptr_tipo) > 1) {
    (*ptr_tipo)--;
    print_jugador(jugador, (*ptr_tipo), (*ptr_y));
  } 
}

void game_lanzar_zombi(unsigned int jugador) {
  if (restantes_a != 0 && sched_hay_lugar_zombi(jugador)) {
    if (jugador == player_A) {
      // Juicy info
      posicion pos_zombi = { .x = 1, .y = y_a };
      unsigned int i = sched_indice_libre(jugador);

      // Actualizar variables del juego
      restantes_a--;
      zombis_pos_a[i] = pos_zombi;
      zombis_tipo_a[i] = tipo_a;

      // Rescribir estructuras de la tarea
      unsigned int cr3 = tss_leer_cr3(jugador, i);
      mmu_mapear_vision_zombi(jugador, cr3, pos_zombi.x, pos_zombi.y);
      //tss_zombisA[i].esp0 = mmu_prox_pag_libre() + PAGE_SIZE; FUUUUUUCUUUUUUUUUUUUUUUUUUUUUUUUUCK

      // Copiar zombi físicamente
      copiar_zombi(cr3, tipo_a, jugador);

      // Avisarle al scheduler
      sched_activar_zombi(jugador, i);

      // Pintar
      print_zombi(jugador, zombis_tipo_a[i], zombis_pos_a[i]);
    }
  }
}


// ZOMBIS
// --------------------------

void game_move_current_zombi(direccion dir) {
}