#include "include/scheduler.h"
#include "include/memoryManager.h"
#include "include/videoMode.h"

extern void printPcb(Pcb pcb);
extern void freeProcessResources(Pcb pcb);

void * schedule(void * rsp) {
    Pcb terminated = NULL;
    Pcb blocked = NULL;

    if (runningPcb == NULL && isEmpty(readyQueue)) {
        return NULL;
    }

    if (isEmpty(readyQueue)) {
        return rsp;
    }

    if (runningPcb->state == RUNNING) {
        putString("Hola\n");
        runningPcb->stackPointer = rsp;
        enqueueProcess(runningPcb);
    } else if (runningPcb->state == TERMINATED) {
        terminated = runningPcb;
    } else if(runningPcb->state == BLOCKED) {
        runningPcb->stackPointer = rsp;
        enqueue(blockedQueue,runningPcb);
        putString("EL que estaba corriendo se bloqueo\n");
    }

    if (terminated != NULL) {
        freeProcessResources(terminated);
    }

    runningPcb = dequeue(readyQueue);

    while (runningPcb->state == TERMINATED) {
        terminated = runningPcb;
        runningPcb = dequeue(readyQueue);
    }

    if (terminated != NULL) {
        freeProcessResources(terminated);
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
