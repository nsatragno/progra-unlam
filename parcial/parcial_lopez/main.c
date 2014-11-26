#include <stdio.h>
#include <stdlib.h>

#define SIZE_SEMILLA 15
#define NOMBRE_ARCHIVO "parcelas.dat"

#define TRUE 1
#define FALSE 0

typedef struct {
    int numero;
    char semilla[SIZE_SEMILLA];
} t_sembrada;

typedef struct {
    int numero;
    float cantidad;
    double monto;
} t_cosechada;

typedef struct {
    int numero;
    double monto;
} t_guardada;

typedef struct t_nodol {
    t_sembrada dato;
    struct t_nodol *sig;
} t_nodol;

typedef t_nodol* t_lista;

void crear_lista(t_lista *lista);
int rem_lista(int id, t_lista* lista);
void push_lista(t_lista *lista, t_nodol *dato);

typedef struct t_nodoc {
    t_cosechada dato;
    struct t_nodoc *sig;
} t_nodoc;

typedef struct {
    t_nodoc *primero;
    t_nodoc *ultimo;
} t_cola;

void crear_cola(t_cola *cola);
int cola_vacia(t_cola *cola);
t_nodoc* pop_cola(t_cola *cola);
void push_cola(t_cola *cola, t_nodoc *dato);

FILE* abrir_archivo(void);
void actualizar_archivo(FILE *archivo, const t_cosechada *dato);

void llenar_cola_cosechadas(t_cola *cola_cosechadas);
void llenar_lista_sembradas(t_lista *lista_sembradas);

int main()
{
    t_cola cola_cosechadas;
    t_cola cola_error;
    t_lista lista_sembradas;
    t_nodoc *nodoc;

    crear_cola(&cola_cosechadas);
    crear_cola(&cola_error);
    crear_lista(&lista_sembradas);

    FILE *archivo = abrir_archivo();

    llenar_cola_cosechadas(&cola_cosechadas);
    llenar_lista_sembradas(&lista_sembradas);

    while (!cola_vacia(&cola_cosechadas)) {
        nodoc = pop_cola(&cola_cosechadas);
        if (rem_lista(nodoc->dato.numero, &lista_sembradas)) {
            printf("Actualizado archivo para parcela %d (%f)\n", nodoc->dato.numero, nodoc->dato.monto);
            actualizar_archivo(archivo, &nodoc->dato);
            printf("Actualizado!\n");
            free(nodoc);
        } else {
            printf("Error, la parcela no se encuentra en el listado de sembradas\n");
            push_cola(&cola_error, nodoc);
        }
    }
    fclose(archivo);
}

void crear_lista(t_lista *lista) {
    *lista = NULL;
}

int rem_lista(int id, t_lista* lista) {
    t_nodol *aux;
    if (!*lista)
        return FALSE;

    if ((*lista)->dato.numero == id) {
        aux = *lista;
        *lista = aux->sig;
        free(aux);
        return TRUE;
    }

    while ((*lista)->sig != NULL && (*lista)->sig->dato.numero != id)
        lista = &(*lista)->sig;

    if (!(*lista)->sig)
        return FALSE;

    aux = (*lista)->sig;
    (*lista)->sig = aux->sig;
    free(aux);
    return TRUE;
}

void push_lista(t_lista *lista, t_nodol *dato) {
    dato->sig = *lista;
    *lista = dato;
}

void crear_cola(t_cola *cola) {
    cola->primero = NULL;
    cola->ultimo = NULL;
}

int cola_vacia(t_cola *cola) {
    return cola->primero == NULL;
}

void push_cola(t_cola *cola, t_nodoc *dato) {
    if (cola_vacia(cola))
        cola->primero = dato;
    else
        cola->ultimo->sig = dato;
    dato->sig = NULL;
    cola->ultimo = dato;
}

t_nodoc* pop_cola(t_cola *cola) {
    t_nodoc *nodoc;
    nodoc = cola->primero;
    cola->primero = nodoc->sig;
    return nodoc;
}


FILE* abrir_archivo() {
    FILE *archivo = fopen(NOMBRE_ARCHIVO, "r+b");
    if (archivo == NULL) {
        printf("No se puede abrir el archivo %s\n", NOMBRE_ARCHIVO);
        exit(EXIT_FAILURE);
    }
    return archivo;
}

void actualizar_archivo(FILE *archivo, const t_cosechada *dato) {
    t_guardada guardada;
    rewind(archivo);
    fread(&guardada, sizeof(t_guardada), 1, archivo);
    while (!feof(archivo)) {
        if (guardada.numero == dato->numero) {
            fseek(archivo, (long)-sizeof(t_guardada), SEEK_CUR);
            guardada.monto += dato->monto;
            printf("El nuevo monto es %f\n", guardada.monto);
            fwrite(&guardada, sizeof(t_guardada), 1, archivo);
            return;
        }
        fread(&guardada, sizeof(t_guardada), 1, archivo);
    }
    printf("Creando entrada con un monto de %f\n", dato.monto);
    fwrite(dato, sizeof(t_guardada), 1, archivo);
}
void llenar_cola_cosechadas(t_cola *cola_cosechadas) {
    t_cosechada dato;
    t_nodoc *nodo;
    printf("Ingrese num, cant y monto de la cosecha. -1 para terminar.\n?: ");
    scanf("%d", &dato.numero);
    while (dato.numero != -1) {
        scanf("%f %lf", &dato.cantidad, &dato.monto);
        nodo = malloc(sizeof(t_nodoc));
        if (!nodo) {
            printf("No hay suficiente memoria en el sistema para continuar.\n");
        } else {
            nodo->dato = dato;
            push_cola(cola_cosechadas, nodo);
        }
        printf("?: ");
        scanf("%d", &dato.numero);
    }
}

void llenar_lista_sembradas(t_lista *lista_sembradas) {
    t_sembrada dato;
    t_nodol *nodo;
    printf("Ingrese num, y nombre de semilla de sembrada. -1 para terminar.\n?: ");
    scanf("%d\n", &dato.numero);
    while (dato.numero != -1) {
        scanf("%s", dato.semilla);
        nodo = malloc(sizeof(t_nodol));
        if (!nodo) {
            printf("No hay suficiente memoria en el sistema para continuar.\n");
        } else {
            nodo->dato = dato;
            push_lista(lista_sembradas, nodo);
        }
        printf("?: ");
        scanf("%d", &dato.numero);
    }
}
