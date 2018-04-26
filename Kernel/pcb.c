#include "include/pcb.h"

static Pcb * enlistedProcesses;

Pcb newPCB(int pid) {
    Pcb ret = malloc(sizeof(pcb));
    ret->pid = pid;
    ret->state = CREATED;

    return ret;
}
