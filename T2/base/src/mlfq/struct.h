#include <stdbool.h>

#pragma once


typedef enum estado {
    RUNNING,
    READY,
    WAITING,
    FINISHED,
    IDLE
} Estado;

typedef struct proceso {
    int pid;
    char nombre[32];
    int prioridad;
    int inicio;
    int duracion;
    Estado estado;
    bool in_queue;
    bool finished;
    int quantum_counter;
    int total_counter;
    int turnaround_time;
    int response_time;
    int waiting_time;
    int turnos_cpu;
    int interrupciones;
} Proceso;

typedef struct node {
    struct node* prev;
    struct node* next;
    Proceso* proceso;
} Node;

typedef struct queue {
    Node* head;
    Node* tail;
    int largo;
} Queue;

bool has_finished(Proceso* proceso);

void queue_printer(Node* node);

Queue* queue_init();

Queue* try_queue_up(Proceso* proceso, Queue* queue);

Proceso* queue_pop(Queue* queue);

void append(Proceso* process, Queue* queue);

Proceso* proceso_init();