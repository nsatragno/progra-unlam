#include <stdio.h>
#include "funciones_array.h"

#define COLUMNAS 10
#define FILAS 10
#define VECINOS 8

void inicializar(int matriz[COLUMNAS][FILAS], const int columnas, const int filas);

void obtener_vecinos(int matriz[COLUMNAS][FILAS],
                     const int posicion_col,
                     const int posicion_fil,
                     const int columnas,
                     const int filas,
                     int vecinos[VECINOS],
                     int *cantidad_vecinos);

void imprimir_matriz(int matriz[COLUMNAS][FILAS], const int columnas, const int filas);

int main() {
  int columnas, filas;
  printf("Ingrese la cantidad de columnas\n?: ");
  scanf("%d", &columnas);
  printf("Ingrese la cantidad de filas\n?: ");
  scanf("%d", &filas);

  if (filas > FILAS || columnas > COLUMNAS) {
    printf("No entran esos valores :(\n");
    return -1;  
  }
    
  
  int matriz[COLUMNAS][FILAS];
  inicializar(matriz, columnas, filas);

  printf("Matriz: \n");
  imprimir_matriz(matriz, columnas, filas);

  int posicion_col, posicion_fil;
  printf("Ingrese la columna de la que quiere obtener los vecinos.\n");
  scanf("%d", &posicion_col);

  printf("Ingrese la fila de la que quiere obtener los vecinos.\n");
  scanf("%d", &posicion_fil);

  int vecinos[VECINOS];
  int cantidad_vecinos;
  obtener_vecinos(matriz, --posicion_col, --posicion_fil, columnas, filas, vecinos, &cantidad_vecinos);

  if (cantidad_vecinos == 0) {
    printf("No hay vecinos\n");
  } else {
    printf("Vecinos:\n");
    imprimir(vecinos, cantidad_vecinos);
  }
  return 0;
}

void inicializar(int matriz[COLUMNAS][FILAS], const int columnas, const int filas) {
  int c = 1;
  for (int i = 0; i < columnas; i++)
    for (int j = 0; j < filas; j++)
      matriz[i][j] = c++;
}

void imprimir_matriz(int matriz[COLUMNAS][FILAS], const int columnas, const int filas) {
  for (int j = 0; j < filas; j++) {
    for (int i = 0; i < columnas; i++) {
      printf("%2d ", matriz[i][j]);
    }
    printf("\n");
  }
}

void obtener_vecinos(int matriz[COLUMNAS][FILAS],
                     const int posicion_col,
                     const int posicion_fil,
                     const int columnas,
                     const int filas,
                     int vecinos[VECINOS],
                     int *cantidad_vecinos) {
  *cantidad_vecinos = 0;
  if (posicion_col > columnas || posicion_fil > filas)
    return;

  int limite_col_inferior = posicion_col == 0 ? 0 : posicion_col - 1;
  int limite_col_superior = posicion_col >= columnas - 1 ? columnas - 1 : posicion_col + 1;
  int limite_fil_inferior = posicion_fil == 0 ? 0 : posicion_fil - 1;
  int limite_fil_superior = posicion_fil >= filas - 1 ? filas - 1 : posicion_fil + 1;
  for (int i = limite_col_inferior; i <= limite_col_superior; i++) {
    for (int j = limite_fil_inferior; j <= limite_fil_superior; j++) {
        if (i == posicion_col && j == posicion_fil)
          continue;
        vecinos[(*cantidad_vecinos)++] = matriz[i][j];
      }
    }
}
