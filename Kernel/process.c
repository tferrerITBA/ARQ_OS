#include "include/process.h"
#include "include/memoryManager.h"
#include "include/videoMode.h"

extern void enqueueProcess(Pcb pcb);

Process newProcess(void * stackPointer, void * stackBase, void * heap) {

    Process newP = malloc(sizeof(process));
    newP->pcb = newPcb();
    newP->pcb->stackPointer = stackPointer;
    newP->pcb->stackBase = stackBase;
    newP->pcb->heapBase = heap;
    enqueueProcess(newP->pcb);
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
    enqueueProcess(newP->pcb);

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
    int i;
    int zero = 0;
    int flags = 0x202;
    void * stack = initializeProcessStack();
    void * heap = reserveHeapSpace(1);
    void * stackPointer = stack;
    for (i = 0; i < 20; i ++) {
        stackPointer -= 8;
        if( i == 2) { //rflag
            memcpy(stackPointer, &flags, 8);
        } else if(i == 4) {
            memcpy(stackPointer,ti,8);
        } else {
            memcpy(stackPointer, &zero, 8);
        }
    }
    newProcess(stackPointer,stack,heap);
}

pid_t getRunningProcessPid() {
    return runningPcb->pid;
}

