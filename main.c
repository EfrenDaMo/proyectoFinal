#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int en_lista(char letra, char* lista);

char* listar_letras(char* frase);
char* organizar_lista(char* lista);

void dibujar_gui(int errores, char* frase, char* lista_letras, char* lista_corr, char* lista_inco, char guia);
void dibujar_munieco(int errores);
void dibujar_banco_letras(char* lista_corr, char* lista_inco);

int main(void) {
    int errores = 0;
    int salir = 0;

    char letra;
    char respuesta;
    char guia = 's';

    char* frase =  "Hola, mundo!";
    char* lista_letras = listar_letras(frase);
    if (lista_letras == NULL) {
        printf("Ocurrio un error al asignar memoria \n");
        return 1;
    }
    lista_letras = organizar_lista(lista_letras);

    int tam_lis_corr = 1;
    char* lista_corr = malloc(tam_lis_corr * sizeof(char));
    if (lista_corr == NULL) {
        printf("Ocurrio un error al asignar memoria \n");
        return 1;
    }
    lista_corr[0] = '\0';

    int tam_lis_inco = 1;
    char* lista_inco = malloc(tam_lis_inco * sizeof(char));
    if (lista_inco == NULL) {
        printf("Ocurrio un error al asignar memoria \n");
        return 1;
    }
    lista_inco[0] = '\0';

    do {
        do {
            dibujar_gui(errores, frase, lista_letras, lista_corr, lista_inco, guia);
            
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
                dibujar_gui(errores, frase, lista_letras, lista_corr, lista_inco, guia);
            }
            else if(errores == 6) {
                salir = 1;
                guia = 'p';
                dibujar_gui(errores, frase, lista_letras, lista_corr, lista_inco, guia);
            }

        } while (salir != 1);

        printf("\n\n Le gustaria seguir jugando \n (S)i (N)o\n : ");
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

void dibujar_gui(int errores, char* frase, char* lista_letras, char* lista_corr, char* lista_inco, char guia) {
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif

    // Pista de la frase
    printf("Pista: Frase de todo primer codigo\n");

    // Guia de acertaje
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
		//no se tiene que mover ya que le imprime '|' despues de 77 y 90␍
		if(i == 90 || i == 77) {
			printf("|");
		}
	}
	
	printf("\n");
	printf(" -----------------------------\n");
}
