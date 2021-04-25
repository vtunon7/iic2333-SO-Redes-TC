#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../file_manager/manager.h"


int main(int argc, char **argv){
  FILE* fp;
  Proceso* head;
  Queue* queue = NULL;
  int prioridad, inicio, duracion;
  int pid = 0;
  int quantum = 0;
  bool listo = false;
  bool running = false;
  int cantidad_procesos = 1;
  char* nombre = malloc(sizeof(char)*32);
  Proceso** procesos = malloc(sizeof(Proceso*)*cantidad_procesos);
  InputFile* lista_inicial = read_file(argv[1]);
  //printf("%i\n", lista_inicial -> len);
  printf("%s\n", lista_inicial -> lines[0][1]);
  printf("%s\n", lista_inicial -> lines[0][2]);
  printf("%s\n", lista_inicial -> lines[0][3]);
  // Definimos la cantidad de colas
  int cantidad_colas = atoi(argv[3]);
  // q es parte del input y sirve para calcular el quantium
  int q = atoi(argv[4]);
  // creamos nuestro arreglo de colas
  Queue* arreglo_colas[cantidad_colas]; 
  for (int i = 0; i < cantidad_colas; i++)
  {
    /* code */
    arreglo_colas[i] = queue_init(i, cantidad_colas, q);
  }
  
  printf("cantidad_colas: %i\n", cantidad_colas);

  if (argc < 5){
    fprintf(stderr, "Uso: %s <file> <output> <Q> <q> <S>\n", argv[0]);
        free(nombre);
        free(queue);
        free(procesos);
        return 1;
    }
  
  if ((fp = fopen(argv[1], "r")) == NULL) {
        perror("fopen source-file");
        free(nombre);
        free(queue);
        free(procesos);
        return 1;
    }
  
  
  while (fscanf(fp, "%s %i %i %i", nombre, &prioridad, &inicio, &duracion) == 4) {
      //int* subprocesos = malloc(sizeof(int) * (2 * process_length - 1));
      //for (int i=0; i < (2*process_length - 1); i++) {
        //  fscanf(fp, "%i", &subprocesses[i]);
      //}
      Proceso* proceso = proceso_init(pid, nombre, prioridad, inicio, duracion);
      if (pid == cantidad_procesos) {  // If size of procesos won't be enough
          Proceso** nuevo = malloc(sizeof(Proceso*) * cantidad_procesos * 2);
          for (int i=0; i < cantidad_procesos; i++){
              nuevo[i] = procesos[i];
          }
          cantidad_procesos *= 2;
          free(procesos);
          procesos = nuevo;
      }
      procesos[pid] = proceso;
      pid++;
  }
  fclose(fp);
}
/**
  FILE* fpout = fopen(argv[2], "w");
    for (int i=0; i < pid; i++) {
        fprintf(fpout, "%s, %i, %i, %i, %i, %i\n", procesos[i] -> nombre, procesos[i] -> turnos_cpu, 
                procesos[i] -> interrupciones, procesos[i] -> turnaround_time, 
                procesos[i] -> response_time, procesos[i] -> waiting_time);
    }
    fclose(fpout); 
}
*/