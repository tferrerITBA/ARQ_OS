#include <sys/types.h>
#include <stddef.h>
#include "include/mutex.h"
#include "producerConsumer.h"

/*
int *mutexList = NULL;
int mutexListSize = 0;
int **semList = NULL;
int semSize = BUFFER_SIZE;
int semListSize = 0;
*/
extern int lockMutexAndShowPrevState(int *mutex);


void down(int *mutex) {
    int previousState;

    if (mutex == NULL) {
		runningPcb->state = TERMINATED;
		return;
	}

	if (*mutex == LOCKED) {
		runningPcb->state = BLOCKED;
	} else {
		previousState = lockMutexAndShowPrevState(mutex);

		if (previousState == LOCKED)
			runningPcb->state = BLOCKED;
			// another process locked down right before me
	}
}

void up(int *mutex) {
    if (mutex == NULL) {
		runningPcb->state = TERMINATED;
		return;
	}

    *mutex = LOCKED;
}

void downSem(int *sem) {
    
}

void upSem(int *sem) {

}

/*
void addNewMutex() {
    if (mutexList == NULL)
        mutexList = malloc(sizeof(int));
    else
        realloc(mutexList, sizeof(int));

    mutexListSize++;
    mutexList[mutexListSize - 1] = FREE;
}

void addNewSem() {
    if (semList == NULL)
        semList = malloc(sizeof(int *));
    else
        realloc(semList, sizeof(int *));

    semListSize++;
    semList[semListSize - 1] = malloc(semSize * sizeof(int *));
    // Each sem is an array of semSize mutexes

    for (int i = 0; i < semSize; i++)
        semList[semListSize - 1][i] = FREE;
}
*/
