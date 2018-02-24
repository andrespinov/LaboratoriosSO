#include <stdio.h>
#include <string.h>
//#include <time.h>
char* cadena[50];
char* auxiliar[50];
char* reversar (char* a);

int main () { 
  
    printf("Digite la cadena de caracteres que quiere invertir(maximo 50 digitos)");
  scanf("%s",&cadena);
      printf ( "%s" , reversar );
   
  return 0;
}

char* reversar (char* a){
    int tamano= strlen(a);
    for(int i=tamano;i>=0;i--){
       
            auxiliar[tamano-i+1]= cadena[i];
    }
   return auxiliar;
}