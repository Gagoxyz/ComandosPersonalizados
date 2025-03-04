
//fichero principal, contiene liber�a propia y funci�n main

#define _CRT_SECURE_NO_WARNINGS
#include "funciones.h"

int main() {
	setlocale(LC_ALL, ""); //hace que se muestren las tildes correctamente

	int menuOpcion;
	int salir = 0;
	char ipMejorMedia[20]; //obtendr� la mejor IP a trav�s de un puntero
	char nombreRed[20]; //obtendr� el nombre de la red elegida por el usuario a trav�s de un puntero

	bienvenida(); //llama a la faunci�n de bienvenida
	
	//bucle while que llamar� a la funci�n menuInicio mientras que la variable "salir" sea 0 (NOT)
	while (!salir) {
		menuInicio();
		scanf("%d", &menuOpcion);
		switch (menuOpcion) {
		case 1:
			accesoRutaFichero(); //llama a la funci�n accesoRutaFichero
			break;
		case 2:
			adaptadoresRed(nombreRed); //llama a la funci�n adaptadoresRed, se pasa como par�metro la cadena "nombreRed"
			break;
		case 3:
			pruebasPing(); //llama a la funci�n pruebasPing
			break;
		case 4:
			mediaMS(ipMejorMedia); //llama a la funci�n mediaMS, se pasa como par�metro la cadena "ipMejorMedia"
			break;
		case 5:
			configAdaptador(ipMejorMedia, nombreRed); //llama a la funci�n configAdaptador, se pasan como par�metros las cadenas "ipMejorMedia" y "nombreRed"
			break;
		case 0:
			salir = 1; //actualiza la variable salir en 1, saliendo de la aplicaci�n
			break;
		default:
			printf("\nOpci�n incorrecta.");
			break;
		}
	}
	return 0;
}
