#ifndef PRODUCERCONSUMER_H
#define PRODUCERCONSUMER_H

#include <stddef.h>

#define BUFFER_SIZE 50
#define MUTEX_T 4
#define SEM_EMPTY_T 5
#define SEM_FULL_T 6
#define FAIL -1
#define SUCCESS 1

void produce();
void consume();
void make();
char *take();
void initializeProdCons();
extern char * downInt();
extern char * upInt();
extern char * initializeSemsAndMutexInt();

#endif
