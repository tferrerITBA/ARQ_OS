#include <stdint.h>
#include "include/keyboard.h"
#include "include/time.h"

typedef void (*hardwareI)(void);

void irqDispatcher(uint64_t irq);
void int_20();

hardwareI hardwareInterrupts[2] = {&int_20, &printInput};

void irqDispatcher(uint64_t irq) {
	hardwareInterrupts[irq]();
}

void int_20() {
	timer_handler();
}