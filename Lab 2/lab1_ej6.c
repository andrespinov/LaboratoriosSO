#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int lanzar();

int main () { 
  int cant, caras, sellos, i;
  printf("Digite la cantidad de lanzamientos para la moneda: ");
  scanf("%d",&cant);
  srand(time(NULL));
  caras = 0;
  sellos = 0;
  for(i = 0; i < cant; i ++) {
    if(lanzar() == 0){
        printf("%c", 'C');
        caras = caras + 1;
    } else{
        printf("%c", 'S');
        sellos = sellos + 1;
    }
  } 
  printf(", # de caras = %d, # de sellos = %d.\n", caras, sellos);   
  return 0;
}

int lanzar(){
    return rand()%2;
}