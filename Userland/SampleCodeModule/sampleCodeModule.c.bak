/* sampleCodeModule.c */
#include <stdint.h>

char * v = (char*)0xB8000 + 79 * 2;
//extern void timeSysCall();
extern char * timeInt(char * str);
extern char * printStr(char * str, uint64_t t);
extern char * clearScr();
extern char * changeBColors(uint8_t * colors);
extern char * changeCColors(uint8_t * colors);
extern void mathFunc(double, double, double);
extern char * pixelInt(uint64_t x, uint64_t y);
extern char * readStr(uint64_t, uint64_t);


static int var1 = 0;
static int var2 = 0;


int main() {
	//All the following code may be removed 
	*v = 'X';
	*(v+1) = 0x74;

	char temp[9];
	int i;
	uint8_t c1[] = {0xA9, 0x12, 0x56};
	uint8_t c2[] = {0x38, 0xF0, 0x19};
	while(i < 250) {
		pixelInt(0,i);
	timeInt(temp);
	char * status = printStr(temp, 0x0000000000000009);
	//char * status4 = clearScr();
	changeCColors(c2);
	char * status2 = printStr(temp, 0x0000000000000009);
	changeBColors(c1);
	char * status3 = printStr(temp, 0x0000000000000009);
	i++;
	
	}

	mathFunc(0.5, 1.5, -40);

	while(1) {
		char buf[] = {0};
		char * ptr = readStr(buf, 1);
		if(ptr != 0) {
			char * status2 = printStr(buf, 1);
		}
	}
	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}