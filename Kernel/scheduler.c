#include "include/scheduler.h"
#include "include/memoryManager.h"
#include "include/videoMode.h"

extern void printPcb(Pcb pcb);

void * schedule(void * rsp) {

    if(runningPcb == NULL && isEmpty(readyQueue)) {
        putnString("null\n",5);
        return NULL;

    }

    runningPcb->stackPointer = rsp;

    if(isEmpty(readyQueue)) {
        return runningPcb->stackPointer;
    }

    putnString("EN SCHEDULER! Cola no vacia\n",14);

    if(runningPcb->state == TERMINATED) {
        free(runningPcb);
    } else {
        putnString("enqueue\n",8);
        enqueueProcess(runningPcb);
    }

    runningPcb = dequeue(readyQueue);
    printHex(runningPcb->stackPointer);
    putString("\n--------\n");
    printPcb(runningPcb);
    runningPcb->state = RUNNING;
    printPcb(runningPcb);
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
    putString("RIP: 0x");
    printHex(tf->ip2);
    putString("\nCS: 0x");
    printHex(tf->cs2);
    putString("\nRFLAGS: 0x");
    printHex(tf->flags2);
    putString("\nRSP: 0x");
    printHex(tf->sp2);
    putString("\nSS: 0x");
    printHex(tf->ss2);
    putString("\n");
    putString("RIP: 0x");
    printHex(tf->ip3);
    putString("\nCS: 0x");
    printHex(tf->cs3);
    putString("\nRFLAGS: 0x");
    printHex(tf->flags3);
    putString("\nRSP: 0x");
    printHex(tf->sp3);
    putString("\nSS: 0x");
    printHex(tf->ss3);
    putString("\n");
    putString("RIP: 0x");
    printHex(tf->ip4);
    putString("\nCS: 0x");
    printHex(tf->cs4);
    putString("\nRFLAGS: 0x");
    printHex(tf->flags4);
    putString("\nRSP: 0x");
    printHex(tf->sp4);
    putString("\nSS: 0x");
    printHex(tf->ss4);
    putString("\n");
}
