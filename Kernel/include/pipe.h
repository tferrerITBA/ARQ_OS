#include "memoryManager.h"
#include "PCBTADs.h"
#include "queue.h"
#include "processStates.h"
#include "videoMode.h"


#define READ 0
#define WRITE 1
#define MAX_PIPE_LENGTH 20

typedef struct pipeStruct {
    pid_t writer;
    pid_t reader;
    int pipeID;
    char * buff;
    int len;
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
Pipe getPipe(PipeTable pt, int id);




