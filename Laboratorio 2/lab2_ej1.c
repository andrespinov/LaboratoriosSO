#include <stdio.h>

int contarCaracter(char *array, char ch);
void test(void);

int main(){
    test();
    return 0;
}

int contarCaracter(char *array, char ch){
    int count = 0;
    while (*array != '\0'){
        if(*array == ch){
            count++;
        }
        array++;
    }
    if(count == 0){
        return -1;
    }
    return count;
}

void test(void){
    char array[] = {'a','r','a','t','x','a'};
    char ch = 'a';
    int rep = contarCaracter(array, ch);
    printf("El caracter aparece %d veces\n", rep);
}