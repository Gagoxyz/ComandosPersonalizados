
//fichero principal, contiene libería propia y función main

#define _CRT_SECURE_NO_WARNINGS
#include "funciones.h"


int main() {
	setlocale(LC_ALL, ""); //hace que se muestren las tildes correctamente

	int menuOpcion;
	int salir = 0;
	char nombreRed[50]; //obtendrá el nombre de la red elegida por el usuario a través de un puntero
	char ip[20]; //obtendrá la IP del adaptador a través de un puntero
	char mascaraRed[20]; //obtendrá la IP de la máscara a través de un puntero
	char puertaEnlace[20]; //obtendrá la IP de la puerta de enlace a través de un puntero
	char dns1[20]; //obtendrá la IP de la DNS primaria a través de un puntero
	char mediaMs[3]; //obtendrá la media en MS a través de un puntero
	char saltos[3]; //obtendrá la cantidad de saltos a través de un puntero

	bienvenida(); //llama a la faunción de bienvenida

	//bucle while que llamará a la función menuInicio mientras que la variable "salir" sea 0 (NOT)
	while (!salir) {
		menuInicio();
		scanf("%d", &menuOpcion);
		switch (menuOpcion) {
		case 1:
			adaptadoresRed(nombreRed, ip, mascaraRed, puertaEnlace, dns1); //función para obtener datos del adaptador seleccionado
			break;
		case 2:
			testDNS(dns1, mediaMs, saltos); //función para testear la DNS del adaptador seleccionado
			break;
		case 3:
			mostrarInfo(nombreRed, ip, mascaraRed, puertaEnlace, dns1, mediaMs, saltos); //función para mostrar datos después de selección y pruebas
			break;
		case 4:
			generarXML(nombreRed, ip, mascaraRed, puertaEnlace, dns1, mediaMs, saltos); //función para generar fichero XML con datos obtenidos
			break;
		case 5:
			generarXSLT();
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
