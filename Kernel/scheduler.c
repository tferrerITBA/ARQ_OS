#include "include/scheduler.h"
#include "include/memoryManager.h"
#include "include/videoMode.h"
#include "include/pcb.h"

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
        runningPcb->stackPointer = rsp;
        enqueueProcess(runningPcb);
    } else if (runningPcb->state == TERMINATED) {
        terminated = runningPcb;
    } else if(runningPcb->state == BLOCKED) {
        runningPcb->stackPointer = rsp;
        addPcbToTable(blockedProcesses,runningPcb);
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
