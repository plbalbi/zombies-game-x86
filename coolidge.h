#ifndef COOLIDGE_H
#define COOLIDGE_H

typedef bool _Bool;
#define true True
#define false False

// NOTA: Un poxel es un pixel, pero gordito

typedef enum color_t { black, blue, green, cyan, red, magenta, poop, gray} color; // rellenar colores

// Rellena el color de un poxel
void pintar_poxel(unsigned int x, unsigned int y, color c);

// Solo cambia el caracter, manteniendo attrs.
void solo_escribir(unsigned int x, unsigned int y, char ch);

// Cambia todo, atributos y contenido del poxel
void pintar_y_escribir(unsigned int x, unsigned int y, color bg, char ch, color fg,
  bool bb_bg, bool bb_fg);

#endif
