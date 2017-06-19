#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "screen.h"
#include "defines.h"

void error(const char * text);
void warning(const char * text);
void notify_int(const char * text, unsigned int var);
void notify_hex(const char * text, unsigned int var);

void clear_line(void);

// MODO DEBUG DEL JUEGO
void debug_on();
void debug_off();
void backup_screen();
void restore_screen();
void debug_save_context(unsigned int cr4,
						unsigned int cr3,
						unsigned int cr2,
						unsigned int cr0,
						unsigned int ds,
						unsigned int es,
						unsigned int fs,
						unsigned int gs,
						unsigned int edi,
						unsigned int esi,
						unsigned int ebp,
						unsigned int esp_actual,
						unsigned int ebx,
						unsigned int edx,
						unsigned int ecx,
						unsigned int eax,
						unsigned int error_code,
						unsigned int eip,
						unsigned int cs,
						unsigned int eflags,
						unsigned int esp,
						unsigned int ss
						);

typedef struct context_t {
    unsigned int edi;
    unsigned int esi;
    unsigned int ebp;
    unsigned int esp;
    unsigned int ebx;
    unsigned int edx;
    unsigned int ecx;
    unsigned int eax;
    unsigned int eip;
    unsigned int eflags;
    unsigned int cr0;
    unsigned int cr2;
    unsigned int cr3;
    unsigned int cr4;
    unsigned short cs;
    unsigned short ds;
    unsigned short es;
    unsigned short fs;
    unsigned short gs;
    unsigned short ss;
}__attribute__((__packed__)) context;


#endif  /* !__DEBUG_H__ */
