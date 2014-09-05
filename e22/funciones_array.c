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
