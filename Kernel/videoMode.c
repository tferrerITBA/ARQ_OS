#include "videoMode.h"

//VBEModeInfoBlock.PhysBasePtr
uint8_t ** physBasePtr = VBEModeInfo + 40;
//VBEModeInfoBlock.BytesPerScanLine
uint16_t * bytesPerScanLine = VBEModeInfo + 16;
//VBEModeInfoBlock.BitsPerPixel
uint8_t * bitsPerPixel = VBEModeInfo + 25;
//VBEModeInfoBlock.XResolution
uint16_t * XResolution = VBEModeInfo + 18;
//VBEModeInfoBlock.YResolution
uint16_t * YResolution = VBEModeInfo + 20;

static uint8_t charColor[] = {0xFF, 0xFF, 0xFF}; //B,G,R; 0xFF == White, 0x00 == Black
static uint8_t backgroundColor[] = {0x00, 0x00, 0x00};
static int currPos = 0;
static int currRow = 0;

void putPixel(unsigned x, unsigned y) {
	if(x < 0 || x > *XResolution || y < 0 || y > *YResolution)
		return;
	uint8_t * screenPosition = (uint8_t *)(y * *bytesPerScanLine + 
		(x * (*bitsPerPixel / 8)) + *physBasePtr);
	*(screenPosition++) = charColor[BLUE];
	*(screenPosition++) = charColor[GREEN];
	*(screenPosition++) = charColor[RED];
}

void put_char(int c) {
	if(c == '\n') {
		newLine();
		return;
	}
	if(c == 0x08) {
		deleteChar();
		return;
	}
	unsigned char * character = pixel_map(c);
	int bytesPerPixel = *bitsPerPixel / 8;
	int i,j;
	for(i = 0; i < CHAR_HEIGHT; i++) {
		for(j = 0; j < CHAR_WIDTH; j++) {
			uint8_t mask = pow(2,CHAR_WIDTH-j-1);
			uint8_t * ptr = (uint8_t *)(*physBasePtr+(currPos* CHAR_WIDTH * bytesPerPixel +
				i * *bytesPerScanLine + currRow * CHAR_HEIGHT * *bytesPerScanLine 
				+ (j * bytesPerPixel)));
			if((*character & mask) == mask) {
				paintPix(ptr, 1);
			}
			else {
				paintPix(ptr, 0);
			}

		}
		character++;
	}
	if(currPos == 0)
		currPos++;
	else if((currPos+1) % (*bytesPerScanLine / (bytesPerPixel * CHAR_WIDTH)) == 0) {
		newLine();
	}
	else
		currPos++;
}

void deleteChar() {
	if(currPos == 0 && currRow == 0)
		return;
	int bytesPerPixel = *bitsPerPixel / 8;
	if(currPos == 0) {
		currPos = (*bytesPerScanLine / (bytesPerPixel * CHAR_WIDTH)) - 1;
		currRow--;
	}
	else
		currPos--;
	int i,j;
	for(i = 0; i < CHAR_HEIGHT; i++) {
		for(j = 0; j < CHAR_WIDTH; j++) {
			uint8_t * ptr = (uint8_t *)(*physBasePtr+(currPos* CHAR_WIDTH * bytesPerPixel +
				i * *bytesPerScanLine + currRow * CHAR_HEIGHT * *bytesPerScanLine 
				+ (j * bytesPerPixel)));
			paintPix(ptr, 0);
		}
	}
}

void putString(char * str) {
	for( ; *str != 0; str++) {
		unsigned char c = *str;
		if(c != '\n' && c != 0x08)
			put_char(c);
		else if(c == '\n')
			newLine();
		else if(c == 0x08)
			deleteChar();
	}
}

void putnString(char * str, uint64_t length) {
	for( ; length > 0 && *str != 0; length--) {
		unsigned char c = *str;
		if(c != '\n' && c != 0x08)
			put_char(c);
		else if(c == '\n')
			newLine();
		else if(c == 0x08)
			deleteChar();
		str++;
	}
}

void setCharColors(uint8_t cb, uint8_t cg, uint8_t cr) {
	charColor[BLUE] = cb;
	charColor[GREEN] = cg;
	charColor[RED] = cr;
}

void setBackgroundColors(uint8_t bb, uint8_t bg, uint8_t br) {
	backgroundColor[BLUE] = bb;
	backgroundColor[GREEN] = bg;
	backgroundColor[RED] = br;
}

void paintPix(uint8_t * pos, int charC) {
	if(!charC) {
		*pos = backgroundColor[BLUE];
		*(pos + 1) = backgroundColor[GREEN];
		*(pos + 2) = backgroundColor[RED];
		return;
	}
	*pos = charColor[BLUE];
	*(pos + 1) = charColor[GREEN];
	*(pos + 2) = charColor[RED];
}

uint8_t pow(uint8_t num, uint8_t exp) {
	uint8_t ret = 1;
	while(exp > 0) {
		ret *= num;
		exp--;
	}
	return ret;
}

void clearScreen() {
	int i;
	unsigned totalBytes = *XResolution * *YResolution * *bitsPerPixel / 8;
	for(i = 0; i < totalBytes; i+= 3) {
		*(*physBasePtr + i) = backgroundColor[BLUE];
		*(*physBasePtr + i + 1) = backgroundColor[GREEN];
		*(*physBasePtr + i + 2) = backgroundColor[RED];
	}
	currPos = currRow = 0;
}

void newLine() {
	if(currRow == ((int)*YResolution / CHAR_HEIGHT) - 1) {
		moveScreenOneUp();
		return;
	}
	currRow++;
	currPos = 0;
}

void moveScreenOneUp() {
	uint8_t * ptr = *physBasePtr + *bytesPerScanLine * CHAR_HEIGHT;
	uint8_t * endPtr = *physBasePtr +
		*bytesPerScanLine * CHAR_HEIGHT * (currRow + 1);
	while(ptr != endPtr) {
		copyPixel(ptr, ptr - *bytesPerScanLine * CHAR_HEIGHT);
		ptr += 3;
	}
	ptr = *physBasePtr + *bytesPerScanLine * CHAR_HEIGHT * (currRow);
	while(ptr != endPtr) {
		paintPix(ptr, 0);
		ptr += 3;
	}
	currPos = 0;
}

void copyPixel(uint8_t * source, uint8_t * dest) {
	*dest = *source;
	*(dest + 1) = *(source + 1);
	*(dest + 2) = *(source + 2);
}