/*
Para todos los nodos de una altura dada, actualizar el archvo de stock.

Archivo de stock:
+----------------+------+
|Nombre producto | Stock|
+----------------+------+

Nodo árbol
+------------+-------------+
|N° Registro | Cant vendida|
+------------+-------------+

Indicar cuántos registros se actualizaron
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOMBRE_ARCHIVO "stock.bin"
#define SIN_MEMORIA 0
#define TODO_OK 1

typedef struct {
    int num_reg;
    int cant;
} t_dato;

typedef struct t_nodo {
    t_dato dato;
    struct t_nodo *izq;
    struct t_nodo *der;
} t_nodo;

typedef struct {
    char nombre_producto[20];
    int stock;
} t_archivo;

typedef t_nodo* t_arbol;

void crear_arbol(t_arbol *arbol);
int push(t_arbol *arbol, t_dato *dato);
void abrir_archivo(FILE **archivo);
void llenar_arbol(t_arbol *arbol);
void actualizar_registro(FILE *archivo, t_dato *dato);
void actualizar_por_altura(FILE *archivo, t_arbol *arbol, int altura, int *contador);
int comparar(t_dato *izq, t_dato *der);
void imprimir(t_dato *dato);

int main() {
    FILE *archivo;
    t_arbol arbol;
    int altura;
    int contador = 0;
    crear_arbol(&arbol);
    llenar_arbol(&arbol);
    abrir_archivo(&archivo);
    printf("Ingrese la altura del árbol\n?: ");
    scanf("%d", &altura);
    actualizar_por_altura(archivo, &arbol, altura, &contador);
    printf("Se actualizaron %d elementos.\n", contador);
    return 0;
}

void crear_arbol(t_arbol *arbol) {
    *arbol = NULL;
}

void llenar_arbol(t_arbol *arbol) {
    srand(time(NULL));
    for (int i = 0; i < 100; i++) {
        t_dato dato;
        dato.num_reg = rand() % 10;
        dato.cant = i * 10;
        push(arbol, &dato);
    }
}

int push(t_arbol *arbol, t_dato *dato) {
    if (*arbol) {
        return push(
            comparar(&(*arbol)->dato, dato) > 0 ?
                &(*arbol)->izq :
                &(*arbol)->der,
            dato);
        }
    *arbol = malloc(sizeof(t_nodo));
    if (!*arbol)
        return SIN_MEMORIA;
    (*arbol)->dato = *dato;
    return TODO_OK;
}

int comparar(t_dato *izq, t_dato *der) {
    return izq->num_reg - der->num_reg;
}

void abrir_archivo(FILE **archivo) {
    *archivo = fopen(NOMBRE_ARCHIVO, "rb+");
    if (!*archivo)
        printf("El archivo %s no se pudo abrir\n", NOMBRE_ARCHIVO);
}

void actualizar_por_altura(FILE *archivo, t_arbol *arbol, int altura, int *contador) {
    if (!*arbol)
        return;
    if (altura <= 1) {
        *contador++;
        printf("Actualizando:\n");
        imprimir(&(*arbol)->dato);
        actualizar_registro(archivo, &(*arbol)->dato);
        return;
    }
    actualizar_por_altura(archivo, &(*arbol)->izq, altura - 1, contador);
    actualizar_por_altura(archivo, &(*arbol)->der, altura - 1, contador);
}

void imprimir(t_dato *dato) {
    printf("N# Reg: %d, cantidad: %d\n", dato->num_reg, dato->cant);
}

void actualizar_registro(FILE *archivo, t_dato *dato) {
    t_archivo dato_a;
    fseek(archivo, sizeof(t_archivo) * dato->num_reg, SEEK_SET);
    fread(&dato_a, sizeof(t_archivo), archivo):
    t_archivo.stock -= dato->cant;
    fseek(archivo, sizeof(t_archivo) * -1, SEEK_CUR);
    fwrite(&dato_a, sizeof(t_archivo), archivo);
}
