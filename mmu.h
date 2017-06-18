	/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "defines.h"
#include "screen.h"
#include "colors.h"
#include "i386.h"
#include "tss.h"
#include "game.h"
#include "debug.h"

#define PRIMERA_PAG_LIBRE 0x100<<12
  
#define INDEX_DIR(dir) (dir >> 22)
#define INDEX_TABLE(dir) (dir >> 12) & 0x3FF
#define OFFSET(dir) (dir) & 0xFFF


unsigned int prox_pag_lib;

void mmu_inicializar(void);
unsigned int mmu_inicializar_zombi(unsigned int tarea, int jugador, int y);
void mmu_inicializar_esquema_kernel(void);
unsigned int mmu_inicializar_esquema_zombi(int jugador, int y);

unsigned int mmu_prox_pag_libre();
void mmu_mapear_pagina(unsigned int vir, unsigned int cr3, unsigned int fis, unsigned char user);
void mmu_unmapear_pagina(unsigned int vir, unsigned int cr3);
void mmu_mapear_vision_zombi(int jugador, unsigned int cr3, int x, int y);

unsigned int dir_fisica(int x, int y);
void copiar_zombi(unsigned int cr3_zombi, unsigned int task, int player);

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
    unsigned int base:20;

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
    unsigned int base:20;

} __attribute__((__packed__, aligned (4))) pt_entry;

#endif	/* !__MMU_H__ */