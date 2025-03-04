
//fichero para declarar las funciones y librer�as utilizadas

#include <stdio.h> //librer�a estandar de lenguaje C para entrada y salida de datos
#include <locale.h> //librer�a para la correcci�n de lenguaje (muestra vocales con tildes)
#include <stdlib.h> //librer�a para la gesti�n de memoria (punteros) y funciones de windows
#include <string.h> //librer�a para el manejo de cadenas de caracteres (strings)

void bienvenida(); //funci�n que muestra mensaje de bienvenida (prints)
void menuInicio(); //funci�n del men� inicio con bucle while hasta pulsar 0
void insertarFechaHora(); //funci�n para insertar fecha y hora en un documento txt
void gestionIPs(); //funci�n que acceder� a otro men� para mostrar el contenido de un fichero (ips.txt) y lanzar un ping a las IPs de su contenido
void adaptadorRed(); //funci�n para mostrar los adaptadores de red que tiene la m�quina local y guardar informaci�n en un documento txt
void mostrarFicheroP2(); //funci�n para mostrar el contenido del fichero producto2.txt
void mostrarFicheroAdaptador(); //funci�n para mostrar el contenido del fichero adaptador.txt
