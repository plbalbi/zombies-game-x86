#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "defines.h"

void handle_interrupt(unsigned int code);
void handle_keyboard(unsigned int key);

#endif  /* !__INTERRUPT_H__ */
