#include <sys/types.h>
#include "queue.h"
#include "pcb.h"
#include "process.h"

#define QUEUE_SIZE 10
extern Queue readyQueue;
extern Pcb runningPcb;
extern pid_t pidCount;

extern void * getRIP();
extern void * getRSP();
extern void setRIP(void * newRIP);

void * schedule();
int terminateProcess(Process p);
void enqueueProcess(Queue q, Pcb pcb);