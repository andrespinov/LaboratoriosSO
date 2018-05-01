#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int factorial (int, char*);
void imprimirAlerta(int);

int main(){
    pid_t pid_1, pid_2, pid_3;
    char *a;
    pid_1 = fork();
    if(pid_1 == -1){
        imprimirAlerta(1);
    } else if(pid_1 == 0){
        factorial(10, "HIJO1");
    } else {
        pid_2 = fork();
        if(pid_2 == -1){
            imprimirAlerta(2);
        } else if(pid_2 == 0){
            factorial(10, "HIJO2");
        } else {
            pid_3 = fork();
            if(pid_3 == -1){
                imprimirAlerta(3);
            } else if(pid_3 == 0){
                factorial(10, "HIJO3");
            } else {
                wait(NULL);
                wait(NULL);
                wait(NULL);
                printf("SOY EL PADRE\n");
            }
        }
    }  
    return 0;
}

int factorial (int x, char *a){
    int res;
    if(x == 0){
        res = 0;
    } else if(x == 1){
        res = 1;
    } else {
        res = x*factorial(x-1, a);
    }
    printf("%s: factorail(%d)=%d\n", a, x, res);
    return res;
}

void imprimirAlerta(int x){
    printf("El proceso %d no pudo ser creado", x);
}