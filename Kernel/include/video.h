#include <stdint.h>

#define SCR_START 0xB8000

void writeToScreenFromStart(char * str, uint8_t color);

void writeToScreen(char * start, char * str, uint8_t color);

void printOneChar(char * start, char ch, uint8_t color);

void deleteChar(char * start);

void newLine();

void clearScreen();