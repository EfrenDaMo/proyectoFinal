#include <time.h> // Se utiliza para obtner una semilla para la generacion de un numero aleatorio 
#include <ctype.h> // Se utiliza para llevar control de los caracteres dentro del codigo
#include <stdio.h> // Se utiliza para imprimir y leer en la consola 
#include <string.h> // Se usa para el control de las cadenas
#include <stdlib.h> // Se usa para funciones basicas con malloc y para limpiar la pantalla de una consola

// Compara una caracter con los contenidos de una cadena caracteres
int en_lista(char letra, char* lista);
// Genera un numero aleatorio a base de una semilla 
int generar_numero(void);

// Imprime un menu que se usa para determinar la categoria a jugar
char seleccionar_categoria(void);

// Toma una cadena de caracteres y extrae cada letra que aparece dentro de ella y las lista 
char* listar_letras(char* frase);
// Toma una cadena de caracteres y los organiza con el metodo de burbuja
char* organizar_lista(char* lista);
// Selecciona una linea de un archivo
char* obtener_de_archivo(char* ruta_archivo, int numero_linea);

// Imprime todo el gui completo
void dibujar_gui(int errores, char* frase, char* pista, char* lista_letras, char* lista_corr, char* lista_inco, char guia, char categoria);
// Imprime la parte del muñeco en el gui
void dibujar_munieco(int errores);
// Imprime la parte del banco de letras del gui.
void dibujar_banco_letras(char* lista_corr, char* lista_inco);

