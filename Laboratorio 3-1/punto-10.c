#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void imprimirInfo (int);
void imprimirAlerta(int);

int main(){
    pid_t pid_2, pid_3, pid_4, pid_5;
    pid_2 = fork();
    if(pid_2 == -1){
        imprimirAlerta(2);
    } else if(pid_2 == 0){
        imprimirInfo(2);
    } else {
        pid_3 = fork();
        if(pid_3 == -1){
            imprimirAlerta(3);
        } else if(pid_3 == 0){
            imprimirInfo(3);
            pid_4 = fork();
            if(pid_4 == -1){
                imprimirAlerta(4);
            } else if(pid_4 == 0){
                imprimirInfo(4);
            } else {
                pid_5 = fork();
                if(pid_5 == -1){
                    imprimirAlerta(5);
                } else if(pid_5 == 0){
                    imprimirInfo(5);
                } else {
                    wait(NULL);
                }
            }
        } else {
            wait(NULL);
            wait(NULL);
            wait(NULL);
            printf("Soy el proceso #1 - El padre\n");
            printf("Mi PID es: %d\n", (int)getpid());
            printf("Mi padre es: %d\n", (int)getppid());
        }
    }
}

void imprimirInfo(int i){
    printf("Soy el hijo #%d\n", i);
    printf("Mi PID es: %d\n", (int)getpid();
    printf("Mi padre es: %d\n", (int)getppid());
}

void imprimirAlerta(int i){
    printf("Elhijo #%d no pudo ser creado", i);
}