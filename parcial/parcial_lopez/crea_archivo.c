#include <stdio.h>
#include <stdlib.h>

#define NOMBRE_ARCHIVO "parcelas.dat"

#define TRUE 1
#define FALSE 0

typedef struct {
    int numero;
    double monto;
} t_guardada;

int main()
{
    FILE *archivo = fopen(NOMBRE_ARCHIVO, "wb");
    t_guardada dato;
    printf("Ingrese num, y monto de cosecha. -1 para terminar.\n?: ");
    scanf("%d\n", &dato.numero);
    while (dato.numero != -1) {
        scanf("%lf", &dato.monto);
        fwrite(&dato, sizeof(t_guardada), 1, archivo);
        printf("?: ");
        scanf("%d", &dato.numero);
    }
    fclose(archivo);
}
