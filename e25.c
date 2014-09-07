#include <stdio.h>
#include "funciones_array.h"

#define SIZE 10
#define CANTIDAD_ELEMENTOS_AUTOMATICA 7
#define CARGAR_VALORES 1
#define BUSCAR 2
#define VER_VECTOR 3
#define LEER_DEL_TECLADO 4
#define SALIR 5 

/*
 * Muestra un menú permitiéndole elegir al usuario modificar el array,
 * ejecutar la función, o salir.
 */
int mostrar_menu();

/*
 * Elimina el elemento de un |array| según su |posición|, que arranca en 1.
 * Devuelve 0 si falló, 1 de lo contrario.
 */
int eliminar(int *array,
             const int size, 
             int *ultima_posicion, // Arranca de 0.
             const int posicion);


int main(void) {
  int array[SIZE];
  int elemento;
  int opcion;
  int posicion;
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
      case BUSCAR:
        printf("Ingrese el elemento que desea buscar.\n?: ");
        scanf("%d", &elemento);
        int posicion = posicion_de(array, cantidad_elementos, elemento);
        if (posicion == -1)
          printf("El elemento no se encuentra en el array.\n");
        else
          printf("El elemento está en la posición %d.\n", posicion + 1);
        break;
      case VER_VECTOR:
        imprimir(array, cantidad_elementos);
        break;
      case LEER_DEL_TECLADO:
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

  int izquierda;
  int derecha = *array;
  
  for (int c = posicion; c <= *ultima_posicion + 1 && c <= size; c++, array++) {
    izquierda = *(array - 1);
    *(array - 1) = derecha;
    derecha = izquierda;
  }
  (*ultima_posicion)--;
  return 1;
}

int mostrar_menu() {
  int decision;
  printf("Elija una opción\n");
  printf("Inicializar vector automáticamente: %d\n", CARGAR_VALORES);
  printf("Buscar valor: %d\n", BUSCAR);
  printf("Ver vector: %d\n", VER_VECTOR);
  printf("Leer array del teclado: %d\n", LEER_DEL_TECLADO);
  printf("Salir: %d\n", SALIR);
  printf("?: ");
  scanf("%d", &decision);
  return decision;
}
