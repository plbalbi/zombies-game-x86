#include "debug.h"
#include "i386.h"
#include "colors.h"
#include "mmu.h"
#include "idt.h"
#include "tss.h"
#include "game.h"



// TESTING ++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++

void run_tests() {
	mmu_inicializar_zombi(1, 1, 0); //tarea, jugador, y
	return;
}


// DEBUG TOOLS +++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++
void error(const char * text) {
	clear_line();
	print(text, 0, 0, FG_LIGHT_RED | BG_BLACK);
	while (1) { hlt(); };
}

void warning(const char * text) {
	clear_line();
	print(text, 0, 0, FG_LIGHT_BLUE | BG_BLACK);
}

void notify_int(const char * text, unsigned int var) {
	clear_line();
	print_int(var, 7, 0, FG_WHITE | BG_BLACK);
	print(text, 10, 0, FG_WHITE | BG_BLACK);
}

void notify_hex(const char * text, unsigned int var) {
	clear_line();
	print_hex(var, 8, 7, 0, FG_WHITE | BG_BLACK);
	print(text, 0, 0, FG_WHITE | BG_BLACK);
}


// AUXILIARES ++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++

void clear_line() {
	int i;
	for (i = 0; i < 50; i++) {
		print(" ", i, 0, BG_BLACK);
	}
}

// MODO DEBUG DEL JUEGO ++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++

// El rectángulo que cubre la pantalla de debug, al menos en el .pdf,
// es de 36 x 30 (contando el marco negro). La esquina superior
// izquierda está en (x,y) = (25,7) según la grilla del .pdf,
// que indexa desde 0.

// TODO: decidir dónde se guarda el backup de la pantalla al activar debug.
// Por ahora es un array e el kernel, acá mismo.
const ca screen_backup_dir[30*36];
context saved_context;

void debug_on(){
	debug = true;
	backup_screen();
	ca (*screen)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
	int x,y;
	for (y = 7; y < 7+36; y++) {
		for (x = 25; x < 25+30; x++) {
			screen[y][x].a = BG_LIGHT_GREY;
			screen[y][x].c = 0;
		}
	}
	for (y = 7; y < 7+36; y++) {
			screen[y][25].a = BG_BLACK;
			screen[y][25].c = 0;
			screen[y][25+30-1].a = BG_BLACK;
			screen[y][25+30-1].c = 0;
	}
	for (x = 25; x < 25+30; x++) {
			screen[7][x].a = BG_BLACK;
			screen[7][x].c = 0;
			screen[7+36-1][x].a = BG_BLACK;
			screen[7+36-1][x].c = 0;
	}

	for (x = 25+1; x < 25+30-1; x++) {
		screen[7+1][x].a = BG_BLUE;
		screen[7+1][x].c = 0;
	}
	print("Zombi - Falta cometida: ", 25+1, 7+1, FG_WHITE | BG_BLUE);
	print_int(saved_context.inter,25+25, 7+1, FG_WHITE | BG_BLUE);

	print("eax", 25+2, 7+3, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.eax,8, 25+2+4, 7+3, FG_WHITE | BG_LIGHT_GREY);
	print("ebx", 25+2, 7+5, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.ebx,8, 25+2+4, 7+5, FG_WHITE | BG_LIGHT_GREY);
	print("ecx", 25+2, 7+7, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.ecx,8, 25+2+4, 7+7, FG_WHITE | BG_LIGHT_GREY);
	print("edx", 25+2, 7+9, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.edx,8, 25+2+4, 7+9, FG_WHITE | BG_LIGHT_GREY);
	print("esi", 25+2, 7+11, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.esi,8, 25+2+4, 7+11, FG_WHITE | BG_LIGHT_GREY);
	print("edi", 25+2, 7+13, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.edi,8, 25+2+4, 7+13, FG_WHITE | BG_LIGHT_GREY);
	print("ebp", 25+2, 7+15, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.ebp,8, 25+2+4, 7+15, FG_WHITE | BG_LIGHT_GREY);
	print("esp", 25+2, 7+17, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.esp,8, 25+2+4, 7+17, FG_WHITE | BG_LIGHT_GREY);
	print("eip", 25+2, 7+19, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.eip,8, 25+2+4, 7+19, FG_WHITE | BG_LIGHT_GREY);

	print("cs", 25+3, 7+21, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.cs,4, 25+3+3, 7+21, FG_WHITE | BG_LIGHT_GREY);
	print("ds", 25+3, 7+23, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.ds,4, 25+3+3, 7+23, FG_WHITE | BG_LIGHT_GREY);
	print("es", 25+3, 7+25, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.es,4, 25+3+3, 7+25, FG_WHITE | BG_LIGHT_GREY);
	print("fs", 25+3, 7+27, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.fs,4, 25+3+3, 7+27, FG_WHITE | BG_LIGHT_GREY);
	print("gs", 25+3, 7+29, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.gs,4, 25+3+3, 7+29, FG_WHITE | BG_LIGHT_GREY);
	print("ss", 25+3, 7+31, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.ss,4, 25+3+3, 7+31, FG_WHITE | BG_LIGHT_GREY);
	print("eflags", 25+3, 7+33, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.eflags,8, 25+3+7, 7+33, FG_WHITE | BG_LIGHT_GREY);

	print("cr0", 25+16, 7+3, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.cr0,8, 25+16+4, 7+3, FG_WHITE | BG_LIGHT_GREY);
	print("cr2", 25+16, 7+5, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.cr2,8, 25+16+4, 7+5, FG_WHITE | BG_LIGHT_GREY);
	print("cr3", 25+16, 7+7, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.cr3,8, 25+16+4, 7+7, FG_WHITE | BG_LIGHT_GREY);
	print("cr4", 25+16, 7+9, FG_BLACK | BG_LIGHT_GREY);
	print_hex(saved_context.cr4,8, 25+16+4, 7+9, FG_WHITE | BG_LIGHT_GREY);

	print("stack", 25+16, 7+20, FG_BLACK | BG_LIGHT_GREY);
	if (saved_context.esp > DIR_INICIO_ZOMBI_VISION && saved_context.esp < DIR_INICIO_ZOMBI_PILA) {
		int i = 0;
		while (saved_context.esp+i*4 < saved_context.ebp && i<MAX_STACK_DEBUG) {
			print_hex(saved_context.stack[i],8, 25+16, 7+20+2+i, FG_WHITE | BG_LIGHT_GREY);
			i++;
		}
	}
}

