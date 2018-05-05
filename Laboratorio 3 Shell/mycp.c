#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int origen, destino, tamano;
    char *buffer[500];
    if(argc < 3) {
        printf("Ingrese los parámetros necesarios (origen y destino)\n");
        return 1;
    }
    origen = open(argv[1], O_RDONLY);
    if (origen < 0) {
        printf("El archivo de origen no se pudo abrir, es posible que no exista o que deba agregarle la extensión (por ejemplo: %s.txt).\n", argv[1]);
        return 1;
    }
    tamano = read(origen, buffer, sizeof(buffer));
    if (tamano < 0) {
        printf("No se pudo leer el contenido del archivo origen.\n");
        return 1;
    }
    destino = open(argv[2], O_WRONLY|O_CREAT);
    if (destino < 0) {
        printf("El archivo de destino no pudo ser creado).\n");
        return 1;
    }
    if (write(destino, buffer, tamano) < 0) {
        printf("No se pudo escribir el contenido al archivo de destino.\n");
        return 1;
    }
    close(origen);
    close(destino);
    return 0;
}
