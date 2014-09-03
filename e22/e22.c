#include<stdio.h>

#define SIZE 10

/*
 * Inserta un |elemento| en |array| de |size|, en la |posicion| determinada.
 * Devuelve 0 si falló, 1 de lo contrario.
 */
int insertar(int *array,
              const int size, 
              const int ultima_posicion, // Arranca de 0.
              int posicion, // Arranca de 1.
              int elemento);

/*
 * Inicializa un array con pares de 0 a (size - 1) * 2
 */
void inicializar_con_pares(int *array, const int size);

/*
 * Imprime un |array| en pantalla.
 */
void imprimir(int *array, const int size);

int main(void) {
  int array[SIZE];
  int posicion;
  int elemento;

  // Decido inicializar el array con pares para hacer el testeo
  // más fácil.
  inicializar_con_pares(array, SIZE);
  printf("Array original:\n");
  imprimir(array, SIZE);

  printf("Ingrese la posición para el elemento\n?: ");
  scanf("%d", &posicion);
  printf("Ingrese el elemento que tiene que insertar\n?: ");
  scanf("%d", &elemento);

  insertar(array, SIZE, SIZE, posicion, elemento);
  imprimir(array, SIZE);
}

int insertar(int *array,
             const int size, 
             const int ultima_posicion, 
             int posicion, 
             int elemento) {
  if (posicion > size) {
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

void inicializar_con_pares(int *array, const int size) {
  for (int i = 0; i < size; i++, array++)
    *array = 2 * i; 
}

void imprimir(int *array, const int size) {
  for (int i = 0; i < size; i++, array++)
    printf("%d ", *array);  
  printf("\n");
}
