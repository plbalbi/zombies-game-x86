/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#define DIR_INICIO_IM_KERNEL_PD 0x27000
#define DIR_INICIO_IM_KERNEL_PT 0x28000

void mmu_inicializar() {

    unsigned int* PD = (unsigned int*) DIR_INICIO_IM_KERNEL_PD;
    unsigned int* PT = (unsigned int*) DIR_INICIO_IM_KERNEL_PT;

    // Llenando la Page Directory
    *PD = 0x28007; // Base Address = 0x28, US=1, RW=1, P=1
    PD++;
    for (int i = 1; i < 1024; i++) {
        *PD = 0x00000; // P=0
        PD++;
    }

    // Llenando la Page Table
    for (int i = 0; i < 2<<20; i+=2<<10) {
        *PT = 0x00007 | i; // P=0
        PT++;
    }
}
