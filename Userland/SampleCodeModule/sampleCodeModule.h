#include "lib.h"
#include "commands.h"
#include <stdint.h>
int toInt(char c);
void readCommand(char command[]);
void readWordFromCommand(char word[], char command[], int from, char to);
int validateColors(uint8_t ret[], char params[]);
int integerValue(char num[], int len);
int validateMath(double * ret, char * params);
void calculateFactor(double arr[], int digits);
int integerPartLength(char * number);
int isDigit(char c);
int toInt(char c);
int length(char word[]);