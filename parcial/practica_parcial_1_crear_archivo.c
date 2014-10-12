/* Ayuda para el ejercicio de parcial */

/* Crea el archivo binario de empleados */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define SIZE_APELLIDO 30
#define SIZE_NOMBRE 25
#define NOMBRE_ARCHIVO_EMPLEADOS "empleados.bin"
#define FALSE 0
#define TRUE 1

typedef struct {
    char apellido[SIZE_APELLIDO];
    char nombre[SIZE_NOMBRE];
    int numero_expediente;
} t_empleado;

int main() {
    char *apellidos[7] = {"Alvarez", "Benito", "Carrio", "Davini", "Etchecopar", "Fernandez", "Gomez"};
    char *nombres[7] = {"Ada", "Bernardo", "Carlos", "Diogenes", "Ernesto", "Fernanda", "Gerardo"};
    srand(time(NULL));
    int empleados = rand() % 5 + 5;
    FILE *file = fopen(NOMBRE_ARCHIVO_EMPLEADOS, "wb");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }
    for (int i = 0; i <= empleados; i++) {
        t_empleado empleado;
        strcpy(empleado.apellido, apellidos[rand() % 7]);
        strcpy(empleado.nombre, nombres[rand() % 7]);
        empleado.numero_expediente = 0;
        printf("Escribiendo %s %s\n", empleado.nombre, empleado.apellido);
        fwrite(&empleado, sizeof(t_empleado), 1, file);
    }
    fclose(file);
    return EXIT_SUCCESS;
}
