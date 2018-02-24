#include <stdio.h>

int multiplo(int x, int y);

int main(){
    int mult, num;
    printf("Digite el número que desea usar como múltiplo: ");
    scanf("%d", &mult);
    printf("Digite el número del que desea saber si es multiplo de %d: ", multiplo);
    scanf("%d", &num);
    if(multiplo(mult, num) == 1){
        printf("%d es múltiplo de %d\n", num, mult);
    } else{
        printf("%d no es múltiplo de %d\n", num, mult);
    }
    return 0;
}

/*
Este método determina si y es múltiplo de x, 
retornando 1 si lo es, o 0 en caso contrario 
*/
int multiplo(int x, int y){
    if(y mod x == 0){
        return 1;
    }
    return 0;
}