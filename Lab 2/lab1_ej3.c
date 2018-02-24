#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randomNum(int a, int b);

int main () { 
  int a, b, cant, i;
  printf("Digite la cantidad de números que desea generar: ");
  scanf("%d",&cant);
  printf("Digite los limites (primero el superior, luego el inferior): ");
  scanf("%d,%d",&a,&b);
  srand(time(NULL));
  for(i = 0; i < cant; i ++) {
    printf("%d ",randomNum(a,b));
  } 
  printf("\n");
   
  return 0;
}

int randomNum(int a, int b){
    int random;
    random = rand()%(b-a+1)+a;
    return random;
}