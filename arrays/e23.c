#include <stdio.h>
#include "funciones_array.h"

#define SIZE 10
#define CANTIDAD_ELEMENTOS_AUTOMATICA 7
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
 * Inserta un |elemento| en |array| de |size|, manteniendo el orden ascendente.
 * Devuelve 0 si falló, 1 de lo contrario.
 */
int insertar_con_orden(int *array,
                       const int size, 
                       int *ultima_posicion, // Arranca de 0.
                       int elemento);


int main(void) {
  int array[SIZE];
  int elemento;
  int opcion;
  // La cantidad de elementos que voy a almacenar.
  // Es el tamaño menos el "Búfer".
  int cantidad_elementos = 0;
  do {
    opcion = mostrar_menu();
    switch (opcion) {
      case CARGAR_VALORES:
        // Decido inicializar el array con pares para hacer el testeo
        // más fácil.
        cantidad_elementos = CANTIDAD_ELEMENTOS_AUTOMATICA;
        inicializar_con_pares(array, cantidad_elementos);
        break;
      case INSERTAR:
        printf("Ingrese el elemento que tiene que insertar\n?: ");
        scanf("%d", &elemento);
        insertar_con_orden(array, SIZE, &cantidad_elementos, elemento);
        break;
      case VER_VECTOR:
        imprimir(array, cantidad_elementos);
        break;
      case LEER_DEL_TECLADO:
        printf("%s%s", "Si no inserta un array ordenado en forma ascendente, ",
                       "el comportamiento queda indefinido.\n");
        leer_del_teclado(array, &cantidad_elementos, SIZE);
        break;
      case SALIR:
        break;
      default:
        printf("La opción no es válida");
        break;
    }
  } while (opcion != SALIR);
}

int insertar_con_orden(int *array,
                       const int size, 
                       int* ultima_posicion, 
                       int elemento) {
  int posicion = 1;
  int *puntero = array;
  // Nos paramos en el elemento que hay que remplazar.
  while (*puntero < elemento && 
         posicion < size && 
         posicion < *ultima_posicion + 1) {
    puntero++;
    posicion++;
  }
  if (posicion >= size) {
    printf("No hay espacio para el valor\n");
    return 0;
  }

  return insertar(array, size, ultima_posicion, posicion, elemento);
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
