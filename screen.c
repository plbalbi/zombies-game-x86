/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"

// PRINT FUNCTIONS ++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
    int i;
    for (i = 0; text[i] != 0; i++) {
        p[y][x].c = (unsigned char) text[i];
        p[y][x].a = (unsigned char) attr;
        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }
}

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    int i;
    char hexa[8];
    char letras[16] = "0123456789ABCDEF";
    hexa[0] = letras[ ( numero & 0x0000000F ) >> 0  ];
    hexa[1] = letras[ ( numero & 0x000000F0 ) >> 4  ];
    hexa[2] = letras[ ( numero & 0x00000F00 ) >> 8  ];
    hexa[3] = letras[ ( numero & 0x0000F000 ) >> 12 ];
    hexa[4] = letras[ ( numero & 0x000F0000 ) >> 16 ];
    hexa[5] = letras[ ( numero & 0x00F00000 ) >> 20 ];
    hexa[6] = letras[ ( numero & 0x0F000000 ) >> 24 ];
    hexa[7] = letras[ ( numero & 0xF0000000 ) >> 28 ];
    for(i = 0; i < size; i++) {
        p[y][x + size - i - 1].c = hexa[i];
        p[y][x + size - i - 1].a = attr;
    }
}

void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    if( n > 9 ) {
        int a = n / 10;
        n -= 10 * a;
        print_int(a,x-1,y,attr);
    }
    p[y][x].c = '0'+n;
    p[y][x].a = attr;
}


// USER FUNCTIONS ++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void print_puntajes(unsigned int a, unsigned int b){
    print_int(a, 39-2, 50-3, FG_WHITE | BG_RED);
    print_int(b, 39+3, 50-3, FG_WHITE | BG_BLUE);
}

void print_cantidad_zombis(unsigned int a, unsigned int b){
    print_int(0, 39-8-1, 50-3, FG_WHITE | BG_RED);
    print_int(a, 39-8, 50-3, FG_WHITE | BG_RED);
    print_int(0, 39+9-1, 50-3, FG_WHITE | BG_BLUE);
    print_int(b, 39+9, 50-3, FG_WHITE | BG_BLUE);
}

void print_screen(){
    // Index declare
    int i, j;

    // Fondo verde
    for (i = 0; i < 80; i++) {
        for (j = 0; j < 50; j++) {
          print(" ", i, j, BG_GREEN);
        }
    }

    // Barras coloreadas de los jugadores
    for (j = 0; j < 50; j++) {
        print(" ", 0, j, BG_RED);
        print(" ", 79, j, BG_BLUE);
    }

    // Barra negra superior
    for (i = 0; i < 80; i++) {
        print(" ", i, 0, BG_BLACK);
    }

    // Barra negra inferior
    for (i = 0; i < 80; i++) {
        for (j = 50-5; j < 50; j++) {
            print(" ", i, j, BG_BLACK);
        }
    }

    // Cuadraditos de puntajes
    int x_medio_red = 39-2;
    int x_medio_blue = x_medio_red + 5;
    int y_medio = 50-3;
    for (i = -2; i <= 2; i++) {
        for (j = -2; j <= 2; j++) {
            print(" ", x_medio_red + i, y_medio + j, BG_RED);
            print(" ", x_medio_blue + i, y_medio + j, BG_BLUE);
        }
    }

    // Números para los zombis
    print("1 2 3 4 5 6 7 8", 4, 50-4, FG_WHITE | BG_BLACK);
    print("1 2 3 4 5 6 7 8", 80-20, 50-4, FG_WHITE | BG_BLACK);

    // Tareas activas
    print("X X X X X X X X", 4, 50-2, FG_RED | BG_BLACK);
    print("X X X X X X X X", 80-20, 50-2, FG_RED | BG_BLACK);

    // Puntajes y Restantes
    print_puntajes(0, 0);
    print_cantidad_zombis(20, 20);

    // Personajes
    print_jugador(1, tipo_a, y_a);
    print_jugador(2, tipo_b, y_b);

    // Firma
    const char s[] = "Bonobon Championship";
    print(s, 80-2-strlen(s), 0, FG_WHITE | BG_BLACK);

    // Null key
    print("0", 80-1, 0, FG_LIGHT_GREY | BG_BLACK);
}


void print_teclado(unsigned int key){
    // Player A
    if (key == KEY_W) { // w - Up
        print("w", 79, 0, FG_LIGHT_GREY | BG_BLACK);
    } else if (key == KEY_S) { // s - Down
        print("s", 79, 0, FG_LIGHT_GREY | BG_BLACK);
    } else if (key == KEY_A) { // a - Left
        print("a", 79, 0, FG_LIGHT_GREY | BG_BLACK);
    } else if (key == KEY_D) { // d - Right
        print("d", 79, 0, FG_LIGHT_GREY | BG_BLACK);
    } else if (key == KEY_LS) { // LShift
        print("L", 79, 0, FG_LIGHT_GREY | BG_BLACK);
    // Player 2
    } else if (key == KEY_I) { // i - Up
        print("i", 79, 0, FG_LIGHT_GREY | BG_BLACK);
    } else if (key == KEY_K) { // k - Down
        print("k", 79, 0, FG_LIGHT_GREY | BG_BLACK);
    } else if (key == KEY_L) { // l - Left
        print("l", 79, 0, FG_LIGHT_GREY | BG_BLACK);
    } else if (key == KEY_J) { // j - Right
        print("j", 79, 0, FG_LIGHT_GREY | BG_BLACK);
    } else if (key == KEY_RS) { // RShift
        print("R", 79, 0, FG_LIGHT_GREY | BG_BLACK);
    }
}

void print_jugador(unsigned short jugador, unsigned short tipo, int y){
    char* s;
    if (tipo == 1){
        s = CHAR_GUERRERO;
    } else if (tipo == 2){
        s = CHAR_MAGO;
    } else {
        s = CHAR_CLERICO;
    }

    unsigned int x;
    unsigned short attr;
    if (jugador == 1) {
        x = 0;
        attr = FG_LIGHT_RED | BG_RED;
    } else if (jugador == 2) {
        x = 79;
        attr = FG_LIGHT_BLUE | BG_BLUE;
    }

    print(s, x, y+1, attr);
}

void print_zombi(unsigned short jugador, unsigned short tipo, posicion pos){
    char* s;
    if (tipo == 1){
        s = CHAR_GUERRERO;
    } else if (tipo == 2){
        s = CHAR_MAGO;
    } else {
        s = CHAR_CLERICO;
    }

    unsigned short attr;
    if (jugador == 1) {
        attr = FG_RED | BG_GREEN;
    } else if (jugador == 2) {
        attr = FG_BLUE | BG_GREEN;
    }

    print(s, pos.x+1, pos.y+1, attr);
}


// AUXILIARS +++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned int strlen(const char *str){
    const char *s;
    for (s = str; *s; ++s);
    return(s - str);
}