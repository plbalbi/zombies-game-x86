/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "defines.h"
#include "gdt.h"
#include "tss.h"

// Bases en descriptores TSS en la GDT:
// Podemos estar seguros de que la base de las TSS van a estar
// en el kernel, AKA en las primeras 0x100 páginas, con lo cual
// lidiamos con direcciones de memoria menores a 0x100000, con
// lo cual nos bastan 21 bits, y entran en 'base'. Como en los descriptores las
// bases están fragmentadas, defino las siguientes macros:
#define BITS_0_15(base) (unsigned int)base & 0xFFFF // base[0:15]
#define BITS_16_23(base) ((unsigned int)base >> 16) & 0xFF  // base[23:16]

tss tss_inicial;
tss tss_idle = {
      .esp0 = DIR_INICIO_PILA_KERNEL,
      .ss0 = GDT_DATA_L0_REG,
      .esp1 = DIR_INICIO_PILA_KERNEL,
      .ss1 = GDT_DATA_L0_REG,
      .esp2 = DIR_INICIO_PILA_KERNEL,
      .ss2 = GDT_DATA_L0_REG,
      .cr3 = 0x27000,
      .eip = DIR_INICIO_TASK_IDLE,
      .eflags = ((1<<9)|0x2), //Seteo IF
      .es = GDT_SCREEN_REG,
      .cs = GDT_CODE_L0_REG,
      .ss = GDT_DATA_L0_REG,
      .ds = GDT_DATA_L0_REG,
      .fs = GDT_DATA_L0_REG,
      .gs = GDT_DATA_L0_REG,
};

tss tss_zombisA[CANT_ZOMBIS];
tss tss_zombisB[CANT_ZOMBIS];

void tss_inicializar() {
      // Inicialización de los descriptores de tss en la gdt
      gdt[GDT_IDX_TSS_INIT] = (gdt_entry) {};
      gdt[GDT_IDX_TSS_IDLE] = (gdt_entry){
        (unsigned short)    TSS_SIZE-1,            /* limit[0:15]   */
        (unsigned short)    BITS_0_15(&tss_idle),  /* base[0:15]    */
        (unsigned char)     BITS_16_23(&tss_idle), /* base[23:16]   */
        (unsigned char)     0x9,                   /* type (tss)    */
        (unsigned char)     0x0,                   /* s (supervisor)*/
        (unsigned char)     0x00,                  /* dpl           */
        (unsigned char)     0x01,                  /* p             */
        (unsigned char)     0x00,                  /* limit[16:19]  */
        (unsigned char)     0x00,                  /* avl           */
        (unsigned char)     0x00,                  /* l             */
        (unsigned char)     0x01,                  /* db            */
        (unsigned char)     0x00,                  /* g             */
        (unsigned char)     0x00,                  /* base[31:24]   */
      };
}