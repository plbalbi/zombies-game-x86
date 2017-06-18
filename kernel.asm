; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

global start


;; Saltear seccion de datos
jmp start

;;
;; Símbolos externos
;; ------------------------------------------------------------------------- ;;
%define BREAK xchg bx, bx

%define GDT_IDX_CODE_KERNEL 8
%define GDT_IDX_CODE_USER 9
%define GDT_IDX_DATA_KERNEL 10
%define GDT_IDX_DATA_USER 11
%define GDT_IDX_SCREEN 12
%define GDT_IDX_TSS_INIT 30

extern GDT_DESC

extern idt_inicializar
extern IDT_DESC

extern mmu_inicializar
extern mmu_inicializar_esquema_kernel

extern tss_inicializar

extern resetear_pic
extern habilitar_pic

extern run_tests

extern print_screen

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

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
	or eax, 1
	mov cr0, eax
    
    ; Saltar a modo protegido
	; ¡Estoy en modo mi protegido pero mi CS no tiene un índice a la
	; GDT ni a palos! ¡Fuck! Tengo que hacer un jump far para que tenga
	; un valor como la gente antes de que se pudra todou
	jmp GDT_IDX_CODE_KERNEL<<3:protegido ; índice 8 y tres primeros bits en 0 (esto actualiza CS)

BITS 32
protegido:
    ; Establecer selectores de segmentos
    xor eax, eax
    mov ax, GDT_IDX_DATA_KERNEL<<3
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov ax, GDT_IDX_SCREEN<<3
    mov fs, ax ; segmento para video
    mov gs, ax

    ; Establecer la base de la pila
    mov esp, 0x27000
    mov ebp, esp
    
    ; Inicializar pantalla
    call print_screen
    
    ; Inicializar el directorio de paginas
    call mmu_inicializar_esquema_kernel
    
    ; Cargar directorio de paginas
    mov eax, 0x27000
    mov cr3, eax

    ; Inicializar mmu
    call mmu_inicializar

    ; Habilitar paginacion
    mov eax, cr0
    or eax, 1<<31
    mov cr0, eax
    
    ; Inicializar tss
    call tss_inicializar

    ; Inicializar la IDT
    call idt_inicializar

    ; Cargar IDT
    lidt [IDT_DESC]
      ; Excepcion GP -> mov [gs:0xFFFFFFFFFFFF], eax
      ; Excepción DIV0 -> xor ax, ax     div ax 
 
    ; Configurar controlador de interrupciones
    call resetear_pic
    call habilitar_pic

    ; Cargar tarea inicial
    mov ax, (GDT_IDX_TSS_INIT << 3)
    ltr ax

    ; Habilitar interrupciones
    ; Nota: El scheduler ya se encarga
    sti

    ; Tests
    call run_tests

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"