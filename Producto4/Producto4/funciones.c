
//fichero para desarrollar las funciones

#define _CRT_SECURE_NO_WARNINGS
#include "funciones.h"

//funci�n que muestra unos printf
void bienvenida() {
	printf("\n***************************************************");
	printf("\n**                                               **");
	printf("\n**                Producto 4                     **");
	printf("\n**  Programa comandos personalizados para el SO  **");
	printf("\n**                                               **");
	printf("\n***************************************************");
}

//funci�n que muestra diferentes opciones
void menuInicio() {
	printf("\n");
	printf("\n1. Mostrar adaptadores de red");
	printf("\n2. Probar adaptador seleccionado");
	printf("\n3. Mostrar informaci�n de las pruebas realizadas");
	printf("\n4. Exportar informaci�n a fichero XML");

	printf("\n0. Salir");
	printf("\n\nElige una opci�n (1,2,3,4 o 0): ");
}

//funci�n para obtener los datos de un adaptador seleccionado
void adaptadoresRed(char* nombreRed, char* ip, char* mascaraRed, char* puertaEnlace, char* dns1) {
	FILE* fp1, * fp2; //punteros de tipo FILE
	char buffer[200], fichero[20]; //cadenas para lectura de buffer y combinaci�n de cadenas
	int contRedes = 0; //contador

	system("cls"); //limpiamos pantalla
	printf("\n\nLista de adaptadores encontrados:\n");
	system("ipconfig /all > config.txt"); //ejecutamos comando del sistema y lo guardamos en fichero TXT

	fp1 = fopen("config.txt", "r"); //abrimos el fichero generado en modo lectura
	if (fp1 == NULL) { //verificamos que se accede correctamente al fichero
		perror("Error al abrir el fichero");
		return;
	}
	//bucle while para recorrer cada l�nea del fichero con fgets, cuando haya coincidencia con la palabra "Descrip" aumentar� el contador y printaremos informaci�n
	while (fgets(buffer, sizeof(buffer), fp1)) {
		if (strstr(buffer, "Descrip") != NULL) {
			char* nombre = strchr(buffer, ':');
			if (nombre) {
				nombre += 2;
				contRedes++;
				printf("%d - %s", contRedes, nombre);
			}
		}
	}
	rewind(fp1); //ubicamos el cursor al inicio del fichero (config.txt)
	for (int i = 1; i <= contRedes; i++) { //bucle for para iterar la cantidad de adaptadores encontrados (contador)
		rewind(fp1); //ubicamos el cursor al inicio del fichero
		int adaptadorActual = 0; //declaramos nuevo contador para referenciar la iteraci�n actual
		while (fgets(buffer, sizeof(buffer), fp1)) { //bucle para recorrer las l�neas del fichero (config.txt)
			if (strstr(buffer, "Descrip") != NULL) { //condicional que se acceder� cuando encuentre la cadena "Descrip"
				adaptadorActual++; //aumentamos la iteraci�n actual
				if (adaptadorActual == i) { //comparamos con un condicional si la iteraci�n actual es igual que la iteraci�n del contador de adaptadores
					snprintf(fichero, sizeof(fichero), "red%d.txt", adaptadorActual); //combinamos cadenas para generar una cadena con la iteraci�n (red1.txt, red2.txt, etc.)
					fp2 = fopen(fichero, "w"); //abrimos un fichero con la cadena genearda anteriormente en modo escritura
					if (fp2 == NULL) { //verificamos que se accede correctamente al fichero
						perror("Error al abrir el fichero");
						return;
					}
					char* nombre = strchr(buffer, ':'); //con un puntero ubicamos el caracter ':'
					if (nombre) { //si lo encuentra avanzaremos 2 posiciones el puntero y a�adiremos el contenido de la cadena al fichero
						nombre += 2;
						fprintf(fp2, "%s", nombre);
						fclose(fp2); //cerramos fichero
					}
				}
			}
			//utilizando condicionales verificaremos cada una de las cadenas necesarias (IPv4, subred, Puerta, DNS) y verificamos que la iteraci�n actual coincida con el contador de red
			//siguiendo el mismo proceso que el anterior, iremos guardando en el fichero (redX.txt) los par�metros necesarios
			else if (strstr(buffer, "IPv4") != NULL && adaptadorActual == i) {
				char* ipv4 = strchr(buffer, ':');
				if (ipv4) {
					ipv4 += 2;
					for (int i = 0; i < strlen(ipv4); i++) {
						if (ipv4[i] == '(') {
							ipv4[i] = '\0';
						}
					}
					fp2 = fopen(fichero, "a");
					if (fp2 == NULL) {
						perror("Error al abrir el fichero");
						return;
					}
					fprintf(fp2, "%s\n", ipv4);
					fclose(fp2);
				}
			}
			else if (strstr(buffer, "subred") != NULL && adaptadorActual == i) {
				char* subred = strchr(buffer, ':');
				if (subred) {
					subred += 2;
					fp2 = fopen(fichero, "a");
					if (fp2 == NULL) {
						perror("Error al abrir el fichero");
						return;
					}
					fprintf(fp2, "%s", subred);
					fclose(fp2);
				}
			}
			else if (strstr(buffer, "Puerta") != NULL && adaptadorActual == i) {
				char* puerta = strchr(buffer, ':');
				if (puerta) {
					puerta += 2;
					fp2 = fopen(fichero, "a");
					if (fp2 == NULL) {
						perror("Error al abrir el fichero");
						return;
					}
					fprintf(fp2, "%s", puerta);
					fclose(fp2);
				}
			}
			else if (strstr(buffer, "DNS") != NULL && adaptadorActual == i) {
				char* dnsprim = strchr(buffer, ':');
				if (dnsprim) {
					dnsprim += 2;
					fp2 = fopen(fichero, "a");
					if (fp2 == NULL) {
						perror("Error al abrir el fichero");
						return;
					}
					fprintf(fp2, "%s", dnsprim);
					fclose(fp2);
				}
			}
		}
	}
	fclose(fp1); //cerramos fichero (config.txt)
	int numAdaptador; //declaramos variable para la elecci�n del adaptador
	char fichero2[20]; //cadena para nueva combinaci�n de cadenas
	printf("\n\nElige un adaptador: "); //solicitamos al usuario que elija adaptador
	scanf("%d", &numAdaptador); //guardamos la elecci�n en la variable numAdaptador
	snprintf(fichero2, sizeof(fichero2), "red%d.txt", numAdaptador); //combinamos cadenas para genarar (red<numAdaptador>.txt) red1.txt, red2.txt, etc.
	fp1 = fopen(fichero2, "r"); //abrimos el fichero con la cadena combinada anteriormente en modo lectura
	if (fp1 == NULL) { //verificamos que se accede correctamente
		perror("Error al abrir el fichero");
		return;
	}
	int contLineas = 0; //contador de l�neas (para lectura de los ficheros redX.txt)
	while (fgets(buffer, sizeof(buffer), fp1)) { //bucle while para acceder a cada l�nea del fichero redX.txt
		buffer[strcspn(buffer, "\n")] = '\0'; //cambiamos los saltos de l�nea por caracteres nulos
		switch (contLineas) { //switch para cada una de las l�neas de los ficheros redX.txt
		case 0: //ser� la primera l�nea del fichero redX.txt, copiaremos el contenido del buffer al puntero nombreRed
			strncpy(nombreRed, buffer, 50);
			nombreRed[49] = '\0'; //a�adimos caracter nulo en la �ltima posici�n de la cadena
			break;
		case 1: //ser� la segunda l�nea del fichero redX.txt, copiaremos el contenido del buffer al puntero ip
			strncpy(ip, buffer, 20);
			ip[19] = '\0'; //a�adimos caracter nulo en la �ltima posici�n de la cadena
			break;
		case 2: //ser� la tercera l�nea del fichero redX.txt, copiaremos el contenido del buffer al puntero mascaraRed
			strncpy(mascaraRed, buffer, 20);
			mascaraRed[19] = '\0'; //a�adimos caracter nulo en la �ltima posici�n de la cadena
			break;
		case 3: //ser� la cuarta l�nea del fichero redX.txt, copiaremos el contenido del buffer al puntero puertaEnlace
			strncpy(puertaEnlace, buffer, 20);
			puertaEnlace[19] = '\0'; //a�adimos caracter nulo en la �ltima posici�n de la cadena
			break;
		case 4: //ser� la quinta l�nea del fichero redX.txt, copiaremos el contenido del buffer al puntero dns1
			strncpy(dns1, buffer, 20);
			dns1[19] = '\0'; //a�adimos caracter nulo en la �ltima posici�n de la cadena
			break;
		default:
			break;
		}
		contLineas++; //por cada l�nea que se accede con el buffer aumentaremos el contador, de esta manera iremos accediendo a cada caso
	}
	if (contLineas < 5) { //condicional para indicar que no se han obtenido todos los datos (5 par�metros necesarios)
		printf("\nAdvertencia: El adaptador seleccionado no contiene todos los datos necesarios");
	}
	fclose(fp1); //cerramos fichero
	for (int i = 1; i <= contRedes; i++) { //bucle for para eliminar los ficheros temporales geneardos
		char fichero3[20];
		snprintf(fichero3, sizeof(fichero3), "red%d.txt", i);
		remove(fichero3);
	}
	//printamos la informaci�n por pantalla
	printf("\n\n");
	printf("Datos del adaptador seleccionado\n");
	printf("--------------------------------\n");
	printf("Nombre: %s\n", nombreRed);
	printf("IP: %s\n", ip);
	printf("M�scara de red: %s\n", mascaraRed);
	printf("Puerta de enlace: %s\n", puertaEnlace);
	printf("DNS primaria: %s\n", dns1);
	printf("\n\n");
	system("pause");
	system("cls");
	remove("config.txt");
}

