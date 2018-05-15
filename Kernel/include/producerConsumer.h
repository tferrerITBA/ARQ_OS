#ifndef PRODUCERCONSUMER_H
#define PRODUCERCONSUMER_H

#include <stddef.h>
#include "mutex.h"

#define BUFFER_SIZE 3

void createBuffer();
void produce();
void consume();
void make();
void take();

#endif
