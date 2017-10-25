#include <stdint.h>

void timeToString();

char getFirstDigit(uint8_t num);

char getSecondDigit(uint8_t num);

void writeToScreen(char * str, unsigned color);

extern uint8_t get_sec();

extern uint8_t get_min();

extern uint8_t get_hr();