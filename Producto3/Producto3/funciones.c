
//fichero para desarrollar las funciones

#define _CRT_SECURE_NO_WARNINGS
#include "funciones.h"

//función que muestra unos printf
void bienvenida() {
	printf("\n***************************************************");
	printf("\n**                                               **");
	printf("\n**                Producto 3                     **");
	printf("\n**  Programa comandos personalizados para el SO  **");
	printf("\n**                                               **");
	printf("\n***************************************************");
}

//función que muestra diferentes opciones
void menuInicio() {
	printf("\n");
	printf("\n1. Indicar ruta del fichero DNSips.txt (mostrará el contenido si es correcta)");
	printf("\n2. Mostrar adaptadores de red");
	printf("\n3. Verificar IPs de fichero DNSips.txt");
	printf("\n4. Comprobar velocidad de las DNSs");
	printf("\n5. Configurar adaptador con DNS más rápida");

	printf("\n0. Salir");
	printf("\n\nElige una opción (1,2,3,4,5 o 0): ");
}

//función para acceder al fichero DNSips.txt
void accesoRutaFichero() {
	char rutaFichero[100]; //cadena de 100 posiciones
	char buffer[200]; //cadena de 200 posiciones, se utilizará de buffer para lectura de ficheros

	printf("\n\n\nIndica la ruta completa del fichero que contiene las DNS:\n");
	scanf("%s", &rutaFichero); //guardamos en la cadena rutaFichero la ruta indicada por el usuario
	rutaFichero[strcspn(rutaFichero, "\n")] = '\0'; //cambiamos los saltos de línea por caracteres nulos
	//Comparamos la ruta que ha introducido el usuario con la ruta exacta del fichero
	//si ambas rutas coinciden accederemos al condicional, 
	//la función strcmp devuelve 0, si no coinciden devuelve un número diferente a 0
	if (strcmp(rutaFichero, "c:\\ficheros\\DNSips.txt") == 0) {
		system("cls");
		printf("\n\nContenido del fichero DNSips.txt");
		printf("\n--------------------------------\n");
		//puntero de tipo FILE llamado "fp", abre el fichero ubicado en la dirección de la variable "rutaFichero", se abrirá en modo lectura
		FILE* fp = fopen(rutaFichero, "r");
		//utilizando un bucle while recorreremos cada línea del fichero utilizando "fgets" printando cada una de estas líneas por pantalla
		while (fgets(buffer, sizeof(buffer), fp)) {
			printf("%s", buffer);
		}
		fclose(fp); //cerramos el fichero
		printf("\n");
		printf("\n");
		system("pause"); //comando del sistema para poder leer pantalla hasta pulsar tecla
		system("cls");
	}
	else {
		//si la ruta indicada por el usuario no es correcta, aparecerá un print con el error e indicando la ruta correcta
		//accede de nuevo a la función accesoRutaFichero
		printf("\nRuta incorrecta, la correcta es: c:\\ficheros\\DNSips.txt");
		accesoRutaFichero();
	}
}

