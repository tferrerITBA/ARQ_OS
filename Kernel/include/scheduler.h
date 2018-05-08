#include <sys/types.h>
#include <stddef.h>
#include "queue.h"
#include "processStates.h"
#include "PCBTADs.h"
#include "processTADs.h"

#define QUEUE_SIZE 10
#define TRUE 1
#define FALSE 0

Queue readyQueue;

void * schedule(void * rsp);
int terminateProcess(Process p);
void enqueueProcess(Pcb pcb);
void createReadyQueue();
