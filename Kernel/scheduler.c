#include "include/scheduler.h"
#include "include/memoryManager.h"
#include "include/videoMode.h"

extern void printPcb(Pcb pcb);

void * schedule(void * rsp) {

    if(runningPcb == NULL && isEmpty(readyQueue)) {
        putString("NULL Running Pcb\n");
        return NULL;
    }

    if(isEmpty(readyQueue)) {
        //putString("Empty queue\n");
        return rsp;
    }

    if(runningPcb->state == RUNNING) {
        putString("Enqueuing\n");
        enqueueProcess(runningPcb);
    }

    runningPcb = dequeue(readyQueue);
    runningPcb->state = RUNNING;
    if(runningPcb->pid == 2){
        putString("Dequeueing forked process\nStack pointer: ");
        printHex(runningPcb->stackPointer);
        putString("\n");

    }

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
