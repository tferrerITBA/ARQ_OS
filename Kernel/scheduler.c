#include "include/scheduler.h"
#include "include/memoryManager.h"
#include "include/videoMode.h"

extern void printPcb(Pcb pcb);

void * schedule(void * rsp) {

    if(runningPcb == NULL && isEmpty(readyQueue)) {
        putnString("null\n",5);
        return NULL;

    }
    if(isEmpty(readyQueue)) {
        return runningPcb->stackPointer;
    }

    putnString("EN SCHEDULER!\n",14);


    runningPcb->stackPointer = rsp;

    if(runningPcb->state == TERMINATED) {
        free(runningPcb);
    } else {
        putnString("enqueue\n",8);
        enqueueProcess(runningPcb);
    }

    runningPcb = dequeue(readyQueue);
    printPcb(runningPcb);
    runningPcb->state = RUNNING;
    printHex(runningPcb->stackPointer);
    put_char('\n');
    return runningPcb->stackPointer;
}

void enqueueProcess(Pcb pcb) {
    pcb->state = WAITING;
    enqueue(readyQueue,pcb);
}

void createReadyQueue() {
    readyQueue = newQueue(QUEUE_SIZE);
}
