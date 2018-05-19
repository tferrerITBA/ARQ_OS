#include "include/pipeBuffer.h"


PipeBuffer newBuffer() {
    PipeBuffer pb = malloc(sizeof(pipeBuffer),0);
    pb->buffLen = 0;
    pb->content = malloc(sizeof(char)*MAX_PIPE_LENGTH,0);
    return pb;
}

void writeChar(PipeBuffer pb, char c) {
    if(pb->buffLen == MAX_PIPE_LENGTH) {
        runningPcb->state = BLOCKED;
        while(runningPcb->state == BLOCKED);
    }
    memcpy(pb->content+pb->buffLen,&c,sizeof(char));
    pb->buffLen++;
}

char readChar(PipeBuffer pb) {
    int i;

    if(pb->buffLen == 0) {
        runningPcb->state = BLOCKED;
        while(runningPcb->state == BLOCKED);
    }
    char ret = pb->content[0];

    for(i = 0; i < pb->buffLen - 1; i++) {
        pb->content[i] = pb->content[i+1];
    }
    pb->buffLen--;

    return ret;
}