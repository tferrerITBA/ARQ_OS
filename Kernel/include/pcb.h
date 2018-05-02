//Process control block. Guarda informacion de los procesos
#include <sys/param.h>

#define NULL 0
#define CREATED 1
#define WAITING 2
#define BLOCKED 3
#define TERMINATED 4
#define RUNNING 5
#define BLOCK_SIZE 5

typedef struct pcbCDT{
    int pid;
    int state;
    void * stackPointer;
    void * stackOrigin;
    void * instructionPointer;
    void * heapOrigin;
    //Agregar campos a medida que se vayan necesitando
} pcb;

typedef pcb * Pcb;

typedef struct pcbTable{
    Pcb first;
    int size;
} pcbTable;

typedef pcbTable * PcbTable;

Pcb newPcb();
void addPcbToTable(Pcb pcb);
void removeProcessFromTable(pid_t pid);

