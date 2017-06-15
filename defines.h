/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1

typedef bool _Bool;
#define true True
#define false False


/* Misc */
/* -------------------------------------------------------------------------- */
#define CANT_ZOMBIS             8

#define SIZE_W                  78
#define SIZE_H                  44

#define TSS_SIZE                104

/* Direcciones en memoria */
/* -------------------------------------------------------------------------- */

#define DIR_INICIO_PILA_KERNEL  0x27000
#define DIR_INICIO_TASK_AG      0X10000
#define DIR_INICIO_TASK_AM      0X11000
#define DIR_INICIO_TASK_AC      0X12000
#define DIR_INICIO_TASK_BG      0X13000
#define DIR_INICIO_TASK_BM      0X14000
#define DIR_INICIO_TASK_BC      0X15000
#define DIR_INICIO_TASK_IDLE    0X16000

/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 30

#define GDT_IDX_NULL_DESC           0
#define GDT_IDX_CODE_L0             8
#define GDT_IDX_CODE_L3             9
#define GDT_IDX_DATA_L0             10
#define GDT_IDX_DATA_L3             11
#define GDT_IDX_SCREEN              12

#define GDT_IDX_TSS_INIT            15
#define GDT_IDX_TSS_IDLE            GDT_IDX_TSS_INIT+1

/* Selectores de la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_CODE_L0_REG             (GDT_IDX_CODE_L0 << 3)
#define GDT_DATA_L0_REG             (GDT_IDX_DATA_L0 << 3)
#define GDT_SCREEN_REG              (GDT_IDX_SCREEN << 3)

/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */
#define VIDEO                   0x000B8000 /* direccion fisica del buffer de video */

#endif  /* !__DEFINES_H__ */
