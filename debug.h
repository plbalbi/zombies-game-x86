#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "defines.h"
#include "i386.h"
#include "screen.h"
#include "colors.h"
#include "mmu.h"
#include "idt.h"
#include "tss.h"
#include "game.h"

void error(const char * text);
void warning(const char * text);
void notify_int(const char * text, unsigned int var);
void notify_hex(const char * text, unsigned int var);

void clear_line(void);

// MODO DEBUG DEL JUEGO
void debug_on();
void debug_off();
const ca* screen_backup_dir;
void backup_screen();
void restore_screen();

#endif  /* !__DEBUG_H__ */
