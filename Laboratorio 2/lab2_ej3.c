#include <stdio.h>
#include <string.h>

char *obtenerSubcadena(char *array, int index);
void test(void);

int main(){
    test();
    return 0;
}

char *obtenerSubcadena(char *array, int index) {
    char *subcadena = array;
    int i;
    int length = strlen(array);
    for(i = 0; i < length; i++){
        if (i == index){
            return subcadena;;
        }
        subcadena++;
    }
    return subcadena;
}

void test(void){
    char *p1 = "Hola que tal"; 
    char *p2;
    p2 = obtenerSubcadena(p1, 20);
    printf("%s\n",p1);
    printf("%s\n",p2);
}