//funci�n para testear la DNS del adaptador seleccionado
void testDNS(char* dns1, char* mediaMs, char* saltos) {
	FILE* fp1; //puntero de tipo FILE
	char comando[50], comando2[50], buffer[200]; //cadenas para combinaci�n de cadenas y buffer de acceso a ficheros
	int saltarLinea1 = 1, saltarLinea2 = 1, contSaltos = 0; //contador y variables para saltar l�neas
	system("cls");
	printf("\n\n");
	printf("Se van a realizar pruebas PING y TRACERT para verificar la IP %s\n\n", dns1);
	system("pause");
	printf("\n\nRealizando PING a %s...", dns1);
	snprintf(comando, sizeof(comando), "ping %s > ping.txt", dns1); //combinamos cadenas para obtener "ping (dns1) > ping.txt"
	system(comando); //ejecutamos comando del sistema (combinaci�n de cadenas generada)

	fp1 = fopen("ping.txt", "r"); //abrimos el fichero ping.txt en modo lectura
	if (fp1 == NULL) { //verificamos si se accede correctamente al fichero
		perror("Error al abrir el fichero");
		return;
	}
	char media[3]; //cadena con tama�o 3
	fseek(fp1, -6, SEEK_END); //posicionamos el cursor 6 caracteres hacia atr�s desde el final del fichero
	fread(media, 1, 2, fp1); //lee los 2 caracteres desde la posici�n del cursor y los almacena en la cadena media
	media[2] = '\0'; //actualiza la �ltima posici�n de la cadena a un caracter nulo
	fclose(fp1); //cerramos fichero
	strncpy(mediaMs, media, 3); //copiamos el contenido de la cadena media al puntero mediaMs
	mediaMs[2] = '\0'; //a�adimos un caracter nulo en la �ltima posici�n de la cadena

	printf("\n");
	printf("La media de respuesta de la IP %s es de %sms\n", dns1, mediaMs); //printamos informaci�n

	printf("\n\nRealizando TRACERT a %s...", dns1);
	snprintf(comando2, sizeof(comando2), "tracert -d -w 500 %s > tracert.txt", dns1); //combinamos cadenas para generar un comando tracert con "dns1"
	system(comando2); //ejecutamos cadena combinada anteriormente
	fp1 = fopen("tracert.txt", "r"); //abrimos el fichero tracert.txt en modo lectura
	if (fp1 == NULL) { //verificamos si se accede correctamente al fichero
		perror("Error al abrir el fichero");
		return;
	}
	//bucle while para acceder con fgets a cada l�nea del fichero tracert.txt
	while (fgets(buffer, sizeof(buffer), fp1)) {
		if (saltarLinea1) { //condicional para saltar la primera l�nea del fichero
			saltarLinea1 = 0;
			continue;
		}
		if (saltarLinea2) { //condicional para saltar la segunda l�nea del fichero
			saltarLinea2 = 0;
			continue;
		}
		contSaltos++; //aumentamos contador por cada l�nea accedida del buffer
	}
	fclose(fp1); //cerramos fichero
	contSaltos -= 3; //restamos 3 (son las 3 �ltimas l�neas del fichero, no relevantes)
	char saltosCadena[3]; //cadena para "convertir" la variable "contSaltos" en cadena
	snprintf(saltosCadena, sizeof(saltosCadena), "%d", contSaltos); //combinamos cadenas y a�adimos los saltos
	//copiamos la cadena saltosCadena al puntero "saltos" (si lo hac�a directamente con un puntero "int" me daba errores)
	strncpy(saltos, saltosCadena, 3);
	saltos[2] = '\0'; //a�adimos caracter nulo a la �ltima posici�n de la cadena

	printf("\n");
	printf("La IP %s ha obtenido %s saltos\n", dns1, saltos); //printamos informaci�n
	printf("\n\n");
	remove("ping.txt"); //eliminamos ficheros temporales
	remove("tracert.txt"); //eliminamos ficheros temporales
	system("pause");
	system("cls");
}

