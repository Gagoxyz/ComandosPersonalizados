
//fichero principal, contiene libería propia y función main

#define _CRT_SECURE_NO_WARNINGS
#include "funciones.h"

int main() {
	setlocale(LC_ALL, ""); //hace que se muestren las tildes correctamente

	int menuOpcion;
	int salir = 0;
	char ipMejorMedia[20]; //obtendrá la mejor IP a través de un puntero
	char nombreRed[20]; //obtendrá el nombre de la red elegida por el usuario a través de un puntero

	bienvenida(); //llama a la faunción de bienvenida
	
	//bucle while que llamará a la función menuInicio mientras que la variable "salir" sea 0 (NOT)
	while (!salir) {
		menuInicio();
		scanf("%d", &menuOpcion);
		switch (menuOpcion) {
		case 1:
			accesoRutaFichero(); //llama a la función accesoRutaFichero
			break;
		case 2:
			adaptadoresRed(nombreRed); //llama a la función adaptadoresRed, se pasa como parámetro la cadena "nombreRed"
			break;
		case 3:
			pruebasPing(); //llama a la función pruebasPing
			break;
		case 4:
			mediaMS(ipMejorMedia); //llama a la función mediaMS, se pasa como parámetro la cadena "ipMejorMedia"
			break;
		case 5:
			configAdaptador(ipMejorMedia, nombreRed); //llama a la función configAdaptador, se pasan como parámetros las cadenas "ipMejorMedia" y "nombreRed"
			break;
		case 0:
			salir = 1; //actualiza la variable salir en 1, saliendo de la aplicación
			break;
		default:
			printf("\nOpción incorrecta.");
			break;
		}
	}
	return 0;
}
