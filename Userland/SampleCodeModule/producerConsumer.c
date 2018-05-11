#include "producerConsumer.h"


#define BUFFER_SIZE 3
#define MAX_MSG_SIZE 20
#define LOCKED 0
#define FREE 1


int semFullSlots = 0;
int semEmptySlots = BUFFER_SIZE;
int mutex = FREE;
char * buffer[BUFFER_SIZE] = {NULL};


void createBuffer() {
	/*for (int i = 0; i < BUFFER_SIZE; i++)
		buffer[i] = NULL;
*/
}

void make() {}

void take() {}

void produce() {
    while (1) {
        downInt(&semEmptySlots);
		downInt(&mutex);
        make(buffer, "Product");
		upInt(&mutex);
        upInt(&semFullSlots);
    }
}

void consume() {
    while (1) {
        downInt(&semFullSlots);
		downInt(&mutex);
        take();
		upInt(&mutex);
        upInt(&semEmptySlots);
    }
}
