#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../file_manager/manager.h"
#include<signal.h>
#include<math.h>
#include <time.h>

void situar_procesos_primera_cola(){

}

int main(int argc, char **argv){
  
  InputFile* lista_inicial = read_file(argv[1]);
  // Definimos la cantidad de procesos del input
  int cantidad_procesos_a_ejecutar = lista_inicial -> len;
  // Definimos la cantidad de colas
  int cantidad_colas = atoi(argv[3]);
  // q es parte del input y sirve para calcular el quantium
  int q = atoi(argv[4]);
  // La siguiente variable servira para ver cuantos procesos han terminado
  int procesos_terminados = 0;
  // Cantidad de procesos que han entrado al sistema
  int procesos_entrados_sistema = 0;
  // Queremos ver el tiempo que ejcutara nuestro programa
  int tiempo_maximo = 150;
  // creamos nuestro arreglo de colas
  Queue* arreglo_colas[cantidad_colas]; 
  for (int i = 0; i < cantidad_colas; i++)
  {
    /* code */
    arreglo_colas[i] = queue_init(i, cantidad_colas, q, cantidad_procesos_a_ejecutar);
  }
  // tiempo actual
  int tiempo_actual = 0;
  while (tiempo_actual <= tiempo_maximo && procesos_terminados < cantidad_procesos_a_ejecutar)
  {
    /* code */
    if (procesos_entrados_sistema < cantidad_procesos_a_ejecutar)
    {
      /* code */
      for (int i = 0; i < cantidad_procesos_a_ejecutar; i++){
        printf("tiempo actual: %i\n", tiempo_actual);
        int tiempo_inicio_proceso = atoi(lista_inicial -> lines[i][2]);
        if (tiempo_inicio_proceso == tiempo_actual){
          // El indice al que entrara el nuevo proceso en la cola 0
          int indice = arreglo_colas[0] -> cantidad_procesos;
          // Creamos el proceso que esta listo para entrar al sistema
          Proceso* proceso_entrante = proceso_init(); 
          // Le asignamos un valor a cada atributo del proceso,
          // al nombre, pid, prioridad, cycles, wait y waiting_delay
          strcpy(proceso_entrante->nombre, lista_inicial -> lines[i][0]);
          // con atoi Cada atributo del proceso lo pasamos a int
          proceso_entrante -> pid = atoi(lista_inicial -> lines[i][1]);
          proceso_entrante -> prioridad = arreglo_colas[0] -> prioridad;
          proceso_entrante -> cycles = atoi(lista_inicial -> lines[i][3]);
          proceso_entrante -> wait = atoi(lista_inicial -> lines[i][4]);
          proceso_entrante -> waiting_delay = atoi(lista_inicial -> lines[i][5]);
          // ---------------------------------------------
          // arreglo_colas[0] = primera cola, el proceso que acabamos de crear se pone 
          // en la primera cola y queda registrado en la lista de procesos de la cola.
          (arreglo_colas[0] -> lista_procesos[indice]) = proceso_entrante;
          // sumamos la cantidad de procesos que tiene la cola 0 para saber donde insertar
          // el proximo proceso
          arreglo_colas[0] -> cantidad_procesos += 1;
          // sumamos uno al contador de procesos entrados al sistema para una vez que entren todos
          // no seguir revisando (entrando a este for)
          procesos_entrados_sistema += 1;
          printf("-----------------------------\n");
          printf("tiempo: %i\n", tiempo_actual);
          printf("nombre proceso: %s\n", (arreglo_colas[0] -> lista_procesos[indice]) -> nombre);
          printf("Cantidad procesos en sistema: %i\n", procesos_entrados_sistema);
          printf("-----------------------------\n");
          }
      }
    }
    tiempo_actual += 1;
  }
  exit(0);
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