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

typedef _Bool bool;
#define true True
#define false False


/* Misc */
/* -------------------------------------------------------------------------- */
#define CANT_ZOMBIS             8

#define MAP_WIDTH               78
#define MAP_HEIGHT              44

#define TSS_SIZE                104

/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */

#define DIR_INICIO_KERNEL_PD     0x27000
#define DIR_INICIO_KERNEL_PT     0x28000

#define INICIO_MAPA              0x400000

#define DIR_INICIO_PILA_KERNEL   0x27000
#define DIR_INICIO_TASK_AG       0X10000
#define DIR_INICIO_TASK_AM       0X11000
#define DIR_INICIO_TASK_AC       0X12000
#define DIR_INICIO_TASK_BG       0X13000
#define DIR_INICIO_TASK_BM       0X14000
#define DIR_INICIO_TASK_BC       0X15000
#define DIR_INICIO_TASK_IDLE     0X16000

#define DIR_INICIO_ZOMBI_VISION  0x8000000
#define DIR_INICIO_ZOMBI_PILA    0x8001000

#define VIDEO                    0x000B8000

/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 30

#define GDT_IDX_NULL_DESC           0
#define GDT_IDX_CODE_L0             8
#define GDT_IDX_CODE_L3             9
#define GDT_IDX_DATA_L0             10
#define GDT_IDX_DATA_L3             11
#define GDT_IDX_SCREEN              12

#define GDT_IDX_TSS_ZOMBIS_A        13
#define GDT_IDX_TSS_ZOMBIS_B        (GDT_IDX_TSS_ZOMBIS_A + CANT_ZOMBIS)
#define GDT_IDX_TSS_INIT            (GDT_IDX_TSS_ZOMBIS_B + CANT_ZOMBIS)
#define GDT_IDX_TSS_IDLE            (GDT_IDX_TSS_INIT + 1)

/* Selectores de la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_CODE_L0_REG             (GDT_IDX_CODE_L0 << 3)
#define GDT_CODE_L3_REG             (GDT_IDX_CODE_L3 << 3)
#define GDT_DATA_L0_REG             (GDT_IDX_DATA_L0 << 3)
#define GDT_DATA_L3_REG             (GDT_IDX_DATA_L3 << 3)
#define GDT_SCREEN_REG              (GDT_IDX_SCREEN << 3)

/* Keyboard opcodes */
/* -------------------------------------------------------------------------- */
#define KEY_W  0x11
#define KEY_S  0x1f
#define KEY_A  0x1e
#define KEY_D  0x20
#define KEY_LS 0x2a

#define KEY_I  0x17
#define KEY_K  0x25
#define KEY_L  0x26
#define KEY_J  0x24
#define KEY_RS 0x36

#endif  /* !__DEFINES_H__ */
