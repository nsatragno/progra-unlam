// FUNCIONES_ARRAY.H
// Nicolás Satragno.
#include "funciones_array.c"

/*
 * Inicializa un |array| con pares de 0 a (|size| - 1) * 2
 */
void inicializar_con_pares(int *array, const int size);

/*
 * Imprime un |array| en pantalla.
 */
void imprimir(int *array, const int size);

/*
 * Lee hasta |size| del teclado.
 */
void leer_del_teclado(int *array, const int size);

/*
 * Inserta un |elemento| en |array| de |size|, en la |posicion| determinada.
 * Devuelve 0 si falló, 1 de lo contrario.
 */
int insertar(int *array,
              const int size, 
              const int ultima_posicion, // Arranca de 0.
              int posicion, // Arranca de 1.
              int elemento);

