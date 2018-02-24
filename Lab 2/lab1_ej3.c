#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random(int a, int b);

int main () { 
  int a, b, cant, i, aleatorio;
  printf("Digite la cantidad de números que desea generar: ");
  scanf("%d",&cant);
  printf("Digite los limites (primero el superior, luego el inferior): ");
  scanf("%d%d",&a,&b);
  for(i = 0; i < cant; i ++) {
    printf("%d ", random(a,b));
  } 
  printf("\n");
  return 0;
}

int random(int a, int b){
    int random;
    srand(time(NULL));
    random = rand()%(a-b+1)+b;
    system("PAUSE");
    return random;
}