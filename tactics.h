
#define PAGE_SIZE               (1<<12)
#define DIR_INICIO_ZOMBI_VISION  0x8000000

#define NEUTRAL                 (DIR_INICIO_ZOMBI_VISION + 0*PAGE_SIZE)
#define ADELANTE                (DIR_INICIO_ZOMBI_VISION + 1*PAGE_SIZE)
#define DIAG_ADE_DER            (DIR_INICIO_ZOMBI_VISION + 2*PAGE_SIZE)
#define DIAG_ADE_IZQ            (DIR_INICIO_ZOMBI_VISION + 3*PAGE_SIZE)
#define DERECHA                 (DIR_INICIO_ZOMBI_VISION + 4*PAGE_SIZE)
#define IZQUIERDA               (DIR_INICIO_ZOMBI_VISION + 5*PAGE_SIZE)
#define ATRAS                   (DIR_INICIO_ZOMBI_VISION + 6*PAGE_SIZE)
#define DIAG_ATR_IZQ            (DIR_INICIO_ZOMBI_VISION + 7*PAGE_SIZE)
#define DIAG_ATR_DER            (DIR_INICIO_ZOMBI_VISION + 8*PAGE_SIZE)

#define ALREDEDOR               (DIR_INICIO_ZOMBI_VISION + 1*PAGE_SIZE)
#define ALREDEDOR_SIZE          (8*PAGE_SIZE)


#define BREAK __asm__ volatile ("xchg %%bx, %%bx" : );


unsigned int random();
void destroy();


#define REP0(X)
#define REP1(X) X
#define REP2(X) REP1(X) X
#define REP3(X) REP2(X) X
#define REP4(X) REP3(X) X
#define REP5(X) REP4(X) X
#define REP6(X) REP5(X) X
#define REP7(X) REP6(X) X
#define REP8(X) REP7(X) X
#define REP9(X) REP8(X) X
#define REP10(X) REP9(X) X

#define REP(HUNDREDS,TENS,ONES,X) \
  REP##HUNDREDS(REP10(REP10(X))) \
  REP##TENS(REP10(X)) \
  REP##ONES(X)

 // clc -> clear carry flag. It's 1 bit long.
#define WALL __asm__ ( REP(9, 0, 0, "clc\n\t") );