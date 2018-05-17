#include "producerConsumer.h"

int fullSlots = 0;
int emptySlots = BUFFER_SIZE;
char *buffer[BUFFER_SIZE] = {NULL};


void make(char *product) {
    fullSlots++;
    emptySlots--;
    buffer[fullSlots] = product;
    printf("Making product, ");
    printInt(emptySlots);
    printf(" emptySlots left\n");
}

char *take() {
    char *product;
    fullSlots--;
    emptySlots++;
    product = buffer[fullSlots];
    buffer[fullSlots] = NULL;
    printf("Consuming product, ");
    printInt(emptySlots);
    printf(" emptySlots left\n");
    return product;
}

void produce() {
    int blocked;

    while (1) {
        blocked = downInt(SEM_EMPTY_T);

        if (!blocked) {
            blocked = downInt(MUTEX_T);
            //printInt(emptySlots);
            //printf(" emptySlots\n");

            if (!blocked) {
                make("product");
                blocked = upInt(MUTEX_T);
                blocked = upInt(SEM_FULL_T);
            }
        }
    }
}

void consume() {
    char * product;
    int blocked;

    while (1) {
        blocked = downInt(SEM_FULL_T);

        if (!blocked) {
            blocked = downInt(MUTEX_T);

            if (!blocked && emptySlots >= 0) {
                product = take();
                blocked = upInt(MUTEX_T);
                blocked = upInt(SEM_EMPTY_T);
            }
        }
    }
}

void initializeProdCons() {
    initializeSemsAndMutexInt();
}
