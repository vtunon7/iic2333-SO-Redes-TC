#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "struct.h"


int main(int argc, char **argv){
  FILE* fp;
  Proceso* head;
  Queue* queue;
  int prioridad, inicio, duracion;
  int pid = 0;
  int quantum = 0;
  bool listo = false;
  bool running = false;
  int cantidad_procesos = 1;
  queue = queue_init();
  char* nombre = malloc(sizeof(char)*32);
  Proceso** procesos = malloc(sizeof(Proceso*)*cantidad_procesos);
  printf("Hello T2we!\n");

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

  FILE* fpout = fopen(argv[2], "w");
    for (int i=0; i < pid; i++) {
        fprintf(fpout, "%s, %i, %i, %i, %i, %i\n", procesos[i] -> nombre, procesos[i] -> turnos_cpu, 
                procesos[i] -> interrupciones, procesos[i] -> turnaround_time, 
                procesos[i] -> response_time, procesos[i] -> waiting_time);
    }
    fclose(fpout); 
}
