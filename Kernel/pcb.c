#include "include/pcb.h"
#include "include/memoryManager.h"

static PcbTable allProcesses;
static pid_t pidCount;

Pcb newPcb() {
    Pcb ret = malloc(sizeof(pcb));
    ret->pid = ++pidCount;
    ret->state = CREATED;

    return ret;
}

void addPcbToTable(Pcb pcb) {
    if(allProcesses == NULL) {
        allProcesses = malloc(sizeof(pcbTable));
        allProcesses->first = malloc(sizeof(tableNode));
    }
    else {
        TableNode new = malloc(sizeof(tableNode));
        new->block = pcb;
        new->next = allProcesses->first;
        allProcesses->first = new;
        allProcesses->size++;
    }
}
 void removeProcessFromTable(pid_t pid) {
     TableNode current = allProcesses->first;

     while(current->next->block->pid != pid) {
         current = current->next;
     }

     TableNode selected = current->next;
     current->next = current->next->next;
     free(selected->block);
     free(selected);

 }

