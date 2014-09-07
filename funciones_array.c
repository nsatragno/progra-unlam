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

void leer_del_teclado(int *array, int *cantidad_elementos, const int size) {
  int i;
  printf("Inserte %d números\n?: ", size);
  for (i = 0; i < size; i++, array++)
    scanf("%d", array);
  *cantidad_elementos = i;
}

int insertar(int *array,
             const int size, 
             int *ultima_posicion, 
             int posicion, 
             int elemento) {
  if (posicion > size || posicion < 0 || posicion > *ultima_posicion + 1) {
    printf("ERROR: Se intentó insertar en una posición no válida\n");
    return 0;
  }

  // Nos paramos en el elemento que hay que remplazar.
  array += posicion - 1;
  int izquierda = elemento;
  int derecha;
  for (int c = posicion; c <= *ultima_posicion + 1 && c <= size; c++, array++) {
    derecha = *array;
    *array = izquierda;
    izquierda = derecha;
  }
  // Si inserté un elemento nuevo y no perdí ninguno, aumento la última 
  // posición utilizada del vector.
  if (*ultima_posicion < size)
    (*ultima_posicion)++;
  return 1;
}

int posicion_de(int *array, const int size, int elemento) {
  for (int i = 0; i < size; i++, array++) {
    if (*array == elemento)
      return i;
  }
  // Si llegamos hasta acá es porque el elemento no estaba en el array.
  return -1;
}
