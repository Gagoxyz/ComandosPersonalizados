
//fichero principal, contiene librería propia y funcion main

#define _CRT_SECURE_NO_WARNINGS //definimos una constante para que no muestre warnings
#include "funciones.h" //librería propia que contiene las funciones

int main() {
	setlocale(LC_ALL, ""); //hace que se muestren las tildes correctamente

	int menuOpcion;
	int salir = 0;

	bienvenida(); //llamamos a la función de bienvenida

	//bucle while que llamará a la función menuInicio mientras que la variable "salir" sea 0 (NOT)
	while (!salir) {
		menuInicio();
		scanf("%d", &menuOpcion);
		//switch para llamar a cada función dependiendo del caso
		switch (menuOpcion) {
		case 1:
			insertarFechaHora(); //llama a la función insertarFechaHora
			break;
		case 2:
			gestionIPs(); //llama a la función gestionIPs
			break;
		case 3:
			adaptadorRed(); //llama a la función adaptadorRed
			break;
		case 4:
			mostrarFicheroP2(); //llama a la función mostrarFicheroP2
			break;
		case 5:
			mostrarFicheroAdaptador();
			break;
		case 0:
			salir = 1; //este caso actualiza la variable "salir" en 1, saldremos del programa
			break;
		default:
			printf("\nOpción incorrecta.");
			break;
		}
	}
	
	return 0;
}
