
#include "include/queue.h"
#include "include/scheduler.h"
#include "include/pcb.h"

static Pcb runningPcb;

void schedule(Queue readyQueue) {
    if(runningPcb->state == TERMINATED) {
        free(runningPcb);
    } else if(runningPcb) {

    }
    runningPcb = dequeue(readyQueue);
    runningPcb->state = RUNNING;
    return;
}

void addProcess(Queue q, Pcb pcb) {
    pcb->state = WAITING;
    enqueue(q,pcb);
}
