#include "include/process.h"

Process newProcess(void * stackPointer, void * stackBase, void * heap, pid_t newPid) {

    Process newP = malloc(sizeof(process),newPid);
    newP->pcb = newPcb(newPid);
    newP->pcb->stackPointer = stackPointer;
    newP->pcb->stackBase = stackBase;
    newP->pcb->heapBase = heap;
    addPcbToTable(newP->pcb);
    enqueueProcess(newP->pcb);
    return newP;
}

void terminateProcess(pid_t pid) {
    Pcb p = getProcess(pid);
    if(p != 0) {
        p->state = TERMINATED;
    }
}

void freeProcessResources(Pcb pcb) {
    removeProcessMemory(pcb->pid);
    pcb->heapBase = NULL;
    pcb->stackBase = NULL;
    pcb->stackPointer = NULL;
}


void initializeProcess(functionIP ti) {
    pid_t newPid = ++pidCount;
    void * stack = initializeProcessStack(newPid);
    void * heap = reserveHeapSpace(newPid);
    void * stackPointer = stack;
    stackPointer = buildStackFrame(ti,stackPointer);
    newProcess(stackPointer,stack,heap, newPid);
}

pid_t getRunningProcessPid() {
    return runningPcb->pid;
}

void * buildStackFrame(void * entryPoint, void * userStack) {
    StackFrame * frame = (StackFrame*)userStack - 1;
    frame->gs =		0x001;
    frame->fs =		0x002;
    frame->r15 =	0x003;
    frame->r14 =	0x004;
    frame->r13 =	0x005;
    frame->r12 =	0x006;
    frame->r11 =	0x007;
    frame->r10 =	0x008;
    frame->r9 =		0x009;
    frame->r8 =		0x00A;
    frame->rsi =	0x00B;
    frame->rdi =	0x00C;
    frame->rbp =	0x00D;
    frame->rdx =	0x00E;
    frame->rcx =	0x00F;
    frame->rbx =	0x010;
    frame->rax =	0x011;
    frame->rip =	(uint64_t)entryPoint;
    frame->cs =		0x008;
    frame->eflags = 0x202;
    frame->rsp =	(uint64_t)&(frame->base);
    frame->ss = 	0x000;
    frame->base =	0x000;

    return frame;
}

