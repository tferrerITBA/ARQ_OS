#include "lib.h"
#include "commands.h"
#include <stdint.h>
int toInt(char c);
int readCommand(char command[], int mode);
void readWordFromCommand(char word[], char command[], int from, char to);
int validateColors(uint8_t ret[], char params[]);
int integerValue(char num[], int len, uint8_t colVals[] , int index);
int validateMath(double * ret, char * params);
void calculateFactor(double arr[], int digits);
int integerPartLength(char * number);
int isDigit(char c);
int toInt(char c);
int length(char word[]);
extern void raiseInvOp();
