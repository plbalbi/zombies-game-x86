#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "defines.h"
#include "game.h"

void handle_kernel_exception(unsigned int code);
void handle_zombi_exception(unsigned int code);
void handle_keyboard(unsigned int key);
void handle_syscall_mover(direccion d);

#endif  /* !__INTERRUPT_H__ */
