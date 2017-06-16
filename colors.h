#ifndef __COLORS_H__
#define __COLORS_H__

/* Definicion de colores */
/* -------------------------------------------------------------------------- */
#define FG_BLACK              (0x0)
#define FG_BLUE               (0x1)
#define FG_GREEN              (0x2)
#define FG_CYAN               (0x3)
#define FG_RED                (0x4)
#define FG_MAGENTA            (0x5)
#define FG_BROWN              (0x6)
#define FG_LIGHT_GREY         (0x7)
#define FG_DARK_GREY          (0x8)
#define FG_LIGHT_BLUE         (0x9)
#define FG_LIGHT_GREEN        (0xA)
#define FG_LIGHT_CYAN         (0xB)
#define FG_LIGHT_RED          (0xC)
#define FG_LIGHT_MAGENTA      (0xD)
#define FG_LIGHT_BROWN        (0xE)
#define FG_WHITE              (0xF)

#define BG_BLACK              (0x0 << 4)
#define BG_BLUE               (0x1 << 4)
#define BG_GREEN              (0x2 << 4)
#define BG_CYAN               (0x3 << 4)
#define BG_RED                (0x4 << 4)
#define BG_MAGENTA            (0x5 << 4)
#define BG_BROWN              (0x6 << 4)
#define BG_LIGHT_GREY         (0x7 << 4)

#define BLINK                 (0x8 << 4)

#endif /* !__COLORS_H__ */