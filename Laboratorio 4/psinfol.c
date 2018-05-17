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
#define TAM_BUFFER 10
#define MAX_BUFFER 100

//Estructura de cada elemento de un archivo
typedef struct estructura_procesos
{
  int pid;
  char name[MAX_BUFFER];
  char state[MAX_BUFFER];
  char vmsize[MAX_BUFFER];
  char vmdata[MAX_BUFFER];
  char vmexe[MAX_BUFFER];
  char vmstk[MAX_BUFFER];
  int voluntary_ctxt_switches;
  int nonvoluntary_ctxt_switches;
} procesos_info;

sem_t silencia;
sem_t lleno;
sem_t vacio;


//Estructura de los identificadores de cada proceso
typedef struct params
{
  FILE *archivo;
  int pid;
  procesos_info datos; //aqui se almacena la otra estructura correspondiente a cada proceso
} parametros;


procesos_info load_info(FILE *ficheroStatus);
void print_info(procesos_info *pi);

int main(int argc, char *argv[])
{

  int i;

  // number of process ids passed as command line parameters
  // (first parameter is the program name)
  int n_procs = argc - 1;
  parametros *detalles;

  if (argc < 2)
  {
    printf("Error\n");
    exit(1);
  }
  /*Allocate memory for each process info*/
  detalles = (parametros *)malloc(sizeof(parametros) * n_procs);
  //assert(ficheroStatus != NULL);
  pthread_t hilos[n_procs + 1];
  sem_init(&silencia, 0, 1);
  sem_init(&lleno, 0, 0);
  sem_init(&vacio, 0, TAM_BUFFER);

  // Get information from status file
  for (i = 0; i < n_procs; i++)
  {
    char path[MAX_BUFFER];
    int pid = atoi(argv[i + 1]);
    procesos_info process;
    sprintf(path, "/proc/%d/status", pid);
    FILE *fpstatus = fopen(path, "r");

    if (fpstatus != NULL)
    {

      detalles[i].archivo = fpstatus;
      detalles[i].datos = process;
      detalles[i].pid = pid;
      //crear el hilo del proceso i correspondiente
    }
    else
    {
      printf("El proceso %s no fue encontrado\n\n", argv[i + 1]); 
      exit(1);
    }
  }

  

  // free heap memory
  free(detalles);
  sem_destroy(&silencia);
  sem_destroy(&lleno);
  sem_destroy(&vacio);
    return 0;
  
}

/**
 *  \brief load_info
 *
 *  Load process information from status file in proc fs
 *
 *  \param pid    (in)  process id 
 *  \param myinfo (out) process info struct to be filled
 */
procesos_info load_info(FILE *ficheroStatus)
{
  char buffer[MAX_BUFFER];
  char path[MAX_BUFFER];
  procesos_info processinfo;
  char *token;
  char *token2 = buffer;

#ifdef DEBUG
  printf("%s\n", path);
#endif // DEBUG
  
  while (fgets(buffer, MAX_BUFFER, ficheroStatus))
  {
    token = strtok_r(buffer, ":\t", &token2);
    strcpy(processinfo.pid, token);
    strcat(processinfo.pid, "\n");
    if (strstr(token, "Name"))
    {
      token = strtok_r(NULL, ":\t", &token2);
#ifdef DEBUG
      printf("%s\n", token);
#endif // DEBUG
      strcpy(processinfo.name, token);
    }
    else if (strstr(token, "State"))
    {
      token = strtok_r(NULL, ":\t", &token2);
      strcpy(processinfo.state, token);
    }
    else if (strstr(token, "VmSize"))
    {
      token = strtok_r(NULL, ":\t", &token2);
      strcpy(processinfo.vmsize, token);
    }
    else if (strstr(token, "VmData"))
    {
      token = strtok_r(NULL, ":\t", &token2);
      strcpy(processinfo.vmdata, token);
    }
    else if (strstr(token, "VmStk"))
    {
      token = strtok_r(NULL, ":\t", &token2);
      strcpy(processinfo.vmstk, token);
    }
    else if (strstr(token, "VmExe"))
    {
      token = strtok_r(NULL, ":\t", &token2);
      strcpy(processinfo.vmexe, token);
    }
    else if (strstr(token, "nonvoluntary_ctxt_switches"))
    {
      token = strtok_r(NULL, ":\t", &token2);
      processinfo.nonvoluntary_ctxt_switches = atoi(token);
    }
    else if (strstr(token, "voluntary_ctxt_switches"))
    {
      token = strtok_r(NULL, ":\t", &token2);
      processinfo.voluntary_ctxt_switches = atoi(token);
    }
#ifdef DEBUG
    printf("%s\n", token);
#endif
  }
  fclose(ficheroStatus);
  return processinfo;
}
/**
 *  \brief print_info
 *
 *  Print process information to stdout stream
 *
 *  \param pi (in) process info struct
 */
void print_info(procesos_info *pi)
{
  printf("PID: %d \n", pi->pid);
  printf("Nombre del proceso: %s", pi->name);
  printf("Estado: %s", pi->state);
  printf("TamaÃ±o total de la imagen de memoria: %s", pi->vmsize);
  printf("TamaÃ±o de la memoria en la regiÃ³n TEXT: %s", pi->vmexe);
  printf("TamaÃ±o de la memoria en la regiÃ³n DATA: %s", pi->vmdata);
  printf("TamaÃ±o de la memoria en la regiÃ³n STACK: %s", pi->vmstk);
  printf("NÃºmero de cambios de contexto realizados (voluntarios"
         "- no voluntarios): %d  -  %d\n\n",
         pi->voluntary_ctxt_switches, pi->nonvoluntary_ctxt_switches);
}
