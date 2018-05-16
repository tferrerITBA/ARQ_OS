#include <sys/types.h>
#include <stddef.h>
#include "include/sem.h"


extern int lockSemAndShowPrevState(semT sem);

void down(semT sem) {
    int previousState;

    if (sem == NULL) {
		runningPcb->state = TERMINATED;
		return;
	}

	if (sem->count == LOCKED) {
        //putString("---BLOQUEANDO\n");
		runningPcb->state = BLOCKED;
	} else {
        //putString("semCount: ");
        //printDecimal(sem->count);
        //putString("\n");
		previousState = lockSemAndShowPrevState(&(sem->count));

        //putString("previousState: ");
        //printDecimal(previousState);
        //putString("\nnewState:");
        //printDecimal(sem->count);
        //putString("\n\n");

		if (previousState == sem->count)
			runningPcb->state = BLOCKED;
			// another process locked down right before me
	}
}

void up(semT sem) {
    if (sem == NULL) {
		runningPcb->state = TERMINATED;
		return;
	}

    if (sem->type == MUTEX_T)
        sem->count = FREE;
    else if (sem->count < SEM_SIZE -1)
        sem->count++;
}

semT initializeSem(int initCount) {
    semT sem = malloc(sizeof(semStruct), getRunningProcessPid());
    sem->count = initCount;
    sem->id = 0;
    sem->type = SEM_T;
    return sem;
}

semT initializeMutex() {
    semT sem = malloc(sizeof(semStruct), getRunningProcessPid());
    sem->count = FREE;
    sem->id = 0;
    sem->type = MUTEX_T;
    return sem;
}
