;; -------------------------------------------------------------------------- ;;
; RUTINA:   limpiarPantalla
; REQ:      Ser kernel; Queres limpiar la pantalla; Ganas de ejecutarla?
;; -------------------------------------------------------------------------- ;;
; Se encarga de rellenar la pantalla con el fondo verde, los rectangulitos de los jugadores
; y los numeros de los  zombies. Accede mediante el segmente de video (con permisos de kernel)

extern print_misc

%define FILA_SIZE 80
%define CANT_FILAS 50
%define FONDO_VERDE 0x20FF
%define FONDO_NEGRO 0x0FFF
%define FONDO_ROJO 0x40FF
%define FONDO_AZUL 0x10FF

limpiarPantalla:
  xor ebx, ebx ; Registro para ir llevando la cuenta del que recorro
  ; mov ecx, 80*50 ; Cantidad de poxles a recorrer (Cargado para loopear)

  ; Barra negra de arriba
  mov ecx, FILA_SIZE ; Cantidad de poxles a recorrer (Cargado para loopear)
  .filaNegra:
  mov word[es:ebx], FONDO_NEGRO ; Cargo el relleno
  inc ebx
  inc ebx ; Incremento los 2Bytes del Poxel
  loop .filaNegra

  ; Fondo verde del mapa
  mov ecx, (CANT_FILAS-1-5)*FILA_SIZE ; 50 filas totales - la negra de arriba - la barra de abajo
  .fondoVerde:
  mov word[es:ebx], FONDO_VERDE ; Cargo el relleno
  inc ebx
  inc ebx ; Incremento los 2Bytes del Poxel
  loop .fondoVerde

  ; Barra de info de abajo
  mov ecx, FILA_SIZE*5 ; Cantidad de poxles a recorrer (Cargado para loopear)
  .filaNegra2:
  mov word[es:ebx], FONDO_NEGRO ; Cargo el relleno
  inc ebx
  inc ebx ; Incremento los 2Bytes del Poxel
  loop .filaNegra2

  ; Columna roja y azul
  mov ebx, FILA_SIZE*2 ; Para comienze en la segunda fila
  mov ecx, (CANT_FILAS-1-5) ; 50 filas totales - la negra de arriba - la barra de abajo
  .cols_de_colores:
  mov word[es:ebx], FONDO_ROJO ; Cargo el relleno
  mov word[es:ebx + (FILA_SIZE-1)*2], FONDO_AZUL ; Cargo el relleno
  add ebx, FILA_SIZE*2
  loop .cols_de_colores

  ; Pongo los numeritos y la firma
  call print_misc
  
  ret