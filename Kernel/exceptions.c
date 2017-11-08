#include "videoMode.h"
#include "exceptions.h"
#define ZERO_EXCEPTION_ID 0
#define OPCODE_EXCEPTION_ID 6
#define OVERFLOW_EXCEPTION_ID 12


static void zero_division();

typedef void (*exceptionI)(void);

void exceptionDispatcher(int exception, uint64_t rsp) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division(rsp);
}

static void zero_division(uint64_t rsp) {
	putString("Caught arithmetic exception");
}