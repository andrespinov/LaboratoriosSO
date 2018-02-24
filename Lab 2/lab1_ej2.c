#include <stdio.h>
#include <math.h>

long progresion(int x, int n);

int main(){
    int x, n;
    printf("Este programa consiste en ingresar dos npumeros x y n de modo que se calcule la progresión geométrica 1 + x + x^2 + x^3 + x^4 + ⋯ + x^n\n");
    printf("Ingresa x:");
    scanf("%d", &x);
    printf("Ingresa n: ", multiplo);
    scanf("%d", &n);
    printf("El resultado de 1 + %d + %d^2  ⋯ + %d^%d es %ld\n",x, x, x, n, progresion(x,n));
    return 0;
}

long progresion(int x, int n){
    if(n == 0){
        return 1;
    }
    return (pow(x,n + 1) - 1)/(x - s1);
}