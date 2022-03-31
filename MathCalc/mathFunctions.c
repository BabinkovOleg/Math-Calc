#include "mathFunctions.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ERR_ALLOC "Allocation failed;("
#define RES_STR_LENGTH 30

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

double Atoi(char* str, int length) {
	int indexOfPoint = FindChar(str, '.', length), degree = 1;
	double digit = 0.0f;
	if (indexOfPoint == -1) {
		for (int i = length - 1; i >= 0; --i) {
			digit += degree * (str[i] - '0');
			degree *= 10;
		}
		return digit;
	}
	else {
		double negativeDegree = 0.1f;
		for (int i = indexOfPoint + 1; i < length; ++i) {
			digit += negativeDegree * (str[i] - '0');
			negativeDegree /= 10;
		}
		for (int i = indexOfPoint - 1; i >= 0; --i) {
			digit += degree * (str[i] - '0');
			degree *= 10;
		}
		return digit;
	}
}

double FunctionRes(char* str, int length) {
	if (str[1] == '-') {
		return atof(Substr(str, 1, length - 2));
	}
	else if (str[0] == '-') {
		return atof(Substr(str, 0, length - 1));
	}
	char operation = 'n';
	int indexOfOperator = -1;

	if (FindChar(str, 's', length) != -1 && FindChar(str, 'i', length) != -1) {
		indexOfOperator = FindChar(str, 's', length);
		operation = 'S';
	}
	if (FindChar(str, 'c', length) != -1 && FindChar(str, 'o', length) != -1) {
		indexOfOperator = FindChar(str, 'c', length);
		operation = 'C';
	}

	if (FindChar(str, 's', length) != -1 && FindChar(str, 'q', length) != -1) {
		indexOfOperator = FindChar(str, 's', length);
		operation = 's';
	}

	if (FindChar(str, '+', length) != -1) {
		indexOfOperator = FindChar(str, '+', length);
		operation = '+';
	}
	if (FindChar(str, '-', length) != -1) {
		indexOfOperator = FindChar(str, '-', length);
		operation = '-';
	}

	if (FindChar(str, '*', length) != -1) {
		indexOfOperator = FindChar(str, '*', length);
		operation = '*';
	}
	if (FindChar(str, '/', length) != -1) {
		indexOfOperator = FindChar(str, '/', length);
		operation = '/';
	}

	if (FindChar(str, '^', length) != -1) {
		indexOfOperator = FindChar(str, '^', length);
		operation = '^';
	}

	if (operation == 'n') {
		return atof(str);
	}

	if (operation == 'S') {
		int indexOfLeftBracket = FindChar(str, '(', length), indexOfRightBracket = FindCharR(str, ')', length);
		return sin(FunctionRes(Substr(str, indexOfLeftBracket + 1, indexOfRightBracket - 1), length - 5));
	}
	if (operation == 'C') {
		int indexOfLeftBracket = FindChar(str, '(', length), indexOfRightBracket = FindCharR(str, ')', length);
		return cos(FunctionRes(Substr(str, indexOfLeftBracket + 1, indexOfRightBracket - 1), length - 5));
	}

	if (operation == 's') {
		int indexOfLeftBracket = FindChar(str, '(', length), indexOfRightBracket = FindCharR(str, ')', length);
		return sqrt(FunctionRes(Substr(str, indexOfLeftBracket + 1, indexOfRightBracket - 1), length - 6));
	}

	if (operation == '+') {
		double a = FunctionRes(Substr(str, 1, indexOfOperator - 1), indexOfOperator);
		double b = FunctionRes(Substr(str, indexOfOperator + 1, length - 2), length - indexOfOperator - 1);
		return a + b;
	}
	if (operation == '-') {
		double a = FunctionRes(Substr(str, 1, indexOfOperator - 1), indexOfOperator);
		double b = FunctionRes(Substr(str, indexOfOperator + 1, length - 2), length - indexOfOperator - 1);
		return a - b;
	}

	if (operation == '*') {
		double a = FunctionRes(Substr(str, 1, indexOfOperator - 1), indexOfOperator);
		double b = FunctionRes(Substr(str, indexOfOperator + 1, length - 2), length - indexOfOperator - 1);
		return a * b;
	}
	if (operation == '/') {
		double a = FunctionRes(Substr(str, 1, indexOfOperator - 1), indexOfOperator);
		double b = FunctionRes(Substr(str, indexOfOperator + 1, length - 2), length - indexOfOperator - 1);
		if (b == 0) {
			printf_s("Dividing by zero..\n");
			exit(2);
		}
		else {
			return a / b;
		}
	}

	if (operation == '^') {
		double a = FunctionRes(Substr(str, 1, indexOfOperator - 1), indexOfOperator);
		double b = FunctionRes(Substr(str, indexOfOperator + 1, length - 2), length - indexOfOperator - 1);
		return pow(a, b);
	}
}

