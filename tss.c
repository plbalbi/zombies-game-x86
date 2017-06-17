/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "defines.h"
#include "gdt.h"
#include "tss.h"
#include "mmu.h"


tss tss_inicial;
tss tss_idle;

tss tss_zombisB[CANT_ZOMBIS];
tss tss_zombisA[CANT_ZOMBIS];


// Bases en descriptores TSS en la GDT:
// Podemos estar seguros de que la base de las TSS van a estar
// en el kernel, AKA en las primeras 0x100 páginas, con lo cual
// lidiamos con direcciones de memoria menores a 0x100000, con
// lo cual nos bastan 21 bits, y entran en 'base'. Como en los descriptores las
// bases están fragmentadas, defino las siguientes macros:
#define BITS_0_15(base) (unsigned int)base & 0xFFFF // base[0:15]
#define BITS_16_23(base) ((unsigned int)base >> 16) & 0xFF  // base[23:16]


void tss_inicializar() {
      tss_inicializar_idle();
      int i;
      for (i = 0; i < CANT_ZOMBIS; i++) {
            tss_inicializar_zombi(1, i);
            tss_inicializar_zombi(2, i);
      }
}

void tss_inicializar_idle() {
      // TSS
      tss_idle = (tss) {
            .esp0 = DIR_INICIO_PILA_KERNEL,
            .ss0 = GDT_DESC_DATA_KERNEL,
            .cr3 = 0x27000,
            .eip = DIR_INICIO_TASK_IDLE,
            .eflags = 0x202, // Seteamos IF y Reserved
            .fs = GDT_DESC_SCREEN,
            .cs = GDT_DESC_CODE_KERNEL,
            .ss = GDT_DESC_DATA_KERNEL,
            .ds = GDT_DESC_DATA_KERNEL,
            .es = GDT_DESC_DATA_KERNEL,
            .gs = GDT_DESC_DATA_KERNEL
      };

      // Task Gate
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

void tss_inicializar_zombi(int jugador, unsigned int i) {
      // Memoria
      // Los cr3 van a tener mapeadas 0x800000 en adelante, pero no importa
      // , los zombis posta las van a pisar al crearse
      unsigned int cr3 = mmu_inicializar_esquema_zombi(1, 1);
      // Para el esp0 pedimos una página y apuntamos a la 'base'
      unsigned int esp0 = mmu_prox_pag_libre() + PAGE_SIZE;

      // TSS
      tss* ptr_tss_zombi;
      if (jugador == 1) {
            ptr_tss_zombi = tss_zombisA + i; // Puntero a tss_zombisA[i]
      } else {
            ptr_tss_zombi = tss_zombisB + i; // Puntero a tss_zombisB[i]
      }

      (*ptr_tss_zombi) = (tss) {
            .esp0 = esp0,
            .ss0 = GDT_DESC_DATA_KERNEL,
            .cr3 = cr3,
            .eip = DIR_INICIO_ZOMBI_VISION,
            .esp = DIR_INICIO_ZOMBI_PILA,
            .ebp = DIR_INICIO_ZOMBI_PILA,
            .eflags = 0x202, // Seteamos IF y Reserved
            .cs = GDT_DESC_CODE_USER,
            .ss = GDT_DESC_DATA_USER,
            .ds = GDT_DESC_DATA_USER,
            .es = GDT_DESC_DATA_USER,
            .fs = GDT_DESC_DATA_USER,
            .gs = GDT_DESC_DATA_USER,
      };

      // Task Gate
      unsigned int task_index;
      if (jugador == 1) {
            task_index = GDT_IDX_TSS_ZOMBIS_A + i;
      } else {
            task_index = GDT_IDX_TSS_ZOMBIS_B + i;
      }

      gdt[task_index] = (gdt_entry){
            (unsigned short)    TSS_SIZE-1,            /* limit[0:15]   */
            (unsigned short)    BITS_0_15(ptr_tss_zombi),  /* base[0:15]    */
            (unsigned char)     BITS_16_23(ptr_tss_zombi), /* base[23:16]   */
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