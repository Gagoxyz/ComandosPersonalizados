
//fichero para declarar las funciones

#define _CRT_SECURE_NO_WARNINGS //definimos una constante para que no muestre warnings
#include "funciones.h"

//función que muestra unos printf
void bienvenida() {
	printf("\n***************************************************");
	printf("\n**                                               **");
	printf("\n**                Producto 2                     **");
	printf("\n**  Programa comandos personalizados para el SO  **");
	printf("\n**                                               **");
	printf("\n***************************************************");
}

//función que muestra diferentes opciones
void menuInicio() {
	printf("\n");
	printf("\n1. Insertar fecha y hora actual en el documento Producto2");
	printf("\n2. Realizar PING a las direcciones de un fichero");
	printf("\n3. Mostrar adaptadores de red");
	printf("\n4. Mostrar contenido del fichero producto2.txt");
	printf("\n5. Mostrar contenido del fichero adaptador.txt");
	printf("\n0. Salir");
	printf("\n\nElige una opción (1,2,3,4,5 o 0): ");
}

//función para insertar fecha y hora en un documento de texto
void insertarFechaHora() {
	system("cls"); //limpiamos pantalla
	FILE* fp; //asignamos un puntero de tipo FILE a "fp"
	fp = fopen("producto2.txt", "a"); //abro el fichero (si no existe se crea) y añado un salto de línea
	if (fp == NULL) { //añado un condicional por si hubiera algún fallo al abrir el fichero
		perror("\nError al abrir el fichero.");
		return;
	}
	fputs("\n", fp);
	fclose(fp); //cierro el fichero

	printf("\n");
	printf("Fecha: ");
	system("date /t");
	system("date /t >> producto2.txt"); //muestro en pantalla un printf con la fecha, seguidamente ese mismo comando lo añado a un fichero txt
	printf("Hora: ");
	system("time /t");
	system("time /t >> producto2.txt"); //muestro en pantalla un printf con la hora, seguidamente ese mismo comando lo añado a un fichero txt

	printf("Datos añadidos al fichero correctamente.\n\n");
	system("pause"); //agrego una pausa para que se pueda leer la pantalla antes de acceder nuevamente al menuInicio
	system("cls"); //limpio pantalla antes de mostrar nuevamente el menuInicio
}

