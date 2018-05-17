#include <sys/types.h>
#include <stddef.h>
#include "include/sem.h"

extern int lockSemAndShowPrevState(semT sem);

semT mutex = NULL;
semT semFullSlots = NULL;
semT semEmptySlots = NULL;

int down(int semType) {
    int previousState, prodConState;
    semT sem = decideSemType(semType);

    if (sem == NULL) {
		runningPcb->state = TERMINATED;
		return FAIL;
	}

    /*
    if (sem->type == SEM_EMPTY_T) {
        putString("SEM_EMPTY_T value is:  ");
        printDecimal(sem->count);
        putString("\n\n");
    }*/

	if (sem->count == LOCKED) {
		runningPcb->state = BLOCKED;
        enqueue(sem->blockedProcs, runningPcb);
        prodConState = BLOCKED;
	} else {
		previousState = lockSemAndShowPrevState(&(sem->count));

		if (previousState == sem->count) {
            // another process locked down right before me
			runningPcb->state = BLOCKED;
            enqueue(sem->blockedProcs, runningPcb);
            prodConState = BLOCKED;
        } else {
            prodConState = !BLOCKED;
        }
	}

    //printDecimal(sem->count);
    //putString("\n");

    return prodConState;
}

int up(int semType) {
    semT sem = decideSemType(semType);
    int prevSemState = sem->count;
    Pcb blockedProc;

    if (sem == NULL) {
		runningPcb->state = TERMINATED;
		return FAIL;
	}

    if (sem->type == MUTEX_T)
        sem->count = FREE;
    else if (sem->count < SEM_SIZE)
        sem->count++;

    if (prevSemState == LOCKED) {
        blockedProc = dequeue(sem->blockedProcs);
        blockedProc->state = RUNNING;
    }

    return !BLOCKED;
}

semT initializeSem(int initCount, int semType) {
    int id;

    if (semType == MUTEX_T)
        id = 5000;
    else if (semType == SEM_EMPTY_T)
        id = 5001;
    else
        id = 5002;

    semT sem = shmget(id);
    sem->count = initCount;
    sem->id = 0;
    sem->type = semType;
    sem->blockedProcs = newQueue(0);
    return sem;
}

void initializeSemsAndMutex() {
    if (mutex == NULL)
        mutex = initializeSem(FREE, MUTEX_T);

    if (semFullSlots == NULL)
        semFullSlots = initializeSem(0, SEM_FULL_T);

    if (semEmptySlots == NULL)
        semEmptySlots = initializeSem(SEM_SIZE, SEM_EMPTY_T);
}

semT decideSemType(int semType) {
    semT sem;

    if (semType == MUTEX_T) {
        sem = mutex;
        //putString("MUTEX_T ");
    } else if (semType == SEM_EMPTY_T) {
        sem = semEmptySlots;
        //putString("SEM_EMPTY_T ");
    } else {
        sem = semFullSlots;
        //putString("SEM_FULL_T ");
    }
    return sem;
}
