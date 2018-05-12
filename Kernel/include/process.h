#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>
#include <stdint.h>
#include "pcb.h"
#include "lib.h"
#include "queue.h"
#include "processTADs.h"
#include "processStates.h"

#define STACK_SIZE 8192
#define HEAP_SIZE 8192

typedef void (*terminalCaller)(void);


Process newProcess(void * stackPointer, void * stackBase, void * heap);
void * duplicateStack(uint64_t offset);
void * duplicateHeap();
void initializeFirstProcess(terminalCaller ti);
int terminateProcess(Process p);
pid_t processFork(uint64_t rsp);
pid_t getRunningProcessPid();
void * buildStackFrame(void * entryPoint, void * userStack);

#endif