//función para mostrar adaptadores de red y seleccionar uno
void adaptadoresRed(char* nombreRed) {
	FILE* fp1, * fp2, * fp3, * fp4; //diferentes punteros de tipo FILE
	//diferentes cadenas para almacenar buffer, nombre combinado de un fichero y nombre del adaptador
	char buffer[200], fichero[20], nombreAdaptador[20];
	//contador para los adaptadores, segundaLinea se utilizará para saltarnos líneas de un fichero
	int contAdaptadores = 1, segundaLinea = 0;

	system("cls");
	printf("\nLista de adaptadores encontrados:\n");
	//comando del sistema que guardará en el fichero "dnss.txt" las DNSs configuradas actualmente en el adaptador
	system("netsh interface ip show dnsserver > dnss.txt");
	fp1 = fopen("dnss.txt", "r"); //abrimos el fichero dnss.txt en modo lectura
	fp2 = fopen("contenido.txt", "w"); //abrimos un fichero nuevo en modo escritura llamado contenido.txt
	if (fp1 == NULL || fp2 == NULL) { //verificamos que ambos ficheros sonm accesibles
		perror("Error al abrir el fichero");
		return;
	}
	//mediante bucle while accedemos a cada línea del fichero utilizando el buffer
	while (fgets(buffer, sizeof(buffer), fp1)) {
		if (strstr(buffer, "Config") != NULL) { //condicional que buscará la cadena "Config" en la línea actual del buffer
			contAdaptadores++; //si la encuentra, aumentará el contador
		}
	}
	rewind(fp1); //movemos el cursor al principio del fichero
	for (int i = 1; i <= contAdaptadores; i++) { //bucle for para iterar n veces por cantidad de adaptadores encontrados
		rewind(fp1); //movemos el cursor al principio del fichero
		int adaptadorActual = 0; //nuevo contador para registrar la iteración del adaptador actual

		while (fgets(buffer, sizeof(buffer), fp1)) {
			if (segundaLinea) { //condicional que verifica si la variable "segundaLinea" es positiva (1) para acceder al condicional
				char* dns2 = strrchr(buffer, ' '); //busca el primer ' ' desde el final de la cadena dns2
				if (dns2) { //si encuentra el caracter anterior, accedemos al condicional
					fprintf(fp2, "DNS secundario:%s\0", dns2); //printamos el contenido de dns2
					fp3 = fopen(fichero, "a"); //abrimos el fichero (se crea en el siguiente condicional) en modo append
					if (fp3 == NULL) {
						perror("\nError al abrir el fichero");
						return;
					}
					fprintf(fp3, "DNS secundario:%s\0", dns2); //añadimos al fichero una cadena con el contenido de dns2
					fclose(fp3); //cerramos el fichero
					segundaLinea = 0; //actualizamos la variable segundaLinea a 0
				}
			}
			if (strstr(buffer, "Config") != NULL) { //condicional que buscará la cadena "Config" en la línea actual del buffer
				adaptadorActual++; //aumenta el contador de adaptadorActual
				if (adaptadorActual == i) { //condicional para verificar si el ambos contadores coinciden
					snprintf(fichero, sizeof(fichero), "red%d.txt", adaptadorActual); //combinamos en una cadena 2 cadenas, creando un fichero por cada iteración
					snprintf(nombreAdaptador, sizeof(nombreAdaptador), "adaptador%d.txt", adaptadorActual); //combinamos en una cadena 2 cadenas, creando un fichero por cada iteración
					fp3 = fopen(fichero, "w"); //abrimos el fichero que hemos combinado (red1.txt, red2.txt, etc.) en modo escritura
					if (fp3 == NULL) {
						perror("\nError al abrir el fichero");
						return;
					}
					char* nombre = strchr(buffer, '"'); //buscamos el caracter "
					if (nombre) { //si encuentra el caracter
						nombre++; //avanzamos 1 posición en el buffer
						for (int j = 0; j < strlen(nombre); j++) { //iteramos sobre la longitud de la cadena nombre
							if (nombre[j] == '"') { //condicional para verificar si en la posición de la iteración es igual que el caracter "
								nombre[j] = '\0'; //si se cumple, cambiamos el caracter " por un caracter nulo
							}
						}
						printf("%d - Adaptador: %s \n", i, nombre); //mostramos por pantalla el nº de iteración y el nombre del adaptador
						fprintf(fp2, "Adaptador: %s\n", nombre); //añadimos al fichero "contenido.txt" la información
						fprintf(fp3, "Adaptador: %s\n", nombre); //añadimos al fichero "redX.txt" la información
						fclose(fp3); //cerramos el fichero
						fp3 = fopen(nombreAdaptador, "w"); //abrimos el fichero "adaptadorX.txt" en modo escritura
						if (fp3 == NULL) {
							perror("\nError al abrir el fichero");
							return;
						}
						fputs(nombre, fp3); //añadimos únicamente el nombre del adaptador
						fclose(fp3); //cerramos el fichero
					}
				}
			}
			//condicional que buscará la cadena "DNS" en la línea actual del buffer Y que el adaptadorActual coincida con la iteración
			else if (strstr(buffer, "DNS") != NULL && adaptadorActual == i) {
				char* dns = strchr(buffer, ':'); //busca el caracter ":"
				if (dns) { //si encuentra el caracter específico
					dns += 2; //avanzamos 2 posiciones en el buffer
					fprintf(fp2, "DNS primario:%s", dns); //añadimos al fichero contenido.txt una cadena con la cadena "dns"
					fp3 = fopen(fichero, "a"); //abrimos en modo append el fichero combinado redX.txt
					if (fp3 == NULL) {
						perror("\nError al abrir el fichero");
						return;
					}
					fprintf(fp3, "DNS primario:%s", dns); //añadimos en el fichero la información
					fclose(fp3); //cerramos el fichero
					segundaLinea = 1; //actualizamos variable "segundaLinea" a 1, en la siguiente vuelta del while accederá al primer condicional
				}
			}
		}
	}
	fclose(fp1); //cerramos fichero
	fclose(fp2); //cerramos fichero

	int numAdaptador; //entero para el nº de adaptador que indique el usuario
	char fichero2[20], nombreAdaptador2[20]; //nuevas cadenas para las combinaciones de cadenas
	printf("\nElige un adaptador para modificarlo: ");
	scanf("%d", &numAdaptador);
	snprintf(fichero2, sizeof(fichero2), "red%d.txt", numAdaptador); //combinamos en la cadena fichero2 el redX.txt que indique el usuario
	snprintf(nombreAdaptador2, sizeof(nombreAdaptador2), "adaptador%d.txt", numAdaptador); //combinamos en nombreAdaptador2 el adaptadorX.txt que indique el usuario
	fp1 = fopen(fichero2, "r"); //abrimos el fichero2 redX.txt en modo lectura
	if (fichero2 == NULL) {
		perror("Error al abrir el fichero");
		return;
	}
	printf("\n\nEstas son las DNS actuales del adaptador");
	printf("\n------------------------------------------\n");
	fp4 = fopen("temp.txt", "w");
	if (fp4 == NULL) {
		perror("\nError al abrir el fichero");
		return;
	}
	int primeraLinea = 1; //variable para saltar la primera linea del buffer
	while (fgets(buffer, sizeof(buffer), fp1)) { //leemos cada línea del fichero2 (redX.txt)
		printf("%s", buffer);
		if (primeraLinea) { //verifica si la variable es positiva (1)
			primeraLinea = 0; //actualiza la variable a 0
			continue; //continue para iniciar una iteración nueva del bucle while (se habrá saltado la primera línea)
		}
		char* dato = strchr(buffer, ':'); //buscamos el caracter ":" en el buffer
		if (dato) { //si se encuentra
			dato += 2; //avanzamos 2 posiciones
			fputs(dato, fp4); //añadimos en el "temp.txt" la información
		}
	}
	fclose(fp4); //cerramos fichero
	fclose(fp1); //cerramos fichero

	//con este bucle eliminamos todos los ficheros temporales (redX.txt y adaptadorX.txt) menos el indicado por el usuario
	for (int i = 1; i < contAdaptadores; i++) {
		char fichero3[20], nombreAdaptador3[20];
		snprintf(fichero3, sizeof(fichero3), "red%d.txt", i);
		snprintf(nombreAdaptador3, sizeof(nombreAdaptador3), "adaptador%d.txt", i);
		if (strcmp(fichero3, fichero2) != 0 && strcmp(nombreAdaptador3, nombreAdaptador2) != 0) {
			remove(fichero3);
			remove(nombreAdaptador3);
		}
	}
	fp1 = fopen(nombreAdaptador2, "r"); //abrimos el fichero adaptadorX.txt (indicado por usuario) en modo lectura
	if (fp1 == NULL) {
		perror("\nError al abrir el fichero");
		return;
	}
	while (fgets(buffer, sizeof(buffer), fp1)) { //recorremos cada línea del fichero (solo será 1 con el nombre del adaptador indicado por el usuario)
		buffer[strcspn(buffer, "\n")] = '\0';
		strncpy(nombreRed, buffer, 20); //con strncpy copiamos la lectura del buffer en la cadena "nombreRed", indicamos el tamaño de la cadena
	}
	fclose(fp1); //cerramos fichero
	remove("contenido.txt"); //eliminamos fichero
	remove("dnss.txt"); //eliminamos fichero
	printf("\n");
	printf("\n");
	system("pause");
	system("cls");
}

