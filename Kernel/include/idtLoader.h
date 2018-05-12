#include <stdint.h>
#include "defs.h"
#include "interrupts.h"
#include "videoMode.h"
#include "RTC.h"
#include "mutex.h"

static void setup_IDT_entry (int index, uint64_t offset);

void load_idt();

extern void _cli();

extern void _sti();

extern void picMasterMask(uint8_t);

extern void picSlaveMask(uint8_t);