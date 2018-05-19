#include "include/pipe.h"


int pipeIdCount = 0;
PipeTable allPipes = NULL;

Pipe newPipe() {
    Pipe newPipe = malloc(sizeof(pipeStruct),(pid_t)0); //Se guarda en el kernel
    newPipe->writer = NULL;
    newPipe->reader = NULL;
    newPipe->pipeID = ++pipeIdCount;
    newPipe->buff = newBuffer();
    addPipeToTable(allPipes,newPipe);
}

void writeOnPipe(Pipe pipe, char c) {
    writeChar(pipe->buff,c);
}

char readFromPipe(Pipe pipe) {
    readChar(pipe->buff);
}

void openPipe(int id, int mode) {
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
}

void addPipeToTable(PipeTable pt, Pipe pipe) {
    PipeTableNode ptn = malloc(sizeof(pipeTableNode),0);
    ptn->pipe = pipe;
    ptn->next = NULL;

    if(pt->firstNode == NULL) {
        pt->firstNode = ptn;
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
    PipeTableNode ptn = pt->firstNode;
    while(ptn->pipe->pipeID != id) {
        if(ptn == NULL) {
            return NULL;
        }
        ptn = ptn->next;
    }
    return ptn->pipe;
}

