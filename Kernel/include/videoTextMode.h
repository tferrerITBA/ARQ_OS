#include <stdint.h>

#define SCR_START 0xB8000

void writeToScreenFromStart(char * str, uint8_t color);

void writeToScreen(char * str, uint8_t color);

void printOneChar(char ch, uint8_t color);

void deleteChar();

void newLine();

void clearScreen();