
//fichero para declara las funciones y librer�as utilizadas

#include <stdio.h> //librer�a estandar de lenguaje C para entrada y salida de datos
#include <locale.h> //librer�a para la correcci�n de lenguaje (muestra vocales con tildes)
#include <stdlib.h> //librer�a para la gesti�n de memoria (punteros) y funciones de windows
#include <string.h> //librer�a para el manejo de cadenas de caracteres (strings)

void bienvenida(); //llamada a la funci�n de bienvenida
void menuInicio(); //llamada a la funci�n de inicio
void accesoRutaFichero(); //llamada a la funci�n de accesoRutaFichero
void adaptadoresRed(char* nombreRed); //llamada a la funci�n de adaptadoresRed, como par�metro un puntero tipo char
void pruebasPing(); //llamada a la funci�n de pruebasPing
void mediaMS(char* ipMejorMedia); //llamada a la funci�n de mediaMS, como par�metro un puntero tipo char
void configAdaptador(char* ipMejorMedia, char* nombreRed); //llamada a la funci�n de configAdaptador, como par�metros 2 punteros tipo char