void debug_off(){
	debug = false;
	restore_screen();
}

void backup_screen(){
	ca (*screen_src)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
	ca* screen_dst = (ca*) screen_backup_dir;
	int x,y;
	int i = 0;
	for (y = 7; y < 7+36; y++) {
		for (x = 25; x < 25+30; x++) {
			screen_dst[i] = screen_src[y][x];
			i++;
		}
	}
}

void restore_screen(){
	ca (*screen_src)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
	ca* screen_dst = (ca*) screen_backup_dir;
	int x,y;
	int i = 0;
	for (y = 7; y < 7+36; y++) {
		for (x = 25; x < 25+30; x++) {
			screen_src[y][x] = screen_dst[i];
			i++;
		}
	}
}

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
						unsigned int inter,
						unsigned int error_code,
						unsigned int eip,
						unsigned int cs,
						unsigned int eflags,
						unsigned int esp,
						unsigned int ss
						)
{
	saved_context.edi = edi;
	saved_context.esi = esi;
	saved_context.ebp = ebp;
	saved_context.esp = esp;
 	saved_context.ebx = ebx;
	saved_context.edx = edx;
	saved_context.ecx = ecx;
	saved_context.eax = eax;
 	saved_context.eflags = eflags;
 	saved_context.cs = cs;
 	saved_context.ds = ds;
 	saved_context.es = es;
 	saved_context.fs = fs;
 	saved_context.gs = gs;
 	saved_context.ss = ss;
 	saved_context.eip = eip;
	saved_context.cr0 = cr0;
	saved_context.cr2 = cr2;
	saved_context.cr3 = cr3;
	saved_context.cr4 = cr4;
	saved_context.inter = inter;

	if (esp > DIR_INICIO_ZOMBI_VISION && esp < DIR_INICIO_ZOMBI_PILA) {
		unsigned int* sp = (unsigned int*) esp;
		int i = 0;
		while (sp < (unsigned int*)ebp && i<MAX_STACK_DEBUG) {
			saved_context.stack[i] = *sp;
			sp++;
			i++;
		}
	}
}
