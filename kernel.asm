; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

; ** por compatibilidad se omiten tildes **
%include "imprimir.mac"

global start


;; Saltear seccion de datos
jmp start


;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

charly_mp_msg db        'Think for youself, dont be sheep...'
charly_mp_len equ       $ - charly_mp_msg

%define GDT_NULL_DESC           0
%define GDT_CODE_L0             8
%define GDT_CODE_L3             9
%define GDT_DATA_L0             10
%define GDT_DATA_L3             11
%define GDT_SCREEN              12

%macro BREAK 0
xchg bx,bx
%endmacro
%macro CALL_C 1
extern %1
call %1
%endmacro

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

; Cosas que llamo desde c
extern GDT_DESC
extern IDT_DESC
extern idt_inicializar
extern mmu_inicializar
extern mmu_mapear_pagina
extern habilitar_pic
extern resetear_pic
extern init_prrint_frame
extern test_prrint


;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a 80 X 50
      mov ax, 0003h
      int 10h ; set mode 03h
      xor bx, bx
      mov ax, 1112h
      int 10h ; load 8x8 font

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0

    ; Habilitar A20
    call habilitar_A20

    ; Cargar la GDT
    lgdt [GDT_DESC]

    ; Setear el bit PE del registro CR0
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    ; Saltar a modo protegido
    jmp 0x40:STARTProtMode

BITS 32
STARTProtMode:
    ; Establecer selectores de segmentos
    mov ax, GDT_DATA_L0 << 3
    mov ds, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax
    mov ax, GDT_SCREEN << 3
    mov es, ax ; 'es' es el segmento de video

    ; Establecer la base de la pila
    mov esp, 0x2700
    mov ebp, esp

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mp charly_mp_msg, charly_mp_len, 0x07, 2, 0

    ; Pintar pantalla
    call limpiarPantalla

    ; Inicializar el manejador de memoria
    call mmu_inicializar

    ; Cargar directorio de paginas
    mov eax, 0x27000 ; bits menos significativos son atributos, la base es 0x27
    mov cr3, eax

    ; Habilitar paginacion
    mov eax, cr0
    or eax, 1<<31; prendemos el bit más significativo
    mov cr0, eax

    ; Inicializar tss
    ; ...

    ; Inicializar tss de la tarea Idle
    ; ...

    ; Inicializar el scheduler
    ; ...

    ; Inicializar la IDT
    lidt [IDT_DESC]

    ; Cargar IDT
    call idt_inicializar

    ; Configurar controlador de interrupciones
    call resetear_pic
    call habilitar_pic

    ; Cargar tarea inicial
    ; ...

    ; Habilitar interrupciones
    sti

    ; Saltar a la primera tarea: Idle
    ; ...

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $


%include "screen.asm"

%include "a20.asm"