#ifndef SEM_H
#define SEM_H

#include "processTADs.h"
#include "PCBTADs.h"
#include "processStates.h"
#include "memoryManager.h"

#define FAIL -1
#define SUCCESS 1
#define FREE 1
#define LOCKED 0
#define SEM_SIZE 8
#define MUTEX_T 4
#define SEM_T 5

typedef struct {
    int count;
    int id;
    int type;
} semStruct;
typedef semStruct * semT;


void down(semT sem);
void up(semT sem);
semT initializeMutex();
semT initializeSem();

#endif
