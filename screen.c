/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"


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

#define error_msg_size 16
void print_int_error(){
    int error_num;
    asm("movl %%eax, %0;" : "=r" (error_num) : );
    char* msg = "ERROR en int: ";
    print(msg, 40-error_msg_size/2 - 2,  25, 0x24);
    print_int(error_num, 40+error_msg_size/2, 25, 0x24);
}

void set_print_ptr(unsigned int x, unsigned int y)
  { cursor_reset = 1; frame_x = x; frame_y = y; };

void prrint(char* str){
  unsigned int x = cursor_x, y = cursor_y; // Carga el seteo de donde empieza el frame del cursor
  if (cursor_reset) {
    x = frame_x; y = frame_y;
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

void areloco(){
    int str_size = 5;
    char* testo= "PUTOO";
    while(1){
        for (int i = 0; i < 80-80%str_size; i+=1) {
            print(" ", i-1, 30, 0x20);
            print(testo, i, 30, 0x24);
            for (int j = 0; j < 2556000; j++) {

            }
        }
        print("    ", 80-1, 30, 0x20);
    }
}

void test_prrint(){
  set_print_ptr(10, 10);
  prrint("Esto es una prueba de imrpimir -> ");
  prrint("Esto deberia seguir ahora \ny esto deberia ir abajo");
}
