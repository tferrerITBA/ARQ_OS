//Process control block. Guarda informacion de los procesos
#include <sys/types.h>
#include "lib.h"
#include "processStates.h"
#include "PCBTADs.h"
#include "buddy.h"

extern PcbTable allProcesses;
extern PcbTable blockedProcesses;
extern pid_t pidCount;

Pcb newPcb(pid_t newPid);
void addPcbToTable(PcbTable table, Pcb pcb);
void initializePcbTable(PcbTable table);
Pcb getProcess(PcbTable table, pid_t pid);
void removeProcessFromTable(PcbTable table, pid_t pid);
void printPcb(Pcb pcb);
void printPid(pid_t pid);
void printAll(PcbTable table);

