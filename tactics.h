
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