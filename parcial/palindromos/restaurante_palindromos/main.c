#include <stdio.h>

#define CANTIDAD_PALINDROMOS 50
#define SIZE_PALINDROMO 16

int comparar(char *izq, char *der);
void completar_palindromo(char *palindromo);

int main() {
    char palindromos[CANTIDAD_PALINDROMOS][SIZE_PALINDROMO];
    int cantidad = 0, contador = 0;

    printf("Ingrese un palindromo, o - para terminar.\n?: ");
    scanf("%s", palindromos[cantidad]);
    while (comparar(palindromos[cantidad], "-") != 0 && cantidad < CANTIDAD_PALINDROMOS - 1) {
        cantidad++;
        printf("Ingrese un palindromo, o - para terminar.\n?: ");
        scanf("%s", palindromos[cantidad]);
    }
    if (comparar(palindromos[cantidad], "-") != 0)
        cantidad++;

    while (contador < cantidad) {
        completar_palindromo(palindromos[contador]);
        printf("%s\n", palindromos[contador]);
        contador++;
    }

    return 0;
}


int comparar(char *izq, char *der) {
    while (1) {
        if (*izq > *der)
            return 1;
        if (*izq < *der)
            return -1;
        if (*izq == '\0' && *der == '\0')
            return 0;
        izq++;
        der++;
    }
}

void completar_palindromo(char *palindromo) {
    char *der = palindromo;
    char *izq;
    while (*der != '\0')
        der++;
    der--;
    izq = der - 1;
    if (*der == '1') {
        if (izq == palindromo) {
            *der = '\0';
            return;
        }
        izq--;
    }
    while (izq != palindromo) {
        *der = *izq;
        der++;
        izq--;
    }
    *der = *izq;
    *(der + 1) = '\0';
}
