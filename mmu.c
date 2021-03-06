/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "defines.h"
#include "mmu.h"


// INICIALIZACIÓN ++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void mmu_inicializar() {
    // Inicialización
	int i;
    unsigned int* pd = (unsigned int*) DIR_INICIO_KERNEL_PD;
    unsigned int* pt = (unsigned int*) DIR_INICIO_KERNEL_PT;

    // Llenando la Page Directory
    *pd = 0x28003; // Base Address = 0x28, US=1, RW=1, P=1
    pd++;
    for (i = 1; i < 1024; i++) {
        *pd = 0x00000; // P=0
        pd++;
    }

    // Llenando la Page Table
    for (i = 0; i < 1024; i++) {
        *pt = 0x00003 | (i<<12); // P=0
        pt++;
    }

    // Páginas Libres
    prox_pag_lib = PRIMERA_PAG_LIBRE;
}

unsigned int mmu_inicializar_dir_zombi(unsigned int tarea, unsigned int jugador, int y){
  return 0;
}

// TODO: Reformular las dos funciones de abajo para que las podamos reutilizar al mover
// zombies.

unsigned int crear_esquema_zombi(int jugador, int y) {
    // Crea el esquema de paginación para un zombie, y devuelve
    // el CR3 correspondiente (AKA la dirección del page directory)
    int i;

    // Memory Allocation
    pd_entry* pd = (pd_entry*) mmu_prox_pag_libre();
    pt_entry* pt = (pt_entry*) mmu_prox_pag_libre();

    // Page Directory
    for (i = 0; i < 1024; i++) pd[i] = (pd_entry) { }; // zero everything
    pd[0] = (pd_entry) { .p = 1, .rw = 1, .frame = 0x28 }; // first entry
    pd[0x20] = (pd_entry) { .p = 1, .rw = 1, .frame = (unsigned int)pt>>12 }; // zombi sight

    // Page Table
    for (i = 0; i < 1024; i++) pt[i] = (pt_entry) { }; // zero everything
    if (jugador == 0) {
        int x = 0+1; // Jugador rojo
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 0*PAGE_SIZE, (unsigned int)pd, dir_fisica(x, y)); // 1
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 1*PAGE_SIZE, (unsigned int)pd, dir_fisica(x+1, y)); // 2
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 2*PAGE_SIZE, (unsigned int)pd, dir_fisica(x+1, y+1)); // 3
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 3*PAGE_SIZE, (unsigned int)pd, dir_fisica(x+1, y-1)); // 4
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 4*PAGE_SIZE, (unsigned int)pd, dir_fisica(x, y+1)); // 5
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 5*PAGE_SIZE, (unsigned int)pd, dir_fisica(x, y-1)); // 6
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 6*PAGE_SIZE, (unsigned int)pd, dir_fisica(x-1, y)); // 7
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 7*PAGE_SIZE, (unsigned int)pd, dir_fisica(x-1, y-1)); // 8
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 8*PAGE_SIZE, (unsigned int)pd, dir_fisica(x-1, y+1)); // 9
    } else {
        int x = 77-1; // Jugador azul (Recordar que el mapa es 78x44)
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 0*PAGE_SIZE, (unsigned int)pd, dir_fisica(x, y)); // 1
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 1*PAGE_SIZE, (unsigned int)pd, dir_fisica(x-1, y)); // 2
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 2*PAGE_SIZE, (unsigned int)pd, dir_fisica(x-1, y-1)); // 3
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 3*PAGE_SIZE, (unsigned int)pd, dir_fisica(x-1, y+1)); // 4
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 4*PAGE_SIZE, (unsigned int)pd, dir_fisica(x, y-1)); // 5
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 5*PAGE_SIZE, (unsigned int)pd, dir_fisica(x, y+1)); // 6
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 6*PAGE_SIZE, (unsigned int)pd, dir_fisica(x+1, y)); // 7
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 7*PAGE_SIZE, (unsigned int)pd, dir_fisica(x+1, y+1)); // 8
        mmu_mapear_pagina(DIR_INICIO_ZOMBI_VISION + 8*PAGE_SIZE, (unsigned int)pd, dir_fisica(x+1, y-1)); // 9
    }
    return (unsigned int) pd;
}

void copiar_zombi(unsigned int task, unsigned int player, int y){
    // Tareas Jug 1 (A)
    // 1 0x10000 - 0x10FFF
    // 2 0x11000 - 0x11FFF
    // 3 0x12000 - 0x12FFF
    // Tareas Jug 2 (B)
    // 1 0x13000 - 0x13FFF
    // 2 0x14000 - 0x14FFF
    // 3 0x15000 - 0x15FFF

    // Las direccions de arriba están en la parte de kernel (identity mapping)
    char* dir_task;
    // base de jugador
    if(player==1){
        dir_task = (char*) 0x10000;
    }else{
        dir_task = (char*) 0x13000;
    }
    // offset de tarea
    dir_task += (task-1)*0x1000;

    int x = (player==1) ? 1 : MAP_WIDTH-2; // Operador ternario
    char* dir_mapa = (char*) dir_fisica(x,y);
    int i;
    for(i = 0; i < 0x1000; i++){
        *dir_mapa = *dir_task;
        dir_mapa++;
        dir_task++;
    }
}


// ADMINISTRACIÓN DE MEMORIA +++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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


// AUXILIARES ++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned int dir_fisica(int x, int y){
    int modulo_x = x % MAP_WIDTH;
    int modulo_y = (y + MAP_HEIGHT) % MAP_HEIGHT;
    return INICIO_MAPA + (modulo_y * MAP_WIDTH + modulo_x)*PAGE_SIZE;
}

posicion x_y(unsigned int dir_fisica){
  posicion res;
  res.x = (dir_fisica % (MAP_WIDTH*PAGE_SIZE))/PAGE_SIZE;
  res.y = dir_fisica / (MAP_WIDTH*PAGE_SIZE);
  return res;
}