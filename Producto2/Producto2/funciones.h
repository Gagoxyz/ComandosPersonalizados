
//fichero para declarar las funciones y librerías utilizadas

#include <stdio.h> //librería estandar de lenguaje C para entrada y salida de datos
#include <locale.h> //librería para la corrección de lenguaje (muestra vocales con tildes)
#include <stdlib.h> //librería para la gestión de memoria (punteros) y funciones de windows
#include <string.h> //librería para el manejo de cadenas de caracteres (strings)

void bienvenida(); //función que muestra mensaje de bienvenida (prints)
void menuInicio(); //función del menú inicio con bucle while hasta pulsar 0
void insertarFechaHora(); //función para insertar fecha y hora en un documento txt
void gestionIPs(); //función que accederá a otro menú para mostrar el contenido de un fichero (ips.txt) y lanzar un ping a las IPs de su contenido
void adaptadorRed(); //función para mostrar los adaptadores de red que tiene la máquina local y guardar información en un documento txt
void mostrarFicheroP2(); //función para mostrar el contenido del fichero producto2.txt
void mostrarFicheroAdaptador(); //función para mostrar el contenido del fichero adaptador.txt
