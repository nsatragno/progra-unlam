// FUNCIONES_ARRAY.H
// Nicolás Satragno.
// Contiene las funciones comunes a los ejercicios que operan sobre arrays.
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
 * Lee hasta |size| del teclado, guardando en |cantidad_elementos| la cantidad
 * de elementos leída.
 */
void leer_del_teclado(int *array, int *cantidad_elementos, const int size);

/*
 * Inserta un |elemento| en |array| de |size|, en la |posicion| determinada.
 * Actualiza ultima_posicion si se agregaron valores.
 * Devuelve 0 si falló, 1 de lo contrario.
 */
int insertar(int *array,
             const int size, 
             int *ultima_posicion, // Arranca de 0.
             int posicion,         // Arranca de 1.
             int elemento);

/*
 * Devuelve la primera posición del elemento dado en el array.
 * Si no existe, devuelve -1.
 */
int posicion_de(int *array, const int size, int elemento);
