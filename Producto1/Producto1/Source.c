#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void fizzbuzz() {
	printf("//////////////////////////////\n");
	printf("| \t\t\t     |\n");
	printf("|      Programa FIZZBUZZ     |\n");
	printf("| \t\t\t     |\n");
	printf("//////////////////////////////\n");
}

int main() {

	fizzbuzz();

	printf("\n\nEl programa muestra los multiplos de 3 y 5 desde el 1 hasta el numero indicado.\n");
	printf("Multiplos de 3 -> Fizz\n");
	printf("Multiplos de 5 -> Buzz\n");
	printf("Multiplos de ambos -> FizzBuzz\n\n");

	// Declaramos variables
	int numero; // sera el numero introducido por el usuario
	int salir = 1; // utilizaremos para finalizar el programa

	do {
		printf("Introduce un numero: ");
		scanf("%d", &numero);

		for (int i = 1; i <= numero; i++) {
			if (i % 3 == 0 && i % 5 == 0) {
				printf("%d FizzBuzz\n", i);
			}
			else if (i % 3 == 0) {
				printf("%d Fizz\n", i);
			}
			else if (i % 5 == 0) {
				printf("%d Buzz\n", i);
			}
			else {
				printf("%d No es multiplo ni de 3 ni de 5\n", i);
			}
		}
		printf("\n1. Comprobar nuevo rango\n0. Salir\n");
		scanf("%d", &salir);
	} while (salir);

	return 0;
}