/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "defines.h"
#include "i386.h"
#include "tss.h"
#include "game.h"

#define PRIMERA_PAG_LIBRE 0x100<<12
#define PAGE_SIZE (2<<12)

#define INDEXAR_DIR(virt) (virt >> 22)
#define INDEXAR_TABLE(virt) (virt >> 12) & 0x000003FF
#define DEVOLVER_OFF(virt) (virt) & 0x00000FFF

#define ui unsigned int

unsigned int prox_pag_lib;
unsigned int mmu_prox_pag_libre();



void mmu_inicializar();

void mmu_mapear_pagina(unsigned int vir, unsigned int cr3, unsigned int fis);
void mmu_unmapear_pagina(unsigned int vir, unsigned int cr3);

// Funciones zombies
typedef struct posicion_t {
  unsigned short x;
  unsigned short y;
}__attribute__((__packed__)) posicion;

unsigned int dir_fisica(int x, int y);
posicion x_y(unsigned int dir_fisica); // SIDENOTE: Devuelve por pila
void copiar_zombi(unsigned int task, unsigned int player, int y);

unsigned int crear_esquema_zombi(int jugador, int y);


typedef struct str_pd_entry_t{
    unsigned char p:1;
    unsigned char rw:1;
    unsigned char us:1;
    unsigned char pwt:1;
    unsigned char pcd:1;
    unsigned char a:1;
    unsigned char d:1;
    unsigned char pat:1;
    unsigned char ign:4;
    unsigned int frame:20;

} __attribute__((__packed__, aligned (4))) pd_entry;

typedef struct str_pt_entry_t{
    unsigned char p:1;
    unsigned char rw:1;
    unsigned char us:1;
    unsigned char pwt:1;
    unsigned char pcd:1;
    unsigned char a:1;
    unsigned char d:1;
    unsigned char pat:1;
    unsigned char g:1;
    unsigned char ign:3;
    unsigned int frame:20;

} __attribute__((__packed__, aligned (4))) pt_entry;

#endif	/* !__MMU_H__ */
