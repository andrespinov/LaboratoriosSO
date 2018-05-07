#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estructuras que representarán a los procesos.
struct Tamano{
  char total[20];
  char text[20];
  char data[20];
  char stack[20];
};

typedef struct Tamano Tamano;

struct Proceso{
  char id[20];
  char nombre[20];
  char estado[25];
  Tamano tam;
  char cambiosv[20];
  char cambiosi[20];
};

typedef struct Proceso Proceso;

//Variables globales a utilizar.
FILE *fpr;
FILE *fp;
char ruta[80];

//Definición de las funciones a utilizar.
void procesarProceso(char *, int);
void imprimirProceso(Proceso);
void guardarProceso(Proceso);
int  validararchivo(char *);

//Método principal.
int main(int argc, char *argv[]){
  if(argc == 1 || ((strncmp( argv[1], "-l", 3) == 0 || strncmp( argv[1], "-r", 3) == 0) && argc == 2)){ //Primero se rectifica que sí hayan ingresado procesos como parámetros.
    printf("No se ingresó ningún proceso como parámetro.\n");
    exit(1);
  } else if(strncmp( argv[1], "-l", 3) == 0){ //Se identifica si se usa la bandera -l.
    //Se hace el proceso de obtención de información y escritura en consola de cada uno de los procesos ingresados como parámetros.
    for(int index = 2; index < argc; ++index){
       procesarProceso(argv[index], 0);
    }
  } else if(strncmp( argv[1], "-r", 3) == 0){ //Se identifica si se usa la bandera -r.
    char nombreArchivo[50]; //Nombre del archivo que se creará.
    strcpy(nombreArchivo, "psinfo-report");
    for(int index = 2; index < argc; ++index){
        if(validararchivo(argv[index])!=0){
          strcat(nombreArchivo, "-");
          strcat(nombreArchivo, argv[index]);
        }else{
          printf("El proceso %s no existe actualmente, por ende no se incluira en el archivo.\n", argv[index]);
        }
      }
    strcat(nombreArchivo, ".info");
    //Se crea el archivo donde se escribirá la información de los procesos.
    fpr = fopen(nombreArchivo, "w");
    if (fpr == NULL){
      printf("No se pudo crear el archivo.");
      exit(1);
    }
    //Se hace el proceso de obtención de información y escritura en el archivo de cada uno de los procesos ingresados como parámetros.
    for(int index = 2; index < argc; ++index){
       procesarProceso(argv[index], 1);
    }
    fclose(fpr);
    printf("Archivo de salida generado: %s\n", nombreArchivo);
  } else{ //Si no es ninguno de los casos anteriores, se dará por entendido que sólo ingresó el pid de un proceso por parámetro. En caso de haber ingresado más sólo tomará en cuenta el primero.
    procesarProceso(argv[1], 0);
  }
  return 0;
}
/**
* Este método traerá las características del proceso con id ingresado por parámetro.
* Además dependiendo de la bandera imprimirá o escribirá en un archivo dichas características:
* 0 para imprimir en pantalla, cualquier otro valor para escribir en un archivo.
*/
void procesarProceso(char *id, int bandera){
  
  Proceso proc = {
    "No disponible\n",
    "No disponible\n",
    "No disponible\n",
    {
      "No disponible\n",
      "No disponible\n",
      "No disponible\n",
      "No disponible\n"
    },
    "No disponible\n",
    "No disponible\n"
  };
  char linea[200];
  if(validararchivo(id)==0){
   printf("El archivo %s no se encuentra actualmente, es probable que el proceso %s no exista o este ingresando un PID invalido.\n\n", ruta, id);
   return;
  }
  //Se inicializa el PID del proceso.
  strcpy(proc.id, id);
  strcat(proc.id, "\n");
  //Se recorre el archivo línea por línea para capturar la información necesaria.
  while(fgets(linea, 200, fp) != NULL){
    //La variable dato contedrá sólo la información del parámetro (se elimina el título: name, state, etc...).
    char *dato;
    dato = strchr(linea, 9); //9 es el codigo ASCII para el tab horizontal.
    dato++;
    if(strncmp(linea, "Name", 4) == 0){
      strcpy(proc.nombre, dato);
    } else if(strncmp(linea, "State", 5) == 0){
      strcpy(proc.estado, dato);
    } else if(strncmp(linea, "VmSize", 6) == 0){
      strcpy(proc.tam.total, dato);
    } else if(strncmp(linea, "VmExe", 5) == 0){
      strcpy(proc.tam.text, dato);
    } else if(strncmp(linea, "VmData", 6) == 0){
      strcpy(proc.tam.data, dato);
    } else if(strncmp(linea, "VmStk", 5) == 0){
      strcpy(proc.tam.stack, dato);
    } else if(strncmp(linea, "voluntary", 9) == 0){
      strcpy(proc.cambiosv, dato);
    } else if(strncmp(linea, "nonvoluntary", 12) == 0){
      strcpy(proc.cambiosi, dato);
    }
  }
  //Se cierra el archivo.
  fclose(fp);
  //según el parámetro ingresado se llama el método para imprimir en consola o guardar en archivo.
  if(bandera == 0){
    imprimirProceso(proc);
  } else{
    guardarProceso(proc);
  }
  //exit(0);
}

///Este método imprimirá a información del proceso en consola.
void imprimirProceso(Proceso p){
  printf("Pid: %sEl nombre del proceso es: %sEl estado del proceso es: %sEl tamano total de imagen en memoria es: %s Tamano de la memoria en la region TEXT es: %s Tamano de la memoria en la region DATA es: %s Tamano de la memoria en la region STACK es: %sNumero de cambios de contexto realizados:\n Voluntarios: %s No voluntarios: %s\n", 
          p.id, p.nombre, p.estado, p.tam.total, p.tam.text, p.tam.data, p.tam.stack, p.cambiosv, p.cambiosi);
}

/**
 * Este método guardará la información del proceso en un archivo.
 * 
 */
void guardarProceso(Proceso p){
  fprintf(fpr, "Pid: %sEl nombre del proceso es: %sEl estado del proceso es: %sEl tamano total de imagen en memoria es: %s Tamano de la memoria en la region TEXT es: %s Tamano de la memoria en la region DATA es: %s Tamano de la memoria en la region STACK es: %sNumero de cambios de contexto realizados:\n Voluntarios: %s No voluntarios: %s\n", 
          p.id, p.nombre, p.estado, p.tam.total, p.tam.text, p.tam.data, p.tam.stack, p.cambiosv, p.cambiosi);
}

/**
 * Este metodo validará si el archivo que se desea abrir existe, recibe como parametro el id ingresado por el usuario para cada proceso y retornará 1 en caso de que exista y 0 en caso contrario.
 */
int  validararchivo(char *id){
   
  ///Se iniciliza la ruta del archivo que contiene la información del estado del proceso.
  strcpy(ruta, "/proc/");
  strcat(ruta, id );
  strcat(ruta, "/status" );
  //Se abre el archivo.
  fp = fopen(ruta, "r");
  if (fp == NULL){
    
    //exit(1);
    return 0;
  }
  return 1;
}