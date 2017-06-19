#include "interrupt.h"
#include "i386.h"
#include "screen.h"
#include "colors.h"
#include "mmu.h"
#include "sched.h"
#include "tss.h"
#include "game.h"
#include "debug.h"


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
		game_mover_jugador(player_A, UP);
	} else if (key == KEY_S) {
		game_mover_jugador(player_A, DOWN);
	} else if (key == KEY_A) {
		game_cambiar_tipo(player_A, DOWN);
	} else if (key == KEY_D) {
		game_cambiar_tipo(player_A, UP);
	} else if (key == KEY_LS) {
		game_lanzar_zombi(player_A);
	}

	// Jugador B
	if (key == KEY_I) {
		game_mover_jugador(player_B, UP);
	} else if (key == KEY_K) {
		game_mover_jugador(player_B, DOWN);
	} else if (key == KEY_J) {
		game_cambiar_tipo(player_B, DOWN);
	} else if (key == KEY_L) {
		game_cambiar_tipo(player_B, UP);
	} else if (key == KEY_RS) {
		game_lanzar_zombi(player_B);
	}

	// Juego
	if (key == KEY_Y) {
		if (debug == false) {
			debug_on();
		} else {
			debug_off();
		}
		// TODO: este if también debería preguntar si el modo debug está
		// ON o OFF. Es otra varaible global a agregar
	}

}


void handle_syscall_mover(direccion d){
	// Averiguar la posicion actual del zombie en la tarea
		// Averiguar pos_actual y CR3
	// Averiguar con la direccion para donde ir
		// Saber que direccion es la que debo ir
		// Calcular nueva posicion, asi el codigo siguiente es el mismo para cualquier opcion posible

	// Desmapear paginacion actual

	// Mapearme las nuevas posiciones

	// Copiar el codigo ahi

	// Borrarme del mapa mi iconito, dejando rastro

	// Dibujarme en el mapa nuevamente


	// TODO: Casos en que llegue al final (sumar puntos), me maten, etc...
}