//funci�n para mostrar datos despu�s de selecci�n y pruebas
void mostrarInfo(char* nombreRed, char* ip, char* mascaraRed, char* puertaEnlace, char* dns1, char* mediaMs, char* saltos) {
	system("cls");
	printf("\n\n\n");
	//printamos los datos obtenidos en funciones anteriores indicando cada puntero
	printf("Datos obtenidos\n");
	printf("---------------\n");
	printf("Adaptador: %s\n", nombreRed);
	printf("IP: %s\n", ip);
	printf("M�scara de red: %s\n", mascaraRed);
	printf("Puerta de enlace: %s\n", puertaEnlace);
	printf("DNS primaria: %s\n", dns1);
	printf("Media obtenida: %sms\n", mediaMs);
	printf("N�mero de saltos: %s\n", saltos);
	printf("\n");
	system("pause");
	system("cls");
}

//funci�n para generar fichero XML con datos obtenidos
void generarXML(char* nombreRed, char* ip, char* mascaraRed, char* puertaEnlace, char* dns1, char* mediaMs, char* saltos) {
	FILE* fp; //puntero de tipo FILE
	system("cls");
	printf("\n\n");
	//printamos la informaci�n que se va a exportar al fichero XML
	printf("Se va a exportar la siguiente informaci�n en un fichero XML:\n\n");
	printf("Adaptador: %s\n", nombreRed);
	printf("IP: %s\n", ip);
	printf("M�scara de red: %s\n", mascaraRed);
	printf("Puerta de enlace: %s\n", puertaEnlace);
	printf("DNS primaria: %s\n", dns1);
	printf("Media obtenida: %sms\n", mediaMs);
	printf("N�mero de saltos: %s\n", saltos);
	printf("\n\n");
	system("pause");
	fp = fopen("adaptador.xml", "w"); //abrimos un fichero XML en modo escritura
	if (fp == NULL) { //verificamos que se acceda correctamente al fichero
		perror("Error al abrir el fichero");
		return;
	}
	//a�adimos con "fprintf" cada l�nea con su correcto etiquetado y como contenido el puntero
	fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"); //l�nea para indicar el tipo de "encoding", debe ser UTF-8 para un correcto visionado en el navegador
	fprintf(fp, "<adaptador>\n");
	fprintf(fp, "<nombre>\n");
	fprintf(fp, "%s\n", nombreRed);
	fprintf(fp, "</nombre>\n");
	fprintf(fp, "<ip>\n");
	fprintf(fp, "%s\n", ip);
	fprintf(fp, "</ip>\n");
	fprintf(fp, "<mascara>\n");
	fprintf(fp, "%s\n", mascaraRed);
	fprintf(fp, "</mascara>\n");
	fprintf(fp, "<puerta>\n");
	fprintf(fp, "%s\n", puertaEnlace);
	fprintf(fp, "</puerta>\n");
	fprintf(fp, "<dns>\n");
	fprintf(fp, "%s\n", dns1);
	fprintf(fp, "</dns>\n");
	fprintf(fp, "<media>\n");
	fprintf(fp, "%s\n", mediaMs);
	fprintf(fp, "</media>\n");
	fprintf(fp, "<saltos>\n");
	fprintf(fp, "%s\n", saltos);
	fprintf(fp, "</saltos>\n");
	fprintf(fp, "</adaptador>\n");
	fclose(fp); //cerramos fichero
	printf("\n\n");
	printf("Fichero XML generado correctamente.\n\n");
	system("pause");
	system("cls");
}