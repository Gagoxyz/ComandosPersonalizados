
//fichero principal, contiene liber�a propia y funci�n main

#define _CRT_SECURE_NO_WARNINGS
#include "funciones.h"


int main() {
	setlocale(LC_ALL, ""); //hace que se muestren las tildes correctamente

	int menuOpcion;
	int salir = 0;
	char nombreRed[50]; //obtendr� el nombre de la red elegida por el usuario a trav�s de un puntero
	char ip[20]; //obtendr� la IP del adaptador a trav�s de un puntero
	char mascaraRed[20]; //obtendr� la IP de la m�scara a trav�s de un puntero
	char puertaEnlace[20]; //obtendr� la IP de la puerta de enlace a trav�s de un puntero
	char dns1[20]; //obtendr� la IP de la DNS primaria a trav�s de un puntero
	char mediaMs[3]; //obtendr� la media en MS a trav�s de un puntero
	char saltos[3]; //obtendr� la cantidad de saltos a trav�s de un puntero

	bienvenida(); //llama a la faunci�n de bienvenida

	//bucle while que llamar� a la funci�n menuInicio mientras que la variable "salir" sea 0 (NOT)
	while (!salir) {
		menuInicio();
		scanf("%d", &menuOpcion);
		switch (menuOpcion) {
		case 1:
			adaptadoresRed(nombreRed, ip, mascaraRed, puertaEnlace, dns1); //funci�n para obtener datos del adaptador seleccionado
			break;
		case 2:
			testDNS(dns1, mediaMs, saltos); //funci�n para testear la DNS del adaptador seleccionado
			break;
		case 3:
			mostrarInfo(nombreRed, ip, mascaraRed, puertaEnlace, dns1, mediaMs, saltos); //funci�n para mostrar datos despu�s de selecci�n y pruebas
			break;
		case 4:
			generarXML(nombreRed, ip, mascaraRed, puertaEnlace, dns1, mediaMs, saltos); //funci�n para generar fichero XML con datos obtenidos
			break;
		case 5:
			generarXSLT();
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
