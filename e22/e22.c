#include <stdio.h>
#include "funciones_array.h"

#define SIZE 10
#define CARGAR_VALORES 1
#define INSERTAR 2
#define VER_VECTOR 3
#define LEER_DEL_TECLADO 4
#define SALIR 5 

/*
 * Muestra un menú permitiéndole elegir al usuario modificar el array,
 * ejecutar la función, o salir.
 */
int mostrar_menu();

/*
 * Inserta un |elemento| en |array| de |size|, en la |posicion| determinada.
 * Devuelve 0 si falló, 1 de lo contrario.
 */
int insertar(int *array,
              const int size, 
              const int ultima_posicion, // Arranca de 0.
              int posicion, // Arranca de 1.
              int elemento);


int main(void) {
  int array[SIZE];
  int posicion;
  int elemento;
  int opcion;
  do {
    opcion = mostrar_menu();
    switch (opcion) {
      case CARGAR_VALORES:
        // Decido inicializar el array con pares para hacer el testeo
        // más fácil.
        inicializar_con_pares(array, SIZE);
        break;
      case INSERTAR:
        printf("Ingrese la posición para el elemento\n?: ");
        scanf("%d", &posicion);
        printf("Ingrese el elemento que tiene que insertar\n?: ");
        scanf("%d", &elemento);
        insertar(array, SIZE, SIZE, posicion, elemento);
        break;
      case VER_VECTOR:
        imprimir(array, SIZE);
        break;
      case LEER_DEL_TECLADO:
        leer_del_teclado(array, SIZE);
        break;
      case SALIR:
        break;
      default:
        printf("La opción no es válida");
        break;
    }
  } while (opcion != SALIR);
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

int mostrar_menu() {
  int decision;
  printf("Elija una opción\n");
  printf("Inicializar vector automáticamente: %d\n", CARGAR_VALORES);
  printf("Insertar valor: %d\n", INSERTAR);
  printf("Ver vector: %d\n", VER_VECTOR);
  printf("Leer array del teclado: %d\n", LEER_DEL_TECLADO);
  printf("Salir: %d\n", SALIR);
  printf("?: ");
  scanf("%d", &decision);
  return decision;
}
