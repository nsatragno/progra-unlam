#include <stdio.h>
#include "funciones_array.h"

#define SIZE 10
#define CANTIDAD_ELEMENTOS_AUTOMATICA 7
#define CARGAR_VALORES 1
#define ELIMINAR 2
#define VER_VECTOR 3
#define LEER_DEL_TECLADO 4
#define SALIR 5 

/*
 * Muestra un menú permitiéndole elegir al usuario modificar el array,
 * ejecutar la función, o salir.
 */
int mostrar_menu();

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
      case ELIMINAR:
        printf("Ingrese el elemento que desea eliminar.\n?: ");
        scanf("%d", &elemento);
        int posicion = posicion_de(array, cantidad_elementos, elemento);
        if (posicion == -1)
          printf("El elemento no se encuentra en el array.\n");

        int respuesta;
        // TODO Esta no es la forma óptima de eliminar múltiples, pero hoy no
        // tengo tiempo de modificar la función eliminar.
        while (posicion != -1) {
          printf("Eliminando elemento en posición: %d\n", posicion);
          respuesta = eliminar(array, SIZE, &cantidad_elementos, posicion + 1);
          if (respuesta == -1)
            printf("Ha ocurrido un error\n");
          posicion = posicion_de(array, cantidad_elementos, elemento);
        }
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


int mostrar_menu() {
  int decision;
  printf("Elija una opción\n");
  printf("Inicializar vector automáticamente: %d\n", CARGAR_VALORES);
  printf("Eliminar valor: %d\n", ELIMINAR);
  printf("Ver vector: %d\n", VER_VECTOR);
  printf("Leer array del teclado: %d\n", LEER_DEL_TECLADO);
  printf("Salir: %d\n", SALIR);
  printf("?: ");
  scanf("%d", &decision);
  return decision;
}
