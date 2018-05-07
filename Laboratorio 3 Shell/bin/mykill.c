#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int senal=9,
        resultado,
        i=1,
        proceso;
    //printf("el %s\n",proceso);
    if(argc == 1) {
        printf("Debe indicar el numero de proceso\n");
    } else if(strncmp(argv[1], "-", 1) == 0 && argc ==2){
        printf("Debe indicar el numero de proceso \n");
    }else if(strncmp(argv[1], "-", 1) == 0){
        char *dato;
        dato = strchr(argv[1],45); //9 es el codigo ASCII para el tab horizontal.
        dato++;
        senal= atoi(dato);
        i++;
    }  
          
        for(i;i<argc;i++){
            proceso= atoi(argv[i]);
            resultado = kill(proceso,senal);
            if(resultado == -1){
                if(errno == ESRCH){
                    printf("El PID ingresado no existe\n");
                }
                if(errno==EINVAL){
                    printf("La señal ingresada no existe\n");
                }

            }
        }
    

    return 0;
}
