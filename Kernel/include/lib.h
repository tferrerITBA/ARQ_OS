#ifndef LIB_H
#define LIB_H

#include <stdint.h>

#define SCR_START 0xB8000

typedef void (*terminalCaller)(void);

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);

#endif