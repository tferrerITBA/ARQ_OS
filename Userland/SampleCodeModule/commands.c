#include "commands.h"
#include "lib.h"
#include "functionGraph.h"
#include <stdint.h>
#define STEP 6
extern char * clearScr();
extern char * timeInt();
extern char * changeBColors(uint8_t colors[]);
extern char * changeCColors(uint8_t colors[]);

void runHelp() {
	printf("clear: erases all visible text \n");
	printf("\n");
	printf("chcolor b g r: changes characters color (previously written characters keep the original color). b, g and r are hexadecimal values for red, green and blue components\n");
	printf("\n");
	printf("bgcolor b g r: changes background color. b, g and r are hexadecimal values for blue, green and red components \n");
	printf("\n");
	printf("zerodiv: shows zero division exception handling\n");
	printf("\n");
	printf("overflow: shows overflow exception handling\n");
	printf("\n");
	printf("invopc: shows invalid opcode exception handling\n");
	printf("\n");
	printf("zerodiv: shows zero division exception handling\n");
	printf("\n");
	printf("echo str: prints string str\n");
	printf("math a b c: plots mathemathical function ax^2 + bx + c\n");
	printf("\n");
	printf("securityon: hides input characters until securityoff is invoked\n");
	printf("\n");
	printf("securityoff: recovers from securityon mode\n");
	printf("\n");
	printf("colorfade from to: prints a color fade effect between any of the primary colors or between black and white\n");
	printf('\n');
}

void runClear() {
	clearScr();
}

void runZeroDiv() {
	int a = 1;
	int b = 0;
	a = a/b;
}

void runOverflow() {

}

void runInvOpc() {
	raiseInvOp();
}

void runTime() {
	printf(timeInt());
	putChar('\n');
}

void runChcolor(uint8_t blue, uint8_t green, uint8_t red) {
	uint8_t colors [3] = {blue, green, red};
	changeCColors(colors);
}

void runBgcolor(uint8_t blue, uint8_t green, uint8_t red) {
	uint8_t colors [3] = {blue, green, red};
	changeBColors(colors);
}

void runMath(double a, double b, double c) {
	clearScr();
	mathFunc(a,b,c);
}

void colorFade(uint8_t from[], uint8_t to[]) {
	int j = 0;
	uint8_t cBlue = from[0];
	uint8_t cGreen = from[1];
	uint8_t cRed = from[2];

	for(int i = 0; i<255/STEP; i++ ) {
		if(cBlue >= 0 && cBlue < 256 && cGreen >= 0 && cGreen < 256 && cRed >= 0 && cRed < 256) {
			runBgcolor(cBlue, cGreen, cRed);
			if(cBlue < to[0] ) {
				cBlue += STEP;
			} else if(cBlue > to[0] ) {
				cBlue -= STEP;
			}

			if(cGreen < to[1]) {
				cGreen += STEP;
			} else if(cGreen > to[1]){
				cGreen -= STEP;
			}
			if(cRed < to[2]) {
				cRed += STEP;
			} else if(cRed > to[2]) {
				cRed -= STEP;
			}
			
		}
		for(j = 0; j < 127; j++) {
			putChar(' ');
		}
		putChar('\n');
	}
	putChar('\n');
	runBgcolor(0,0,0);
}

uint8_t getDistance(uint8_t a, uint8_t b) {
	if(a > b) {
		return a - b;
	} else {
		return b - a;
	}
}