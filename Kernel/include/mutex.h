#ifndef MUTEX_H
#define MUTEX_H

#include "processTADs.h"
#include "PCBTADs.h"
#include "processStates.h"
#include "memoryManager.h"

#define FAIL -1
#define SUCCESS 1
#define FREE 1
#define LOCKED 0

void downMutex(int *mutex);
void upMutex(int *mutex);

#endif
