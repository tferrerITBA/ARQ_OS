//Process control block. Guarda informacion de los procesos

#define CREATED 1

typedef struct pcbCDT{
    int pid;
    int state;
    //Agregar campos a medida que se vayan necesitando
} pcb;

typedef pcb * Pcb;