/*
 * La funcion principal del juego, se encarga de la mayoria de la logica del juego 
 * 
 * Parametros: Ninguno, representado con el "void"
 *
 * Valores de regreso:
 *  - 0: Ejecución exitosa
 *  - 1: Error al asignar o reasignar memoria con malloc o realloc 
 *  - 2: Error al abrir archivo
 *  - 3: Error al elegir una categoria inexistente
*/
int main(void) {
    // Usadas para llevar control de la entrada del jugador
    char letra; 
    char respuesta;

    // Ciclo que continua el juego hasta que el juego determine que el jugador a ganado o perdido usando una variable tipo int como booleano
    do {
        // Usadas para llevar el control de partes del juego
        int salir = 0; // Usado para determinarsi el juego puede acabar
        int errores = 0; // LLeva control de los errores registrados

        int numero_aleatorio = generar_numero(); 

        char guia = 's'; // Se usa para control el mensaje de guia en la GUI.

        char* archivo_frase; // Cadena que contiene la ruta al archivo de frase de la categoria seleccionada
        char* archivo_pista; // Cadena que contiene la ruta al archivo de pista correspondiente a la frase

        char categoria = seleccionar_categoria();

        /*
         * Asigna las rutas adecuadas a base de la categoria seleccionada,
         * cierra el programa con un valor correspondiente si una categoria no es seleccionada correctamente
        */
        switch (categoria) {
            case 'a':
                archivo_frase = "./categorias/anime.txt";
                archivo_pista = "./pistas/anime.txt";
                break;

            case 'b':
                archivo_frase = "./categorias/municipios.txt";
                archivo_pista = "./pistas/municipios.txt";
                break;

            case 'c':
                archivo_frase = "./categorias/peliculas.txt";
                archivo_pista = "./pistas/peliculas.txt";
                break;

            case 'd':
                archivo_frase = "./categorias/musica.txt";
                archivo_pista = "./pistas/musica.txt";
                break;

            case 'e':
                archivo_frase = "./categorias/paises.txt";
                archivo_pista = "./pistas/paises.txt";
                break;

            case 'q':
                printf("Entendido cerrando el programa \n");
                return 0;

            default:
                printf("Categoría no reconocida.\n");
                return 3;
        }

        /*
         * Obtine la frase del archivo correspondiente a la categoria seleccionada,
         * lee el contenido de la cadena y determina si un error sucedio al momento de conseguir la frase,
         * si es el caso imprime un mensaje de error y cierra el programa con el valor correspondiente.
        */
        char* frase = obtener_de_archivo(archivo_frase, numero_aleatorio);
        if (frase == NULL) {
            printf("Ocurrió un error al abrir el archivo\n");
            return 2;
        }

        /*
         * Obtine la pista del archivo correspondiente a la categoria seleccionada,
         * lee el contenido de la cadena y determina si un error sucedio al momento de conseguir la pista,
         * si es el caso imprime un mensaje de error y cierra el programa con el valor correspondiente.
        */
        char* pista = obtener_de_archivo(archivo_pista, numero_aleatorio);
        if (pista == NULL) {
            printf("Ocurrió un error al abrir el archivo\n");
            return 2;
        }

        /*
         * Toma la frase correspondiente y lista en un lista sin repetir,
         * lee el contenido de la cadena y determina si un error sucedio al momento de listar las letras,
         * si es el caso imprime un mensaje de error y cierra el programa con el valor correspondiente,
         * si no es el caso entonces organiza las letras de manera alfabetica con el metodo de burbuja.
        */
        char* lista_letras = listar_letras(frase);
        if (lista_letras == NULL) {
            printf("Ocurrió un error al asignar memoria \n");
            return 1; 
        }
        lista_letras = organizar_lista(lista_letras);

        /*
         * Crea una cadena de caracteres a base de memoria con la suficiente para poder resguadar un caracter,
         * se lee el contenido de la cadena y a base del valor de la variable se determina si sucedio algun error,
         * si es el caso se imprime un mensaje de error y se cierra el programa con valor de regreso correspondiente,
         * si no es el caso se dentro de la memoria se asigna un caracter nulo para evitar algun problema mas adelante.
        */
        int tam_lis_corr = 1;
        char* lista_corr = malloc(tam_lis_corr * sizeof(char));
        if (lista_corr == NULL) {
            printf("Ocurrió un error al asignar memoria \n");
            return 1;
        }
        lista_corr[0] = '\0';

        /*
         * Crea una cadena de caracteres a base de memoria con la suficiente para poder resguadar un caracter,
         * se lee el contenido de la cadena y a base del valor de la variable se determina si sucedio algun error,
         * si es el caso se imprime un mensaje de error y se cierra el programa con valor de regreso correspondiente,
         * si no es el caso se dentro de la memoria se asigna un caracter nulo para evitar algun problema mas adelante.
        */
        int tam_lis_inco = 1;
        char* lista_inco = malloc(tam_lis_inco * sizeof(char));
        if (lista_inco == NULL) {
            printf("Ocurrió un error al asignar memoria \n");
            return 1;
        }
        lista_inco[0] = '\0';

        do {
            // Llama la funcion que dibuja la GUI principal pasando las variables de control previamente establecidas como paramentros.
            dibujar_gui(errores, frase, pista, lista_letras, lista_corr, lista_inco, guia, categoria);
            
            printf(": ");
            scanf(" %c", &letra);

            /*
             * Se compara la letra introducida por el jugador a la cadena que contiene la lista de las letras en la frase,
             * se asigna a la lista correspondiente dependiendo si se encuentra en la lista o no,
             * se hace una ultima revision con la lista a la que se va a asignar para determinar si ya fue intentada o no,
             * se incrementa el tamaño de la lista correspondiente y se le asigna mas memoria y se repite la verificación de errores,
             * la letra se asigna a la lista correspondiente y mueve el caracter nulo al final de la lista.
            */
            if(en_lista(tolower(letra), lista_letras)) {
                if(en_lista(tolower(letra), lista_corr))
                    guia = 'a';
                else {
                    guia = 'c';
                    tam_lis_corr++;
                    lista_corr = realloc(lista_corr,(tam_lis_corr * sizeof(char)));            
                    if (lista_corr == NULL) {
                        printf("Ocurrió un error al asignar memoria \n");
                        return 1;
                    }
                    lista_corr[tam_lis_corr - 2] = tolower(letra);
                    lista_corr[tam_lis_corr - 1] = '\0';
                }
            }
            else if(!en_lista(tolower(letra), lista_letras)) {
                if(en_lista(tolower(letra), lista_inco)) 
                    guia = 'a';
                else {
                    guia = 'i';
                    errores++;
                    tam_lis_inco++;
                    lista_inco = realloc(lista_inco,(tam_lis_inco * sizeof(char)));
                    if (lista_inco == NULL) {
                        printf("Ocurrió un error al asignar memoria \n");
                        return 1;
                    }
                    lista_inco[tam_lis_inco - 2] = tolower(letra);
                    lista_inco[tam_lis_inco - 1] = '\0';
                }
            }
            // Se organiza la lista de letras adivinadas correctamente para facilitar la comparacion
            lista_corr = organizar_lista(lista_corr);
            
            /*
             * Se determina si se puede cerrar el juego verificando las condiciones de finalizacion,
             * condiciones:
             *  - 6 errores
             *  - La lista de letras de la frase y la lista de letras adivinadas correctamente son iguales.
             *  Se actualiza adecuadamente el GUI ya que al evaluar se cierra completamente el ciclo.
            */
            if(!strcmp(lista_corr, lista_letras)) {
                salir = 1;
                guia = 'g';
                errores = -1; // Hecho para que active la caso default en el switch case utilizado.
                dibujar_gui(errores, frase, pista, lista_letras, lista_corr, lista_inco, guia, categoria);
            }
            else if(errores == 6) {
                salir = 1;
                guia = 'p';
                dibujar_gui(errores, frase, pista, lista_letras, lista_corr, lista_inco, guia, categoria);
            }

        } while (salir != 1);

        // Libera todas las variables que son apuntadores para que se libere la memoria correspondiente
        free(frase);
        free(pista);
        free(lista_corr);
        free(lista_inco);
        free(lista_letras);

        printf("\n\n Le gustaría seguir jugando \n (S)i (N)o\n : ");
        scanf(" %c", &respuesta);
    } while(tolower(respuesta) != 'n');

   return 0;
}

