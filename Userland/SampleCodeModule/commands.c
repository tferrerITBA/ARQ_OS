#include "commands.h"


void runHelp() {
	printf("clear: erases all visible text \n");
	printf("chcolor b g r: changes characters color (previously written characters keep the original color). b, g and r are hexadecimal values for red, green and blue components\n");
	printf("bgcolor b g r: changes background color. b, g and r are hexadecimal values for blue, green and red components \n");
	printf("zerodiv: shows zero division exception handling\n");
	printf("invopc: shows invalid opcode exception handling\n");
	printf("echo str: prints string str\n");
	printf("math a b c: plots mathemathical function ax^2 + bx + c\n");
	printf("securityon: hides input characters until securityoff is invoked\n");
	printf("securityoff: recovers from securityon mode\n");
	printf("colorfade from to: prints a color fade effect between any of the primary colors or between black and white\n");
	printf("-----------------------------------------------------------\n");
	printf("-----------------------------------------------------------\n");
	printf("multiDemo: enters a finite loop. It allows the user to run new processes in the meantime \n");
	printf("killDemo: enters an infinite loop so that the only way for it to finish is killing it with the command kill\n");
	printf("kill [pid]: kills the process with the given PID\n");
	printf("mallocDemo: a simple usage of user level malloc and free\n");
	printf("ps: lists all processes including terminated ones\n");
	printf("prodcons: a simple implementation of producer consumer problem\n");
	putChar('\n');
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

void sh(function functionName, int foreground) {
	if(foreground) {
		printf("Running in foreground\n");
		functionName();
	} else {
		newProcessInt(functionName);
	}
}

void ps() {
	psint();
}

void prodcons() {
	initializeProdConsInt();
	newProcessInt(producer);
	//newProcessInt(producer);
	newProcessInt(consumer);
	endOfProcess();
}

void producer() {
	produceInt();
	endOfProcess();
}

void consumer() {
	consumeInt();
	endOfProcess();
}

void multiDemo() {
    int i=0;
    while(i< 500000000) {
        i++;
    }

    printf("\nLoop is finished\n>");
    endOfProcess();
}

void mallocDemo() {

    char * demo = malloc(30);
    printf("\nMemory allocated\n");
    demo[0] = 'a';
    demo[1] = 'b';
    demo[2] = 'c';
    demo[3] =  0;
    printf(demo);
    printf("\n");
    printf("\nMemory Reallocated\n");
    char * redemo = realloc(demo,40);
    printf(demo);
    printf("\n");
    printf("\nMemory allocated with zeros\n");
    char * c_demo = calloc(20);
    c_demo[0] = 'a';
    c_demo[1] = 'b';
    c_demo[2] = 'c';
    printf(c_demo);
    printf("\n");
    free(demo);
    free(c_demo);
    printf("\nMemory deallocated\n>");
    endOfProcess();
}

void killDemo() {
    pid_t pid = getpid();
    printf("My pid is: ");
    if(pid >= 10) {
        putChar('0' + pid/10);
    }
    putChar('0' + pid%10);
    putChar('\n');
    while(1);
}


void endOfProcess() {
    int pid = (int)getpid();
    if(pid != 1) {
        kill(pid);
        while(1);
    }
}