//función para verificar si las IPs del fichero son accesibles
void pruebasPing() {
	system("cls");
	char ruta[25] = "c:\\ficheros\\DNSips.txt"; //indicamos en una cadena la ruta del fichero DNSips.txt
	FILE* fp1, * fp2, * fp3; //punteros de tipo FILE
	char buffer[200], comando[50]; //cadena para el buffer y combinación de cadenas para crear un comando de sistema

	printf("\n\nContenido del fichero:\n\n");
	fp1 = fopen(ruta, "r"); //abrimos el fichero de la ruta en modo lectura y verificamos si es accesible
	if (fp1 == NULL) {
		perror("\nError al abrir el fichero");
		return;
	}
	while (fgets(buffer, sizeof(buffer), fp1)) { //recorremos cada línea del buffer y la printamos
		printf("%s", buffer);
	}
	rewind(fp1); //ponemos el cursor al inicio del fichero
	printf("\n\nSe va a revisar si las IPs son accesibles.\n\n");
	system("pause");
	while (fgets(buffer, sizeof(buffer), fp1)) { //recorremos nuevamente el fichero
		buffer[strcspn(buffer, "\n")] = '\0';
		snprintf(comando, sizeof(comando), "ping %s -n 2 > pingtemp.txt", buffer); //combinamos cadenas con snprintf y creamos un comando de sistema para lanzar ping
		printf("\nComprobando la IP %s - Espera...", buffer);
		system(comando); //ejecutamos comando de sistema con la cadena combinada anteriormente
		fp2 = fopen("pingtemp.txt", "r"); //abrimos el fichero "pingtemp.txt" en modo lectura
		if (fp2 == NULL) { //verificamos que es accesible
			perror("\nError al abrir el fichero");
			return;
		}
		char linea[6]; //cadena con tamaño asignado (6)
		fseek(fp2, -5, SEEK_END); //muevo el cursor del fichero 5 posiciones atrás desde el final
		fread(linea, 1, 5, fp2); //lee y almacena los 5 últimos caracteres en la cadena linea 
		linea[5] = '\0'; //añade en la quinta posición de la cadena un caracter nulo
		//busca si la cadena "linea" contiene la cadena "ms", si no es nulo (si la contiene) la variable pingCorrecto será true
		int pingCorrecto = strstr(linea, "ms") != NULL;
		fclose(fp2); //cerramos fichero
		if (pingCorrecto) { //condicional para cuando la variable "pingCorrecto" sea true
			fp3 = fopen("temp.txt", "a"); //abrimos el fichero "temp.txt" en modo append
			if (fp3 == NULL) { //verificamos que sea accesible
				perror("\nError al abrir el fichero");
				return;
			}
			fputs(buffer, fp3); //añadimos al fichero el contenido del buffer
			fputs("\n", fp3); //añadimos al fichero un salto de línea
			fclose(fp3); //cerramos fichero
		}
	}
	fclose(fp1); //cerramos fichero
	remove("pingtemp.txt"); //eliminamos fichero
	printf("\n\n");
	//mostramos prints de ejecuciones correctas
	printf("\nRevisión finalizada correctamente.\n");
	printf("\nLas IPs con respuesta positiva se han guardado en el fichero \"temp.txt\"\n\n");
	system("pause");
	system("cls");
}

