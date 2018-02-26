#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * reversar (char *a);
char cadena[50];
int main () {

    printf("Digite la cadena de caracteres que quiere invertir(maximo 50 digitos):");
    scanf("%[^\n]", &cadena);
      //codigo opcional
    printf ("La cadena original es: %s\n", cadena);
    printf ("La cadena despues de invertirse: %s\n", reversar(cadena));
    return 0;
}

char * reversar (char *a){
  int len = strlen(a);
  char temp[len];
    for(int i=0;i<=len;i++){
      temp[i]=a[len-i-1];
    }

  temp[len+1]='\0';
  strcpy (a,temp); // funcion que copia la cadena de caracteres
  //strrev(a);
  return a;
}
