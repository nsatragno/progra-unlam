#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define TAM 100

typedef struct {
  long dni;
  char apellido[TAM];
  char nombre[TAM];
} datos_personales_t;

int comparar(datos_personales_t *a, datos_personales_t *b);

typedef struct {
  datos_personales_t datos;
  double sueldo;
} empleado_t;

typedef struct {
  datos_personales_t datos;
  float promedio;
} alumno_t;

void imprimir(datos_personales_t *t);

int main () {
  const char nombre_empleados[] = "empleados.bin";
  const char nombre_alumnos[]   = "alumnos.bin";

  const char alumnos[][100] = {"Ana",
                               "Benito",
                               "Carlos",
                               "Diogenes",
                               "Elizabeth",
                               "Franco",
                               "Galileo",
                               "Hernan",
                               "Ignacio",
                               "Julia",
                               "Kant",
                               "Laura",
                               "Maria",
                               "Nicolas",
                               "Orense",
                               "Pedro"}; // 16.

  const char empleados[][100] = {"Ada",
                                 "Bernardino",
                                 "Carlos",
                                 "Diogenes",
                                 "Elizabeth",
                                 "Felicitas",
                                 "Galileo",
                                 "Hernan",
                                 "Ignacio",
                                 "Julia",
                                 "Kant",
                                 "Laura",
                                 "Maria",
                                 "Nicolas",
                                 "Oscar",
                                 "Pedro"}; // 16.

  FILE *pe = fopen(nombre_empleados, "w");
  FILE *pa = fopen(nombre_alumnos, "w");

  if (!pa || !pe) {
    printf("Alguno de los archivos no se pudo abrir, verifique su existencia.\n");
    exit(EXIT_FAILURE);
  }

  srand(time(NULL));

  alumno_t alumno;
  empleado_t empleado;

  //int cantidad = rand() % 100 + 50;
  int cantidad = 16;
  for (int i = 0; i < cantidad; i++) {
    strcpy(alumno.datos.nombre, alumnos[i]);
    strcpy(alumno.datos.apellido, alumnos[i]);
    alumno.datos.dni = i;
    alumno.promedio = rand() % 11;
    fwrite(&alumno, sizeof(alumno_t), 1, pa);
    imprimir(&alumno.datos);
  }
  for (int i = 0; i < cantidad; i++) {
    strcpy(empleado.datos.nombre, empleados[i]);
    strcpy(empleado.datos.apellido, empleados[i]);
    empleado.datos.dni = i;
    empleado.sueldo = 2000 + rand() % 1000;
    fwrite(&empleado, sizeof(empleado_t), 1, pe);
    imprimir(&empleado.datos);
  }

  fclose(pa);
  fclose(pe);
  return 0;
}

int comparar(datos_personales_t *a, datos_personales_t *b) {
  int comp = strcasecmp(a->apellido, b->apellido);
  if (comp == 0)
    comp = strcasecmp(a->nombre, b->nombre);
  if (comp == 0) {
    if (a->dni < b->dni)
      comp = -1;
    if (a->dni > b->dni)
      comp = 1;
  }
  return comp;
}

void imprimir(datos_personales_t *t) {
  printf("Nombre: %s\nApellido: %s\nDNI: %ld\n\n", t->nombre, t->apellido, t->dni);
}
