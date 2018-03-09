#include <stdio.h>

int obtenerIndice(char *array, char ch);
void test(void);

int main(){
    test();
    return 0;
}

int obtenerIndice(char *array, char ch) {
    int count = 0;
    while (*array != '\0'){
        if(*array == ch){
            return count;
        }
        count++;
        array++;
    }
    return -1;
}

void test(void){
    char array[] = {'a','r','a','t','x','a'};
    char ch = 'x';
    int rep = obtenerIndice(array, ch);
    printf("El caracter aparece por primera vez en la posición %d\n", rep);
}