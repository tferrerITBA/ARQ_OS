#ifndef PRODUCERCONSUMER_H
#define PRODUCERCONSUMER_H

#include <stddef.h>
#include "sem.h"

#define BUFFER_SIZE 3

void produce();
void consume();
void make();
char *take();
void initializeProdCons();

#endif
