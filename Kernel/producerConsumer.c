#include "producerConsumer.h"


#define MAX_MSG_SIZE 20

int mutex = FREE;
int semFullSlots[BUFFER_SIZE] = {0};
int fullSlots = 0;
int semEmptySlots[BUFFER_SIZE] = {BUFFER_SIZE};
int emptySlots = BUFFER_SIZE;
char *buffer[BUFFER_SIZE] = {NULL};


void make(char *product) {
    /*
    int i;
    for (i = 0; *product; i++)
        buff[fullSlots][i] = product[i];
    buff[fullSlots][i] = 0;
    */
    buffer[fullSlots] = product;
    fullSlots++;
    emptySlots--;
}

char *take() {
    return buffer[fullSlots];
}

void produce() {
    while (1) {
        downSem(semEmptySlots);
		down(&mutex);
        make("Producing");
		up(&mutex);
        upSem(semFullSlots);
    }
}

void consume() {
    char * product;

    while (1) {
        downSem(semFullSlots);
		down(&mutex);
        product = take();
		up(&mutex);
        upSem(semEmptySlots);

    }
}
