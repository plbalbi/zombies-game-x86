#include "debug.h"


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
	ca (*screen_src)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
	int x,y;
	for (y = 7; y < 7+36; y++) {
		for (x = 25; x < 25+30; x++) {
			screen_src[y][x].a = 0;
			screen_src[y][x].c = 0;
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





//
