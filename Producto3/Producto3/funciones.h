
//fichero para declara las funciones y librerías utilizadas

#include <stdio.h> //librería estandar de lenguaje C para entrada y salida de datos
#include <locale.h> //librería para la corrección de lenguaje (muestra vocales con tildes)
#include <stdlib.h> //librería para la gestión de memoria (punteros) y funciones de windows
#include <string.h> //librería para el manejo de cadenas de caracteres (strings)

void bienvenida(); //llamada a la función de bienvenida
void menuInicio(); //llamada a la función de inicio
void accesoRutaFichero(); //llamada a la función de accesoRutaFichero
void adaptadoresRed(char* nombreRed); //llamada a la función de adaptadoresRed, como parámetro un puntero tipo char
void pruebasPing(); //llamada a la función de pruebasPing
void mediaMS(char* ipMejorMedia); //llamada a la función de mediaMS, como parámetro un puntero tipo char
void configAdaptador(char* ipMejorMedia, char* nombreRed); //llamada a la función de configAdaptador, como parámetros 2 punteros tipo char