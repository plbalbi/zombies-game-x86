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

void mmu_inicializar();

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

} __attribute__((__packed__, aligned (32))) pd_entry;

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

} __attribute__((__packed__, aligned (32))) pt_entry;

#endif	/* !__MMU_H__ */




