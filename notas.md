--------------------------------------------------------------------------------
  NOTAS
--------------------------------------------------------------------------------

1 - funcion que formatee un poxel
2 - funcion que cambie el caracter escirto en un poxel
3 - Una que haga todo? ---> se podria definir con esta cada una de las de arriba

__Ideas para hacer el super coso del paint__
- Cosito en JavaScript o simil, que le dibujas en una grilla seleccionando entre los colores posibles, y te lo traduce a una tablita de:
offset | color a pintar
- Funcion que lee la tablita, y a partir de un punto en particular, lo dibuja, pudiendo tomar algo que permite o no el Overflow (Termina arriba -> Sigue abajo)
- Tener una copia de la screen donde se guarde el background siempre.

NOTA1:    Usar macros o inline
NOTA1.1:  Inline no sirve, usar macros.
NOTA1.2:  Hacer una macro, la cual se utilizaria en los ciclos para pintar. Y una funcion con la macro adentro para exportarla.
NOTA2:    Para los colores usar un typdef, total son solo 8 posibles

Aridades de las funciones de arriba:
