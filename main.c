#include <time.h> // Se utiliza para obtner una semilla para la generacion de un numero aleatorio 
#include <ctype.h> // Se utiliza para llevar control de los caracteres dentro del codigo
#include <stdio.h> // Se utiliza para imprimir y leer en la consola 
#include <string.h> // Se usa para el control de las cadenas
#include <stdlib.h> // Se usa para funciones basicas con malloc y para limpiar la pantalla de una consola

// Compara una caracter con los contenidos de una cadena caracteres
int en_lista(char letra, char* lista);
// Genera un numero aleatorio a base de una semilla 
int generar_numero();

// Imprime un menu que se usa para determinar la categoria a jugar
char seleccionar_categoria();

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
         * Toma la fresa correspondiente y lista en un lista sin repetir,
         * lee el contenido de la cadena y determina si un error sucedio al momento de listar las letras
         * si es el caso imprime un mensaje de error y cierra el programa con el valor correspondiente,
         * si no es el caso entonces organiza las letras de manera alfabetica con el metodo de burbuja.
        */
        char* lista_letras = listar_letras(frase);
        if (lista_letras == NULL) {
            printf("Ocurrió un error al asignar memoria \n");
            return 1;
        }
        lista_letras = organizar_lista(lista_letras);

        int tam_lis_corr = 1;
        char* lista_corr = malloc(tam_lis_corr * sizeof(char));
        if (lista_corr == NULL) {
            printf("Ocurrió un error al asignar memoria \n");
            return 1;
        }
        lista_corr[0] = '\0';

        int tam_lis_inco = 1;
        char* lista_inco = malloc(tam_lis_inco * sizeof(char));
        if (lista_inco == NULL) {
            printf("Ocurrió un error al asignar memoria \n");
            return 1;
        }
        lista_inco[0] = '\0';

        do {
            dibujar_gui(errores, frase, pista, lista_letras, lista_corr, lista_inco, guia, categoria);
            
            printf(": ");
            scanf(" %c", &letra);

            if(en_lista(tolower(letra), lista_letras)) {
                if(en_lista(tolower(letra), lista_corr)) {
                    printf("\nYa fue adivinada \n");
                    guia = 'a';
                }
                else {
                    guia = 'c';
                    tam_lis_corr++;
                    lista_corr = realloc(lista_corr,(tam_lis_corr * sizeof(char)));
                    lista_corr[tam_lis_corr - 2] = tolower(letra);
                    lista_corr[tam_lis_corr - 1] = '\0';
                }
            }
            else if(!en_lista(tolower(letra), lista_letras)) {
                if(en_lista(tolower(letra), lista_inco)) { 
                    printf("\nYa fue adivinada \n");
                    guia = 'a';
                }
                else {
                    guia = 'i';
                    errores++;
                    tam_lis_inco++;
                    lista_inco = realloc(lista_inco,(tam_lis_inco * sizeof(char)));
                    lista_inco[tam_lis_inco - 2] = tolower(letra);
                    lista_inco[tam_lis_inco - 1] = '\0';
                }
            }
            lista_corr = organizar_lista(lista_corr);

            if(!strcmp(lista_corr, lista_letras)) {
                salir = 1;
                guia = 'g';
                errores = -1;
                dibujar_gui(errores, frase, pista, lista_letras, lista_corr, lista_inco, guia, categoria);
            }
            else if(errores == 6) {
                salir = 1;
                guia = 'p';
                dibujar_gui(errores, frase, pista, lista_letras, lista_corr, lista_inco, guia, categoria);
            }

        } while (salir != 1);

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

int en_lista(char letra, char* lista) {
    for (int i = 0; i < strlen(lista); i++) {
        if (letra == lista[i])
            return 1;
    }
    return 0;
}

int generar_numero() {
    srand(time(NULL));
    return rand() % 10 + 1;
}

char* listar_letras(char* frase) {
    int tam_lista = 1;

    char* lista = malloc(tam_lista * sizeof(char));
    if (lista == NULL) 
        return NULL;
    lista[0] = '\0';

    for (int i = 0; i < strlen(frase); i++) {
        if (!isalpha(frase[i]))
            continue;

        if (!en_lista(tolower(frase[i]), lista)) {
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

char* obtener_de_archivo(char* ruta_archivo, int numero_linea) {
    const int TAM_MAX = 212;

    int tam_regreso = 1;
    int contador_linea = 0;

    char carac;

    char linea[TAM_MAX];
    
    char* linea_regreso = malloc(sizeof(char));

    FILE *archivo;

    archivo = fopen(ruta_archivo, "r");
    if (archivo == NULL) {
        return NULL;
    }

    while (fgets(linea, TAM_MAX, archivo) != NULL) {
        contador_linea++;

        if (contador_linea == numero_linea) {
            break; 
        }
    }

    fclose(archivo);

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

char seleccionar_categoria() {
	char categoria;

#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
	
    printf("\n ~~~~~ Bienvenido al juego del colgado! ~~~~~\n");
	printf("\n Introduce la categoría: \n  a) Anime \n  b) Municipios de Oaxaca \n  c) Películas \n  d) Música \n  e) Países \n : ");
	scanf(" %c", &categoria);

    return tolower(categoria);
}

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
            printf("\tYa fue adivinada \n");
        break;

        default:
            return;
    }

    dibujar_munieco(errores);

    printf(" Errores: %i \t Letras Faltantes: %lu\n", errores, (strlen(lista_letras) - strlen(lista_corr)) );

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

    if(guia == 'p') {
        printf("\t");

        for (int i = 0; i < strlen(frase); i++) {
            printf("%c", frase[i]);
        }

        printf("\n");
    }

    dibujar_banco_letras(lista_corr, lista_inco);
}

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
        default:
            printf("\t   _____ \n \t   |     \n \t   |     \n \t   |    O \n \t   |   -|- \n \t ----- / \\ \n");
            break;
    }
}

void dibujar_banco_letras(char* lista_corr, char* lista_inco) {
    printf(" -----------------------------");

	for(int i = 65; i <= 90; i++) {
		if(i == 78||i == 65) {
			printf("\n | ");
		}
		
        if(en_lista(tolower(i), lista_corr)) {
		    printf("1 ");
        }
        else if(en_lista(tolower(i), lista_inco)) {
            printf("0 ");
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
