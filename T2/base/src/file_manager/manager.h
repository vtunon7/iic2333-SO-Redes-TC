#include <stdbool.h>
// Tells the compiler to compile this file once
#pragma once

// Define compile-time constants
#define MAX_SPLIT 255
#define BUFFER_SIZE 4096

// Define the struct
typedef struct inputfile {
  int len;
  char*** lines;  // This is an array of arrays of strings
} InputFile;

typedef struct proceso {
    int pid;
    char nombre[32];
    int prioridad;
    int duracion;
    int estado; // 1 -> RUNNING, 2 -> READY, 3-> WAITING, 4 -> FINISHED
    bool in_queue;
    bool finished;
    int cycles;
    int wait;
    int waiting_delay;
    //int quantum_counter;
    //int total_counter;
    //int turnaround_time;
    //int response_time;
    //int waiting_time;
    //int turnos_cpu;
    //int interrupciones;
} Proceso;

typedef struct queue {
    Proceso* lista_procesos[2048];
    int quantium;
    int prioridad;
    int cantidad_procesos;
} Queue;

// Declare functions
InputFile* read_file(char* filename);
void input_file_destroy(InputFile* input_file);
Proceso* proceso_init(); 
bool has_finished(Proceso* proceso);
Queue* queue_init(int lugar_en_la_cola, int cantidad_colas, int q, int cantidad_procesos_a_ejecutar);
Queue* try_queue_up(Proceso* proceso, Queue* queue);
Proceso* queue_pop(Queue* queue);
void append(Proceso* process, Queue* queue);