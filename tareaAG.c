/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "tactics.h"
#include "syscall.h"

void task() {
    int i;
    char* src;
    char* dst;
    // Preparation
    syscall_mover(ADE); // move forward
    src = NEUTRAL; // copy back
    dst = ATRAS;
    for (i = 0; i < PAGE_SIZE; i++) {
        *dst = *src; 
        src++;
        dst++; 
    }
    __asm__("jmp next+4096*6"); // move ip back

    __asm__("next:");
    while (1) {
        destroy(); // kill forward (está en 'tactics.c'. lo único que hace es poner en 0 los 3 cuadrados de adelante)
        //src = ATRAS; // copy forward
        //dst = NEUTRAL;
        //for (i = 0; i < PAGE_SIZE; i++) {
        //    *dst = *src;
        //    src++;
        //    dst++; 
        //}
        syscall_mover(ADE); // mode forward
    }
    // Esto de arriba sin descomentar funca, pero es lo mismo que no mover el eip
    // atrás. Al moverte adelante el cuadradito del medio
    // se copia adelante, y cuando el kernel mapea el zombi más adelante,
    // el cuadrado que antes que era medio y tenía al zombi ahora está atrás.
    // El problema es si te atacan el cuadrado del medio. En el turno en el que
    // te querés mover se copia el zombi roto. Y excepción.
    // El código comentado 'refresca' el cuadrado del medio. Pero se pincha
    // en algún lado, don no why. Yo sospecho de las variables, que no se
    // a donde carajo intenta buscarlas el código desde la página de atrás.
    // Igual el 'destroy' también usa variables y el stack, y todo, y parece
    // que anda (no probé que efectivamente destruya otros zombies, pero
    // al menos no se rompe).
    // Por eso intenté usar sólo assembler y registros, sin pasar por
    // memoria. Pero no lo pude hacer andar, no sé por qué salta excepción.

    //__asm__("next:");
    //__asm__("mov 0x8000000 + 4096*6, %eax"); // eax = ATRAS (src)
    //__asm__("mov 0x8000000, %ebx"); // ebx = NEUTRAL (src)
    //__asm__("mov 0, %ecx"); // ecx = 0 (index)
    //syscall_mover(ADE); // move forward
    //__asm__("jmp next");
}

#include "tactics.c"

