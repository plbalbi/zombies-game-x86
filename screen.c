/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"

// PRINT FUNCTIONS +++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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

void prrint(char* str){
  unsigned int x = cursor_x, y = cursor_y; // Carga el seteo de donde empieza el frame del cursor
  if (cursor_reset) {
    x = frame_x; y = frame_y;
    cursor_reset = 0;
  }
  ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
  int i;
  unsigned char attr = p[y][x].a; // Deja los atributos del fondo
  for (i = 0; str[i] != 0; i++) {
    if (str[i] == '\n') {
      x = frame_x;
      y++;
    }else{
      p[y][x].c = (unsigned char) str[i];
      p[y][x].a = (unsigned char) attr;
      x++;
      if (x == VIDEO_COLS) {
        x = frame_x;
        y++;
      }
    }
    if (y == VIDEO_FILS) y = frame_y;
  }
  cursor_x = x;
  cursor_y = y;
}

void init_prrint_frame(){
  frame_x = 0;
  frame_y = 0;
  cursor_x = 0;
  cursor_y = 0;
  cursor_reset = 1;
}

void set_print_ptr(unsigned int x, unsigned int y)
  { cursor_reset = 1; frame_x = x; frame_y = y; };


// USER FUNCTIONS ++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define error_msg_size 16
void print_int_error(){
    int error_num;
    asm("movl %%eax, %0;" : "=r" (error_num) : );
    char* msg = "ERROR en int: ";
    print(msg, 40-error_msg_size/2 - 2,  25, 0x24);
    print_int(error_num, 40+error_msg_size/2, 25, 0x24);
}

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

void print_misc(){
  // Cuadraditos de puntajes
  int i, j;
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

  // Firma
  const char s[] = "Windows 2000";
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


// TEST DUMP +++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void areloco(){
  int str_size = 5;
  char* testo= "PUTOO";
	int i, j;
    while(1){
        for (i = 0; i < 80-80%str_size; i+=1) {
            print(" ", i-1, 30, 0x20);
            print(testo, i, 30, 0x24);
            for (j = 0; j < 2556000; j++) {

            }
        }
        print("    ", 80-1, 30, 0x20);
    }
}

void firmar_tp(){
  set_print_ptr(2, 0);
  prrint("Felizmente desarrolado en Windows Vista");
}

void seguir_llenando_pantalla(){
  set_print_ptr(4, 50-4);
  prrint("1 2 3 4 5 6 7 8");
  set_print_ptr(80-20, 50-4);
  prrint("1 2 3 4 5 6 7 8");
}

void test_prrint(){
  set_print_ptr(10, 10);
  prrint("imprimir \nimprimir\n");
  prrint("imprimir \nimprimir");
  prrint("imprimir \n\nimprimirjodasd asdijas d 9uds");
}

void testing_shit() {
  char s[] = "Wassup";
  print(s, 80-strlen(s), 3, FG_BLACK | BG_LIGHT_GREY);
}


// AUXILIARS +++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned int strlen(const char *str){
    const char *s;
    for (s = str; *s; ++s);
    return(s - str);
}