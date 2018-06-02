#include "sampleCodeModule.h"

int main(void) {
	newProcessInt(terminal);
    return 1;
}

void terminal() {
	char command[SIZE] = {0};
	int index = 0;
	int ret = 1;

	printf("Welcome! Type 'help' for the full command list\n");
	putChar('>');
	char c;
	while(1) {
		c = getChar();
		if(c != 0) {
			if(c == '\n') {
				putChar(c);
				if(index != 0) {
					ret = readCommand(command,ret);
					index = 0;
					command[0] = 0;
				}
				putChar('>');
			} else if(c == BACKSPACE) {
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
					command[1] = 0;
				}
				if(ret != SECURITY) {
					putChar(c);
				} else {
					putChar('*');
				}
			}
		}
	}
}


int readCommand(char command[], int mode) {



    if(mode == 2) {
        if(strequals(command,"exit")) {
            runClear();
            return 1;
        } else {
            printf("Invalid command. Type 'exit' for leaving funcion graph mode\n");
            return 2;
        }
    } else {
        /* One-word commands */
        if(strequals(command,"clear")) {
            runClear();
        } else if(strequals(command,"zerodiv")) {
            runZeroDiv();
        } else if(strequals(command,"overflow")) {
            runOverflow();
        } else if(strequals(command,"invopc")) {
            runInvOpc();
        } else if(strequals(command,"time")) {
            runTime();
        } else if(strequals(command,"securityon")) {
            printf("Security mode is on\n");
            return SECURITY;
        } else if(strequals(command,"securityoff")) {
            printf("Security mode is off\n");
            return STANDARD;
        } else if(strequals(command,"help")) {
            runHelp();
        } else if(strequals(command,"ps")) {
            ps();
        } else if(strequals(command,"prodcons")) {
			sh(prodcons, BACKGROUND);
		} else if(strequals(command,"multiDemo")) {
			sh(multiDemo,BACKGROUND);
		} else if (strequals(command, "mallocDemo")) {
			sh(mallocDemo, BACKGROUND);
		} else if (strequals(command, "killDemo")) {
			sh(killDemo, BACKGROUND);
		} else if (strequals(command, "messageDemo")) {
            sh(messageDemo, BACKGROUND);
        } else if (strequals(command, "messageDemo")) {
			sh(messageDemo, BACKGROUND);
		} else if(strequals(command,"pipeProdcons")) {
			sh(pipeProdcons, BACKGROUND);
		} else if(strequals(command,"multiDemo&")) {
			sh(multiDemo,FOREGROUND);
		} else if (strequals(command, "mallocDemo&")) {
			sh(mallocDemo, FOREGROUND);
		} else{
           return readCommandwithArguments(command, mode);
        }
    }
    if(mode == 3) {
        return SECURITY;
    }
    return STANDARD;
}

int readCommandwithArguments(char command[], int mode) {

    char action[SIZE] = {0};
    char params[SIZE] = {0};
    int retValue = 0;
    uint8_t colors[3] = {0};
    uint8_t colorAux[3] = {0};
    double mathCons[3];
    int i;


    readWordFromCommand(action, command,0,' ');
    i = length(action) + 1;
    readWordFromCommand(params, command, i, END);
    if(strequals(action,"echo")) {
        printf(params);
        printf("\n");
    } else if(strequals(action,"chcolor")) {
        retValue = validateColors(colors, params);
        if(retValue != 0) {
            runChcolor(colors[0], colors[1], colors[2]);
        }
    } else if(strequals(action,"bgcolor")) {
        retValue = validateColors(colors, params);
        if(retValue != 0) {
            runBgcolor(colors[0], colors[1], colors[2]);
        }
    } else if(strequals(action,"colorfade")) {
        retValue = validateFade(colors, colorAux, params);
        if(retValue != 0) {
            colorFade(colors, colorAux);
        }
    } else if(strequals(action,"math")) {
        retValue = validateMath(mathCons, params);
        if(retValue != 0) {
            runMath(mathCons[0], mathCons[1], mathCons[2]);
            return MATH;
        }
    } else if(strequals(action,"kill")) {
		pid_t pid = calculatePid(params);
		if(pid > 1) {
			kill(pid);
		} else {
            if(pid == 1) {
                printf("Killing main process is forbidden \n");
            } else {
                printf("Invalid pid entry\n");
            }
		}
	} else {
        printf("Invalid command. Try 'help' for information about avaliable options\n");
    }
}


