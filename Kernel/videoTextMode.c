#include "videoTextMode.h"

static char * screenPosition = (char *) 0xB8000;
/*Color format: 0xF2 == White background (F), Green characters (2)*/
void writeTextToScreenFromStart(char * str, uint8_t color) {
	writeTextToScreen(str, color);
}

void writeTextToScreen(char * str, uint8_t color) {
	while(*str != '\0' && screenPosition - SCR_START < 80 * 50) {
		*(screenPosition++) = *(str++);
		*(screenPosition++) = color;
	}	
}

void printOneTextChar(char ch, uint8_t color) {
	*(screenPosition++) = ch;
	*(screenPosition++) = color;
}

void deleteTextCharacter() {
	screenPosition -= 2;
	*(screenPosition) = 0;
	*(screenPosition+1) = 0;
}

void newTextLine() {
	screenPosition = (char *)((unsigned)screenPosition
		+ 160 - ((unsigned)screenPosition - 0xB8000) % 160);
}

void clearTextScreen() {
	screenPosition = SCR_START;
	while(screenPosition - SCR_START < 80 * 50) {
		*(screenPosition++) = 0;
	}
	screenPosition = SCR_START;
}