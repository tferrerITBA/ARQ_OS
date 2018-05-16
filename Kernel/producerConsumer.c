#include "producerConsumer.h"


#define MAX_MSG_SIZE 20


semT mutex = NULL;
semT semFullSlots = NULL;
semT semEmptySlots = NULL;
char *buffer[BUFFER_SIZE] = {NULL};


void make(char *product) {
    buffer[semFullSlots->count] = product;
}

char *take() {
    char *product = buffer[semFullSlots->count];
    buffer[semFullSlots->count] = NULL;
    return product;
}

void produce() {
    while (1) {
        printDecimal(getRunningProcessPid());
        putString(" - trying to produce :: ");
        printDecimal(semEmptySlots->count);
        putString(" empty slots left\n");

        down(semEmptySlots);
        if (runningPcb->state == BLOCKED)
            return;

		down(mutex);
        if (runningPcb->state == BLOCKED)
            return;

        printDecimal(getRunningProcessPid());
        putString(" - producing :: ");
        printDecimal(semEmptySlots->count);
        putString(" empty slots left\n\n");
/*
        putString("Mutex is: ");

        if (mutex->count == 1) {
            putString("free - ");
        } else if (mutex->count == 0) {
            putString("locked - ");
        }

        printDecimal(mutex->count);
        putString("\n");
        */
        make("product");
        //printDecimal(semEmptySlots->count);
        //putString("\n");
        //printDecimal(semFullSlots->count);
        //putString("\n\n");

        up(mutex);
        up(semFullSlots);
    }
}

void consume() {
    char * product;

    while (1) {
        putString("Consuming\n");
        down(semFullSlots);
        if (runningPcb->state == BLOCKED)
            return;

		down(mutex);
        if (runningPcb->state == BLOCKED)
            return;

        product = take();

		up(mutex);
        up(semEmptySlots);
        putString("I consumed this: ");
        putString(product);
        putString("\n");
    }
}

void initializeProdCons() {
    if (mutex == NULL)
        mutex = initializeMutex(mutex);

    if (semFullSlots == NULL)
        semFullSlots = initializeSem(0);

    if (semEmptySlots == NULL)
        semEmptySlots = initializeSem(BUFFER_SIZE);
}
