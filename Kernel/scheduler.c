#include "include/scheduler.h"

void * schedule() {

    if(isEmpty(readyQueue)) {
        return NULL;
    }

    runningPcb->stackPointer = getRSP();

    if(runningPcb->state == TERMINATED) {
        free(runningPcb);
    } else if(runningPcb->state == RUNNING) {
        enqueueProcess(readyQueue,runningPcb);
    } else if(runningPcb->state == BLOCKED) {
        //TODO:
    }
    runningPcb = dequeue(readyQueue);
    runningPcb->state = RUNNING;

    return runningPcb->stackPointer;

    /** Investigar que hacer si el proceso se bloquea **/
}

void enqueueProcess(Queue q, Pcb pcb) {
    pcb->state = WAITING;
    enqueue(q,pcb);
}

void startScheduler() {

    void * stack = malloc(STACK_SIZE);
    void * heap = malloc(HEAP_SIZE);
    Process scheduler = newProcess(stack,stack,heap);
    readyQueue = newQueue(QUEUE_SIZE);
}