//función para mostrar fichero ips.txt, lanzar pings y guardar resultados positivos
void gestionIPs() {
	system("cls"); //limpio pantalla
	char rutaFichero[100]; //cadena donde se almacenará la ruta indicada por el usuario
	char temp[100]; //cadena para almacenar buffer de ficheros temporalmente
	int opcionIps, opcionMenuIp = 1; //variables enteras para elecciones de usuario


	printf("Indica la ruta del fichero que contiene las IPs\n");
	scanf("%s", rutaFichero); //se solicita al usuario la ruta del fichero ips.txt y se almacena en la cadena rutaFichero
	rutaFichero[strcspn(rutaFichero, "\n")] = '\0'; //con strcspn eliminamos los saltos de línea "\n" y se cambian por caracteres nulos "\0"

	//con strcmp comparamos cadenas (devuelve 0 si son iguales, si no son iguales devuelve un valor diferente a 0)
	//comparamos la cadena rutaFichero con la cadena de la ruta real, si es igual (0) accede al condicional
	//si es diferente aparecería el printf final con la dirección
	if (strcmp(rutaFichero, "c:\\ficheros\\ips.txt") == 0) {
		while (opcionMenuIp) {
			printf("\n\n");
			printf("1. Mostrar contenido del fichero IPs.txt\n");
			printf("2. Realizar PING a las IPs\n");
			printf("0. Atrás\n");

			printf("\nElige una opción (1,2 o 0): ");
			scanf("%d", &opcionIps);

			//puntero de tipo FILE a "fp", iniciamos abriendo la cadena rutaFichero (contiene la ruta) en modo lectura "r"
			FILE* fp = fopen(rutaFichero, "r");
			if (fp == NULL) {
				perror("\nError al abrir el fichero.");
				return;
			}

			//inicio un switch 2 casos, mostrar el contenido del fichero y lanzar ping a las IPs del fichero
			switch (opcionIps) {
			case 1:
				if (fgets(temp, sizeof(temp), fp) == NULL) {
					printf("\nFichero sin contenido.");
					return;
				}
				rewind(fp); //posiciono el cursor al principio del fichero
				printf("\nContenido del fichero:\n");
				//muestra el contenido del fichero que apunta fp, con el bucle while accediendo y metiendo en buffer
				while (fgets(temp, sizeof(temp), fp)) {
					temp[strcspn(temp, "\n")] = '\0';
					printf("IP: %s\n", temp);
				}
				break;
			case 2:
				rewind(fp); //posiciono el cursor al principio del fichero
				if (fgets(temp, sizeof(temp), fp) == NULL) {
					printf("\nFichero sin contenido.");
					return;
				}
				rewind(fp); //posiciono el cursor al principio del fichero
				while (fgets(temp, sizeof(temp), fp)) {
					temp[strcspn(temp, "\n")] = '\0';
					char comando[1024]; //cadena para combinar cadenas
					//snprintf combinamos cadenas según el tamaño indicado, cadena1 ping con parámetros añadido a txt, cadena2 contiene la IP
					snprintf(comando, sizeof(comando), "ping %s -n 2 > ficheropings.txt", temp);
					printf("\nRealizando ping a la IP: %s - Espera...", temp);
					system(comando); //ejecutamos en consola la cadena formada anteriormente

					//puntero tipo FILE a pings, iniciando fichero en modo lectura "r"
					FILE* pings = fopen("ficheropings.txt", "r");
					if (pings == NULL) {
						perror("\nError al abrir el fichero.");
						return;
					}
					char linea[6]; //cadena con tamaño asignado (6)
					fseek(pings, -5, SEEK_END); //muevo el cursor del fichero 5 posiciones atrás desde el final
					fread(linea, 1, 5, pings); //lee y almacena los 5 últimos caracteres en la cadena linea 
					linea[5] = '\0'; //añade en la quinta posición de la cadena un caracter nulo
					//busca si la cadena "linea" contiene la cadena "ms", si no es nulo (si la contiene) la variable pingCorrecto será true
					int pingCorrecto = strstr(linea, "ms") != NULL;
					fclose(pings); //cerramos fichero

					//si pingCorrecto es true mostramos un printf con la IP indicando CORRECTO
					//puntero tipo FILE a "fp", abriendo el fichero producto2.txt en modo append "a", situando el cursor al final del fichero
					//con fputs añadimos la cadena que hay en "temp" al puntero fp (apunta al fichero producto2.txt)
					//seguidamente añadimos una cadena y cerramos el fichero
					if (pingCorrecto) {
						printf("\nPing a la dirección %s: CORRECTO.\n", temp);
						FILE* fp = fopen("producto2.txt", "a");
						if (fp == NULL) {
							perror("Error al abrir el fichero.");
							return;
						}
						fputs(temp, fp);
						fputs(" responde correctamente.\n", fp);
						fclose(fp);
					}
					//si pingCorrecto es false, mostramos un printf con la IP indicando INCORRECTO
					else {
						printf("\nPing a la dirección %s: INCORRECTO.\n", temp);
					}
				}

				printf("\n\nPruebas PING finalizadas.\n");
				printf("Se han añadido al documento Producto2\n\n");
				break;
			case 0:
				system("cls");
				opcionMenuIp = 0;
				break;
			default:
				printf("\nOpción incorrecta.\n");
				break;
			}
			fclose(fp);
		}
	}
	//printf que se muestra al indicar una ruta de fichero incorrecta
	else {
		printf("\nRuta del fichero incorrecta. La ruta es >> c:\\ficheros\\ips.txt \n");
	}
}

//función que muestra el contenido del fichero producto2.txt
void mostrarFicheroP2() {
	system("cls"); //limpio pantalla
	FILE* fp = fopen("producto2.txt", "r"); //puntero tipo FILE que se inicia leyendo ("r") el fichero producto2.txt
	if (fp == NULL) {
		perror("Error al abrir el fichero.");
		return;
	}
	char buffer[1024]; //cadena de caracteres de tamaño 1024, lo usaremos de buffer

	//bucle while para mostrar el contenido del fichero abierto (está en el puntero fp)
	while (fgets(buffer, sizeof(buffer), fp) != NULL) { //con fgets accedemos al puntero y almacenamos línea tras línea su contenido en la cadena buffer
		printf("%s", buffer); //vamos printando cada línea que se almacena en la cadena buffer
	}
	fclose(fp); //cerramos el fichero

	printf("\n");
	system("pause"); //pause para poder leer pantalla hasta pulsar tecla
	system("cls"); //limpio pantalla antes de mostrar nuevamente menuInicio
}

