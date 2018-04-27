#include <sys/types.h>
#include "include/process.h"
#include "include/pcb.h"
#include "include/scheduler.h"

Process newProcess(pid_t pid, void * rip, void * rsp) {
    Process newP = malloc(sizeof(process));
    newP->nextInstruction = 0; /** Se deberia hacer un programa en asm para pasar como
                                *  paramentro el RIP del padre
                                */
    newP->pcb = newPcb(pid); /** Que pid le pasamos */
    newP->stack = malloc(STACK_SIZE);
    return newP;
}

int terminateProcess(Process p) {
    p->pcb->state = TERMINATED;
}

pid_t fork() {

    pid_t newPid = ++pidCount;
    void * instructionPointer;
    void * stackPointer;
    /** Aca es necesario hacer un programa de assembler para obtener el RIP,
     *  la direccion del stack,y toda la informacion necesaria del proceso que llama.
     *  El fork copia toda la informacion del proceso padre. Tambien hay que crear un
     *  nuevo pid para el hijo
     *  Lo que se hace es copiar el proceso que forkeo, sol cambiarle el pid y encolarlo
     *  No estoy seguro pero creo que habria que hacer una copia del stack asi no se pisan
     *  el padre y el hijo
     */

    Process newP = newProcess(newPid, instructionPointer, stackPointer);
    enqueueProcess(readyQueue,newP->pcb);

    if(runningPcb->pid == newPid) {
        return 0;
    }

    return runningPcb->pid;
}

