
//fichero para declara las funciones y librerías utilizadas

#include <stdio.h> //librería estandar de lenguaje C para entrada y salida de datos
#include <locale.h> //librería para la corrección de lenguaje (muestra vocales con tildes)
#include <stdlib.h> //librería para la gestión de memoria (punteros) y funciones de windows
#include <string.h> //librería para el manejo de cadenas de caracteres (strings)

void bienvenida();
void menuInicio();
void adaptadoresRed(char* nombreRed, char* ip, char* mascaraRed, char* puertaEnlace, char* dns1);
void testDNS(char* dns1, char* mediaMs, char* saltos);
void mostrarInfo(char* nombreRed, char* ip, char* mascaraRed, char* puertaEnlace, char* dns1, char* mediaMs, char* saltos);
void generarXML(char* nombreRed, char* ip, char* mascaraRed, char* puertaEnlace, char* dns1, char* mediaMs, char* saltos);