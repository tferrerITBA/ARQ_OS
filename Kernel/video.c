#include "video.h"

static char * screenPosition = (char *) 0xB8000;
/*Color format: 0xF2 == White background (F), Green characters (2)*/
void writeToScreenFromStart(char * str, uint8_t color) {
	writeToScreen(SCR_START, str, color);
}

void writeToScreen(char * start, char * str, uint8_t color) {
	char * pointer = start;
	while(*str != '\0' && pointer - SCR_START < 80 * 50) {
		*(pointer++) = *(str++);
		*(pointer++) = color;
	}	
}

void printOneChar(char * start, char ch, uint8_t color) {
	*(start++) = ch;
	*start = color;
}

void deleteChar(char * start) {
	*(start++) = 0;
	*start = 0;
}

void clearScreen() {
	char * pointer = SCR_START;
	while(pointer - SCR_START < 80 * 50) {
		*(pointer++) = 0;
	}
}