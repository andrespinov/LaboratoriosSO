#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
    char cwd[200];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("No se ha podido obtener el directorio actual.");
    } else {
        printf("Directorio actual: %s\n", cwd);
    }
    return 0;
}
