#include "include/process.h"
#include "include/queue.h"
#include "include/scheduler.h"
#include "include/pcb.h"
#include "include/stack.h"

void * schedule() {

    /** Esta funcion tiene que ser llamada desde la interrupcion del tiemr tick **/
    if(isEmpty(readyQueue)) {
        return NULL;
    }

    runningPcb->stackPointer = getRSP();
    runningPcb->instructionPointer = getRIP();

    if(runningPcb->state == TERMINATED) {
        free(runningPcb);
    } else if(runningPcb->state == RUNNING) {
        runningPcb->state = WAITING;
        enqueueProcess(readyQueue,runningPcb);
    }
    runningPcb = dequeue(readyQueue);
    runningPcb->state = RUNNING;
    setRIP(runningPcb->instructionPointer);

    return runningPcb->stackPointer;

    /** Investigar que hacer si el proceso se bloquea **/
}

void enqueueProcess(Queue q, Pcb pcb) {
    pcb->state = WAITING;
    enqueue(q,pcb);
}

void startScheduler() {

    /** Obtener el instruction pointer del scheduler y crearle un stack **/
    newProcess(++pidCount,);
    readyQueue = newQueue(QUEUE_SIZE);


}
