#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>
#include <stdint.h>
#include "pcb.h"
#include "lib.h"
#include "queue.h"
#include "processTADs.h"
#include "processStates.h"
#include "memoryManager.h"

#define STACK_SIZE 8192
#define HEAP_SIZE 8192

typedef void (*functionIP)(void);


Process newProcess(void * stackPointer, void * stackBase, void * heap);
void initializeProcess(functionIP ip);
void terminateProcess(pid_t pid);
void freeProcessResources(Pcb pcb);
pid_t getRunningProcessPid();
void * buildStackFrame(void * entryPoint, void * userStack);

#endif
