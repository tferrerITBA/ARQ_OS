extern int printNChars(char * s, int len);
extern int scanChar(char * s, int len);

#include "lib.h"


void putChar(unsigned char c) { ////calls assembly function printNChars which uses syscall write
	printNChars(&c, 1);
}

char getChar() { //calls assembly function scanChar which uses syscall read

	unsigned char c = 0; //null character

	do {

		scanChar(&c, 1);

	} while(c == 0);

	return c;
}

void printf(char * s){  //print the string

	int length = stringlength(s); 
	printNChars(s, length);
}

void printInt(int n) {

	int cociente;
	int resto;


	if(n < 0) {
		putChar('-');
		n = n * (-1);
	}
	
	if( n < 10) {

		putChar(n + '0');
		return;
	}

	do {
		cociente = n/10;
		resto = n%10;
		n = cociente;
		putChar(resto + '0');

	} while(n != 0);

	return;
}



int scanf(char * buffer) { 

	char c;
	int count = 0;

	while((c = getChar()) != '\n') {
		
		if(c == '\b') { //c is backspace
			if(count != 0) { //not in start of buffer
				--count;
				*(buffer + count) = 0;
				putChar(c);
			}
		}
		else {

		*(buffer + count) = c;
		count++;
		putChar(c);
		}
	}

	if(count != 0) //No characters added in buffer
		putChar('\n');

	return count;
}


int stringlength(char * s){ //returns length of string

	int len = 0;
	while(*s != '\0'){

		len++;
		s++;
	}
	return len;
} 

int strequals(char * s1, char * s2) {
	int i = 0;
	for(i = 0; s1[i] != 0 && s2[i] != 0; i++){
		if(s1[i] != s2[i]) {
			return 0;
		}
	}
	if(s1[i] != 0 || s2[i] != 0) {
		return 0;
	}
	return 1;
}