#include <stdint.h>
#include "include/keyboard.h"
#include "include/time.h"

typedef void (*hardwareI)(void);

extern void tick_handler();
void irqDispatcher(uint64_t irq);
void int_20();

hardwareI hardwareInterrupts[2] = {&int_20, &printInput};

void irqDispatcher(uint64_t irq) {
	hardwareInterrupts[irq]();
}

void int_20() {
	tick_handler();
}