//función que muestra, registra y guarda en un fichero el adaptador seleccionado
void adaptadorRed() {
	system("cls"); //limpio pantalla
	FILE* fmalo; //puntero de tipo FILE llamado "fmalo"
	char contenido[400]; //cadena de tamañao 400
	char ficheros[20]; //cadena de tamaño 20
	int contRedes = 1, numAdaptador; //variables enteras, una iniciada en 0 y otra sin iniciar

	//eliminamos el fichero "ipconfigall.txt" si existe
	remove("ipconfigall.txt");
	//lanzamos un ipconfig /all y lo metemos en un fichero llamado ipconfigall.txt
	system("ipconfig /all > ipconfigall.txt");

	//abrimos el fichero ipconfigall en modo lectura "r"
	fmalo = fopen("ipconfigall.txt", "r");
	if (fmalo == NULL) {
		perror("Error al abrir el fichero.");
		return;
	}
	printf("Adaptadores encontrados:\n\n");
	//accedemos al contenido del fichero que apunta "fmalo" y lo vamos metiendo en un buffer "contenido"
	//si encuentra una cadena específica accedemos a un condicional
	//puntero tipo caracter que verifica la primera ocurrencia de ese caracter, estando en la línea donde se encontró la cadena "Descrip"
	//si encuentra un caracter igual a ':' accede al condicional, avanzando una posición el puntero "nombre"
	//printamos el entero "contRedes" sumándole 1 (al iniciar está en 0) y el contenido del nombre hasta final de línea
	//aumentamos contRedes en 1
	while (fgets(contenido, sizeof(contenido), fmalo)) {
		if (strstr(contenido, "Descrip") != NULL) {
			char* nombre = strchr(contenido, ':');
			if (nombre) {
				nombre++;
				printf("%d -%s", contRedes, nombre);
				contRedes++;
			}
		}
	}
	rewind(fmalo); //muevo el cursor al inicio del fichero que apunta "fmalo"

	//bucle para iterar sobre el entero "contRedes", realiza varias acciones por cada iteración
	for (int i = 0; i < contRedes; i++) {
		//mete en la cadena "ficheros" la combinación de la cadena "red%d.txt" con el número de la iteración (i)
		snprintf(ficheros, sizeof(ficheros), "red%d.txt", i);
		//puntero tipo FILE a ficheroNuevo, al iniciarlo abrimos "ficheros" (cadena de texto creada anteriormente) en modo escritura "w"
		FILE* ficheroNuevo = fopen(ficheros, "w");
		if (ficheroNuevo == NULL) {
			perror("Error al abrir el fichero.");
			return;
		}
		//mismo proceso que el anterior, si todo se cumple utilizamos "fprintf" para añadir al "ficheroNuevo" una cadena de texto
		while (fgets(contenido, sizeof(contenido), fmalo)) {
			if (strstr(contenido, "Descrip") != NULL) {
				char* nombre = strchr(contenido, ':');
				if (nombre) {
					nombre += 2;
					fprintf(ficheroNuevo, "Nombre del adaptador: %s", nombre);
				}
			}
			//volvemos a revisar si encuentra la cadena "IPv4" y hacemos el mismo proceso
			else if (strstr(contenido, "IPv4") != NULL) {
				char* ipv4_info = strchr(contenido, ':');
				if (ipv4_info) {
					ipv4_info += 2;
					for (int i = 0; i < strlen(ipv4_info); i++) {
						if (ipv4_info[i] == '(') {
							ipv4_info[i] = '\0';
						}
					}
					fprintf(ficheroNuevo, "IPv4: %s\n", ipv4_info);
				}
			}
			//volvemos a revisar si encuentra la cadena "subred" y hacemos el mismo proceso
			else if (strstr(contenido, "subred") != NULL) {
				char* subred_info = strchr(contenido, ':');
				if (subred_info) {
					subred_info += 2;
					fprintf(ficheroNuevo, "Mascara de subred: %s", subred_info);
				}
			}
			//volvemos a revisar si encuentra la cadena "Puerta" y hacemos el mismo proceso
			else if (strstr(contenido, "Puerta") != NULL) {
				char* puerta_info = strchr(contenido, ':');
				if (puerta_info) {
					puerta_info += 2;
					fprintf(ficheroNuevo, "Puerta de enlace: %s", puerta_info);
				}
			}
			//verificamos si la línea actual contiene la cadena "Adaptador" y si no contiene la cadena "Descrip"
			//de esta forma sabremos que estamos de nuevo en el inicio del fichero, por ende una nueva iteración
			if (strstr(contenido, "Adaptador") != NULL && strstr(contenido, "Descrip") == NULL) {
				break;
			}
		}
		fclose(ficheroNuevo); //cerramos "ficheroNuevo"
	}
	fclose(fmalo); //cerramos "fmalo"

	//solicitamos al usuario que indique el número de adaptador que quiere mostrar, se guardará en "numAdaptador"
	printf("\n\nIndica el número para mostrar datos del adaptador: ");
	scanf("%d", &numAdaptador);

	char leerAdaptador[50]; //cadena de tamaño 50, hará de buffer
	char ficheroAdaptador[50]; //cadena de tamaño 50, guardará el nombre del fichero txt

	//combinamos con snprintf las cadenas "red%d.txt" y el numAdaptador, se guardará en "ficheroAdaptador"
	snprintf(ficheroAdaptador, sizeof(ficheroAdaptador), "red%d.txt", numAdaptador);
	//puntero tipo FILE apuntando a "adaptadorElegido", lo iniciamos abriendo el fichero que contiene "ficheroAdaptador" en modo lectura "r"
	FILE* adaptadorElegido = fopen(ficheroAdaptador, "r");
	//puntero tipo FILE apuntando a "adaptadorCopia", lo iniciamos en modo escritura "w", creando o sobreescribiendo el fichero adaptador.txt
	FILE* adaptadorCopia = fopen("adaptador.txt", "w");
	if (adaptadorCopia == NULL) {
		perror("Error al abrir el fichero.");
		return;
	}
	printf("\n");
	//accedemos al contenido de "adaptadorElegido" y lo almacenamos en el buffer "leerAdaptador"
	while (fgets(leerAdaptador, sizeof(leerAdaptador), adaptadorElegido)) {
		printf("%s", leerAdaptador); //mientras se va accediendo vamos printando el contenido
		fputs(leerAdaptador, adaptadorCopia); //mientras se va accediendo lo vamos añadiendo con fputs al puntero de "adaptadorCopia"
	}
	fclose(adaptadorCopia); //cerramos adaptadorCopia
	fclose(adaptadorElegido); //cerramos adaptadorElegido

	printf("\n\nSe han guardado los datos del adaptador %d en el fichero \"adaptador.txt\" \n\n", numAdaptador);

	system("pause");
	system("cls");
}

//función para mostrar el contenido del fichero adaptador.txt
void mostrarFicheroAdaptador() {
	system("cls"); //limpio pantalla
	printf("\n");
	FILE* fp = fopen("adaptador.txt", "r"); //puntero tipo FILE que se inicia leyendo ("r") el fichero adaptador.txt
	if (fp == NULL) {
		perror("Error al abrir el fichero.");
		return;
	}
	char buffer[1024]; //cadena de caracteres de tamaño 1024, lo usaremos de buffer

	//bucle while para mostrar el contenido del fichero abierto (está en el puntero fp)
	while (fgets(buffer, sizeof(buffer), fp) != NULL) { //con fgets accedemos al puntero y almacenamos línea tras línea su contenido en la cadena buffer
		printf("%s", buffer); //vamos printando cada línea que se almacena en la cadena buffer
	}
	fclose(fp); //cerramos el fichero

	printf("\n");
	system("pause"); //pause para poder leer pantalla hasta pulsar tecla
	system("cls"); //limpio pantalla antes de mostrar nuevamente menuInicio
}
