const char * screenStart = 0xB8000;

/*Color format: 0xF2 == White background (F), Green characters (2)*/
void writeToScreen(char * str, unsigned color) {
	char * pointer = screenStart;
	while(*str != '\0' && pointer - screenStart < 80 * 25) {
		*(pointer++) = *str;
		*(pointer++) = color;
		str++;
	}
}

void clearScreen() {
	char * pointer = screenStart;
	while(pointer - screenStart < 80 * 40) {
		*(pointer++) = 0;
	}
}