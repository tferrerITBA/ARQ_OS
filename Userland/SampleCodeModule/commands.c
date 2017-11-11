#include "lib.h"
#include "functionGraph.h"
#include <stdint.h>
extern char * clearScr();
extern char * timeInt();
extern char * changeBColors(uint8_t colors[]);
extern char * changeCColors(uint8_t colors[]);

void runHelp() {
	printf("clear: erases all visible text \n");
	printf("\n");
	printf("chcolor b g r: changes characters color (previously written characters keep the original color) \n");
	printf("               b, g and r are hexadecimal values for red, green and blue components\n");
	printf("\n");
	printf("bgcolor b g r: changes background color.\n");
	printf("               b, g and r are hexadecimal values for blue, green and red components \n");
	printf("\n");
	printf("zerodiv: shows zero division exception handling\n");
	printf("\n");
	printf("overflow: shows overflow exception handling\n");
	printf("\n");
	printf("invopc: shows invalid opcode exception handling\n");
	printf("\n");
	printf("zerodiv: shows zero division exception handling\n");
	printf("\n");
	printf("echo str: prints str\n");
	printf("          str must be a string\n");
	printf("math a b c: plots mathemathical function ax^2 + bx + c\n");
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

}

void runTime() {
	timeInt();
}

void runChcolor(uint8_t blue, uint8_t green, uint8_t red) {

}

void runBgcolor(uint8_t blue, uint8_t green, uint8_t red) {

}

void runMath(double a, double b, double c) {
	mathFunc(a,b,c);
}