#include <stdio.h>
#include <stdlib.h>

#define SIN_MEMORIA 0
#define TODO_OK 1

/*
 * Hacer: eliminar hojas.
 * Eliminar hojas a partir de una clave.
 * Eliminar todo el árbol.
 * Eliminar todo el subárbol a partir de una clave.
 */

typedef struct s_nodo {
  struct s_nodo *izq;
  int dato;
  struct s_nodo *der;
} t_nodo;

typedef t_nodo* t_arbol;

void crear_arbol(t_arbol *arbol);
void cargar_arbol(t_arbol *arbol);
void imprimir_arbol(t_arbol *arbol);
void imprimir_arbol2(t_arbol *arbol);
void imprimir_arbol3(t_arbol *arbol);
void imprimir_arbol4(t_arbol *arbol, int ident);
int contar_nodos(t_arbol *arbol);
int contar_hojas(t_arbol *arbol);
int altura(t_arbol *arbol);
void mostrar_altura(t_arbol *arbol, int altura);
int push(t_arbol *arbol, int info);
int push_i(t_arbol *arbol, int info);
int colocar(t_arbol *arbol, t_nodo *info);
int del(t_arbol *arbol, int clave);
void del_todas(t_arbol *arbol);
double promedio_nodos(t_arbol *arbol);
double promedio_nodos_i(t_arbol *arbol, int *cant);

void mostrar_info(int info);

int main() {
  t_arbol arbol;
  crear_arbol(&arbol);
  cargar_arbol(&arbol);
  while (1) {
    int a;
    imprimir_arbol4(&arbol, 0);
    printf("Cantidad de elementos: %d\n", contar_nodos(&arbol));
    printf("Cantidad de hojas: %d\n", contar_hojas(&arbol));
    printf("Altura: %d\n", altura(&arbol));
    printf("Promedio: %f\n", promedio_nodos(&arbol));
    printf("Ingrese la altura que desea ver\n?: ");
    scanf("%d", &a);
    printf("******\n");
    mostrar_altura(&arbol, a);
    printf("\n******\n");
  }
  return 0;
}

// RID.
void imprimir_arbol(t_arbol *arbol) {
  if (!*arbol)
    return;
  mostrar_info((*arbol)->dato);
  imprimir_arbol(&(*arbol)->izq);
  imprimir_arbol(&(*arbol)->der);
}

// IRD.
void imprimir_arbol2(t_arbol *arbol) {
  if (!*arbol)
    return;
  imprimir_arbol2(&(*arbol)->izq);
  mostrar_info((*arbol)->dato);
  imprimir_arbol2(&(*arbol)->der);
}

// IDR.
void imprimir_arbol3(t_arbol *arbol) {
  if (!*arbol)
    return;
  imprimir_arbol3(&(*arbol)->izq);
  imprimir_arbol3(&(*arbol)->der);
  mostrar_info((*arbol)->dato);
}

// Lindo.
void imprimir_arbol4(t_arbol *arbol, int ident) {
  if (!*arbol)
    return;
  for (int i = 0; i < ident; i++)
    printf(" ");
  mostrar_info((*arbol)->dato);
  printf("\n");
  imprimir_arbol4(&(*arbol)->izq, ident + 2);
  imprimir_arbol4(&(*arbol)->der, ident + 2);
}

int contar_nodos(t_arbol *arbol) {
  if (!*arbol)
    return 0;
  return contar_nodos(&(*arbol)->izq) + contar_nodos(&(*arbol)->der) + 1;
}

int contar_hojas(t_arbol *arbol) {
  if (!*arbol)
    return 0;
  return contar_hojas(&(*arbol)->izq) + contar_hojas(&(*arbol)->der) 
         + (((*arbol)->izq || (*arbol)->der) ? 0 : 1);
}

int altura(t_arbol *arbol) {
  if (!*arbol)
    return 0;
  int altura_izq = altura(&(*arbol)->izq);
  int altura_der = altura(&(*arbol)->der);
  return (altura_izq > altura_der ? altura_izq : altura_der) + 1;
}

void mostrar_altura(t_arbol *arbol, int altura) {
  if (!*arbol)
    return;
  if (altura <= 1) {
    mostrar_info((*arbol)->dato);
    return;
  }
  mostrar_altura(&(*arbol)->izq, altura - 1);
  mostrar_altura(&(*arbol)->der, altura - 1);
}

double promedio_nodos(t_arbol *arbol) {
  if (!*arbol)
    return 0;
  int cantidad_elementos = 0;
  double suma = promedio_nodos_i(arbol, &cantidad_elementos);
  return suma / cantidad_elementos;
}

double promedio_nodos_i(t_arbol *arbol, int *cant) {
  if (!*arbol)
    return 0;
  ++(*cant);
  return (*arbol)->dato + 
         promedio_nodos_i(&(*arbol)->izq, cant) +
         promedio_nodos_i(&(*arbol)->der, cant);
}

void crear_arbol(t_arbol *arbol) {
  *arbol = NULL;
}

void cargar_arbol(t_arbol *arbol) {
  push_i(arbol, 1);
  push_i(arbol, 15);
  push_i(arbol, 21);
  push_i(arbol, -1);
  push_i(arbol, -11);
  push_i(arbol, 51);
  push_i(arbol, 0);
}

int push(t_arbol *arbol, int dato) {
  t_nodo *nodo = malloc(sizeof(t_nodo));
  if (!nodo)
    return SIN_MEMORIA;
  nodo->dato = dato;
  nodo->izq = nodo->der  = NULL;
  return colocar(arbol, nodo);
}

int push_i(t_arbol *arbol, int dato) {
  t_nodo *nodo = malloc(sizeof(t_nodo));
  if (!nodo)
    return SIN_MEMORIA;
  nodo->dato = dato;
  nodo->izq = nodo->der  = NULL;

  while (*arbol) {
    if ((*arbol)->dato > nodo->dato)
      arbol = &(*arbol)->izq;
    else
      arbol = &(*arbol)->der;
  }
  *arbol = nodo;
  return 1;
}

int del(t_arbol *arbol, int clave) {
  t_arbol *rama;
  if (!*arbol) 
    return 0;

  if ((*arbol)->dato > clave)
    rama = &(*arbol)->izq;
  else if ((*arbol)->dato < clave)
    rama = &(*arbol)->der;
  else
    rama = arbol;

  if (*rama && (*rama)->dato == clave) {
    if ((*rama)->izq || (*rama)->der)   // No es hoja.
      return 0;
    free(*rama);
    *rama = NULL;
    return 1;
  }

  return del(rama, clave);
}

void del_todas(t_arbol *arbol) {
  if (!*arbol) 
    return;

  if ((*arbol)->izq || (*arbol)->der) {   // No es hoja.
    del_todas(&(*arbol)->izq);
    del_todas(&(*arbol)->der);
    return;
  }

  free(*arbol);
  *arbol = NULL;
}

int colocar(t_arbol *arbol, t_nodo *nodo) {
  if (!*arbol) {
    *arbol = nodo;
    return TODO_OK;
  }
  if ((*arbol)->dato > nodo->dato)
    return colocar(&(*arbol)->izq, nodo);
  else
    return colocar(&(*arbol)->der, nodo);
}

void mostrar_info(int info) {
  printf("%d ", info);
}
