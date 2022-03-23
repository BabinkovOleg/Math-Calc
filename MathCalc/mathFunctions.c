#include "mathFunctions.h"
#include <malloc.h>
#include <stdio.h>

#define ERR_ALLOC "Allocation failed;("

char* StringAlloc(int length) {
	char* str = (char*)malloc(sizeof(char) * length);
	if (!str) {
		printf_s(ERR_ALLOC);
		exit(1);
	}
	return str;
}

int InputString(char* str, int maxLenght) {
	int charCounter = 0;
	char buffer = '0';
	while (charCounter <= maxLenght && buffer != '\n') {
		buffer = getchar();
		str[charCounter] = buffer;
		++charCounter;
	}
	return charCounter;
}

char* Substr(char* originStr, int left, int right) {
	char* newString = StringAlloc(right - left + 1);
	for (int i = left; i <= right; ++i) {
		newString[i - left] = originStr[i];
	}
	return newString;
}

int FindChar(char* str, char ch, int length) {
	int index;
	for (index = 0; index < length; ++index) {
		if (str[index] == ch) {
			return index;
		}
	}
	return -1;
}

int FindCharL(char* str, char ch, int length) {
	int index;
	for (index = length - 1; index >= 0; --index) {
		if (str[index] == ch) {
			return index;
		}
	}
	return -1;
}

double FunctionRes(char* str, int length) {
	
}