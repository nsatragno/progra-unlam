#include <stdio.h>

void inicializar_con_pares(int *array, const int size) {
  for (int i = 0; i < size; i++, array++)
    *array = 2 * i; 
}

void imprimir(int *array, const int size) {
  for (int i = 0; i < size; i++, array++)
    printf("%d ", *array);  
  printf("\n");
}

void leer_del_teclado(int *array, const int size) {
  printf("Inserte %d números\n?: ", size);
  for (int i = 0; i < size; i++, array++)
    scanf("%d", array);
}

int insertar(int *array,
             const int size, 
             const int ultima_posicion, 
             int posicion, 
             int elemento) {
  if (posicion > size || posicion < 0) {
    printf("ERROR: Se intentó insertar en una posición no válida\n");
    return 0;
  }

  // Nos paramos en el elemento que hay que remplazar.
  array += posicion - 1;
  int izquierda = elemento;
  int derecha;
  for (int c = posicion; c <= ultima_posicion && c <= size; c++, array++) {
    derecha = *array;
    *array = izquierda;
    izquierda = derecha;
  }
  return 1;
}
