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

    // Inicializar esquema de paginación

    unsigned int* PD = (unsigned int*) DIR_INICIO_IM_KERNEL_PD;
    unsigned int* PT = (unsigned int*) DIR_INICIO_IM_KERNEL_PT;

    // Llenando la Page Directory
    *PD = 0x28003; // Base Address = 0x28, US=1, RW=1, P=1
    PD++;
    for (int i = 1; i < 1024; i++) {
        *PD = 0x00000; // P=0
        PD++;
    }

    // Llenando la Page Table
    for (int i = 0; i < 1024; i++) {
        *PT = 0x00003 | (i<<12); // P=0
        PT++;
    }

    // Misc

    prox_pag_lib = PRIMERA_PAG_LIBRE;

}

// void mmu_inicializar_dir_zombi(x,y,jugador,tarea) {
//
// }

unsigned int mmu_prox_pag_libre(){
    unsigned int prev_page = prox_pag_lib;
    prox_pag_lib+=PAGE_SIZE;
    return prev_page;
}

void mmu_mapear_pagina(unsigned int vir, unsigned int cr3, unsigned int fis){
    // Nota: si 'vir' ya está mapeada, se pizza
    // [indice en dir | indice en paginas | offset    ]
    //        10             10               12
    pd_entry* pde = (pd_entry*) (cr3 & 0xFFFFF000);
    pd_entry my_dir_entry = pde[INDEXAR_DIR(vir)];
    pt_entry* pt = (pt_entry*) (my_dir_entry.frame << 12);
    if (my_dir_entry.p == 0) {
        pt = (pt_entry*) mmu_prox_pag_libre();
        pde[INDEXAR_DIR(vir)] = (pd_entry) { .p = 1, .rw = 1, .frame = (unsigned int) pt>>12 };
    }
    pt[INDEXAR_TABLE(vir)] = (pt_entry) { .p = 1, .rw = 1, .frame = fis>>12 };
}

void mmu_unmapear_pagina(unsigned int vir, unsigned int cr3){
    pd_entry* pde = (pd_entry*) (cr3 & 0xFFFFF000);
    pt_entry* pt = (pt_entry*) (pde[INDEXAR_DIR(vir)].frame << 12);
    pt[INDEXAR_TABLE(vir)] = (pt_entry) { };
}

// - dir_fisica(x, y)
#define INICIO_MAPA 0x400000
#define PAGE_SIZE 1024*4
#define MAP_WIDTH 78
unsigned int dir_fisica(unsigned int x, unsigned int y){
  return INICIO_MAPA + ((y % MAP_WIDTH) * MAP_WIDTH + x)*PAGE_SIZE ;
}

// - x_y(dir_fisica) ... For later

// y = dir_fisica div PAGE_SIZE*MAP_WIDTH
// x = remainder(dir_fisica, PAGE_SIZE*MAP_WIDTH) / PAGE_SIZE
