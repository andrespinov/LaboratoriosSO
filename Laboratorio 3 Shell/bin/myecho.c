#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc == 1) {
        printf("No se ingresó ningún parámetro\n");
    } else {
        for(int i = 1; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
    }
    return 0;
}