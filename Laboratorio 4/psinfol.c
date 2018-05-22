/**
 *   \file psinfo-l.c
 *   \brief base code for the program psinfo-l
 *          
 *  This program prints some basic information for a given 
 *  list of processes.
 *  You can use this code as a basis for implementing parallelization 
 *  through the pthreads library. 
 *
 *   \author: Danny Munera - Sistemas Operativos UdeA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_BUFFER 100

//Declaración de estructuras
typedef struct p_ {
  int pid;
  char name[MAX_BUFFER];
  char state[MAX_BUFFER];
  char vmsize[MAX_BUFFER];
  char vmdata[MAX_BUFFER];
  char vmexe[MAX_BUFFER];
  char vmstk[MAX_BUFFER];
  int voluntary_ctxt_switches;
  int nonvoluntary_ctxt_switches;
} proc_info;

typedef struct par {
  int pid;
  FILE *archivo;
} parametros;

//Declaración de funciones
proc_info load_info(FILE*);
void print_info(proc_info*);
void* productor(void *parametros);

//Declaracion de variables globales
proc_info buffer[10]; //Se establece un tamaño máximo de 10 procesos en el buffer
int indice = 0; //Indice del buffer
sem_t mutex;
sem_t full;
sem_t empty;
  
//Hilo principal/padre de ejecución
int main(int argc, char *argv[]){
  if(argc < 2){
    printf("Error\n");
    exit(1);
  }

  int i;
  int n_procs = argc - 1;
  parametros* p;
  pthread_t hilos[n_procs + 1];

  //Inicialización de los semáforos
  sem_init(&mutex, 0, 1);
  sem_init(&full, 0, 0);
  sem_init(&empty, 0, 10);

  p = (parametros *)malloc(sizeof(parametros) * n_procs);
  assert(p!=NULL);
  
  // Generación del hilo de cada proceso.
  for(i = 0; i < n_procs; i++){
    //Abrir el archivo
    FILE *fpstatus;
    char path[MAX_BUFFER];
    int pid = atoi(argv[i + 1]);
    sprintf(path, "/proc/%d/status", pid);
    fpstatus = fopen(path, "r");
    assert(fpstatus != NULL); //El archivo pudo ser abierto correctamente

    //Generación de la estructura con los parámetros del hilo
    p[i].archivo = fpstatus;
    p[i].pid = pid;
    pthread_create(&hilos[i], NULL, &productor, &p[i]);
    pthread_join(hilos[i], NULL);
  }

  //Impresión de los procesos generados por los hilos
  for (i = 0; i < n_procs; i++){
    sem_wait(&full);
    sem_wait(&mutex);
    int j = i % 10;
    print_info(&buffer[j]);
    sem_post(&mutex);
    sem_post(&empty);
  }
  
  // free heap memory
  free(p);

  return 0;
}

//Método encargado de obtener la información del proceso y almacenarlo en el buffer
void* productor(void *p){
  parametros *param = (parametros *)p;
  proc_info proceso = load_info(param->archivo);
  proceso.pid = param->pid;
  sem_wait(&empty);
  sem_wait(&mutex);
  buffer[indice] = proceso;
  indice = (indice + 1) % 10;
  sem_post(&mutex);
  sem_post(&full);
}

/**
 *  \brief load_info
 *
 *  Load process information from status file in proc fs
 *
 *  \param pid    (in)  process id 
 *  \param myinfo (out) process info struct to be filled
 */
proc_info load_info(FILE *file){
  proc_info myinfo;
  char buffer[MAX_BUFFER];
  char* token;
  
  while (fgets(buffer, MAX_BUFFER, file)) {
    token = strtok(buffer, ":\t");
    if (strstr(token, "Name")){
      token = strtok(NULL, ":\t");
      strcpy(myinfo.name, token);
    }else if (strstr(token, "State")){
      token = strtok(NULL, ":\t");
      strcpy(myinfo.state, token);
    }else if (strstr(token, "VmSize")){
      token = strtok(NULL, ":\t");
      strcpy(myinfo.vmsize, token);
    }else if (strstr(token, "VmData")){
      token = strtok(NULL, ":\t");
      strcpy(myinfo.vmdata, token);
    }else if (strstr(token, "VmStk")){
      token = strtok(NULL, ":\t");
      strcpy(myinfo.vmstk, token);
    }else if (strstr(token, "VmExe")){
      token = strtok(NULL, ":\t");
      strcpy(myinfo.vmexe, token);
    }else if (strstr(token, "nonvoluntary_ctxt_switches")){
      token = strtok(NULL, ":\t");
      myinfo.nonvoluntary_ctxt_switches = atoi(token);
    }else if (strstr(token, "voluntary_ctxt_switches")){
      token = strtok(NULL, ":\t");
      myinfo.voluntary_ctxt_switches = atoi(token);
    }
  }
  fclose(file);
  return myinfo;
}

/**
 *  \brief print_info
 *
 *  Print process information to stdout stream
 *
 *  \param pi (in) process info struct
 */ 
void print_info(proc_info* pi){
  printf("PID: %d \n", pi->pid);
  printf("Nombre del proceso: %s\n", pi->name);
  printf("Estado: %s\n", pi->state);
  printf("Tamaño total de la imagen de memoria: %s\n", pi->vmsize);
  printf("Tamaño de la memoria en la región TEXT: %s\n", pi->vmexe);
  printf("Tamaño de la memoria en la región DATA: %s\n", pi->vmdata);
  printf("Tamaño de la memoria en la región STACK: %s\n", pi->vmstk);
  printf("Número de cambios de contexto realizados (voluntarios"
	 "- no voluntarios): %d  -  %d\n\n", pi->voluntary_ctxt_switches,  pi->nonvoluntary_ctxt_switches);
}
