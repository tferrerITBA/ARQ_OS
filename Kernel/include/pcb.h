//Process control block. Guarda informacion de los procesos

#define CREATED 1
#define WAITING 2
#define BLOCKED 3
#define TERMINATED 4
#define RUNNING 5

typedef struct pcbCDT{
    int pid;
    int state;
    //Agregar campos a medida que se vayan necesitando
} pcb;

typedef pcb * Pcb;

Pcb newPcb(int pid);


