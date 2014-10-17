/*
Ejercicio tipo parcial
| Cola de pedidos    | Archivo de stock | Pila de faltante
| N° producto        | Nombre producto
| Cantidad Pedido    | Cantidad stock

Si el pedido se puede pedir en forma completa, actualizo stock y creo archivo
de texto que se llame pedidos atendidos. Pero si no alcanzan, creo una pila
con la cantidad que falta.

N° de producto coincide con el número de registro en el archivo.

Normalizar productos. Actualizo si pedido completo, espacio entre palabras.

1° Palabra  código 3 letras, 3 letras, 2 números (de 2 dígitos)
                   Depto (M)  Sector (m) Fila - columna
1° Letra de producto mayúscula

Empecé 19.50.
*/

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define SIZE_NOMBRE 100
#define NOMBRE_ARCHIVO_PRODUCTOS "productos.bin"
#define NOMBRE_ARCHIVO_ATENDIDOS "atendidos.txt"

typedef struct {
    int numero;
    int cantidad;
} t_pedido;

typedef struct {
    char nombre[SIZE_NOMBRE];
    int cantidad;
} t_producto;

typedef struct t_nodo {
    void *info;
    struct t_nodo *sig;
} t_nodo;

typedef struct {
    t_nodo* primero;
    t_nodo* ultimo;
} t_cola;
typedef t_nodo* t_pila;

void crear_pila(t_pila *pila);
int pila_vacia(const t_pila *pila);
int push_pila(t_pila *pila, t_producto *dato);
void pop_pila(t_pila *pila, t_producto *dato);

void crear_cola(t_cola *cola);
int cola_vacia(const t_cola *cola);
int push_cola(t_cola *cola, t_pedido *dato);
void pop_cola(t_cola *cola, t_pedido *dato);

FILE* abrir_archivo(const char *nombre, const char *modo);

int size_archivo(FILE *f_productos);
void cargar_pedidos(t_cola *pedidos);
void buscar_producto(FILE *f_productos, t_producto *producto, const int indice);
void actualizar_producto(FILE *f_productos, const t_producto *producto, const int indice);
void normalizar_cadena(char *cadena);

char toupper(char c);
char tolower(char c);

int main() {
    t_cola pedidos;
    t_pila faltantes;
    FILE *f_productos, *f_atendidos;
    f_productos = abrir_archivo(NOMBRE_ARCHIVO_PRODUCTOS, "r+b");
    f_atendidos = abrir_archivo(NOMBRE_ARCHIVO_ATENDIDOS, "wt");
    unsigned int size_archivo_producto = size_archivo(f_productos);

    crear_cola(&pedidos);
    crear_pila(&faltantes);

    cargar_pedidos(&pedidos);

    while (!cola_vacia(&pedidos)) {
        t_pedido pedido;
        t_producto producto;

        pop_cola(&pedidos, &pedido);
        printf("Pedido %d %d\n", pedido.numero, pedido.cantidad);

        if (pedido.numero >= size_archivo_producto) {
            printf("El producto no existe.\n");
            continue;
        }

        buscar_producto(f_productos, &producto, pedido.numero);
        normalizar_cadena(producto.nombre);
        printf("Nombre normalizado: %s\n", producto.nombre);
        if (producto.cantidad < pedido.cantidad) {
            t_producto faltante = producto;
            faltante.cantidad = pedido.cantidad - producto.cantidad;
            printf("No hay suficiente cantidad del producto.\n\n");
            push_pila(&faltantes, &faltante);
        } else {
            printf("Se atiende el pedido.\n\n");
            producto.cantidad -= pedido.cantidad;
            fprintf(f_atendidos, "%s: %d\n", producto.nombre, pedido.cantidad);
        }
        actualizar_producto(f_productos, &producto, pedido.numero);
    }

    printf("Productos faltantes: \n");
    if (pila_vacia(&faltantes)) {
        printf("Ninguno\n");
    } else {
        while (!pila_vacia(&faltantes)) {
            t_producto producto;
            pop_pila(&faltantes, &producto);
            printf("%s %d\n", producto.nombre, producto.cantidad);
        }
    }

    fclose(f_productos);
    fclose(f_atendidos);
    return EXIT_SUCCESS;
}

