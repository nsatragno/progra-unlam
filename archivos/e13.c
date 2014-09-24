#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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

  FILE *pe = fopen(nombre_empleados, "r+");
  FILE *pa = fopen(nombre_alumnos, "r");

  if (!pa || !pe) {
    printf("Alguno de los archivos no se pudo abrir, verifique su existencia.\n");
    exit(EXIT_FAILURE);
  }

  alumno_t alumno;
  empleado_t empleado;

  fread(&empleado, sizeof(empleado_t), 1, pe);
  fread(&alumno, sizeof(alumno_t), 1, pa);
  while (!feof(pe) && !feof(pa)) {
    printf("Empleado: \n");
    imprimir(&empleado.datos);
    int comp;
    printf("Alumno: \n");
    imprimir(&alumno.datos);
    while ((comp = comparar(&alumno.datos, &empleado.datos)) < 0 && !feof(pa)) {
      fread(&alumno, sizeof(alumno_t), 1, pa);
      printf("Alumno: \n");
      imprimir(&alumno.datos);
    }
    if (!feof(pa) && comp == 0) {
      printf("Coinciden :D\n\n");
      if (alumno.promedio >= 7) {
        empleado.sueldo *= 1.17;
        fseek(pe, - sizeof(empleado_t), SEEK_CUR);
        fwrite(&empleado, sizeof(empleado), 1, pe);
      }
      fread(&alumno, sizeof(alumno_t), 1, pa);
    }
    if (!feof(pe)) {
      fread(&empleado, sizeof(empleado), 1, pe);
    }
  }
  fclose(pa);
  fclose(pe);

  return 0;
}

int comparar(datos_personales_t *a, datos_personales_t *b) {
  int comp = strcmp(a->apellido, b->apellido);
  if (comp == 0)
    comp = strcmp(a->nombre, b->nombre);
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
