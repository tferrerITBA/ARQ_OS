#include "sampleCodeModule.h"

#define SIZE 128
#define BACKSPACE 8
#define END 0

int main() {
	char command[SIZE] = {0};
	int index = 0;

	putChar('>');
	char c;
	while(1) {
		c = getChar();
		if(c != 0) {
			
			
			if(c == '\n') {
				putChar(c);
				readCommand(command);
				index = 0;
			}

			else if(c == BACKSPACE) {
				if(index > 0) {
					putChar(c);
					index--;
					command[index] = 0;
				}
				
			} else {
				if(index <= SIZE - 1) {
					command[index++] = c;
					command[index] = 0;
				} else {
					printf("Maximum command length reached\n");
					putChar('\n');
					index = 1;
				}	
				putChar(c);
			}
		}
	}
	return 0;
}

void readCommand(char command[]) {
	char action[SIZE] = {0};
	char params[SIZE] = {0};
	uint8_t colors[3]; 
	double mathCons[3];
	int i;
	int retValue;
	/* One-word commands */
	if(strequals(command,"help")) {
		runHelp();
	} else if(strequals(command,"clear")) {
		runClear();
	} else if(strequals(command,"zerodiv")) {
		runZeroDiv();
	} else if(strequals(command,"overflow")) {
		runOverflow();
	} else if(strequals(command,"invopc")) {
		runInvOpc();
	} else if(strequals(command,"time")) {
		runTime();
	}
	/* Commands with arguments */
	else{
		readWordFromCommand(action, command,0,' ');
		i = length(action) + 1;
		readWordFromCommand(params, command, i, END);
		if(strequals(action,"echo")) {
			printf(params);
		} else if(strequals(action,"chcolor")) {
			retValue = validateColors(colors, params);
			if(retValue != 0) {
				runChcolor(colors[0], colors[1], colors[2]);
			}
		} else if(strequals(action,"bgcolor")) {
			validateColors(colors, params);
			if(retValue != 0) {
				runBgcolor(colors[0], colors[1], colors[2]);
			}
		} else if(strequals(action,"math")) {
			retValue = validateMath(mathCons, params);
			if(retValue != 0) {
				runMath(mathCons[0], mathCons[1], mathCons[2]);
			}
		}
	}
}

/**
 * readWordFromCommand returns a char array with a single word to be 
 * compared with the valid commands
**/
void readWordFromCommand(char word[], char command[], int from, char to) {
	int i = from;
	while(command[i] != to) {
		word[i] = command[i];
		i += 1;
	}
}

int isDigit(char c) {
	if(c >= '0' && c <= '9') {
		return 1;
	} 
	return 0;
}

int toInt(char c) {
	return c - '0';
}

int validateColors(uint8_t ret[], char params[]) {
	int i = 0;
	int j = 0;
	int len;
	char number[SIZE];
	for (i = 0; i<3 ; i++) {
		if(i == 0 || i == 1) {
			readWordFromCommand(number, params, j,' ');
		} else {
			readWordFromCommand(number, params, j, END);
		}
		len = length(number);
		if(len > 3) {
			printf("Invalid color parameters");
			return 0; 
		}
		j += len + 1;
		ret [i] = integerValue(number, len);
		if(ret[i] ==  -1){
			printf("Invalid color parameters");
			return 0;
		}
	}
	return 1;	
}

int integerValue(char num[], int len) {
	int ret = 0;
	if(len == 3) {
		if(num[0] == '0' || num[1] == '1'){
			if(isDigit(num[1])) {
				if(isDigit(num[2])) {
					ret = (toInt(num[0]))*100 +  (toInt(num[1]))*10 + (toInt(num[2]));
					return ret; 
				}
			}
		} else if(num[0] == '2') {
			if(num[1] >= '0' && num[1] <= '5') {
				if(num[1] == '5') {
					if(num[2] >= '0' && num[2] <= '5') {
						ret = (toInt(num[0]))*100 +  (toInt(num[1]))*10 + toInt(num[2]);
						return ret; 
					}
				} else {
					if(isDigit(num[2])) {
						ret = (toInt(num[0]))*100 +  (toInt(num[1]))*10 + toInt(num[2]);
						return ret; 
					}
				}				
			}
		} 
		printf("Color values should be integers between 0 and 256");
		return -1;
	} else if(len == 2) {
		if(isDigit(num[0]) && isDigit(num[1])) {
			ret = (toInt(num[0]))*10 + toInt(num[1]);
		}
		printf("Color values should be integers between 0 and 256");
		return -1;
	} else {
		if(isDigit(num[0])) {
			return toInt(num[0]);
		}
		printf("Color values should be integers between 0 and 256");
		return -1;
	}
}

int validateMath(double ret[], char params[]) {
	double current = 0;
	int i = 0; //number of parameter
	int j = 0; //position in arguments array
	int k = 0; //position in current word
	double factor[] = {0.0};
	int len;
	char number[SIZE] = {0};
	for (i = 0; i<3 ; i++) {
		current = 0.0;
		if(i == 0 || i == 1) {
			readWordFromCommand(number, params, j,' ');
		} else {
			readWordFromCommand(number, params, j, END);
		}
		len = length(number);
		j += len + 1;
		int intPart = integerPartLength(number);
		if(intPart == -1) {
			printf("Invalid parameter format\n");
			return 0;
		}
		calculateFactor(factor, intPart);
		k = 0;
		while(intPart != 0) {
			current += factor[0]*(double)(toInt(number[k++]));
			factor[0] = factor[0]/10;
			intPart--;
		}
		k++;
		factor[0] = 0.1;
		while(number[k] != 0) {
			if(isDigit(number[k])) {
				current += factor[0]*(double)(toInt(number[k++])); 
			} else {
				printf("Invalid parameter format\n");
				return 0;
			}
		}
		ret[i] = current;
	}
	return 1;
}

void calculateFactor(double arr[], int digits) {
	double factor = 1;
	while(digits != 1) {
		factor *= 10.0;
	}
	arr[0] = factor;
	return;
}

int integerPartLength(char number[]) {
	int i = 0;
	while(number[i] != 0 && isDigit(number[i])) {
		i++;
	}
	if(i == 0 || number[i] != '.') {
		return -1;
	}
	return i;
}


int length(char * word) {
	int i = 0;

	while(word[i] != 0) {
		i++;
	}

	return i;
}