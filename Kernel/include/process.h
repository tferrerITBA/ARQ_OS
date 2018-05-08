#include <sys/types.h>
#include "pcb.h"
#include "lib.h"
#include "queue.h"
#include "processTADs.h"
#include "processStates.h"

#define STACK_SIZE 256
#define HEAP_SIZE 256

typedef void (*terminalCaller)(void);

Process newProcess(void * stackPointer, void * stackBase, void * heap);
void * duplicateStack(void * stackPointer);
void * duplicateHeap();
void initializeFirstProcess(terminalCaller ti);
int terminateProcess(Process p);
pid_t processFork();
pid_t getRunningProcessPid();