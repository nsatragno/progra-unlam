/* Ejercicio de parcial */

/* Dado un archivo de empleados, donde cada registro del archivo contiene: Apellido (30 caracteres), Nombre (25 caracteres), expediente (número entero).
Dada una pila de expedientes, donde cada elemento de la pila contiene: Número de expediente (valor entero positivo) y un estado del expediente (‘C’ Cerrado, ‘A’ Abierto).
Se pide hacer un proceso que asigne, al azar, los expedientes abiertos a los empleados, actualizando el archivo de “empleados”.
Al inicio del proceso, el campo “expediente” de todos los empleados tiene el valor 0 (cero).
Al asignar los expedientes al azar, si se debiese asignar un expediente a un empleado que ya tenga un expediente asignado, el mismo se asignará al primer empleado siguiente (tomando el archivo en forma circular: luego del último se encuentra el primero) sin expediente asignado.
También se debe crear un archivo de texto “cerrado.txt", de forma que este archivo contenga un  registro por cada expediente cerrado que se procese. */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>

#define SIZE_APELLIDO 30
#define SIZE_NOMBRE 25
#define ESTADO_CERRADO 'c'
#define ESTADO_ABIERTO 'a'
#define NOMBRE_ARCHIVO_EMPLEADOS "empleados.bin"
#define NOMBRE_ARCHIVO_CERRADOS "cerrado.txt"
#define FALSE 0
#define TRUE 1

typedef struct {
    char apellido[SIZE_APELLIDO];
    char nombre[SIZE_NOMBRE];
    int numero_expediente;
} t_empleado;

typedef struct {
    int numero;
    char estado;
} t_expediente;

typedef struct t_nodo {
    t_expediente dato;
    struct t_nodo *sig;
} t_nodo;

typedef t_nodo *t_pila;

void crear_pila(t_pila *pila);
void cargar_pila(t_pila *pila);
int push(t_pila* pila, const t_expediente* dato);
void pop(t_pila *pila, t_expediente *expediente);
int pila_vacia(t_pila* pila);

void abrir_archivo(FILE **file, const char * nombre, const char * modo);
int cantidad_registros_file(FILE *file, size_t size);

void leer_empleado(FILE *file, const size_t indice, t_empleado *empleado);
void escribir_empleado(FILE *file, const size_t indice, const t_empleado *empleado);

int main() {
    t_pila pila;
    FILE *f_empleado, *f_cerrado;
    int cantidad_registros, registros_escritos = 0;

    srand(time(NULL));

    abrir_archivo(&f_empleado, NOMBRE_ARCHIVO_EMPLEADOS, "r+b");
    abrir_archivo(&f_cerrado, NOMBRE_ARCHIVO_CERRADOS, "wt");

    crear_pila(&pila);
    cargar_pila(&pila);

    cantidad_registros = cantidad_registros_file(f_empleado, sizeof(t_empleado));
    printf("Cantidad de empleados: %d\n", cantidad_registros);

    while (!pila_vacia(&pila)) {
        t_expediente expediente;
        pop(&pila, &expediente);
        printf("Expediente %d: ", expediente.numero);
        if (tolower(expediente.estado) == ESTADO_CERRADO) {
            printf("cerrado.\n");
            fprintf(f_cerrado, "%d\n", expediente.numero);
        } else if (tolower(expediente.estado) == ESTADO_ABIERTO) {
            printf("abierto.\n");
            if (cantidad_registros > registros_escritos) {
                t_empleado empleado;
                size_t indice = rand() % cantidad_registros;
                leer_empleado(f_empleado, indice, &empleado);
                while (empleado.numero_expediente != 0) {
                    indice++;
                    if (indice == cantidad_registros)
                        indice = 0;
                    leer_empleado(f_empleado, indice, &empleado);
                }
                empleado.numero_expediente = expediente.numero;
                printf("Asigando a %s %s.\n", empleado.nombre, empleado.apellido);
                escribir_empleado(f_empleado, indice, &empleado);
                registros_escritos++;
            } else {
                printf("Queda pendiente por falta de empleados.\n");
            }
        } else {
            printf("desconocido - no se efectúa acción.\n");
        }

    }

    fclose(f_cerrado);
    fclose(f_empleado);

    return EXIT_SUCCESS;
}

void crear_pila(t_pila *pila) {
    *pila = NULL;
}

void abrir_archivo(FILE **file, const char *nombre, const char *modo) {
    if ((*file = fopen(nombre, modo)) == NULL) {
        printf("No se pudo abir el archivo %s\n", nombre);
        exit(EXIT_FAILURE);
    }
}

int push(t_pila* pila, const t_expediente* dato) {
    t_nodo *nodo = malloc(sizeof(t_nodo));
    if (nodo == NULL)
        return FALSE;
    nodo->dato = *dato;
    nodo->sig = *pila;
    *pila = nodo;
    return TRUE;
}

int pila_vacia(t_pila *pila) {
    return *pila == NULL;
}

void pop(t_pila *pila, t_expediente *expediente) {
    *expediente = (*pila)->dato;
    t_nodo* sig = (*pila)->sig;
    free(*pila);
    *pila = sig;
}

void cargar_pila(t_pila *pila) {
    t_expediente expediente;
    printf("Ingrese los números de expedientes seguidos del estado.\nIngrese número de expediente 0 para finalizar.\n");
    while (1) {
        printf("?: ");
        scanf("%d", &expediente.numero);
        if (expediente.numero == 0)
            break;
        scanf("\n%c", &expediente.estado);
        fflush(stdin);
        if (!push(pila, &expediente)) {
            printf("No hay suficiente memoria para almacenar el expediente.\n");
            break;
        }
    }
}

int cantidad_registros_file(FILE *file, size_t size) {
    fseek(file, 0, SEEK_END);
    return ftell(file) / size;
}

void leer_empleado(FILE *file, const size_t indice, t_empleado *empleado) {
    fseek(file, indice * sizeof(t_empleado), SEEK_SET);
    fread(empleado, sizeof(t_empleado), 1, file);
}

void escribir_empleado(FILE *file, const size_t indice, const t_empleado *empleado) {
    fseek(file, indice * sizeof(t_empleado), SEEK_SET);
    fwrite(empleado, sizeof(t_empleado), 1, file);
}
