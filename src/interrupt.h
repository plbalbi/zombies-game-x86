#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "defines.h"
#include "game.h"

void handle_kernel_exception(unsigned int cr4,
							unsigned int cr3,
							unsigned int cr2,
							unsigned int cr0,
							unsigned int ds,
							unsigned int es,
							unsigned int fs,
							unsigned int gs,
							unsigned int code,
							unsigned int inter,
							unsigned int eip,
							unsigned int cs,
							unsigned int eflags,
							unsigned int esp,
							unsigned int ss);
void handle_zombi_exception(unsigned int code);
void handle_keyboard(unsigned int key);
void handle_syscall_mover(direccion d);

#endif  /* !__INTERRUPT_H__ */