void crear_pila(t_pila *pila) {
    *pila = NULL;
}

int pila_vacia(const t_pila *pila) {
    return *pila == NULL;
}

int push_pila(t_pila *pila, t_producto *dato) {
    t_nodo *nodo = malloc(sizeof(t_nodo));
    t_producto *info = malloc(sizeof(t_producto));
    if (!nodo || !info)
        return FALSE;
    *info = *dato;
    nodo->info = info;
    nodo->sig = *pila;
    *pila = nodo;
    return TRUE;
}

void pop_pila(t_pila *pila, t_producto *dato) {
    t_nodo *aux = *pila;
    *dato = *((t_producto *)(aux->info));
    *pila = aux->sig;
    free(aux->info);
    free(aux);
}

void crear_cola(t_cola *cola) {
    cola->primero = NULL;
    cola->ultimo = NULL;
}

int cola_vacia(const t_cola *cola) {
    return cola->primero == NULL;
}

int push_cola(t_cola *cola, t_pedido *dato) {
    t_nodo *nodo = malloc(sizeof(t_nodo));
    t_pedido *info = malloc(sizeof(t_pedido));
    if (!nodo || !info)
        return FALSE;
    *info = *dato;
    nodo->info = info;
    nodo->sig = NULL;
    if (cola->primero == NULL)
        cola->primero = nodo;
    else
        cola->ultimo->sig = nodo;
    cola->ultimo = nodo;
    return TRUE;
}

void pop_cola(t_cola *cola, t_pedido *pedido) {
    t_nodo *aux = cola->primero;
    *pedido = *((t_pedido *)(aux->info));
    cola->primero = aux->sig;
    free(aux->info);
    free(aux);

    if (cola->primero == NULL)
        cola->ultimo = NULL;
}

FILE* abrir_archivo(const char *nombre, const char *modo) {
    FILE* archivo = fopen(nombre, modo);
    if (archivo == NULL) {
        printf("El archivo %s no se pudo abrir.\n", nombre);
        printf("Saliendo.\n");
        exit(EXIT_FAILURE);
    }
    return archivo;
}

int size_archivo(FILE *f_productos) {
    fseek(f_productos, 0, SEEK_END);
    return ftell(f_productos) / sizeof(t_producto);
}

void cargar_pedidos(t_cola *pedidos) {
    t_pedido pedido;
    int numero, cantidad;
    printf("Ingrese número de producto y cantidad.\n Número -1 para terminar.\n?: ");
    scanf("%d", &numero);
    while (numero != -1) {
        scanf("%d", &cantidad);
        pedido.numero = numero;
        pedido.cantidad = cantidad;
        if (!push_cola(pedidos, &pedido))
            printf("No hay más memoria. Pruebe cerrar aplicaciones para continuar.\n");
        printf("?: ");
        scanf("%d", &numero);
    }
}

void buscar_producto(FILE *f_productos, t_producto *producto, const int indice) {
    fseek(f_productos, sizeof(t_producto) * indice, SEEK_SET);
    fread(producto, sizeof(t_producto), 1, f_productos);
}

void actualizar_producto(FILE *f_productos, const t_producto *producto, const int indice) {
    fseek(f_productos, sizeof(t_producto) * indice, SEEK_SET);
    fwrite(producto, sizeof(t_producto), 1, f_productos);
}

void normalizar_cadena(char *cadena) {
    for (int i = 0; i < 3; i++) {
        *cadena = toupper(*cadena);
        cadena++;
    }
    for (int i = 0; i < 3; i++) {
        *cadena = tolower(*cadena);
        cadena++;
    }
    cadena += 4;
    if (*cadena == ' ') {
        char *der = cadena + 1;
        cadena++;
        while (*der == ' ')
            *cadena = *(++der);
        *cadena = toupper(*cadena);
        while (*cadena != '\0') {
            ++cadena;
            ++der;
            *cadena = tolower(*der);
        }
    } else {
        char *fin = cadena;
        while (*(fin - 1) != '\0')
            fin++;
        while (fin != cadena + 1) {
            *fin = *(fin - 1);
            fin--;
        }
        *cadena = ' ';
    }
}

char toupper(char c) {
    if (c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}

char tolower(char c) {
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}
