; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32


extern fin_intr_pic1

extern sched_proximo_indice

extern handle_interrupt
extern handle_keyboard

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
    pop eax ; error code, see with bochs
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
    push eax
    push ebx
    call fin_intr_pic1
    call proximo_reloj
    str bx ; Cargo el TR en bx
    cmp bx, 0x0 ; Veo si es 0x0 -> Nunca se cargo una tarea todavia
    je .same_task ; Salgo en ese caso
    ; -----------------
    ; SCHEDULER SECTION
    ; -----------------
    call sched_proximo_indice ; EAX <- indice del descriptor de la proxima tarea (en la gdt)
    shl eax, 3 ; 3 primeros bits de atributos para acceder en la gdt, son 0 ya que se accede con privilegios de Kernel
    str bx ; Cargo el TR en bx
    cmp bx, ax ; Comparo la parte visible del TR (el selector), con el selector de la "nueva" tarea
    je .same_task ; Si son distintas, realizo el TASK-SWITCH
    xchg bx, bx
    mov [.jump_far_selector], ax ; Cargo el nuevo selector
    jmp far [.jump_far_address] ; Salto al mismo
.same_task:
    pop ebx
    pop eax
    iret
; Direcciones para salto entre tareas
.jump_far_address:  DD 0xBEBECACA ; fruta que nos chupa dos huevos
.jump_far_selector: DW 0xDEAD ; fruta que vamos a sobreescribir

;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
global _isr33
_isr33:
    push eax
    xor eax, eax
    in al, 0x60
    push eax
    call handle_keyboard
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
%define LAST_POXEL 80*49*2+79*2
%define CLOCK_BG 0x0F

proximo_reloj:
    ; Actualizando relojito
    push eax
    push ebx
    xor ebx, ebx
    mov ah, CLOCK_BG ; Cargo el fondo de poxel del clock
    mov bl, [.last_char] ; Me cargo el ultimos index el clock
    cmp bl, 0x8
    je .reset_clock
    mov al, [.clock_char + ebx]
    mov word [fs:LAST_POXEL], ax
    inc bl
    mov [.last_char], bl
    jmp .fin_clock
    .reset_clock:
    mov byte[.last_char], 0x1
    mov al, 0x7C
    mov word [fs:LAST_POXEL], ax
    .fin_clock:
    pop ebx
    pop eax
    ret

.clock_char: DB 0x7C, 0x2F, 0x2D, 0x5C, 0x7C, 0x2F, 0x2D, 0x5C ; Secuencia de reloj para indexar
.last_char: DB 0x0 ; Ultimo index -> Resetea en 8
