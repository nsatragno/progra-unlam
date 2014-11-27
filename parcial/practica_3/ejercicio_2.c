/*
Dada una lista doblemente enlazada con claves repetidas y desordenada
+------+-------------------+
|Clave | Cant eliminadas   |
+------+-------------------+
Dado un ABB donde cada nodo tiene
+-----+
|Clave|
+-----+
Se pide al usuario ingresar una clave si existe en el ABB
Eliminar todas las hojas a partir de esa raíz y actalizar la lista dejando un único nodo por clave buscada actualizando la cantidad de eliminados.
Actualizar el archivo, invirtiendo cada nombre y normalizando poniendo la 1era en mayúscula y las demás en minúsculas.
Archivo:
+------+-------------------+
|Nombre| Cant eliminadas   |
+------+-------------------+
|Clave = N° Registro arch  |
+------+-------------------+
Indique dónde le conviene que esté el puntero de la lista.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOMBRE_ARCHIVO "claves.bin"
#define TAM_NOMBRE 100

typedef struct {
    char nombre[TAM_NOMBRE];
    int cant_eliminadas;
} t_arch;

typedef struct t_nodo_a {
    struct t_nodo_a *der;
    struct t_nodo_a *izq;
    int clave;
} t_nodo_a;

typedef struct {
    int cant_eliminadas;
    int clave;
} t_dato;

typedef struct t_nodo_l {
    struct t_nodo_l *sig;
    struct t_nodo_l *ant;
    t_dato dato;
} t_nodo_l;

typedef t_nodo_a * t_arbol;
typedef t_nodo_l * t_lista;

void crear_arbol(t_arbol *arbol);
void llenar_arbol(t_arbol *arbol);
void push_arbol(t_arbol *arbol, int clave);
void imprimir_arbol(t_arbol *arbol);
void imprimir_arbol_i(t_arbol *arbol, int iden);
int eliminar_hojas_subarbol_c(t_arbol *arbol, int clave);
void eliminar_hojas_arbol(t_arbol *arbol, int *eliminados);
t_arbol* buscar_nodo(t_arbol *arbol, int clave);
void llenar_arbol(t_arbol *arbol);

void crear_lista(t_lista *lista);
void push_lista(t_lista *lista, t_dato *dato);
void imprimir_lista(t_lista lista);

void abrir_archivo(FILE **archivo);
void actualizar_archivo(FILE *archivo, t_dato *dato);

void normalizar_cadena(char *c);

int main() {
    int d;
    t_arbol arbol;
    t_lista lista;
    FILE *archivo;

    crear_arbol(&arbol);
    crear_lista(&lista);
    abrir_archivo(&archivo);

    llenar_arbol(&arbol);
    printf("Arbol: \n");
    imprimir_arbol(&arbol);

    printf("Ingrese un elemento que eliminar. -1 Para terminar.\n?: ");
    scanf("%d", &d);
    while (d != -1) {
        int eliminados = eliminar_hojas_subarbol_c(&arbol, d);
        if (eliminados == 0) {
            printf("No se ha encontrado la clave.\n");
        } else {
            printf("Eliminados: %d\n", eliminados);
            t_dato dato;
            dato.clave = d;
            dato.cant_eliminadas = eliminados;
            push_lista(&lista, &dato);
            actualizar_archivo(archivo, &dato);
        }
        printf("Arbol: \n");
        imprimir_arbol(&arbol);
        printf("Lista: \n");
        imprimir_lista(lista);
        printf("\n");
        printf("Ingrese un elemento que eliminar. -1 Para terminar.\n?: ");
        scanf("%d", &d);
    }
    return 0;
}
void crear_arbol(t_arbol *arbol) {
    *arbol = NULL;
}

void llenar_arbol(t_arbol *arbol) {
    srand(time(NULL));
    for (int i = 0; i < 20; i++)
        push_arbol(arbol, rand() % 100);
}

void push_arbol(t_arbol *arbol, int clave) {
    if (*arbol) {
        if ((*arbol)->clave == clave)
            return;
        if ((*arbol)->clave > clave)
            push_arbol(&(*arbol)->izq, clave);
        else
            push_arbol(&(*arbol)->der, clave);
        return;
    }
    t_nodo_a *nodo = malloc(sizeof(nodo));
    if (!nodo) {
        printf("Sin memoria\n");
        exit(EXIT_FAILURE);
    }
    nodo->clave = clave;
    nodo->izq = NULL;
    nodo->der = NULL;
    *arbol = nodo;
}

void imprimir_arbol(t_arbol *arbol) {
    imprimir_arbol_i(arbol, 0);
}

void imprimir_arbol_i(t_arbol *arbol, int iden) {
    if (!*arbol)
        return;
    for (int i = 0; i < iden; i++)
        printf(" ");
    printf("%d\n", (*arbol)->clave);
    imprimir_arbol_i(&(*arbol)->izq, iden + 1);
    imprimir_arbol_i(&(*arbol)->der, iden + 1);
}

int eliminar_hojas_subarbol_c(t_arbol *arbol, int clave) {
    t_arbol *subarbol = buscar_nodo(arbol, clave);
    int eliminados = 0;
    eliminar_hojas_arbol(subarbol, &eliminados);
    return eliminados;
}

t_arbol* buscar_nodo(t_arbol *arbol, int clave) {
    if (!*arbol || (*arbol)->clave == clave)
        return arbol;
    if ((*arbol)->clave > clave)
        return buscar_nodo(&(*arbol)->izq, clave);
    return buscar_nodo(&(*arbol)->der, clave);
}

void eliminar_hojas_arbol(t_arbol *arbol, int *eliminados) {
    if (!*arbol)
        return;

    if ((*arbol)->izq || (*arbol)->der) {
        eliminar_hojas_arbol(&(*arbol)->izq, eliminados);
        eliminar_hojas_arbol(&(*arbol)->der, eliminados);
        return;
    }

    ++(*eliminados);
    free(*arbol);
    *arbol = NULL;
}

void crear_lista(t_lista *lista) {
    *lista = NULL;
}

void push_lista(t_lista *lista, t_dato *dato) {
    t_nodo_l *nodo;
    if (!*lista) {
        nodo = malloc(sizeof(nodo));
        *lista = nodo;
        nodo->ant = NULL;
        nodo->sig = NULL;
        nodo->dato.cant_eliminadas = dato->cant_eliminadas;
        nodo->dato.clave = dato->clave;
        return;
    }

    t_nodo_l *p = *lista;
    while (p->sig && p->dato.clave != dato->clave)
        p = p->sig;

    if (p->dato.clave == dato->clave) {
        p->dato.cant_eliminadas += dato->cant_eliminadas;
        return;
    }

    nodo = malloc(sizeof(nodo));
    p->sig = nodo;
    nodo->ant = p;
    nodo->sig = NULL;
    nodo->dato.cant_eliminadas = dato->cant_eliminadas;
    nodo->dato.clave = dato->clave;
}

void imprimir_lista(t_lista lista) {
    while (lista) {
        printf("%d %d\n", lista->dato.clave, lista->dato.cant_eliminadas);
        lista = lista->sig;
    }
}

void abrir_archivo(FILE **archivo) {
    *archivo = fopen(NOMBRE_ARCHIVO, "r+b");
    if (!*archivo) {
        printf("No se pudo abrir el archivo\n");
        exit(EXIT_FAILURE);
    }
}

void actualizar_archivo(FILE *archivo, t_dato *dato) {
    t_arch dato_arch;
    fseek(archivo, sizeof(dato_arch) * dato->clave, SEEK_SET);
    fread(&dato_arch, sizeof(dato_arch), 1, archivo);
    printf("Nombre producto: %s\n", dato_arch.nombre);
    printf("Eliminados: %d\n", dato_arch.cant_eliminadas);

    dato_arch.cant_eliminadas += dato->cant_eliminadas;
    normalizar_cadena(dato_arch.nombre);

    fseek(archivo, sizeof(dato_arch) * -1L, SEEK_CUR);
    fwrite(&dato_arch, sizeof(dato_arch), 1, archivo);
    printf("Despues del cambio, \n");
    printf("Nombre producto: %s\n", dato_arch.nombre);
    printf("Eliminados: %d\n", dato_arch.cant_eliminadas);
}

void normalizar_cadena(char *c) {
    if (!*c)
        return;

    // Inversión.
    char *izq, *der;
    izq = der = c;
    while (*der)
        der++;
    der--;
    while (izq < der) {
        char aux = *izq;
        *izq = *der;
        *der = aux;
        izq++;
        der--;
    }

    // Normalizado de mayúsculas y minúsculas.
    if (*c >= 'a' && *c <= 'z')
        *c -= 32;
    char *d = c + 1;
    while (*d) {
        if (*d >= 'A' && *d <= 'Z')
            *d += 32;
        d++;
    }
}
