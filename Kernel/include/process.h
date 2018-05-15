#include <sys/types.h>
#include <stdint.h>
#include "pcb.h"
#include "lib.h"
#include "queue.h"
#include "processTADs.h"
#include "processStates.h"
#include "memoryManager.h"

typedef void (*functionIP)(void);

Process newProcess(void * stackPointer, void * stackBase, void * heap, pid_t newPid);
void initializeProcess(functionIP ip);
void terminateProcess(pid_t pid);
void freeProcessResources(Pcb pcb);
pid_t getRunningProcessPid();
void * buildStackFrame(void * entryPoint, void * userStack);
