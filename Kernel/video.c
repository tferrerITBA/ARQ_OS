#include "video.h"
/*Color format: 0xF2 == White background (F), Green characters (2)*/
void writeToScreenFromStart(char * str, uint8_t color) {
	char * pointer = SCR_START;
	while(*str != '\0' && pointer - SCR_START < 80 * 25) {
		*(pointer++) = *(str++);
		*(pointer++) = color;
	}
}

void writeToScreen(char * start, char * str, uint8_t color) {
	char * pointer = start;
	while(*str != '\0' && pointer - SCR_START < 80 * 40) {
		*(pointer++) = *(str++);
		*(pointer++) = color;
	}	
}

void clearScreen() {
	char * pointer = SCR_START;
	while(pointer - SCR_START < 80 * 80) {
		*(pointer++) = 0;
	}
}