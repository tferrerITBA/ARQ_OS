#include <sys/types.h>
#include "pcb.h"
#include <sys/types.h>
#include "process.h"
#include "pcb.h"
#include "scheduler.h"
#include "lib.h"
#define STACK_SIZE 256
#define HEAP_SIZE 256

typedef struct processCDT {
    Pcb pcb;
} process;

typedef process * Process;

Process newProcess(void * stackPointer, void * stackBase, void * heap);
void * duplicateStack(void * stackPointer);
void * duplicateHeap();
void initializeFirstProcess(terminalCaller ti);
int terminateProcess(Process p);
pid_t processFork();