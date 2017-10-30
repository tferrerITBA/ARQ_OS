#include <stdint.h>
#include <time.h>
#include "keyboard.h"
typedef void (*hardwareI)(void);

void irqDispatcher(uint64_t irq);
void int_20();

static uint8_t interruptsInitialized = 0;
hardwareI hardwareInterrupts[2];

void initializeHardwareInterrupts() {
	hardwareInterrupts[0] = &int_20;
	hardwareInterrupts[1] = &printInput;
}

void irqDispatcher(uint64_t irq) {
	if(!interruptsInitialized) {
		initializeHardwareInterrupts();
		interruptsInitialized = 1;
	}
	hardwareInterrupts[irq]();
}

void int_20() {
	timer_handler();
}