//función para verificar que IP tiene mejor media
void mediaMS(char* ipMejorMedia) {
	system("cls");
	FILE* fp1, * fp2, * fp3; //punteros de tipo FILE
	char buffer[1024], comando[50], ipAnterior[20]; //cadenas para buffer, combinación de comando y registrar una IP
	int media, mejorMedia = 200, mediaAnterior; //variables enteras para registrar las medias (media actual, mejor media y media anterior)
	fp1 = fopen("temp.txt", "r"); //abrimos el fichero "temp.txt" en modo lectura
	if (fp1 == NULL) { //verificamos que sea accesible
		perror("\nError al abrir el fichero");
		return;
	}
	printf("\n\nSe va a comprobar la velocidad de las DNS que han respondido OK anteriormente y las configuradas actualmente.\n\n");
	system("pause");
	while (fgets(buffer, sizeof(buffer), fp1)) { //recorremos el fichero temp.txt
		buffer[strcspn(buffer, "\n")] = '\0'; //cambiamos los saltos de línea por caracteres nulos
		snprintf(comando, sizeof(comando), "ping %s > mediatemp.txt", buffer); //combinamos cadenas para lanzar pings a las lecturas del buffer
		printf("\nTesteando %s...", buffer);
		system(comando); //ejecuta la cadena combinada anteriormente
		fp2 = fopen("mediatemp.txt", "r"); //abrimos el fichero "mediatemp.txt" en modo lectura
		if (fp2 == NULL) { //verificamos que sea accesible
			perror("\nError al abrir el fichero");
			return;
		}
		char media[3]; //cadena con tamaño 3
		fseek(fp2, -6, SEEK_END); //posicionamos el cursor 6 caracteres hacia atrás desde el final del fichero
		fread(media, 1, 2, fp2); //lee los 2 caracteres desde la posición del cursor y los almacena en la cadena media
		media[2] = '\0'; //actualiza la última posición de la cadena a un caracter nulo
		fp3 = fopen("media.txt", "a"); //abrimos el fichero "media.txt" en modo append
		fprintf(fp3, "%s\n", media); //añadimos en el fichero el contenido de la cadena "media"
		fclose(fp3); //cerramos fichero
		fclose(fp2); //cerramos fichero
	}
	fclose(fp1); //cerramos fichero
	fp1 = fopen("temp.txt", "r"); //abrimos el fichero "temp.txt" en modo lectura
	fp2 = fopen("media.txt", "r"); //abrimos el fichero "media.txt" en modo lectura
	if (fp1 == NULL || fp2 == NULL) { //verificamos si ambos ficheros son accesibles
		perror("\nError al abrir el fichero");
		return;
	}
	printf("\n");
	while (fgets(buffer, sizeof(buffer), fp1)) { //accedemos a cada línea del fichero temp.txt con el buffer
		buffer[strcspn(buffer, "\n")] = '\0'; //cambiamos los saltos de línea por caracteres nulos
		fscanf(fp2, "%d", &media); //buscamos en el fichero "media.txt" un entero
		printf("\nLa media de %s es: %dms", buffer, media); //printamos el contenido del buffer y la media encontrada
		if (media < mejorMedia) { //condicional que verifica si la media actual es menor que la variable mejorMedia
			mediaAnterior = mejorMedia; //actualiza la mediaAnterior a la mejorMedia
			strncpy(ipAnterior, ipMejorMedia, 20); //copiamos en ipAnterior la cadena ipMejorMedia indicando su tamaño
			mejorMedia = media; //actualizamos la mejorMedia con la lectura de media actual
			strncpy(ipMejorMedia, buffer, 20); //copiamos en la cadena ipMejorMedia la lectura del buffer indicando el tamaño
		}
		else if (media < mediaAnterior) { //condicional para verificar si la media actual es menor que la mediaAnterior
			mediaAnterior = media; //si se cumple, actualizamos la mediaAnterior a la media actual
			strncpy(ipAnterior, buffer, 20); //copiamos en la cadena ipAnterio el buffer actual indicando el tamaño
		}
	}
	fclose(fp1); //cerramos fichero
	fclose(fp2); //cerramos fichero
	printf("\n\n");

	//printamos la cadena con la IP que ha obtenido la mejor media (ipMejorMedia) y su media (mejorMedia)
	printf("\nLa mejor DNS es %s con una media de %dms", ipMejorMedia, mejorMedia);
	//printamos la cadena con la IP que ha obtenido la segunda mejor media (ipAnterior) y su media (mediaAnterior)
	printf("\nLa segunda mejor es %s con %dms", ipAnterior, mediaAnterior);

	char nuevoComando1[50], nuevoComando2[50]; //cadenas para combinar nuevos comandos
	int saltarLinea1 = 1, saltarLinea2 = 1, contadorSaltos1 = 0, contadorSaltos2 = 0; //enteros para saltar líneas de de un buffer y contadores de saltos
	if (mejorMedia == mediaAnterior && ipMejorMedia != ipAnterior) { //condicional para verificar si la mejorMedia es igual a la mediaAnterio y si las IPs son diferentes
		printf("\n\nLas medias son iguales, se procede a realizar Tracert para verificar saltos.\n\n");
		system("pause");
		system("cls");
		printf("\n");
		printf("\nRealizando TRACERT a la IP %s...", ipMejorMedia);
		/* combinamos en la cadena "nuevoComando1" para lanzar un tracert
		* -d -> evita resolver el nombre de host de las IPs
		* -w 500 -> tiempo en milisegundos para el timeout de cada prueba (4000 por defecto) */
		snprintf(nuevoComando1, sizeof(nuevoComando1), "tracert -d -w 500 %s > tr1.txt", ipMejorMedia);
		nuevoComando1[strcspn(nuevoComando1, "\n")] = '\0'; //cambiamos los saltos de línea por caracteres nulos
		system(nuevoComando1); //ejecutamos la combinación anterior como comando del sistema
		printf("\nRealizando TRACERT a la IP %s...", ipAnterior);
		snprintf(nuevoComando2, sizeof(nuevoComando2), "tracert -d -w 500 %s > tr2.txt", ipAnterior); //mismo proceso que anterior para la segunda prueba
		nuevoComando2[strcspn(nuevoComando2, "\n")] = '\0';
		system(nuevoComando2);
		fp1 = fopen("tr1.txt", "r"); //abrimos el fichero tr1.txt en modo lectura
		if (fp1 == NULL) {
			perror("\nError al abrir el fichero");
			return;
		}
		while (fgets(buffer, sizeof(buffer), fp1)) { //accedemos a cada línea del fichero
			if (saltarLinea1) { //condicional para saltar la primera línea
				saltarLinea1 = 0; //actualiza la variable a 0
				continue; //deja de leer y vuelve al inicio del bucle while
			}
			if (saltarLinea2) { //condicional para saltar la segunda línea
				saltarLinea2 = 0; //actualiza la variable a 0
				continue; //deja de leer y vuelve al inicio del bucle while
			}
			contadorSaltos1++; //contador por cada vuelta en la lectura del buffer
		}
		fclose(fp1); //cerramos fichero
		saltarLinea1 = 1; //actualizamos variable nuevamente a 1
		saltarLinea2 = 1; //actualizamos variable nuevamente a 1
		fp1 = fopen("tr2.txt", "r"); //abrimos el fichero "tr2.txt" en modo lectura
		if (fp1 == NULL) {
			perror("\nError al abrir el fichero");
			return;
		}
		//realizamos mismo proceso que anterior para el fichero tr2.txt
		while (fgets(buffer, sizeof(buffer), fp1)) {
			if (saltarLinea1) {
				saltarLinea1 = 0;
				continue;
			}
			if (saltarLinea2) {
				saltarLinea2 = 0;
				continue;
			}
			contadorSaltos2++;
		}
		fclose(fp1);
		contadorSaltos1 -= 3; //al contador le restamos 3 (son la 3 últimas líneas del fichero de la prueba)
		contadorSaltos2 -= 3; //al contador le restamos 3 (son la 3 últimas líneas del fichero de la prueba)
		//mostramos los saltos de cada IP
		printf("\n\nLa IP %s ha tenido %d saltos\n", ipMejorMedia, contadorSaltos1);
		printf("La IP %s ha tenido %d saltos\n", ipAnterior, contadorSaltos2);
		if (contadorSaltos1 > contadorSaltos2) { //condicional para verificar si el contador1 es mayor que el contador2
			ipMejorMedia = ipAnterior; //si el contador es mayor actualizamos la cadena "ipMejorMedia" con el contenido de "ipAnterior"
			printf("\nLa IP más rápida es %s con %d saltos.", ipMejorMedia, contadorSaltos2); //mostramos print con la IP y sus saltos
		}
		else {
			printf("\nLa IP más rápida es %s con %d saltos.", ipMejorMedia, contadorSaltos1); //mostramos printf con la IP y sus saltos
		}
	}
	remove("tr1.txt"); //eliminamos fichero
	remove("tr2.txt"); //eliminamos fichero
	remove("media.txt"); //eliminamos fichero
	printf("\n\n");
	system("pause");
	system("cls");
}

//función para configurar el adaptador de red con la IP con mejor media
void configAdaptador(char* ipMejorMedia, char* nombreRed) {
	char comando[100]; //cadena para registrar un comando
	system("cls");
	//printamos información con los datos que se van a configurar
	printf("\nLa configuración será la siguiente:\n");
	printf("\nAdaptador: %s", nombreRed);
	printf("\nDNS: %s\n\n", ipMejorMedia);
	system("pause");
	//combinamos cadenas para generar un comando de sistema que modificará la DNS primaria del adaptador
	//se le pasa el nombre del adaptador que indicó el usuario (nombreRed) y la IP con la mejor media (ipMejorMedia)
	snprintf(comando, sizeof(comando), "netsh interface ip set dnsserver name=\"%s\" static %s primary", nombreRed, ipMejorMedia);
	system(comando); //lanzamos comando
	printf("\n\nAdaptador configurado correctamente.");
	printf("\n\n");
	system("pause");
	system("cls");
}