#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char linea[200];
    if(argc < 3){
        printf("Ingrese los parámetros necesarios (string a buscar y archivo)\n");
        return 1;
    }
    fp = fopen(argv[2], "r");
    if (fp == NULL){
        printf("El archivo no se pudo abrir, es posible que no exista o que deba agregarle la extensión (por ejemplo: %s.txt).\n", argv[2]);
        return 1;
    }
     while(fgets(linea, 200, fp) != NULL){
         if(strstr(linea, argv[1]) != NULL){
             printf("%s", linea);
         }
     }
     return 0;
}
