#include <stdint.h>

#define SCR_START 0xB8000

void writeTextToScreenFromStart(char * str, uint8_t color);

void writeTextToScreen(char * str, uint8_t color);

void printOneTextChar(char ch, uint8_t color);

void deleteTextCharacter();

void newTextLine();

void clearTextScreen();