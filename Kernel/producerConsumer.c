#include "producerConsumer.h"


#define MAX_MSG_SIZE 20


semT mutex = NULL;
semT semFullSlots = NULL;
semT semEmptySlots = NULL;
char *buffer[BUFFER_SIZE] = {NULL};


void make(char *product) {
    /*
    int i;
    for (i = 0; *product; i++)
        buff[fullSlots][i] = product[i];
    buff[fullSlots][i] = 0;
    */
    //buffer[semFullSlots->count] = product;
    //semFullSlots->count++;
    //semEmptySlots->count--;
}

char *take() {
    char *product = buffer[BUFFER_SIZE];
    buffer[BUFFER_SIZE] = NULL;
    return product;
}

void produce() {
    while (1) {
        down(semEmptySlots);
		down(mutex);
        
        if (semEmptySlots->count) {
            putString("Producing\n");
            printHex(semEmptySlots->count);
        }

        putString("\n");
        make("product");
		up(mutex);
        up(semFullSlots);
    }
}

void consume() {
    char * product;

    while (1) {
        putString("Consuming\n");
        down(semFullSlots);
		down(mutex);
        product = take();
		up(mutex);
        up(semEmptySlots);
        putString("I consumed this: ");
        printHex(product);
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
