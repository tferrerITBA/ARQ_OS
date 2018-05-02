#include "include/process.h"

Process newProcess(void * rsp, void * stackOrigin, void * heap) {
    Process newP = malloc(sizeof(process));
    newP->pcb = newPcb();
    newP->pcb->stackPointer = rsp;
    newP->pcb->stackOrigin = stackOrigin;
    newP->pcb->heapOrigin = heap;
    addPcbToTable(newP->pcb);
    return newP;
}

int terminateProcess(Process p) {
    removeProcessFromTable(p->pcb->pid);
    p->pcb->state = TERMINATED;
}

pid_t fork() {

    void * instructionPointer;
    void * childStackPointer;
    void * childStackLimit = duplicateStack(childStackPointer);
    void * childHeap = duplicateHeap();


    Process newP = newProcess(childStackPointer, childStackLimit + STACK_SIZE,);
    enqueueProcess(readyQueue,newP->pcb);

    if(runningPcb->pid == newP->pcb->pid) {
        return 0;
    }

    return runningPcb->pid;
}

void * duplicateStack(void * stackPointer) {
    void * stackLimit = malloc(STACK_SIZE)
    size_t stackLen = runningPcb->stackOrigin - runningPcb->stackPointer;
    stackPointer = stackLimit + STACK_SIZE - stackLen;
    memcpy(stackPointer,runningPcb->stackPointer,stackLen);
    return stackPointer;
}

void * duplicateHeap() {
    void * heap = malloc(HEAP_SIZE);
    memcpy(heap,runningPcb->heapOrigin,HEAP_SIZE);
    return heap;
}

