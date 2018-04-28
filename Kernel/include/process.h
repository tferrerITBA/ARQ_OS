#include <sys/types.h>
#include "pcb.h"
#define STACK_SIZE 256

typedef struct processCDT {
    Pcb pcb;
} process;

typedef process * Process;

Process newProcess(pid_t pid, void * rip, void * rsp);
void * duplicateStack();
int terminateProcess(Process p);
pid_t fork();