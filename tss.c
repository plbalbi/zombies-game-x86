/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"

tss tss_inicial;
tss tss_idle = {
      .esp0 = 0x2700,
      .ss0 = GDT_DATA_L0_REG,
      .esp1 = 0x2700,
      .ss1 = GDT_DATA_L0_REG,
      .esp2 = 0x2700,
      .ss2 = GDT_DATA_L0_REG,
      .cr3 = 0x27000,
      .eip = (unsigned int) &idle,
      .eflags = ((1<<9)|0x2), //Seteo IF
      .es = 12 << 3, // Me dio paja hacer un define
      .cs = GDT_CODE_L0_REG,
      .ss = GDT_DATA_L0_REG,
      .ds = GDT_DATA_L0_REG,
      .fs = GDT_DATA_L0_REG,
      .gs = GDT_DATA_L0_REG,
};

tss tss_zombisA[CANT_ZOMBIS];
tss tss_zombisB[CANT_ZOMBIS];

void tss_inicializar() {

}
