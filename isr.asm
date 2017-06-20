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

extern debug_save_context

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR_BODY 1
    xchg bx, bx
    ; Save context for debug
    pushad
    push gs
    push fs
    push es
    push ds
    mov eax, cr0
    push eax
    mov eax, cr2
    push eax
    mov eax, cr3
    push eax
    mov eax, cr4
    push eax 
    call debug_save_context
    add esp, 4*4 ; 4 reg de control
    add esp, 4*4 ; 4 reg de segmentos
    popad

    ; Nos fijamos si provenimos de un CS de nivel 0 o 3
    mov eax, [esp+4*2] ; cargamos CS (suponemos 'error code', se arregla después)
    and eax, 0x03 ; Nos quedamos con el CPL
    cmp eax, 0x00 ; Preguntamos si es nivel 0
    je .kernel
    jnz .user

    ; Si veniamos del kernel, de idle o de una interrupción,
    ; nos quedamos colgamos y printeamos qué interrupción fue
.kernel:
    push %1
    push gs
    push fs
    push es
    push ds
    mov eax, cr0
    push eax
    mov eax, cr2
    push eax
    mov eax, cr3
    push eax
    mov eax, cr4
    push eax
    call handle_kernel_exception
    ; I'm not coming back \^^/

    ; Si veniamos de una tarea, matamos la tarea, informamos
    ; al scheduler, refrescamos pantalla y saltamos a Idle
.user:
    push %1
    call handle_zombi_exception
    jmp 29<<3:0x0 ; task-switch a Idle
    ; I'm not coming back \^^/

%endmacro


%macro ISR 1
global _isr%1

_isr%1:
    ISR_BODY %1

%endmacro

%macro ISR_NOCODE 1
global _isr%1

_isr%1:
    push 0x12345678 ; easy to identify
    ISR_BODY %1

%endmacro


;;
;; Datos
;; -------------------------------------------------------------------------- ;;
sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00

ISR_NOCODE 0
ISR_NOCODE 1
ISR_NOCODE 2
ISR_NOCODE 3
ISR_NOCODE 4
ISR_NOCODE 5
ISR_NOCODE 6
ISR_NOCODE 7
ISR 8
ISR_NOCODE 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR_NOCODE 15
ISR_NOCODE 16
ISR 17
ISR_NOCODE 18
ISR_NOCODE 19

;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;
global _isr32
_isr32:
    pushad
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
    popad
    iret
; Direcciones para salto entre tareas
.jump_far_address:  DD 0xBEBECACA ; fruta que nos chupa dos huevos
.jump_far_selector: DW 0xDEAD ; fruta que vamos a sobreescribir

;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
global _isr33
_isr33:
    pushad
    xor eax, eax
    in al, 0x60
    push eax
    call handle_keyboard
    pop eax
    call fin_intr_pic1
    popad
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
    pushad
    push eax
    call handle_syscall_mover
    jmp 29<<3:0x0 ; task-switch a IDLE
    pop eax
    popad
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
