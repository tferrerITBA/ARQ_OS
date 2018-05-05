#include "include/process.h"

Process newProcess(void * stackPointer, void * stackBase, void * heap) {
    Process newP = malloc(sizeof(process));
    newP->pcb = newPcb();
    newP->pcb->stackPointer = stackPointer;
    newP->pcb->stackBase = stackBase;
    newP->pcb->heapBase = heap;
    addPcbToTable(newP->pcb);
    return newP;
}

int terminateProcess(Process p) {
    removeProcessFromTable(p->pcb->pid);
    free(p->pcb->heapBase);
    free(p->pcb->stackBase-STACK_SIZE);
    free(p->pcb);
    p->pcb->state = TERMINATED;
}

pid_t processFork() {

    void * childStackPointer;
    void * childStackLimit = duplicateStack(childStackPointer);
    void * childHeap = duplicateHeap();

    Process newP = newProcess(childStackPointer, childStackLimit + STACK_SIZE, childHeap);
    enqueueProcess(readyQueue,newP->pcb);

    if(runningPcb->pid == newP->pcb->pid) {
        return 0;
    }

    return runningPcb->pid;
}

void * duplicateStack(void * stackPointer) {
    void * stackLimit = malloc(STACK_SIZE);
    size_t stackLen = runningPcb->stackBase - runningPcb->stackPointer;
    stackPointer = stackLimit + STACK_SIZE - stackLen;
    memcpy(stackPointer,runningPcb->stackPointer,stackLen);
    return stackPointer;
}

void * duplicateHeap() {
    void * heap = malloc(HEAP_SIZE);
    memcpy(heap,runningPcb->heapBase,HEAP_SIZE);
    return heap;
}

void initializeFirstProcess(terminalCaller ti) {
    void * stack = malloc(STACK_SIZE);
    void * heap = malloc(HEAP_SIZE);
    memcpy(stack,ti, sizeof(terminalCaller));
    newProcess(stack,stack,heap);

}

