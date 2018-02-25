#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *reversar (char a[]);

int main () { 
    char cadena[50];
    printf("Digite la cadena de caracteres que quiere invertir(maximo 50 digitos):");
    scanf("%s", &cadena);
    char *reversa = reversar(cadena);
    printf ("%s\n", reversa);
    free(reversa);
    return 0;
}

char *reversar (char a[]){
    char *auxiliar = malloc(50);
    int tamano = strlen(a);
    for(int i = tamano; i >= 0; i--){
        auxiliar[tamano - i + 1] = a[i];
    }
   return auxiliar;
}