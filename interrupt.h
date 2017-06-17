#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "defines.h"
#include "i386.h"
#include "screen.h"
#include "colors.h"
#include "mmu.h"
#include "tss.h"
#include "game.h"

void handle_interrupt(unsigned int code);

#endif  /* !__INTERRUPT_H__ */