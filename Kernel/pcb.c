#include "include/pcb.h"
#include "include/scheduler.h"
#include "include/lib.h"
static PcbTable allProcesses;

Pcb newPcb() {
    Pcb ret = malloc(sizeof(pcb));
    ret->pid = ++pidCount;
    ret->state = CREATED;

    return ret;
}

void addPcbToTable(Pcb pcb) {
    if(allProcesses == NULL) {
        malloc(allProcesses, sizeof(Pcb)*BLOCK_SIZE);
    }
    else if(allProcesses->size % BLOCK_SIZE == 0) {
        realloc(allProcesses, allProcesses->size + BLOCK_SIZE);
    }
    memcpy(allProcesses->first+sizeof(Pcb)*allProcesses->size,pcb, sizeof(Pcb));
}
 void removeProcessFromTable(pid_t pid) {
     Pcb current = allProcesses->first;
     int index = 0;

     while(current->pid != pid) {
         current += sizeof(Pcb);
     }

 }

