/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__

/* Definicion de la pantalla */
#define VIDEO_FILS 50
#define VIDEO_COLS 80

#include "colors.h"
#include "defines.h"
#include "game.h"

#define print_zombie_trace(pos) print("X", pos.x+1, pos.y+1, BG_GREEN | FG_LIGHT_GREY)

/* Estructura de para acceder a memoria de video */
typedef struct ca_s {
    unsigned char c;
    unsigned char a;
} ca;

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr);

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr);

void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr);

unsigned int strlen(const char *str);

void print_jugador(unsigned short jugador, unsigned short tipo, int y);

void print_zombi(unsigned short jugador, unsigned short tipo, posicion pos);

void print_teclado(unsigned int key);

void print_cantidad_zombis(unsigned int a, unsigned int b);

void print_puntajes(unsigned int a, unsigned int b);

#endif  /* !__SCREEN_H__ */
