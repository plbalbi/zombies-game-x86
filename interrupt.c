#include "interrupt.h"

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

void handle_keyboard(unsigned int key) {
	print_teclado(key);

	// Jugador A
	if (key == KEY_W) {
		if (y_a != 1) {
			y_a--;
			print_jugador(1, tipo_a, y_a);
			print(" ", 0, y_a+1, BG_RED);
		}
	} else if (key == KEY_S) {
		if (y_a != MAP_HEIGHT) {
			y_a++;
			print_jugador(1, tipo_a, y_a);
			print(" ", 0, y_a-1, BG_RED);
		}
	} else if (key == KEY_A) {
		if (tipo_a != 1) {
			tipo_a--;
			print_jugador(1, tipo_a, y_a);
		}
	} else if (key == KEY_D) {
		if (tipo_a != 3) {
			tipo_a++;
			print_jugador(1, tipo_a, y_a);
		}
	}

	// Jugador B
	if (key == KEY_I) {
		if (y_b != 1) {
			y_b--;
			print_jugador(2, tipo_b, y_b);
			print(" ", 79, y_b+1, BG_BLUE);
		}
	} else if (key == KEY_K) {
		if (y_b != MAP_HEIGHT) {
			y_b++;
			print_jugador(2, tipo_b, y_b);
			print(" ", 79, y_b-1, BG_BLUE);
		}
	} else if (key == KEY_J) {
		if (tipo_b != 1) {
			tipo_b--;
			print_jugador(2, tipo_b, y_b);
		}
	} else if (key == KEY_L) {
		if (tipo_b != 3) {
			tipo_b++;
			print_jugador(2, tipo_b, y_b);
		}
	}
}