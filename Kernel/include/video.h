#include <stdint.h>

#define SCR_START 0xB8000

void writeToScreenFromStart(char * str, uint8_t color);

void writeToScreen(char * start, char * str, uint8_t color);

void clearScreen();