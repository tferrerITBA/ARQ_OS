#include "include/scheduler.h"
#include "include/memoryManager.h"
#include "include/videoMode.h"

static int terminalIsBlocked = FALSE;

void * schedule() {

    if(runningPcb == NULL && isEmpty(readyQueue)) {
        putnString("null\n",5);
        return NULL;
    }
    if(isEmpty(readyQueue)) {
        putnString("vacia\n",6);
        return runningPcb->stackPointer;
    }

    putnString("EN SCHEDULER!\n",14);

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
