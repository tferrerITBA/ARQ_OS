#include "include/RTC.h"

static char getFirstDigit(uint8_t num);
static char getSecondDigit(uint8_t num);

static char getFirstDigit(uint8_t num) {
	return (char)(num / 10 + '0');
}

static char getSecondDigit(uint8_t num) {
	return (char)(num % 10 + '0');
}

void timeToString(char * dest) {
	int i;
	uint8_t time[3];
	time[0] = get_hr();
	if(time[0] <= 2)
		time[0] = 21 + time[0];
	else
		time[0] -= 3;
	time[1] = get_min();
	time[2] = get_sec();
	for(i = 0; i < 3; i++) {
		dest[i * 3] = getFirstDigit(time[i]);
		dest[i * 3 + 1] = getSecondDigit(time[i]);
		char separator = (i != 2) ? ':' : '\0';
		dest[i * 3 + 2] = separator;
	}
}

