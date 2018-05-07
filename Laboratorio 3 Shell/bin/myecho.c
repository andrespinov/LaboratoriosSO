#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("el numero deargumentos es : %d estso\n",argc);
    if(argc == 1) {
        printf("No se ingresó ningún parámetro\n");
    } else {
        for(int i = 2; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
    }
    return 0;
}
