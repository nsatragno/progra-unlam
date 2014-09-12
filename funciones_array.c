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
  // Entre otras cosas, no se permite insertar en el área "en blanco" entre 
  // size y ultima_posicion a menos que sea inmediatamente a la derecha de
  // ultima_posicion.
  if (posicion > size || posicion < 0 || posicion > *ultima_posicion + 1) {
    printf("ERROR: Se intentó insertar en una posición no válida\n");
    return 0;
  }

  // Guardo la posición en la que se insertará el elemento.
  int *posicion_insercion = array + posicion - 1;

  // Sitúo el puntero del array justo antes de la última posición que se puede
  // escribir.
  int no_perdi_un_valor = (*ultima_posicion < size) ? 1 : 0;
  array += *ultima_posicion + no_perdi_un_valor;

  // Corro todos los elementos "a la derecha".
  for (; array != posicion_insercion - 1; array--)
    *(array + 1) = *array;

  // Agrego el elemento.
  *posicion_insercion = elemento;

  // Si inserté un elemento nuevo y no perdí ninguno, aumento la última 
  // posición utilizada del vector.
  if (no_perdi_un_valor)
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

int eliminar(int *array,
             const int size, 
             int* ultima_posicion, 
             const int posicion) {
  if (posicion > size || posicion < 0 || posicion > *ultima_posicion + 1) {
    printf("ERROR: Se intentó eliminar una posición no válida\n");
    return 0;
  }
  // Nos paramos en el elemento que hay que eliminar.
  array += posicion - 1;

  for (int c = posicion; c <= *ultima_posicion + 1 && c <= size; c++, array++)
    *array = *(array + 1);

  (*ultima_posicion)--;
  return 1;
}
