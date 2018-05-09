/*
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include "include/mutex.h"
#include "include/processStates.h"


#define FREE 1
#define LOCKED 0


extern int lockMutexAndShowPrevMutex(int *mutex);


int mutexVar = FREE, criticalResource = 0;


int down(int *mutex) {
    int previousMutex, newState = RUNNING;

    assert(mutex != NULL);

	if (*mutex == 0) {
		newState = BLOCKED;
	} else {
		previousMutex = lockMutexAndShowPrevMutex(mutex);

		if (previousMutex == 0)
			newState = BLOCKED; // another process locked down right before me
	}

    return newState;
}

// mutexVar should be a global variable for the program using it
void up(int *mutex) {
    assert(mutex != NULL);

    *mutex += 1;
}
*/
