#include "debug.h"


// TESTING ++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++

void run_tests() {
	return;
}


// DEBUG TOOLS +++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++
void error(const char * text) {
	print(text, 0, 0, FG_LIGHT_RED | BG_BLACK);
	while (1) {};
}

void warning(const char * text) {
	print(text, 0, 0, FG_LIGHT_BLUE | BG_BLACK);
}

void notify_int(const char * text, unsigned int var) {
	print_int(var, 7, 0, FG_WHITE | BG_BLACK);
	print(text, 10, 0, FG_WHITE | BG_BLACK);
}

void notify_hex(const char * text, unsigned int var) {
	print_hex(var, 8, 7, 0, FG_WHITE | BG_BLACK);
	print(text, 0, 0, FG_WHITE | BG_BLACK);
}