#ifndef MUTEX_H
#define MUTEX_H

#include "processTADs.h"
#include "PCBTADs.h"
#include "processStates.h"

void downMutex(int *mutex);
void upMutex(int *mutex);

#endif
