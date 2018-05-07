#include "include/scheduler.h"

static int terminalIsBlocked = FALSE;

void * schedule() {

    if(runningPcb == NULL) {
        return NULL;
    }
    if(isEmpty(readyQueue)) {
        return runningPcb->stackPointer;
    }

    runningPcb->stackPointer = getRSP();

    if(runningPcb->state == TERMINATED) {
        free(runningPcb);
    } else if(runningPcb->state == RUNNING) {
        enqueueProcess(readyQueue,runningPcb);
    } else if(runningPcb->state == BLOCKED) {
        terminalIsBlocked = TRUE;
    }
    runningPcb = dequeue(readyQueue);
    runningPcb->state = RUNNING;

    return runningPcb->stackPointer;
}

void enqueueProcess(Queue q, Pcb pcb) {
    pcb->state = WAITING;
    enqueue(q,pcb);
}

void createReadyQueue() {
    readyQueue = newQueue(QUEUE_SIZE);
}
