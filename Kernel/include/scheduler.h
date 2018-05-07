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
Pcb runningPcb;

extern void * getRSP();
void * schedule();
int terminateProcess(Process p);
void enqueueProcess(Queue q, Pcb pcb);
void createReadyQueue();
