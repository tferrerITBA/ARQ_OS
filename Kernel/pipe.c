#include "include/pipe.h"
#include "include/pcb.h"


int pipeIdCount = 0;
PipeTable allPipes = NULL;

Pipe newPipe() {
    Pipe newPipe = malloc(sizeof(pipeStruct)); //Se guarda en el kernel
    newPipe->writer = NULL;
    newPipe->reader = NULL;
    newPipe->pipeID = ++pipeIdCount;
    newPipe->buff = malloc(sizeof(char)*MAX_PIPE_LENGTH);
    newPipe->len = 0;
    newPipe->access = ALLOWED;
    addPipeToTable(allPipes,newPipe);

    return newPipe;
}

void writeOnPipe(Pipe pipe, char c) {
    while(pipe->access == DENIED);

    if(getRunningProcessPid() != pipe->writer) {
        putString("Access denied! This process is not allowed to write the pipe\n");
        return;
    }

    pipe->access = DENIED;

    if(pipe->len == 0 && pipe->reader != NULL) {
        enqueueProcess(getProcess(blockedProcesses,pipe->reader));
        removeProcessFromTable(blockedProcesses,pipe->reader);
    }
    if(pipe->len == MAX_PIPE_LENGTH) {
        runningPcb->state = BLOCKED;
        pipe->access = ALLOWED;
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
    pipe->access = ALLOWED;
}

char readFromPipe(Pipe pipe) {
    int i = 0;

    while(pipe->access == DENIED);

    if(getRunningProcessPid() != pipe->reader) {
        putString("Access denied! This process is not allowed to read the pipe\n");
        return NULL;
    }

    pipe->access = DENIED;

    if(pipe->len == MAX_PIPE_LENGTH && pipe->writer != NULL) {
        enqueueProcess(getProcess(blockedProcesses,pipe->writer));
        removeProcessFromTable(blockedProcesses,pipe->writer);
    }

    putString("Pipe length: ");
    if(pipe->len > 10) {
        put_char('0' + pipe->len/10);
    }

    put_char('0' + pipe->len%10);
    putString("\n");
    if(pipe->len < 0) {
        runningPcb->state = BLOCKED;
        pipe->access = ALLOWED;
        yield();
    }
    char ret = pipe->buff[0];

    for(i = 0; i < pipe->len - 1; i++) {
        pipe->buff[i] = pipe->buff[i+1];
    }
    pipe->len--;
    pipe->access = ALLOWED;

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
    allPipes = malloc(sizeof(pipeTable));
    allPipes->len = 0;
    allPipes->firstNode = NULL;
}

void addPipeToTable(PipeTable pt, Pipe pipe) {

    PipeTableNode ptn = malloc(sizeof(pipeTableNode));
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

