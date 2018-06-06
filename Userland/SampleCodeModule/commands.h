#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>
#include <sys/types.h>
#include "lib.h"
#include "functionGraph.h"
#include "producerConsumer.h"
#define STEP 6
#define READ 0
#define WRITE 1

typedef void (*function)(void);

void runHelp();
void runClear();
void runZeroDiv();
void runOverflow();
void runInvOpc();
void runTime();
void runChcolor(uint8_t blue, uint8_t green, uint8_t red);
void runBgcolor(uint8_t blue, uint8_t green, uint8_t red);
void runMath(double a, double b, double c);
void colorFade(uint8_t from[], uint8_t to[]);
void sh(function functionName, int foreground);
void ps();
void prodcons();
void producer();
void consumer();
void pipeProdcons();
void pipeProducer();
void pipeConsumer();
void multiDemo();
void mallocDemo();
void killDemo();
void endOfProcess();
void sender();
void receiver();
void messageDemo();
uint8_t getDistance(uint8_t a, uint8_t b);
extern void raiseInvOp();
extern char * newProcessInt(void *);
extern char * psint();
extern char * kill(int pid);
extern char * getpid();
extern char * malloc(size_t size);
extern char * free(void *);
extern char * send(char *);
extern char * receive();
extern char * writePipe(int id, char c);
extern char * readPipe(int id);
extern char * createPipe();
extern char * openPipe(int mode, int pipeId);
extern char * closePipe(int id);

#endif COMMANDS_H
