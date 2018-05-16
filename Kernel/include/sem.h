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
#define SEM_SIZE 50
#define MUTEX_T 4
#define SEM_EMPTY_T 5
#define SEM_FULL_T 6

typedef struct {
    int count;
    int id;
    int type;

} semStruct;

typedef semStruct * semT;


int down(int semType);
int up(int semType);
semT initializeSem(int initCount, int semType);
void initializeSemsAndMutex();
semT decideSemType(int semType);

#endif