/*
 * Se usa para determinar si una caracter se encuentra de una lista de cadenas.
 * 
 * Parametros:
 *  - char letra: Caracter por buscar dentro de la cadena
 *  - char* lista: Cadena de caracteres a la que se va comparar
 *
 * Valores de regreso:
 *  - 0: No se encontro la letra dentro de la lista
 *  - 1: Se encontro la letra dentro de la lista
*/
int en_lista(char letra, char* lista) {
    for (int i = 0; i < strlen(lista); i++) {
        if (letra == lista[i])
            return 1;
    }
    return 0;
}

/*
 * Genera un numero a base de una semilla seleccionada con relacion al tiempo
 * 
 * Parametros: Ninguno, representado con el "void"
 *
 * Valores de regreso: Un numero aleatorio de 1-10
*/
int generar_numero(void) {
    srand(time(NULL));
    return rand() % 10 + 1;
}

/*
 * Imprime un menu y le permite seleccionar al usuario su opcion
 * 
 * Parametros: Ninguno, representado con el "void"
 *
 * Valores de regreso: La letra correspondiente a la categoria seleccionada por el usuario
*/
char seleccionar_categoria(void) {
    char categoria;

// Se usa para determinar el sistema operativo del jugador para limpiar correctamente la terminal
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif

    printf("\n ~~~~~ Bienvenido al juego del colgado! ~~~~~\n");
    printf("\n Introduce la categoría: \n  a) Anime \n  b) Municipios de Oaxaca \n  c) Películas \n  d) Música \n  e) Países \n  q) Salir \n : ");
    scanf(" %c", &categoria);

    return tolower(categoria); // Regresa la letra correspondiente a la categoria seleccionada como minuscula.
}

/*
 * Crea una lista a base de las letras dentro de una cadena de caracteres.
 * 
 * Parametros:
 *  - char* frase: Cadena de caracteres de la cual se va a formar la lista.
 *
 * Valores de regreso:
 *  - lista: Una lista compuestas con las letras del parametro sin repetir
 *  - NULL: Error al momento de asignar o reasignar memoria 
*/
char* listar_letras(char* frase) {
    int tam_lista = 1;

    char* lista = malloc(tam_lista * sizeof(char));
    if (lista == NULL) 
        return NULL;
    lista[tam_lista - 1] = '\0';

    for (int i = 0; i < strlen(frase); i++) {
        if (isalpha(frase[i]) && !en_lista(tolower(frase[i]), lista)) {
            tam_lista++;
            
            lista = realloc(lista, (tam_lista * sizeof(char)));
            if (lista == NULL) 
                return NULL;

            lista[tam_lista - 2] = tolower(frase[i]);
            lista[tam_lista - 1] = '\0';
        }
    }
    return lista;
}

