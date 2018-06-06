#include <sys/param.h>
#include "PCBTADs.h"
#include "queue.h"
#include "processStates.h"
#include "videoMode.h"
#define READ 0
#define WRITE 1
#define MAX_PIPE_LENGTH 100
#define DENIED 0
#define ALLOWED 1

extern void yield();
extern void enqueueProcess(Pcb pcb);
extern Pcb getProcess(PcbTable table, pid_t pid);

typedef struct pipeStruct {
    pid_t writer;
    pid_t reader;
    int pipeID;
    char * buff;
    int len;
    int access;
} pipeStruct;

typedef pipeStruct * Pipe;

typedef struct pipeTableNode {
    Pipe pipe;
    struct pipeTableNode * next;
} pipeTableNode;

typedef pipeTableNode * PipeTableNode;

typedef struct pipeTable {
    PipeTableNode firstNode;
    int len;
} pipeTable;

typedef pipeTable * PipeTable;

extern PipeTable allPipes;
extern int pipeIdCount;

extern pid_t getRunningProcessPid();

Pipe newPipe();
void openPipe(int id, int mode);
void writeOnPipe(Pipe pipe, char c);
char readFromPipe(Pipe pipe);
void initializePipeTable();
void addPipeToTable(PipeTable pt, Pipe pipe);
void closePipe(int id);
Pipe getPipe(PipeTable pt, int id);




