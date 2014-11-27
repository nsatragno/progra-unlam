/*
Helper ej. 2, crea un archivo
Archivo:
+------+-------------------+
|Nombre| Cant eliminadas   |
+------+-------------------+
|Clave = N° Registro arch  |
+------+-------------------+
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NOMBRE_ARCHIVO "claves.bin"
#define TAM_NOMBRE 100

typedef struct {
    char nombre[TAM_NOMBRE];
    int cant_eliminadas;
} t_arch;

int main() {
    FILE *archivo = fopen(NOMBRE_ARCHIVO, "wb");
    const char nombres[10][TAM_NOMBRE] = { "Nicolas", "jUan", "RobErTo", "catalina", "eva", "@nsatragno", "peDro", "jorgelina", "Martina", "7up"};
    for (int i = 0; i < 100; i++) {
        t_arch t;
        t.cant_eliminadas = 0;
        strcpy(t.nombre, nombres[rand() % 10]);
        fwrite(&t, sizeof(t), 1, archivo);
    }
}
