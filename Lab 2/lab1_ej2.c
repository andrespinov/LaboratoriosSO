#include <stdio.h>
#include <math.h>

long progresion(int x, int n);

int main(){
    int x, n;
    printf("Este programa consiste en ingresar dos numeros x y n de modo que se calcule la progresión geométrica 1 + x + x^2 + x^3 + x^4 + ⋯ + x^n\n");
    printf("Ingresa x:");
    scanf("%d", &x);
    printf("Ingresa n: ");
    scanf("%d", &n);

    if(n<=2){
      if(n<=1){
        if(n==0){
          printf("El resultado de %d^%d es %ld\n",
          x,n, progresion(x,n));
        }else{
          printf("El resultado de 1 + %d es %ld\n",
        x, progresion(x,n));
      }}else{
      printf("El resultado de 1 + %d + %d^2 es %ld\n",
      x,x, progresion(x,n));}
    }else{
    printf("El resultado de 1 + %d + %d^2 + ⋯ + %d^%d es %ld\n",
    x, x, x, n, progresion(x,n));}

    return 0;
}

long progresion(int x, int n){
    if(n == 0){
        return 1;
    }
    return (pow(x,n + 1) - 1)/(x - 1);
}
