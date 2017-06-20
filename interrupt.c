#include "interrupt.h"
#include "i386.h"
#include "screen.h"
#include "colors.h"
#include "mmu.h"
#include "sched.h"
#include "tss.h"
#include "game.h"
#include "debug.h"


void handle_kernel_exception(unsigned int cr4,
							unsigned int cr3,
							unsigned int cr2,
							unsigned int cr0,
							unsigned int ds,
							unsigned int es,
							unsigned int fs,
							unsigned int gs,
							unsigned int code,
							unsigned int inter,
							unsigned int eip,
							unsigned int cs,
							unsigned int eflags,
							unsigned int esp,
							unsigned int ss) {
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

	print("esp",28,20, FG_LIGHT_RED | BG_BLACK);
	print_hex(esp,8,28,21, FG_LIGHT_RED | BG_BLACK);
	print("eip",28 ,23, FG_LIGHT_RED | BG_BLACK);
	print_hex(eip,8,28,24, FG_LIGHT_RED | BG_BLACK);
	print("ds",28,26, FG_LIGHT_RED | BG_BLACK);
	print_hex(ds,4,28,27, FG_LIGHT_RED | BG_BLACK);
	print("cs",28,29, FG_LIGHT_RED | BG_BLACK);
	print_hex(cs,4,28,30, FG_LIGHT_RED | BG_BLACK);
	print("ss",28,32, FG_LIGHT_RED | BG_BLACK);
	print_hex(ss,4,28,33, FG_LIGHT_RED | BG_BLACK);
	print("eflags",28,35, FG_LIGHT_RED | BG_BLACK);
	print_hex(eflags,8,28,37, FG_LIGHT_RED | BG_BLACK);
	print("cr3",28,39, FG_LIGHT_RED | BG_BLACK);
	print_hex(cr3,8,28,40, FG_LIGHT_RED | BG_BLACK);

	while (1) { hlt(); };
}

void handle_zombi_exception(unsigned int code) {
	// Matamos la tarea (la sacamos del scheduler)
	sched_desactivar_zombi(current_player(), current_task());

	// Borramos del mapa
	posicion pos;
	if (current_player() == player_A) {
		pos = zombis_pos_a[current_task()];
	} else {
		pos = zombis_pos_b[current_task()];
	}
	print(" ", pos.x+1, pos.y+1, BG_GREEN);

	// Refrescamos a los zombis
	print_zombis();

	// Dibujamos en la barra de control
	clear_line();
	if (current_player() == player_A) {
		print("X", 4+current_task()*2, 50-2, FG_RED | BG_BLACK);
	} else {
		print("X", 80-20+current_task()*2, 50-2, FG_RED | BG_BLACK);
	}

	// Let the people know
	print_int(code, 1, 0, FG_LIGHT_MAGENTA | BG_BLACK);
	print("Zombi", 3, 0, FG_LIGHT_MAGENTA | BG_BLACK);
	if (current_player() == player_A) {
		print("rojo", 9, 0, FG_LIGHT_MAGENTA | BG_BLACK);
	} else {
		print("azul", 9, 0, FG_LIGHT_MAGENTA | BG_BLACK);
	}
	print_int(current_task(), 14, 0, FG_LIGHT_MAGENTA | BG_BLACK);
	print("se recato", 16, 0, FG_LIGHT_MAGENTA | BG_BLACK);
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

extern void _isr0(void);

void handle_syscall_mover(direccion d){
	// Averiguar la info del zombi
	unsigned int curr_player = current_player();
	unsigned int curr_task = current_task();
	posicion pos_vieja = (player_A == curr_player) ? zombis_pos_a[curr_task] : \
		zombis_pos_b[curr_task];
	unsigned int curr_cr3 = tss_leer_cr3(curr_player, curr_task);

	// Averiguar con la direccion para donde ir
	posicion destiny;
	int reverse = 1;
	if (curr_player == player_B) reverse = -1;
	if (d == IZQ) {
		destiny.x = pos_vieja.x;
		destiny.y = ( (pos_vieja.y - (1 * reverse) + MAP_HEIGHT) % MAP_HEIGHT);
	}else if (d == DER) {
		destiny.x = pos_vieja.x;
		destiny.y = ( (pos_vieja.y + (1 * reverse) + MAP_HEIGHT) % MAP_HEIGHT);
	}else if (d == ADE) {
		destiny.x = pos_vieja.x + (1*reverse);
		destiny.y = pos_vieja.y;
	}else{ // d==ATR
		destiny.x = pos_vieja.x - (1*reverse);
		destiny.y = pos_vieja.y;
	}

	// Verificar que los parámetros sean correctos
	if (d != IZQ && d != DER && d != ADE && d != ATR) {
		_isr0(); // KILL
	}

	// Actualizar posicion
	if (curr_player == player_A) {
		zombis_pos_a[curr_task] = destiny;
	}else{
		zombis_pos_b[curr_task] = destiny;
	}

	// 'Moverse'
	replicar_zombi(d);

	// Desmapear paginacion actual -> No me hace falta desmapear, solo piso el mapeo anterior
	// Mapearme las nuevas posiciones
	mmu_mapear_vision_zombi(curr_player, curr_cr3, destiny.x, destiny.y);

	// Borrarme del mapa mi iconito, dejando rastro
	print_zombie_trace(pos_vieja);

	// Refresco todos los zombis
	print_zombis();

	if (destiny.x == 0 || destiny.x == MAP_WIDTH-1) {
		// Winning! ~ Charlie Sheen (1972-2017)
		// Acabo de buscar si murio, tranquilos chicos, Charlie still alive

		// Actualizamos info del juego
		if (destiny.x == 0) {
			puntaje_b++;
		} else {
			puntaje_a++;
		}

		// Matamos la tarea (la sacamos del scheduler)
		sched_desactivar_zombi(curr_player, curr_task);

		// Dibujamos en el mapa
		print(" ", destiny.x+1, destiny.y+1, BG_GREEN);

		// Dibujamos en la barra de control
		clear_line();
		if (curr_player == player_A) {
			print("X", 4+curr_task*2, 50-2, FG_RED | BG_BLACK);
		} else {
			print("X", 80-20+curr_task*2, 50-2, FG_RED | BG_BLACK);
		}
		print_puntajes(puntaje_a, puntaje_b);

		// Let the people know
		clear_line();
		print("Zombi", 1, 0, FG_LIGHT_GREEN | BG_BLACK);
		if (current_player() == player_A) {
			print("rojo", 7, 0, FG_LIGHT_GREEN | BG_BLACK);
		} else {
			print("azul", 7, 0, FG_LIGHT_GREEN | BG_BLACK);
		}
		print_int(current_task(), 12, 0, FG_LIGHT_GREEN | BG_BLACK);
		print("se gano un bonobon", 14, 0, FG_LIGHT_GREEN | BG_BLACK);
	}


}
