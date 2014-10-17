/* Ayuda para el ejercicio de parcial */

/* Crea el archivo binario de productos */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE_NOMBRE 100
#define NOMBRE_ARCHIVO "productos.bin"
#define FALSE 0
#define TRUE 1

typedef struct {
    char nombre[SIZE_NOMBRE];
    int cantidad;
} t_producto;

int main() {
    srand(time(NULL));
    int productos = 100;
    int cantidad = 10;
    char nombres[4][SIZE_NOMBRE] = {
        "zXcZxX0503 alpha",
        "cccxxX0106  bravo",
        "CvvxxX0586 CHarlie",
        "aaabbb0102 delta"};
    FILE *file = fopen(NOMBRE_ARCHIVO, "wb");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }
    for (int i = 0; i < productos; i++) {
        t_producto producto;
        strcpy(producto.nombre, nombres[rand() % 4]);
        producto.cantidad = cantidad;
        printf("Escribiendo %s %d\n", producto.nombre, producto.cantidad);
        fwrite(&producto, sizeof(t_producto), 1, file);
    }
    fclose(file);
    return EXIT_SUCCESS;
}
