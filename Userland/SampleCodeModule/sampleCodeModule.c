/* sampleCodeModule.c */
#include <stdint.h>

char * v = (char*)0xB8000 + 79 * 2;
//extern void timeSysCall();
extern char * timeInt(char * str);
extern char * printStr(char * str, uint64_t t);


static int var1 = 0;
static int var2 = 0;


int main() {
	//All the following code may be removed 
	*v = 'X';
	*(v+1) = 0x74;

	char temp[9];
	char * time = timeInt(temp);
	char * status = printStr(temp, 0x0000000000000009);

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return time;

	return 0xDEADBEEF;
}