
//fichero para declara las funciones y librer�as utilizadas

#include <stdio.h> //librer�a estandar de lenguaje C para entrada y salida de datos
#include <locale.h> //librer�a para la correcci�n de lenguaje (muestra vocales con tildes)
#include <stdlib.h> //librer�a para la gesti�n de memoria (punteros) y funciones de windows
#include <string.h> //librer�a para el manejo de cadenas de caracteres (strings)

void bienvenida();
void menuInicio();
void adaptadoresRed(char* nombreRed, char* ip, char* mascaraRed, char* puertaEnlace, char* dns1);
void testDNS(char* dns1, char* mediaMs, char* saltos);
void mostrarInfo(char* nombreRed, char* ip, char* mascaraRed, char* puertaEnlace, char* dns1, char* mediaMs, char* saltos);
void generarXML(char* nombreRed, char* ip, char* mascaraRed, char* puertaEnlace, char* dns1, char* mediaMs, char* saltos);