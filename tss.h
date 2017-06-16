/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#ifndef __TSS_H__
#define __TSS_H__

#include "defines.h"
#include "i386.h"
#include "gdt.h"

// Acerca de cómo definir las bases de las TSS en la GDT:
// Podemos estar seguros de que la base de las TSS van a estar
// en el kernel, AKA en las primeras 0x100 páginas, con lo cual
// lidiamos con direcciones de memoria menores a 0x100000, con
// lo cual nos bastan 21 bits. Como en los descriptores las
// bases están fragmentadas, defino las siguientes macros:
#define INDEXAR_DIR(virt) (virt >> 22)
#define INDEXAR_TABLE(virt) (virt >> 12) & 0x000003FF
#define DEVOLVER_OFF(virt) (virt) & 0x00000FFF
#define TSS_IDLE_INDEX 16

typedef struct str_tss {
    unsigned short  ptl;
    unsigned short  unused0;
    unsigned int    esp0;
    unsigned short  ss0;
    unsigned short  unused1;
    unsigned int    esp1;
    unsigned short  ss1;
    unsigned short  unused2;
    unsigned int    esp2;
    unsigned short  ss2;
    unsigned short  unused3;
    unsigned int    cr3;
    unsigned int    eip;
    unsigned int    eflags;
    unsigned int    eax;
    unsigned int    ecx;
    unsigned int    edx;
    unsigned int    ebx;
    unsigned int    esp;
    unsigned int    ebp;
    unsigned int    esi;
    unsigned int    edi;
    unsigned short  es;
    unsigned short  unused4;
    unsigned short  cs;
    unsigned short  unused5;
    unsigned short  ss;
    unsigned short  unused6;
    unsigned short  ds;
    unsigned short  unused7;
    unsigned short  fs;
    unsigned short  unused8;
    unsigned short  gs;
    unsigned short  unused9;
    unsigned short  ldt;
    unsigned short  unused10;
    unsigned short  dtrap;
    unsigned short  iomap;
} __attribute__((__packed__, aligned (8))) tss;

void tss_inicializar();
extern void idle();

#endif  /* !__TSS_H__ */
