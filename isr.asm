; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32


extern fin_intr_pic1

extern sched_proximo_indice

extern print_teclado

extern handle_interrupt

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
    push %1
    call handle_interrupt
    add esp, 4
    iret

%endmacro

;;
;; Datos
;; -------------------------------------------------------------------------- ;;
sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00

isrnumero:           dd 0x00000000
isrClock:            db '|/-\'

ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19

;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;
global _isr32
_isr32:
    call fin_intr_pic1
    call proximo_reloj
    iret

;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
global _isr33
_isr33:
    push eax
    xor eax, eax
    in al, 0x60
    push eax
    call print_teclado
    pop eax
    call fin_intr_pic1
    pop eax
    iret


;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;

%define IZQ 0xAAA
%define DER 0x441
%define ADE 0x83D
%define ATR 0x732

global _isr102
_isr102:
    iret

;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
proximo_reloj:
        pushad
        inc DWORD [isrnumero]
        mov ebx, [isrnumero]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrnumero], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock
                imprimir_texto_mp ebx, 1, 0x0f, 49, 79
                popad
        ret