
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include "include/semaphore.h"
#include "include/processStates.h"


#define FAIL -1
#define SUCCESS 1


extern int lockSemAndShowPrevSem(int *sem);


int down(int *sem) {
    int previousSem, newState = RUNNING;

    if (sem == NULL)
        return FAIL;

	if (*sem == 0) {
		newState = BLOCKED;
	} else {
		previousSem = lockSemAndShowPrevSem(sem);

		if (previousSem == 0)
			newState = BLOCKED; // another process locked down right before me
	}

    return newState;
}

// semVar should be a global variable for the program using it
int up(int *sem) {
    if (sem == NULL)
        return FAIL;

    *sem += 1;

    return SUCCESS;
}
