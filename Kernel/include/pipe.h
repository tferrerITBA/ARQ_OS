#include "memoryManager.h"
#include "PCBTADs.h"
#include "queue.h"
#include "processStates.h"
#include "pipeBuffer.h"
#include "videoMode.h"
#include "process.h"

#define READ 0
#define WRITE 1

typedef struct pipeStruct {
    PipeBuffer buff;
    pid_t writer;
    pid_t reader;
    int pipeID;
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

Pipe newPipe();
void writeOnPipe(Pipe pipe, char c);
char readFromPipe(Pipe pipe);
void initializePipeTable();
void addPipeToTable(PipeTable pt, Pipe pipe);
Pipe getPipe(PipeTable pt, int id);




