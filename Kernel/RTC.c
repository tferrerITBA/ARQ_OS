#include "RTC.h"

static char getFirstDigit(uint8_t num) {
	return (char)(num / 10 + '0');
}

static char getSecondDigit(uint8_t num) {
	return (char)(num % 10 + '0');
}

void timeToString() {
	int i;
	char str[9];
	uint8_t time[3];
	time[0] = get_hr();
	time[1] = get_min();
	time[2] = get_sec();
	for(i = 0; i < 3; i++) {
		str[i * 3] = getFirstDigit(time[i]);
		str[i * 3 + 1] = getSecondDigit(time[i]);
		char separator = (i != 2) ? ':' : '\0';
		str[i * 3 + 2] = separator;
	}
	writeToScreen(str, 0xF2);
}

