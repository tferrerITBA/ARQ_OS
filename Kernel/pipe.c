#include "include/pipe.h"
#include "include/pcb.h"


int pipeIdCount = 0;
PipeTable allPipes = NULL;

Pipe newPipe() {
    Pipe newPipe = malloc(sizeof(pipeStruct),0); //Se guarda en el kernel
    newPipe->writer = NULL;
    newPipe->reader = NULL;
    newPipe->pipeID = ++pipeIdCount;
    newPipe->buff = malloc(sizeof(char)*MAX_PIPE_LENGTH,5);
    newPipe->len = 0;
    addPipeToTable(allPipes,newPipe);

    return newPipe;
}

void writeOnPipe(Pipe pipe, char c) {
    //TODO: chequear que quien este escribiendo sea writer
    if(pipe->len == 0 && pipe->reader != NULL) {
        enqueueProcess(getProcess(blockedProcesses,pipe->reader));
        removeProcessFromTable(blockedProcesses,pipe->reader);
    }
    if(pipe->len == MAX_PIPE_LENGTH) {
        runningPcb->state = BLOCKED;
        yield();
    }
    memcpy(pipe->buff+pipe->len,&c,sizeof(char));
    pipe->len++;
    putString(pipe->buff);
    putString("\n");
    putString("Pipe length: ");
    if(pipe->len > 10) {
        put_char('0' + pipe->len/10);
    }
    put_char('0' + pipe->len%10);
    putString("\n");
}

char readFromPipe(Pipe pipe) {
    int i;
    putString("Pipe length: ");
    if(pipe->len > 10) {
        put_char('0' + pipe->len/10);
    }
    put_char('0' + pipe->len%10);
    putString("\n");
    if(pipe->len < 0) {
        runningPcb->state = BLOCKED;
        while(runningPcb->state == BLOCKED) {putString("\nLlegue a read\n");}
    }
    char ret = pipe->buff[0];

    for(i = 0; i < pipe->len - 1; i++) {
        pipe->buff[i] = pipe->buff[i+1];
    }
    pipe->len--;

    return ret;
}

void openPipe(int mode, int id) {

    Pipe pipe = getPipe(allPipes, id);
    if (mode == READ) {
        if (pipe->reader != NULL) {
            putString("Error! Pipe has already been opened for reading\n");
            return;
        }
        pipe->reader = getRunningProcessPid();
    } else if (mode == WRITE) {
        if (pipe->writer != NULL) {
            putString("Error! Pipe has already been opened for writing\n");
            return;
        }
        pipe->writer = getRunningProcessPid();
    }
}


void initializePipeTable() {
    allPipes = malloc(sizeof(pipeTable), 0);
    allPipes->len = 0;
    allPipes->firstNode = NULL;
}

void addPipeToTable(PipeTable pt, Pipe pipe) {

    PipeTableNode ptn = malloc(sizeof(pipeTableNode),0);
    ptn->pipe = pipe;
    ptn->next = NULL;

    if(pt->len == 0) {
        pt->firstNode = ptn;
        pt->len++;
        return;
    }

    PipeTableNode current = pt->firstNode;
    while(current->next != NULL) {
        current = current->next;
    }

    current->next = ptn;
    pt->len++;


}

Pipe getPipe(PipeTable pt, int id) {

    PipeTableNode current = pt->firstNode;
    while (current->pipe->pipeID != id) {
        current = current->next;
        if(current == NULL) {
            return NULL;
        }
    }
    return current->pipe;
}

