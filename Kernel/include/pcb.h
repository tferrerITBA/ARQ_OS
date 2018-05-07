//Process control block. Guarda informacion de los procesos
#include <sys/param.h>
#include "lib.h"
#include "processStates.h"
#include "PCBTADs.h"

Pcb newPcb();
void addPcbToTable(Pcb pcb);
void removeProcessFromTable(pid_t pid);