/*
 * Organiza una lista en orden alfabetico via el uso del metodo de burbuja.
 * 
 * Parametros:
 *  - char* lista: Cadena de caracteres que se quiere organizar
 *
 * Valores de regreso:
 *  - lista: La lista organizada de forma alfabetica
*/
char* organizar_lista(char* lista) {
    for(int i = 0; i < strlen(lista); i++) {
        for (int j = i + 1; j < strlen(lista); j++) {
            if(lista[i] > lista[j]) {
                int temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }
    return lista;
}

/*
 * Obtiene el contenido de una linea especifica de un archivo a base de su ruta.
 * 
 * Parametros:
 *  - char* ruta_archivo: Contiene la ruta al archivo que se deasea abrir.
 *  - int numero_linea: Es el numero de la linea que se desea elegir.
 *
 * Valores de regreso:
 *  - linea_regreso: Una version optima de la linea del archivo seleccionado.
 *
 * Nota: Es necesario realizar el procedimiento de malloc para evitar el problema de
 * imprimir caracteres de sobra que hayan quedado registrados en el arreglo "linea".
*/
char* obtener_de_archivo(char* ruta_archivo, int numero_linea) {
    const int TAM_MAX = 212;

    int tam_regreso = 1;
    int contador_linea = 0;

    char carac;

    char linea[TAM_MAX];
    
    char* linea_regreso = malloc(sizeof(char));

    FILE *archivo;

    // Abre el archivo en modo lectura indicado por el "r", y regresa NULL en caso de que suceda un error
    archivo = fopen(ruta_archivo, "r");
    if (archivo == NULL) 
        return NULL;

    // Obtiene la linea indicada que es especificada por el parametro "numero_linea"
    while (fgets(linea, TAM_MAX, archivo) != NULL) {
        contador_linea++;
        if (contador_linea == numero_linea) {
            break; 
        }
    }

    fclose(archivo); // Cierra el archivo para evitar problemas de memoria

    // Obtine todo el contenido antes del '.' en la linea
    for (int i = 0; linea[i] != '.'; i++) {
        tam_regreso++;

        linea_regreso = realloc(linea_regreso, (tam_regreso * sizeof(char)));
        if (linea_regreso == NULL) 
            return NULL;

        linea_regreso[tam_regreso - 2] = linea[i];
        linea_regreso[tam_regreso - 1] = '\0';
    }

    return linea_regreso;
}

/*
 * Imprime la GUI completa utilizando las otras dos partes
 * 
 * Parametros:
 *  - int errores: Cantidad de errores cometidos
 *  - char* frase: La frase seleccionada aleatoriamente de la categoria seleccionada
 *  - char* pista: La pista correspondiente a la frase 
 *  - char* lista_letras: La lista de las letras en la frase
 *  - char* lista_corr: La lista de letras adivinadas correctamente
 *  - char* lista_inco: La lista de letras adivinadas incorrectamente
 *  - char guia: Guia de la ultima acción realizada
 *  - char categoria: Categoría seleccionada por el jugador
 *
 * Valores de regreso: Ninguno, representado con el "void"
*/
void dibujar_gui(int errores, char* frase, char* pista, char* lista_letras, char* lista_corr, char* lista_inco, char guia, char categoria) {
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif

    printf(" Categoría: ");
    switch (categoria) {
        case 'a':
            printf("Anime");
            break;

        case 'b':
            printf("Municipios de Oaxaca");
            break;

        case 'c':
            printf("Películas");
            break;

        case 'd':
            printf("Música");
            break;

        case 'e':
            printf("Países");
            break;

        default:
            printf("Categoría no reconocida.\n");
            return;
    }
    printf(" \n");

    // Pista de la frase
    printf(" Pista: %s \n", pista);

    // Impresión de guia
    switch (guia) {
        case 's':
            printf("\n");
        break;

        case 'i':
            printf("\tIncorrecto!\n");
        break;

        case 'c':
            printf("\tCorrecto!\n");
        break;

        case 'p':
            printf("\tHa perdido :( \n");
        break;

        case 'g':
            printf("\tHa ganado :D \n");
        break;

        case 'a':
            printf("\tYa fue intentada \n");
        break;

        default:
            return;
    }

    dibujar_munieco(errores);

    // Imprime los errores con el parametro y las letras Faltantes que es la diferencia entre la lista principal y la lista de letras correctas
    printf(" Errores: %i \t Letras Faltantes: %lu\n", errores, (strlen(lista_letras) - strlen(lista_corr)) );

    // Imprime los espacios vacios por llenar de la frase 
    printf("\n\t");
    for (int i = 0; i < strlen(frase); i++) {
        if(!isalpha(frase[i]))
            printf("%c", frase[i]);
        else if (en_lista(tolower(frase[i]), lista_corr))
            printf("%c", frase[i]);
        else
            printf("_");
    }
    printf("\n");

    // Si el jugador ha perdido imprime la frase correcta
    if(guia == 'p') 
        printf("\t%s \n", frase);

    dibujar_banco_letras(lista_corr, lista_inco);
}

/*
 * Imprime el muñeco y la ahorca a base de los errores del jugador
 * 
 * Parametros:
 *  - int errores: El numero de errores cometidos por el jugador
 *
 * Valores de regreso: Ninguno, representado con el "void"
*/
void dibujar_munieco(int errores) {
    switch (errores) {
        case 0:
            printf("\t   _____ \n \t   |     \n \t   |     \n \t   |     \n \t   |        \n \t ----- \n");
            break;
        case 1:
            printf("\t   _____ \n \t   |   | \n \t   |   O \n \t   |     \n \t   |        \n \t ----- \n");
            break;
        case 2:
            printf("\t   _____ \n \t   |   | \n \t   |   O \n \t   |   | \n \t   |        \n \t ----- \n");
            break;
        case 3:
            printf("\t   _____ \n \t   |   | \n \t   |   O \n \t   |  -| \n \t   |        \n \t ----- \n");
            break;
        case 4:
            printf("\t   _____ \n \t   |   | \n \t   |   O \n \t   |  -|- \n \t   |       \n \t ----- \n");
            break;
        case 5:
            printf("\t   _____ \n \t   |   | \n \t   |   O \n \t   |  -|- \n \t   |  /    \n \t ----- \n");
            break;
        case 6:
            printf("\t   _____ \n \t   |   | \n \t   |   X \n \t   |  -|- \n \t   |  / \\ \n \t ----- \n");
            break;
        default: // Caso especial para el caso de ganar pude ser activado por un numero fuera del rango 0-6
            printf("\t   _____ \n \t   |     \n \t   |     \n \t   |    O \n \t   |   -|- \n \t ----- / \\ \n");
            break;
    }
}

/*
 * Imprime el banco de letras a base de unas condiciones
 * 
 * Parametros:
 *  - char* lista_corr: La lista de letras adivinadas correctamente
 *  - char* lista_inco: La lista de letras adivinadas incorrectamente
 *
 * Valores de regreso: Ninguno, representado con el "void"
 *
 * Nota: Imprime un '*' si la letra ya fue intentada y fue correcta,
 * Imprime un '/' si la letra ya fue intentada y fue incorrecta.
*/
void dibujar_banco_letras(char* lista_corr, char* lista_inco) {
    printf(" -----------------------------");
	for(int i = 65; i <= 90; i++) {
		if(i == 78||i == 65) {
			printf("\n | ");
		}
		
        if(en_lista(tolower(i), lista_corr)) {
		    printf("* ");
        }
        else if(en_lista(tolower(i), lista_inco)) {
            printf("/ ");
        }
        else {
		    printf("%c ", i);
        }
		//no se tiene que mover ya que le imprime '|' después de 77 y 90␍
		if(i == 90 || i == 77) {
			printf("|");
		}
	}
	printf("\n");
	printf(" -----------------------------\n");
}

