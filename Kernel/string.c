#include "string.h"

int strcmp(const char * str1, char * str2) {
	if(str1 == NULL && str2 == NULL)
		return 0;
	if(str1 == NULL || str2 == NULL)
		return -1;
	while(*str1 != '\0' && *str2 != '\0') {
		int diff = *str1 - *str2;
		if(diff != 0)
			return diff;
	}
	return *str1 - *str2;
}

int strlen(char * str) {
	if(str == NULL)
		return 0;
	int count = 0;
	while(*(str++) != '\0')
		count++;
	return count;
}

char * strchr(char * str, char c) {
	if(str == NULL)
		return NULL;
	while(*str != c && *str != '\0')
		str++;
	return (*str == c) ? str : NULL;
} 
