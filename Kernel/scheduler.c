#include "include/scheduler.h"
#include "include/memoryManager.h"
#include "include/videoMode.h"

extern void printPcb(Pcb pcb);
extern void freeProcessResources(Pcb pcb);

void * schedule(void * rsp) {
    Pcb terminated = NULL;

    if (runningPcb == NULL && isEmpty(readyQueue)) {
        return NULL;
    }

    if (isEmpty(readyQueue)) {
        return rsp;
    }

    if (runningPcb->state == BLOCKED) {
        putString("proc bloquea3\n");
    }

    if (runningPcb->state == RUNNING || runningPcb->state == BLOCKED) {
        runningPcb->stackPointer = rsp;
        enqueueProcess(runningPcb);
    } else if (runningPcb->state == TERMINATED) {
        terminated = runningPcb;
    }

    runningPcb = dequeue(readyQueue);


    while (runningPcb->state == BLOCKED) {
        runningPcb->stackPointer = rsp;
        enqueueProcess(runningPcb);
        runningPcb = dequeue(readyQueue);
    }


    runningPcb->state = RUNNING;

    if (terminated != NULL) {
        freeProcessResources(terminated);
    }

    return runningPcb->stackPointer;
}

void enqueueProcess(Pcb pcb) {
    pcb->state = READY;
    enqueue(readyQueue,pcb);
}

void createReadyQueue() {
    readyQueue = newQueue(sizeof(void *));
}
