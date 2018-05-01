#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

main() {


    printf("Proceso padre \n"); 
    printf("Hola \n");       
      
   int pid_hijo = fork();

   if(pid_hijo==0){
        printf("Proceso 1 \n"); 
       printf("Mundo \n");
       exit(0);
   }
   pid_hijo = fork();
    if(pid_hijo==0){
         printf("Proceso 2 \n"); 
         printf("!\n");
       exit(0);
   }
 
}