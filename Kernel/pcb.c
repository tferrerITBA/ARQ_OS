#include "include/pcb.h"
#include "include/memoryManager.h"
#include "include/videoMode.h"

PcbTable allProcesses = NULL;
pid_t pidCount = 0;

Pcb newPcb(pid_t newPid) {
    Pcb ret = malloc(sizeof(pcb), newPid);
    ret->pid = newPid;
    ret->state = CREATED;

    return ret;
}

void initializePcbTable() {
    allProcesses = malloc(sizeof(pcbTable),(pid_t)1);
    allProcesses->size = 0;
}

void addPcbToTable(Pcb pcb) {
    if(allProcesses == NULL) {
        initializePcbTable();
    }
    TableNode new = malloc(sizeof(tableNode),(pid_t)1);
    new->block = pcb;
    new->next = allProcesses->first;
    allProcesses->first = new;
    allProcesses->size++;
}

Pcb getProcess(pid_t pid) {
    TableNode current = allProcesses->first;
    while (current->block->pid != pid) {
        current = current->next;
        if(current == NULL) {
            return NULL;
        }
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
    if(pcb->state == READY) {
        putString("ready\n");
    }
    if(pcb->state == TERMINATED) {
        putString("terminated\n");
    }
    if(pcb->state == BLOCKED) {
        putString("blocked\n");
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
