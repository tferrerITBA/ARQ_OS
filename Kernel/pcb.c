#include "include/pcb.h"
#include "include/memoryManager.h"
#include "include/videoMode.h"

PcbTable allProcesses = NULL;
extern pid_t pidCount = 0;

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

void printPcb(Pcb pcb) {
    putString("PID: ");
    put_char('0'+ pcb->pid);
    put_char('\n');
    putString("State: ");
    if(pcb->state == RUNNING) {
        putString("running\n");
    }
    if(pcb->state == BLOCKED) {
        putString("blocked\n");
    }
    if(pcb->state == CREATED) {
        putString("created\n");
    }
    if(pcb->state == WAITING) {
        putString("waiting\n");
    }
}

void printAll() {
    TableNode current = allProcesses-> first;
    while(current != NULL) {
        printPcb(current->block);
        current = current->next;
    }
}

