#include "debug.h"


// TESTING ++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++

void run_tests() {
	mmu_inicializar_zombi(1, 1, 0); //tarea, jugador, y
	return;
}


// EXCEPTIONS ++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++
void handle_interrupt(unsigned int code) {
	// Obs: Por default una interrupción haltea el procesador
	clear_line();
	char* str = "Generic Interruption";
	if (code == 0) {
		str = "FAULT: Divide Error";
	} else if (code == 6) {
		str = "FAULT: Invalid Opcode";
	} else if (code == 8) {
		str = "ABORT: Double Fault";
	} else if (code == 10) {
		str = "FAULT: Invalid TSS";
	} else if (code == 11) {
		str = "FAULT: Segment Not Present";
	} else if (code == 12) {
		str = "FAULT: Stack-Segment Fault";
	} else if (code == 13) {
		str = "FAULT: General Protection";
	} else if (code == 14) {
		str = "FAULT: Page Fault";
	}
	print_int(code, 1, 0, FG_LIGHT_RED | BG_BLACK);
	print(str, 3, 0, FG_LIGHT_RED | BG_BLACK);
	while (1) { hlt(); };
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