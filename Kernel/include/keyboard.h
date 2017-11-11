#include <stdint.h>

#define BUFFER_SIZE 5
#define LAST_INDEX BUFFER_SIZE - 1

extern char read_key();

void printInput();

unsigned char getLastInsertion();

char * readBuffer(uint64_t rbx, char * str, uint64_t bufSize);