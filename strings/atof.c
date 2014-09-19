#include <stdio.h>
#include <math.h>

#define TAM 1000

/**
 * Devuelve un float a partir de la siguiente sintaxis:
 * [Letras][Signo]Numero[. Numero][e|E Numero]
 */
double atof(char *string);

/**
 * Devuelve 1 si el caracter es un número, 0 de lo contrario.
 */
int isnum(char c);

/**
 * Devuelve 1 si el caracter es + o -, 0 de lo contrario.
 */
int issigno(char c);

/**
 * Convierte el caracter en un int equivalente a su valor simbólico.
 */
int ctoi(char c);

int main() {
  char string[TAM];
  printf("Ingrese un string para convertir (Máx %d caracteres)\n?: ", TAM - 1);
  scanf("%s", string);
  double numero = atof(string);
  printf("El número convertido es: %f\n", numero);
  return 0;
}

double atof(char *string) {
  double resultado = 0;
  double exponente = 0;
  int parte_decimal = 0;

  // Salteo todos los caracteres hasta el primer número o signo.
  while (!isnum(*string) && !issigno(*string) && *string != '\0')
    string++;

  // Por defecto, el signo es positivo.
  char signo = '+';
  if (issigno(*string)) {
    signo = *string;
    string++;
  }

  // Obtengo el número completo.
  while (isnum(*string) || (*string == '.' && !parte_decimal)) {
    // Si encuentro un punto, levanto la bandera que indica que estamos en la 
    // parte decimal para poder decrementar el exponente en cada vuelta.
    if (*string == '.') {
      parte_decimal = 1;
      string++;
      continue;
    }
    resultado = resultado * 10 + ctoi(*string);
    if (parte_decimal)
      exponente--;
    string++;
  }

  // Para enteder la siguiente línea, ver "El Orígen" (Inception).
  if (*string == 'e' || *string == 'E')
    exponente += atof(string + 1);

  if (signo == '-')
    resultado *= -1;
  return resultado * pow(10, exponente);
}


int isnum(char c) {
  return (c >= '0' && c <= '9') ? 1 : 0;
}

int issigno(char c) {
  return (c == '+' || c == '-') ? 1 : 0;
}

int ctoi(char c) {
  return c - '0';
}