double FunctionResDeep(char* str, int length) {
	if (CountOfChar(str, '(', length) == 0) {
		return atof(str);
	}
	int* deep = (int*)malloc(sizeof(int) * length);
	if (!deep) {
		printf_s(ERR_ALLOC);
		exit(1);
	}
	int currentDeep = 0, max = -1;
	for (int i = 0; i < length; ++i) {
		if (str[i] == '(') {
			++currentDeep;
			if (currentDeep > max) {
				max = currentDeep;
			}
		}
		deep[i] = currentDeep;
		if (str[i - 1] == 'r' && str[i] == 't') {
			deep[i] = currentDeep + 1;
			deep[i - 1] = currentDeep + 1;
			deep[i - 2] = currentDeep + 1;
			deep[i - 3] = currentDeep + 1;
		}
		if (str[i - 1] == 'i' && str[i] == 'n') {
			deep[i] = currentDeep + 1;
			deep[i - 1] = currentDeep + 1;
			deep[i - 2] = currentDeep + 1;
		}
		if (str[i - 1] == 'o' && str[i] == 's') {
			deep[i] = currentDeep + 1;
			deep[i - 1] = currentDeep + 1;
			deep[i - 2] = currentDeep + 1;
		}
		if (str[i] == ')') {
			--currentDeep;
		}
	}

	//for (int i = 0; i < length; ++i) {
	//	printf_s("%d", deep[i]);
	//}
	//printf_s("\n");

	for (int i = 0; i < length; ++i) {
		if (deep[i] == max) {
			int indexStart = i, indexFinish = i - 1;
			while (deep[i] == max && i < length) {
				++indexFinish;
				++i;
			}
			double res = FunctionRes(Substr(str, indexStart, indexFinish), indexFinish - indexStart + 1);
			char* resStr = StringAlloc(RES_STR_LENGTH);
			
			int dec, sign;
			_ecvt_s(resStr, RES_STR_LENGTH, res, RES_STR_LENGTH - 2, &dec, &sign);
			
			if (dec >= 0) {
				for (int j = RES_STR_LENGTH; j >= dec; --j) {
					resStr[j] = resStr[j - dec];
				}
				resStr[dec] = '.';
			}
			else {
				for(int j = RES_STR_LENGTH; j >= -1 * dec + 2; --j){
					resStr[j] = resStr[j + dec - 2];
				}
				for (int j = 0; j < -1 * dec + 2; ++j) {
					resStr[j] = '0';
				}
				resStr[1] = '.';
			}
			//resStr[dec + 1] = resStr[dec];
			
			if (sign) {
				for (int j = 20; j >= 1; --j) {
					resStr[j] = resStr[j - 1];
				}
				resStr[0] = '-';
			}
			
			//printf_s("%d\n",dec);
			//printf_s("%s\n",resStr);

			return FunctionResDeep(Merge3(Substr(str, 0, indexStart), resStr, Substr(str, indexFinish + 1, length - 1), indexStart, 16, length - indexFinish), length - (indexFinish - indexStart) + 16);
		}
	}
	//return 12;
	//double res = F1unctionRes(str, length);
	printf_s("\n");
	//return res;
	free(deep);
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

char* merge2(char* str1, char* str2, int length1, int length2) {
	char* newString = StringAlloc(length1 + length2);
	for (int i = 0; i < length1; ++i) {
		newString[i] = str1[i];
	}
	for (int i = length1; i < length1 + length2; ++i) {
		newString[i] = str2[i - length1];
	}
	return newString;
}