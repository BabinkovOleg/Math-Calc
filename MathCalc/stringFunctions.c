#include "stringFunctions.h"

#include <math.h>
#include <Windows.h>
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

char* Substr(char* originStr, int left, int right) {
	char* newString = StringAlloc(right - left + 1);
	for (int i = left; i <= right; ++i) {
		newString[i - left] = originStr[i];
	}
	return newString;
}

char* Merge2(char* str1, char* str2, int length1, int length2) {
	char* newString = StringAlloc(length1 + length2);
	for (int i = 0; i < length1; ++i) {
		newString[i] = str1[i];
	}
	for (int i = length1; i < length1 + length2; ++i) {
		newString[i] = str2[i - length1];
	}
	return newString;
}

char* Merge3(char* str1, char* str2, char* str3, int length1, int length2, int length3) {
	char* newString = StringAlloc(length1 + length2 + length3);
	for (int i = 0; i < length1; ++i) {
		newString[i] = str1[i];
	}
	for (int i = length1; i < length1 + length2; ++i) {
		newString[i] = str2[i - length1];
	}
	for (int i = length1 + length2; i < length1 + length2 + length3; ++i) {
		newString[i] = str3[i - length1 - length2];
	}
	return newString;
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

int AddBrackets(char** str, int length) {
	int counterOfNewBrackets = 0;
	char* newStr = StringAlloc(length + abs(CountOfChar(*str, '(', length) - CountOfChar(*str, ')', length)));

	newStr = Merge2(*str, "", length, 0);

	while (CountOfChar(newStr, ')', length + counterOfNewBrackets) < CountOfChar(newStr, '(', length + counterOfNewBrackets)) {
		counterOfNewBrackets += 1;
		newStr = Merge2(newStr, ")", length + counterOfNewBrackets - 1, 1);
	}
	while (CountOfChar(newStr, '(', length + counterOfNewBrackets) < CountOfChar(newStr, ')', length + counterOfNewBrackets)) {
		counterOfNewBrackets += 1;
		newStr = Merge2("(", newStr, 1, length + counterOfNewBrackets - 1);
	}
	*str = newStr;
	return length + counterOfNewBrackets;
}

int FindChar(char* str, char ch, int length) {
	int index = 0;
	while (index < length) {
		if (str[index] == ch) {
			return index;
		}
		++index;
	}
	return -1;
}

int FindCharR(char* str, char ch, int length) {
	int index = length - 1;
	while (index >= 0) {
		if (str[index] == ch) {
			return index;
		}
		--index;
	}
	return index;
}

int CountOfChar(char* str, char ch, int lenght) {
	int counter = 0;
	for (int i = 0; i < lenght; ++i) {
		if (str[i] == ch) {
			++counter;
		}
	}
	return counter;
}

//double Atoi(char* str, int length) {
//	int indexOfPoint = FindChar(str, '.', length), degree = 1;
//	double digit = 0.0f;
//	if (indexOfPoint == -1) {
//		for (int i = length - 1; i >= 0; --i) {
//			digit += degree * (str[i] - '0');
//			degree *= 10;
//		}
//		return digit;
//	}
//	else {
//		double negativeDegree = 0.1f;
//		for (int i = indexOfPoint + 1; i < length; ++i) {
//			digit += negativeDegree * (str[i] - '0');
//			negativeDegree /= 10;
//		}
//		for (int i = indexOfPoint - 1; i >= 0; --i) {
//			digit += degree * (str[i] - '0');
//			degree *= 10;
//		}
//		return digit;
//	}
//}