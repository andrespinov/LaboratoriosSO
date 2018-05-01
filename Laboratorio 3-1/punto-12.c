#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  if(argc == 1){
    printf("Ingrese los parámetros.");
  } else if(argc == 2){
    execlp(argv[1], argv[1], NULL, 0);//sin bandera
  } else {
    execlp(argv[1], argv[1], argv[2], 0);//con banderas
  }
  return 0;
}