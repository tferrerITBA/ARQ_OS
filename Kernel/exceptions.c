#include "include/videoMode.h"
#include "include/exceptions.h"

#define ZERO_EXCEPTION_ID 0
#define OPCODE_EXCEPTION_ID 6


static void zero_division();
static void invalid_opcode(uint64_t rsp);
static void printExceptionDetails(trapframe * tf);

void exceptionDispatcher(int exception, uint64_t rsp) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division(rsp);
	else if(exception == OPCODE_EXCEPTION_ID)
		invalid_opcode(rsp);
}

static void zero_division(uint64_t rsp) {
	putString("Caught arithmetic exception\n");
	trapframe * tf = (trapframe *)rsp;
	printExceptionDetails(tf);
}

static void invalid_opcode(uint64_t rsp) {
	putString("Caught Invalid Opcode exception\n");
	trapframe * tf = (trapframe *)rsp;
	printExceptionDetails(tf);
}

static void printExceptionDetails(trapframe * tf) {
	putString("\nRIP: 0x");
	printHex(tf->ip);
	putString("\nCS: 0x");
	printHex(tf->cs);
	putString("\nRFLAGS: 0x");
	printHex(tf->flags);
	putString("\nRSP: 0x");
	printHex(tf->sp);
	putString("\nSS: 0x");
	printHex(tf->ss);
	putString("\n");	
}