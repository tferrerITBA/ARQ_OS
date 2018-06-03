#include <sys/types.h>
#include <stdint.h>
#include "pcb.h"
#include "lib.h"
#include "queue.h"
#include "processTADs.h"
#include "processStates.h"

#define STACK_SIZE 1024
#define HEAP_SIZE 1024

typedef struct StackFrame {

    uint64_t gs;
    uint64_t fs;
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;

    uint64_t rip;
    uint64_t cs;
    uint64_t eflags;
    uint64_t rsp;
    uint64_t ss;
    uint64_t base;
} StackFrame;

typedef void (*functionIP)(void);

extern void enqueueProcess(Pcb pcb);

Process newProcess(void * stackPointer, void * stackBase, void * heap, pid_t newPid);
void initializeProcess(functionIP ip);
void terminateProcess(pid_t pid);
void freeProcessResources(Pcb pcb);
pid_t getRunningProcessPid();
void * buildStackFrame(void * entryPoint, void * userStack);
