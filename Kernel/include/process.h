#include <sys/types.h>
#include "pcb.h"
#define STACK_SIZE 256

typedef struct processCDT {
    Pcb pcb;
    void * stack;
    void * nextInstruction;
} process;

typedef process * Process;

Process newProcess(pid_t pid, void * rip, void * rsp);
int terminateProcess(Process p);
pid_t fork();