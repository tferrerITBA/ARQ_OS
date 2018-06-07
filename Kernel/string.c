#include "string.h"

int strequals(char * s1, char * s2) {
	int i = 0;
	for(i = 0; s1[i] != 0 && s2[i] != 0; i++){
		if(s1[i] != s2[i]) {
			return 0;
		}
	}
	if(s1[i] != 0 || s2[i] != 0) {
		return 0;
	}
	return 1;
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
