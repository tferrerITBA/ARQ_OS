#include <sys/types.h>
#include <stddef.h>
#include "include/mutex.h"


#define FAIL -1
#define SUCCESS 1
#define FREE 1
#define LOCKED 0



extern int lockMutexAndShowPrevState(int *mutex);


void downMutex(int *mutex) {
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

void upMutex(int *mutex) {
    if (mutex == NULL) {
		runningPcb->state = TERMINATED;
		return;
	}

    *mutex += 1;
}
