#include "memoryManager.h"
#include "PCBTADs.h"
#include "processStates.h"
#define MAX_PIPE_LENGTH 20

typedef struct pipeBuffer {
    char * content;
    int buffLen;

} pipeBuffer;

typedef pipeBuffer * PipeBuffer;

PipeBuffer newBuffer();
void writeChar(PipeBuffer pb, char c);
char readChar(PipeBuffer pb);
