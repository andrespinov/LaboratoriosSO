#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randomNum();

int main () { 
  int a, b, respuesta, bandera;
  bandera = 1;
  srand(time(NULL));
  while(bandera == 1){
      a = randomNum();
      b = randomNum();
      printf("¿Cuánto es %d veces %d?:", a, b);
      scanf("%d",&respuesta);
      if(respuesta == a*b){
          printf("Muy bien!\n");
      } else{
          printf("No. Por favor intenta nuevamente\n");
      }
      printf("Para continuar ingresa 1 de lo contrario ingresa 0:");
      scanf("%d", &bandera);
  }
  return 0;
}

int randomNum(){
    return rand()%10;
}