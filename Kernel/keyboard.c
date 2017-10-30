#include "keyboard.h"

static short index = 0;
static char * screenPosition = (char *) 0xB8020;
static unsigned char buffer[80 * 25] = {0};

void readInput() {
	/*char input = read_key();
	if(input == 0)
		return;
	input -= 30; //si apreto A, se imprime A
	input += 'A';
	buffer[index++] = input;
	writeToScreen(0xB8020, buffer[index-1], 0xF2);*/
}

void printInput() {
	unsigned char input = read_key();
	if(input == 0 || input > 0x80)
		return;
	// backspace
	if(input == 0x0E) {
		screenPosition -= 2;
		deleteChar(screenPosition);
		return;
	}
	// key break signal
	/*if(input - 0x80 == buffer[index-1] + 2 - '1')
		return;*/
	buffer[index] = input - 2 + '1';
	printOneChar(screenPosition, buffer[index], 0x0F);
	index = (index < 80 * 25) ? index + 1 : 0;
	screenPosition += 2;
}