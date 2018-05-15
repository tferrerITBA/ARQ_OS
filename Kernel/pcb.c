#include "include/pcb.h"
#include "include/memoryManager.h"
#include "include/videoMode.h"

PcbTable allProcesses = NULL;
pid_t pidCount = 0;

Pcb newPcb() {
    Pcb ret = malloc(sizeof(pcb));
    ret->pid = ++pidCount;
    ret->state = CREATED;

    return ret;
}

void initializePcbTable() {
    allProcesses = malloc(sizeof(pcbTable));
    allProcesses->size = 0;
}

void addPcbToTable(Pcb pcb) {
    if(allProcesses == NULL) {
        initializePcbTable();
    }
    TableNode new = malloc(sizeof(tableNode));
    new->block = pcb;
    new->next = allProcesses->first;
    allProcesses->first = new;
    allProcesses->size++;
}

Pcb getProcess(pid_t pid) {
    TableNode current = allProcesses->first;
    while (current->block->pid != pid) {
        current = current->next;
    }
    return current->block;
}

void printAll() {
    TableNode current = allProcesses-> first;
    while(current != NULL) {
        printPcb(current->block);
        current = current->next;
    }
}

void printPcb(Pcb pcb) {

    printPid(pcb->pid);

    putString("State: ");
    if(pcb->state == RUNNING) {
        putString("running\n");
    }
    if(pcb->state == CREATED) {
        putString("created\n");
    }
    if(pcb->state == WAITING) {
        putString("waiting\n");
    }
    if(pcb->state == TERMINATED) {
        putString("terminated\n");
    }
}

void printPid(pid_t pid) {
    putString("PID: ");
    if(pid < 10 && pid > 0) {
        put_char('0' + pid);
    } else if (pid < 100){
        put_char(pid/10 + '0');
        put_char(pid%10 + '0');
    }
    putString("\t\t");

}
