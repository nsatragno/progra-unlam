#include <stdio.h>

#define SIZE_PALABRA 100
#define TRUE 1
#define FALSE 0

int palindromo(char * palabra);
char tolower(char c);

int main() {
    char palabra[SIZE_PALABRA];
    while (1) {
        printf("Ingrese la palabra\n?: ");
        gets(palabra);
        printf("La frase %s ", palabra);
        printf(palindromo(palabra) ? "es palíndromo\n": "no es palíndromo\n");
    }
}

int palindromo(char * palabra) {
    char *izq = palabra;
    char *der = palabra;
    while (*der != '\0')
        der++;
    der--;
    while (1) {
        if (*izq == ' ') {
            izq++;
            continue;
        }
        if (*der == ' ') {
            der--;
            continue;
        }
        if (tolower(*izq) != tolower(*der))
            return FALSE;
        if (der - izq < 1)
            return TRUE;
        izq++;
        der--;
    }
}

char tolower(char c) {
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}
