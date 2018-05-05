#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "parser.h"

//Colores para el prompot y el texto ingresado respectivamente.
#define COLOR_VERDE   "\x1b[32m"
#define COLOR_BLANCO   "\x1b[0m"

//Declaración de las funciones implementadas.
void myclear();
void ejecutarInstruccion(char *[], int);

int main(int argc, char *argv[]) {
    //Inicialización de los parámetros a utilizar.
    char *prompt = "the-best-shell >";
    char **parametros, expresion[100];
    int ejecucion = 1;
    int background, numParametros;

    //Ciclo en el que permanece la línea de comandos para recibir la entrada.
    while(ejecucion == 1) {
        printf(COLOR_VERDE "%s" COLOR_BLANCO" ", prompt);
        fgets (expresion, 100, stdin);
        numParametros = separaItems (expresion, &parametros, &background);
        if (numParametros > 0) {
            if (strncmp(parametros[0], "myexit", 6) == 0){
                ejecucion = 0;
            } else if(strncmp(parametros[0], "myclear", 7) == 0){
                myclear();
            } else {
                ejecutarInstruccion(parametros, background);
            }
        }
    }
    return 0;
}

/**
 * Método que limpiará la consola, correspondiente al comando myclear del shell.
**/
void myclear(){

}

/**
 * Método que creará un nuevo proceso el cuál se convertirá en la instrucción ingresada.
**/
void ejecutarInstruccion(char *param[], int bg) {
    pid_t instruccionNueva = fork();
    if(instruccionNueva < 0) {
        printf("No se pudo llevar a cabo la instrucción.\n");
        exit(0);
    } else if(instruccionNueva == 0) {
        char path[50];
        //char *subParam[100]; 
        //memcpy(subParam, &param[1], 2*sizeof(*param));
        strcpy(path, "./bin/");
        strcat(path, param[0]);
        execl(path, path, *param, NULL);
        printf("La instrucción %s no puedo ser encontrada.\n", param[0]);
    } else {
        if(bg == 0) {
            wait(NULL);
        }
    }
}
