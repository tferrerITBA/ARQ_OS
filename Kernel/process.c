#include "include/process.h"
#include "include/memoryManager.h"
#include "include/videoMode.h"

extern void enqueueProcess(Queue q, Pcb pcb);

Process newProcess(void * stackPointer, void * stackBase, void * heap) {
    Process newP = malloc(sizeof(process));
    newP->pcb = newPcb();
    newP->pcb->stackPointer = stackPointer;
    newP->pcb->stackBase = stackBase;
    newP->pcb->heapBase = heap;
    enqueueProcess(readyQueue,newP->pcb);
    addPcbToTable(newP->pcb);
    return newP;
}

int terminateProcess(Process p) {
    removeProcessFromTable(p->pcb->pid);
    free(p->pcb->heapBase);
    free(p->pcb->stackBase-STACK_SIZE);
    free(p->pcb);
    p->pcb->state = TERMINATED;
    return 1;
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
    void * stackLimit = initializeProcessStack();
    size_t stackLen = runningPcb->stackBase - runningPcb->stackPointer;
    stackPointer = stackLimit + STACK_SIZE - stackLen;
    memcpy(stackPointer,runningPcb->stackPointer,stackLen);
    return stackPointer;
}

void * duplicateHeap() {
    void * heap = reserveHeapSpace(runningPcb->pid);
    memcpy(heap,runningPcb->heapBase,HEAP_SIZE);
    return heap;
}

void initializeFirstProcess(terminalCaller ti) {
    void * stack = initializeProcessStack();
    void * heap = reserveHeapSpace(1);
    memcpy(stack,ti, sizeof(terminalCaller));
    newProcess(stack,stack,heap);
}

pid_t getRunningProcessPid() {
    return runningPcb->pid;
}