/**
 * readWordFromCommand returns a char array with a single word to be
 * compared with the valid commands
**/
void readWordFromCommand(char word[], char command[], int from, char to) {
	int i = from;
	int j = 0;
	while(command[i] != 0 && command[i] != to) {
		word[j] = command[i];
		word[j+1] = 0;
		i++;
		word++;
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
	int returnValue;
	char number[SIZE] = {0};
	for (i = 0; i<3 ; i++) {
		if(i == 0 || i == 1) {
			readWordFromCommand(number, params, j,' ');
		} else {
			readWordFromCommand(number, params, j, END);
		}
		len = length(number);
		if(len > 3) {
			printf("Invalid color parameters\n");
			return 0;
		}
		j += len + 1;
		returnValue = integerValue(number, len, ret, i);
		if(returnValue ==  -1){
			return 0;
		}
	}
	return 1;
}

int integerValue(char num[], int len, uint8_t colVals[] , int index) {
	uint8_t ret = 0;

	if(len == 3) {
		if(num[0] == '0' || num[0] == '1'){
			if(isDigit(num[1]) && isDigit(num[2])) {
				ret = (toInt(num[0]))*100 +  (toInt(num[1]))*10 + (toInt(num[2]));
				colVals[index] = ret;
				return 1;
			}
		} else if(num[0] == '2') {
			if(num[1] >= '0' && num[1] <= '5') {
				if(num[1] == '5') {
					if(num[2] >= '0' && num[2] <= '5') {
						ret = (toInt(num[0]))*100 +  (toInt(num[1]))*10 + toInt(num[2]);
						colVals[index] = ret;
						return 1;
					}
				} else {
					if(isDigit(num[2])) {
						ret = (toInt(num[0]))*100 +  (toInt(num[1]))*10 + toInt(num[2]);
						colVals[index] = ret;
						return 1;
					}
				}
			}
		}
		printf("Color values should be integers between 0 and 256\n");
		return -1;
	} else if(len == 2) {
		if(isDigit(num[0]) && isDigit(num[1])) {
			ret = (toInt(num[0]))*10 + toInt(num[1]);
			colVals[index] = ret;
			return 1;
		}
		printf("Color values should be integers between 0 and 256\n");
		return -1;
	} else {
		if(isDigit(num[0])) {
			colVals[index] = toInt(num[0]);
			return 1;
		}
		printf("Color values should be integers between 0 and 256\n");
		return -1;
	}
}
int validateFade(uint8_t * colors, uint8_t * colorsAux, char * params) {
	if(strequals(params,"green red") || strequals(params,"red green")) {
		colors[0] = 0;
		colors[1] = 255;
		colors[2] = 0;
		colorsAux[0] = 0;
		colorsAux[1] = 0;
		colorsAux[2] = 255;
		return 1;
	} else if(strequals(params,"blue red") || strequals(params,"red blue")) {
		colors[0] = 255;
		colors[1] = 0;
		colors[2] = 0;
		colorsAux[0] = 0;
		colorsAux[1] = 0;
		colorsAux[2] = 255;
		return 1;
	} else if (strequals(params,"blue green") || strequals(params,"green blue")) {
		colors[0] = 0;
		colors[1] = 255;
		colors[2] = 0;
		colorsAux[0] = 255;
		colorsAux[1] = 0;
		colorsAux[2] = 0;
		return 1;
	} else if (strequals(params,"black white") || strequals(params,"white black")) {
		colors[0] = 0;
		colors[1] = 0;
		colors[2] = 0;
		colorsAux[0] = 255;
		colorsAux[1] = 255;
		colorsAux[2] = 255;
		return 1;
	}
	printf("Colors not supported\n");
	return 0;

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
		number[0] = 0;
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
		k = 0;

		if(number[0] == '-') {
			calculateFactor(factor,intPart - 1);
			k++;
		} else {
			calculateFactor(factor, intPart);
		}
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
				factor[0] /= 10;
			} else {
				printf("Invalid parameter format\n");
				return 0;
			}
		}
		if(number[0] == '-') {
			current *= -1.0;
		}
		ret[i] = current;
	}
	return 1;
}

void calculateFactor(double arr[], int digits) {
	double factor = 1;
	if(digits == 1) {
		arr[0] = 1.0;
		return;
	} else if(digits > 1) {
		while(digits-- != 1) {
			factor *= 10.0;
		}
		arr[0] = factor;
		return;
	} else {
		printf("digits es menor que 0\n");
	}

}

int integerPartLength(char number[]) {
	int i = 0;
	if(number[0] == '-') {
		i++;
	}
	while(number[i] != 0 && isDigit(number[i])) {
		i++;
	}
	if(i == 0 || number[i] != '.' || (i == 1 && number[0] == '-')) {
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

int calculatePid(char * string) {

	if(isDigit(string[0]) && string[1] == 0) {
		return string[0] - '0';
	} else if (isDigit(string[1]) && isDigit(string[0]) && string[2] == 0){
		return (string[0] - '0')*10 + string[1] - '0';
	} else {
		return -1;
	}
}
