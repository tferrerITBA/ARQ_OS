#include "include/pcb.h"
#include "include/videoMode.h"

PcbTable allProcesses = NULL;
PcbTable blockedProcesses = NULL;
pid_t pidCount = 0;

Pcb newPcb(pid_t newPid) {
    Pcb ret = malloc(sizeof(pcb));
    ret->pid = newPid;
    ret->state = CREATED;

    return ret;
}

void initializePcbTable(PcbTable table) {
    table = malloc(sizeof(pcbTable));
    table->size = 0;
}

void addPcbToTable(PcbTable table, Pcb pcb) {
    if(table == NULL) {
        initializePcbTable(table);
    }
    TableNode new = malloc(sizeof(tableNode));
    new->block = pcb;
    new->next = table->first;
    table->first = new;
    table->size++;
}

Pcb getProcess(PcbTable table, pid_t pid) {
    TableNode current = table->first;
    while (current->block->pid != pid) {
        current = current->next;
        if(current == NULL) {
            return NULL;
        }
    }
    return current->block;
}

void printAll(PcbTable table) {
//    TableNode current = table-> first;
//    while(current != NULL) {
//        printPcb(current->block);
//        current = current->next;
//
//    }
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

void removeProcessFromTable(PcbTable table, pid_t pid) {
    TableNode current = table->first;
    while (current->next->block->pid != pid) {
        current = current->next;
        if(current == NULL) {
            return;
        }
    }
    current->next = current->next->next;
}
