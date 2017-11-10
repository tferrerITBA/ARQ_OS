extern int printNChars(char * s, int len);
extern int scanChar(char * s, int len);


void putChar(char c) { ////calls assembly function printNChars which uses syscall write
	printNChars(&c, 1);
}

char getChar() { //calls assembly function scanChar which uses syscall read

	char c = 0; //null character

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



int scanf(char * buff) { 

	char c;
	int count = 0;

	while((c = getChar()) != '\n') {

		*(buff + count) = c;
		count++;
		putChar(c);
	}

	if(count != 0) 
		putchar('\n');

	return count;
}


int stringlength(char * s){ //returns length of string

	int len = 0;
	while(*str != '\0'){

		len++;
		str++;
	}
	return len;
}
