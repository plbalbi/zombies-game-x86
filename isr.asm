; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32


extern fin_intr_pic1

extern sched_proximo_indice

extern handle_kernel_exception
extern handle_zombi_exception
extern handle_keyboard
extern handle_syscall_mover

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
    push %1
    ; Lo siguiente es medio tricky. Si estaba en el kernel, quiero
    ; decir que interrupción sé y colgarme. Si estaba en una tarea,
    ; quiero matar la tarea y seguir con el programa. Para checkear
    ; qué es lo que soy, checkeo los 2 bits más bajos de 'ds'. En
    ; un stack-switch el segmento de datos no cambia, por eso.
    xor eax, eax
    mov ax, ds
    and ax, 0x0003
    cmp ax, 0x0000
    je .kernel
    jnz .user
.kernel:
    call handle_kernel_exception
    ;note: this function never returns
.user:
    call handle_zombi_exception
    jmp 29<<3:0x0 ; task-switch a IDLE
    ; I'm not coming back \^^/

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
    ; xchg bx, bx
    ; push eax
    ; call handle_syscall_mover
    ; pop eax
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
