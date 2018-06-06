#include "lib.h"
#include "commands.h"
#include <stdint.h>
#define SIZE 128
#define BACKSPACE 8
#define END 0
#define STANDARD 1
#define MATH 2
#define SECURITY 3
#define FOREGROUND 1
#define BACKGROUND 0

void terminal();
int toInt(char c);
int readCommand(char command[], int mode);
int readCommandwithArguments(char command[], int mode);
void readWordFromCommand(char word[], char command[], int from, char to);
int validateColors(uint8_t ret[], char params[]);
int validateFade(uint8_t ret[], uint8_t aux[], char params[]);
int integerValue(char num[], int len, uint8_t colVals[] , int index);
int validateMath(double * ret, char * params);
void calculateFactor(double arr[], int digits);
int integerPartLength(char * number);
int isDigit(char c);
int toInt(char c);
int length(char word[]);
int isNumber(char * str);
int calculatePid(char * string);
void validateRm(char * params);
extern void raiseInvOp();
