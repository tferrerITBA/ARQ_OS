#ifndef PCB_H
#define PCB_H

//Process control block. Guarda informacion de los procesos
#include <sys/types.h>
#include "lib.h"
#include "processStates.h"
#include "PCBTADs.h"

Pcb newPcb();
void addPcbToTable(Pcb pcb);
void initializePcbTable();
Pcb getProcess(pid_t pid);
void printPcb(Pcb pcb);
void printPid(pid_t pid);
extern PcbTable allProcesses;
extern pid_t pidCount;

#endif
