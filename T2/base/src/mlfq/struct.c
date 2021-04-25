#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "struct.h"

Proceso* process_init(int pid, char* nombre, int prioridad, int inicio, int duracion) {
    Proceso* p = malloc(sizeof(Proceso));
    p -> pid = pid;
    strcpy(p -> nombre, nombre);
    p -> prioridad = prioridad;
    p -> inicio = inicio;
    p -> duracion = duracion;
    p -> estado = IDLE;
    p -> finished = false;
    p -> total_counter = 0;
    p -> turnaround_time = 0;
    p -> response_time = -1;
    p -> waiting_time = 0;
    p -> turnos_cpu = 0;
    p -> interrupciones = 0;
    return p;
}

Queue* queue_init() {
    Queue* q = malloc(sizeof(Queue));
    q -> head = NULL;
    q -> tail = NULL;
    q -> largo = 0;
    return q;
}

Node* node_init(Proceso* proceso) {
    Node* n = malloc(sizeof(Node));
    n -> prev = NULL;
    n -> next = NULL;
    n -> proceso = proceso;
    return n;
}
