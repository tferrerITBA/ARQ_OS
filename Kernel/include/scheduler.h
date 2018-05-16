#include <sys/types.h>
#include <stddef.h>
#include <stdint.h>
#include "queue.h"
#include "processStates.h"
#include "PCBTADs.h"
#include "processTADs.h"
#include <stdint.h>

#define TRUE 1
#define FALSE 0

void * schedule(void * rsp);
int terminateProcess(Process p);
void enqueueProcess(Pcb pcb);
void createReadyQueue();

