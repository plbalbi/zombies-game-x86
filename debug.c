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

// TODO: decidir dónde se guarda el backup de la pantalla al activar debug
// podría incluso un array acá mismo. Por ahora está en 0xCACA;
const ca* screen_backup_dir = (ca*) 0xCACA;

void debug_on(){
	// TODO: lo primero que se debería hacer es guardar el estado sin romper nada
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
	print("Zombi tu vieja", 25+1, 7+1, FG_WHITE | BG_BLUE);

	print("eax", 25+2, 7+3, FG_BLACK | BG_LIGHT_GREY);
	print("ebx", 25+2, 7+5, FG_BLACK | BG_LIGHT_GREY);
	print("ecx", 25+2, 7+7, FG_BLACK | BG_LIGHT_GREY);
	print("edx", 25+2, 7+9, FG_BLACK | BG_LIGHT_GREY);
	print("esi", 25+2, 7+11, FG_BLACK | BG_LIGHT_GREY);
	print("edi", 25+2, 7+13, FG_BLACK | BG_LIGHT_GREY);
	print("ebp", 25+2, 7+15, FG_BLACK | BG_LIGHT_GREY);
	print("esp", 25+2, 7+17, FG_BLACK | BG_LIGHT_GREY);
	print("eip", 25+2, 7+19, FG_BLACK | BG_LIGHT_GREY);

	print("cs", 25+3, 7+21, FG_BLACK | BG_LIGHT_GREY);
	print("ds", 25+3, 7+23, FG_BLACK | BG_LIGHT_GREY);
	print("es", 25+3, 7+25, FG_BLACK | BG_LIGHT_GREY);
	print("fs", 25+3, 7+27, FG_BLACK | BG_LIGHT_GREY);
	print("gs", 25+3, 7+29, FG_BLACK | BG_LIGHT_GREY);
	print("ss", 25+3, 7+31, FG_BLACK | BG_LIGHT_GREY);
	print("eflags", 25+3, 7+33, FG_BLACK | BG_LIGHT_GREY);

	print("cr0", 25+16, 7+3, FG_BLACK | BG_LIGHT_GREY);
	print("cr2", 25+16, 7+5, FG_BLACK | BG_LIGHT_GREY);
	print("cr3", 25+16, 7+7, FG_BLACK | BG_LIGHT_GREY);
	print("cr4", 25+16, 7+9, FG_BLACK | BG_LIGHT_GREY);

	print("stack", 25+16, 7+20, FG_BLACK | BG_LIGHT_GREY);


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





//
