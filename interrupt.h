#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "defines.h"
#include "i386.h"
#include "screen.h"
#include "colors.h"
#include "mmu.h"
#include "sched.h"
#include "tss.h"
#include "game.h"

void handle_interrupt(unsigned int code);
void handle_keyboard(unsigned int key);
void lanzar_zombi(unsigned short jugador);

#endif  /* !__INTERRUPT_H__ */