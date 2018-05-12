#include "include/scheduler.h"
#include "include/memoryManager.h"
#include "include/videoMode.h"

extern void printPcb(Pcb pcb);

void * schedule(void * rsp) {

    if(runningPcb == NULL && isEmpty(readyQueue)) {
        return NULL;
    }

    if(isEmpty(readyQueue)) {
        return rsp;
    }

    if(runningPcb->state == RUNNING) {
        enqueueProcess(runningPcb);
    }

    Pcb deq = dequeue(readyQueue);
    runningPcb = deq;
    runningPcb->state = RUNNING;

    putString("Stack pointer for dequeued process: ");
    printHex(runningPcb->stackPointer);
    put_char('\n');


    //printPcb(runningPcb);
    return runningPcb->stackPointer;
}

void enqueueProcess(Pcb pcb) {
    pcb->state = WAITING;
    enqueue(readyQueue,pcb);
}

void createReadyQueue() {
    readyQueue = newQueue(sizeof(void *));
}

void printStack(trapframe * tf) {
    putString("RIP: 0x");
    printHex(tf->ip);
    putString("\nCS: 0x");
    printHex(tf->cs);
    putString("\nRFLAGS: 0x");
    printHex(tf->flags);
    putString("\nRSP: 0x");
    printHex(tf->sp);
    putString("\nSS: 0x");
    printHex(tf->ss);
    putString("\n");

}

void printRIP(trapframe *tf) {
    putString("RIP: ");
    printHex(tf->ip);
    put_char('\t');

}
