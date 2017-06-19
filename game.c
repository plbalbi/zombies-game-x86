/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "screen.h"
#include "sched.h"
#include "mmu.h"
#include "tss.h"

int y_a = 22, y_b = 22;
unsigned short tipo_a = 1, tipo_b = 1; // Tipo de zombi: 1,2 o 3
unsigned short restantes_a = 20, restantes_b = 20;
unsigned short puntaje_a = 0, puntaje_b = 0;
posicion zombis_pos_a[8] = {};
posicion zombis_pos_b[8] = {};
unsigned short zombis_tipo_a[8] = {};
unsigned short zombis_tipo_b[8] = {};

bool debug = false;


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
  }else if(value == UP && (*ptr_tipo) == 3){
    (*ptr_tipo) = 1;
  }else if (value == DOWN && (*ptr_tipo) > 1) {
    (*ptr_tipo)--;
  }else if(value == DOWN && (*ptr_tipo) == 1){
    (*ptr_tipo) = 3;
  }
  print_jugador(jugador, (*ptr_tipo), (*ptr_y));
}

void game_lanzar_zombi(unsigned int jugador) {
  if (jugador == player_A && restantes_a != 0 && sched_hay_lugar_zombi(jugador)) {
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
    tss_refrescar_zombi(jugador, i);

    // Copiar zombi físicamente
    copiar_zombi(cr3, tipo_a, jugador);

    // Avisarle al scheduler
    sched_activar_zombi(jugador, i);

    // Pintar
    print_zombi(jugador, zombis_tipo_a[i], zombis_pos_a[i]);
    print("O", 4+i*2, 50-2, FG_LIGHT_GREEN | BG_BLACK);
    print_cantidad_zombis(restantes_a, restantes_b);
  }
  // Aca ya se que jugador != player_A => jugador == player_B
  else if ( jugador == player_B && restantes_b != 0 && sched_hay_lugar_zombi(jugador)  ){
     // Debe ser jugador == player_B, sino agregar otro if
    // Juicy info
    posicion pos_zombi = { .x = MAP_WIDTH-1, .y = y_b };
    unsigned int i = sched_indice_libre(jugador);

    // Actualizar variables del juego
    restantes_b--;
    zombis_pos_b[i] = pos_zombi;
    zombis_tipo_b[i] = tipo_b;

    // Rescribir estructuras de la tarea
    unsigned int cr3 = tss_leer_cr3(jugador, i);
    mmu_mapear_vision_zombi(jugador, cr3, pos_zombi.x, pos_zombi.y);
    tss_refrescar_zombi(jugador, i);

    // Copiar zombi físicamente
    copiar_zombi(cr3, tipo_b, jugador);

    // Avisarle al scheduler
    sched_activar_zombi(jugador, i);

    // Pintar
    print_zombi(jugador, zombis_tipo_b[i], zombis_pos_b[i]);
    print("O", 80-20+i*2, 50-2, FG_LIGHT_GREEN | BG_BLACK);
    print_cantidad_zombis(restantes_a, restantes_b);

    // asm("xchg %bx, %bx"); // Lleva los % en cada registro porque es AT&T syntax
  }else if((jugador == player_A && restantes_a == 0) || (jugador == player_B && restantes_b == 0)){
    print("Baja un cambio ", 1, 0, FG_LIGHT_RED | BG_BLACK);
    if (jugador == player_A) {
      print("A", 16, 0, FG_LIGHT_RED | BG_BLACK);
    }else{
      print("B", 16, 0, FG_LIGHT_RED | BG_BLACK);
    }
    print(", te quedaste sin zombies...", 17, 0, FG_LIGHT_RED | BG_BLACK);      
  }
}


// ZOMBIS
// --------------------------

void game_move_current_zombi(direccion dir) {
}
