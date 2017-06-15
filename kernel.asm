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
    ;imprimir_texto_mp charly_mp_msg, charly_mp_len, 0x07, 2, 0
    ; CALL_C init_prrint_frame
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

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT
    lidt [IDT_DESC]

    ; Cargar IDT
    call idt_inicializar

    ; Configurar controlador de interrupciones
    call resetear_pic
    call habilitar_pic

    ; Cargar tarea inicial


    ; Habilitar interrupciones
    sti


    ; Saltar a la primera tarea: Idle

    ; Prrint Test

    ; call init_prrint_frame
    ; call test_prrint

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $


;; -------------------------------------------------------------------------- ;;
; RUTINA:   limpiarPantalla
; REQ:      Ser kernel; Queres limpiar la pantalla; Ganas de ejecutarla?
;; -------------------------------------------------------------------------- ;;
; Se encarga de rellenar la pantalla con el fondo verde, los rectangulitos de los jugadores
; y los numeros de los  zombies. Accede mediante el segmente de video (con permisos de kernel)
%define FILA_SIZE 80
%define CANT_FILAS 50
%define FONDO_VERDE 0x20FF
%define FONDO_NEGRO 0x0FFF
%define FONDO_ROJO 0x40FF
%define FONDO_AZUL 0x10FF
limpiarPantalla:
  xor ebx, ebx ; Registro para ir llevando la cuenta del que recorro
  ; mov ecx, 80*50 ; Cantidad de poxles a recorrer (Cargado para loopear)
  ; Barra negra de arriba
  mov ecx, FILA_SIZE ; Cantidad de poxles a recorrer (Cargado para loopear)
  .filaNegra:
  mov word[es:ebx], FONDO_NEGRO ; Cargo el relleno
  inc ebx
  inc ebx ; Incremento los 2Bytes del Poxel
  loop .filaNegra
  ; Fondo verde del mapa
  mov ecx, (CANT_FILAS-1-5)*FILA_SIZE ; 50 filas totales - la negra de arriba - la barra de abajo
  .fondoVerde:
  mov word[es:ebx], FONDO_VERDE ; Cargo el relleno
  inc ebx
  inc ebx ; Incremento los 2Bytes del Poxel
  loop .fondoVerde
  ; Barra de info de abajo
  mov ecx, FILA_SIZE*5 ; Cantidad de poxles a recorrer (Cargado para loopear)
  .filaNegra2:
  mov word[es:ebx], FONDO_NEGRO ; Cargo el relleno
  inc ebx
  inc ebx ; Incremento los 2Bytes del Poxel
  loop .filaNegra2
  ; Columnda roja y azul
  mov ebx, FILA_SIZE*2 ; Para comienze en la segunda fila
  mov ecx, (CANT_FILAS-1-5) ; 50 filas totales - la negra de arriba - la barra de abajo
  .cols_de_colores:
  mov word[es:ebx], FONDO_ROJO ; Cargo el relleno
  mov word[es:ebx + (FILA_SIZE-1)*2], FONDO_AZUL ; Cargo el relleno
  add ebx, FILA_SIZE*2
  loop .cols_de_colores
  ; Pongo los numeritos
  ; TODO: Ver alineación pila
  ; CALL_C seguir_llenando_pantalla
  ; CALL_C firmar_tp
  ret
  ;; -------------------------------------------------------------------------- ;;


%include "a20.asm"
