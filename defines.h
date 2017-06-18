/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Tipos */
/* -------------------------------------------------------------------------- */
typedef _Bool bool;
#define true True
#define false False

typedef struct posicion_t {
  unsigned short x;
  unsigned short y;
}__attribute__((__packed__)) posicion;

/* Misc */
/* -------------------------------------------------------------------------- */
#define CANT_ZOMBIS             8

#define MAP_WIDTH               78
#define MAP_HEIGHT              44

#define PAGE_SIZE               (1<<12)
#define TSS_SIZE                104

#define CHAR_CLERICO            "\x03"
#define CHAR_MAGO               "\x04"
#define CHAR_GUERRERO           "\x06"


/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */

#define DIR_INICIO_KERNEL_PD     0x27000
#define DIR_INICIO_KERNEL_PT     0x28000

#define DIR_INICIO_PILA_KERNEL   0x27000
#define DIR_INICIO_TASK_AG       0X10000
#define DIR_INICIO_TASK_AM       0X11000
#define DIR_INICIO_TASK_AC       0X12000
#define DIR_INICIO_TASK_BG       0X13000
#define DIR_INICIO_TASK_BM       0X14000
#define DIR_INICIO_TASK_BC       0X15000
#define DIR_INICIO_TASK_IDLE     0X16000

#define DIR_INICIO_MAPA          0x400000

#define DIR_INICIO_ZOMBI_VISION  0x8000000
#define DIR_INICIO_ZOMBI_PILA    0x8001000

#define VIDEO                    0x000B8000


/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 31

#define GDT_IDX_NULL_DESC           0
#define GDT_IDX_CODE_KERNEL         8
#define GDT_IDX_CODE_USER           9
#define GDT_IDX_DATA_KERNEL        10
#define GDT_IDX_DATA_USER          11
#define GDT_IDX_SCREEN             12

#define GDT_IDX_TSS_ZOMBIS_A       13
#define GDT_IDX_TSS_ZOMBIS_B       (GDT_IDX_TSS_ZOMBIS_A + CANT_ZOMBIS)
#define GDT_IDX_TSS_IDLE           (GDT_IDX_TSS_ZOMBIS_B + CANT_ZOMBIS) // 29
#define GDT_IDX_TSS_INIT           (GDT_IDX_TSS_IDLE + 1) // 30


/* Descriptores en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_DESC_CODE_KERNEL        (GDT_IDX_CODE_KERNEL << 3)
#define GDT_DESC_CODE_USER          (GDT_IDX_CODE_USER << 3)
#define GDT_DESC_DATA_KERNEL        (GDT_IDX_DATA_KERNEL << 3)
#define GDT_DESC_DATA_USER          (GDT_IDX_DATA_USER << 3)
#define GDT_DESC_SCREEN             (GDT_IDX_SCREEN << 3)

#define GDT_DESC_TSS_ZOMBIS_A       (GDT_IDX_TSS_ZOMBIS_A << 3)
#define GDT_DESC_TSS_ZOMBIS_B       (GDT_IDX_TSS_ZOMBIS_B << 3)
#define GDT_DESC_TSS_IDLE           (GDT_IDX_TSS_IDLE << 3)
#define GDT_DESC_TSS_INIT           (GDT_IDX_TSS_INIT << 3)


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
