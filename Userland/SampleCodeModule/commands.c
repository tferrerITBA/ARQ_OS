#include "commands.h"

static int prodconsPipeId;

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
	printf("-----------------------------------------------------------\n");
	printf("-----------------------------------------------------------\n");
	printf("fileDemo: creates a file and writes to it. Its content is then read.\n");
	printf("ls: shows current directorie's subfolders and files\n");
	printf("cd [path]: changes the current working directory to a specified subdirectory.\n");
	printf("touch [pathAndName]: creates a file with the specified name in the specified directory.\n");
	printf("mkdir [pathAndName]: creates a directory with the specified name in the specified directory.\n");
	printf("rm [pathAndName] [type]: deletes a file (if type is isFile), or a directory recursively (if type is isDir).\n");
	printf("fileDetails [pathAndName]: prints a file's name, size and current status.\n");
	printf("pipeProdcons: executes a producer consumer problem using pipes .\n");
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
	initializeProdCons();
	newProcessInt(producer);
	//newProcessInt(producer);
	newProcessInt(consumer);
	endOfProcess();
}

void producer() {
	produce();
	endOfProcess();
}

void consumer() {
	consume();
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

void messageDemo() {

	newProcessInt(sender);
	newProcessInt(receiver);
    endOfProcess();
}

void sender() {
	char * msg = "Message";
	send(msg);
	endOfProcess();
}

void receiver() {
	char * message;
    message = receive();
    printf("I received the following message: ");
	printf(message);
	putChar('\n');
    putChar('>');
	endOfProcess();
}

void pipeProdcons() {
    prodconsPipeId = (int)createPipe();
    newProcessInt(pipeProducer);
    newProcessInt(pipeConsumer);
    endOfProcess();
}

void pipeProducer() {
    int i;
    openPipe(WRITE,prodconsPipeId);
    while(1) {
        printf("Producing item");
        printf("\n");
        writePipe(prodconsPipeId,'c');
    }
    endOfProcess();
}

void pipeConsumer() {
    int consumed = 0;
    openPipe(READ, prodconsPipeId);
    while (1) {
        printf("Consuming\n");
        printf(readPipe(prodconsPipeId));
        consumed++;
    }
    endOfProcess();
}

int changeDir(char * path) {
	return cd(path);
}

void l_s() {
	ls();
}

int makeDir(char * path) {
	return mkdir(path);
}

int createFile(char * path) {
	return touch(path);
}

int remove(char * path, int isDir) {
	int a = rm(path, isDir);
	return a;
}

int getFileDetails(char * path) {
	return fileDetails(path);
}

void fileDemo() {
	char aux[] = {'w', '0'};
	printf("Creating file in cwd called: HelloWorld\n");
	touch("HelloWorld");
	int open1;
	printf("Opening in w mode and writing 'Hello world!'.\n");
	open1 = open("HelloWorld", "w");
	char * hello = "Hello world!";
	int status = write(hello, 14, 1, open1);
	close(open1);
	aux[0] = 'r';
	printf("Closing and opening same file in r mode\n");
	open1 = open("HelloWorld", "r");
	char buffer[50] = {0};
	status = read(buffer, 7, 2, open1);
	printf("Read: ");
	printf(buffer);
	printf("\n");
	close(open1);
	printf("File details:\n");
	fileDetails("HelloWorld");
	printf("You can now check the file is present, and see its details with the fileDetails <path> command.\n");
	return;
}
