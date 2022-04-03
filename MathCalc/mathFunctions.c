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
			
			if (dec > 0) {
				for (int j = RES_STR_LENGTH; j >= dec + 1; --j) {
					resStr[j] = resStr[j - 1];
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
			if (sign) {
				for (int j = RES_STR_LENGTH; j >= 1; --j) {
					resStr[j] = resStr[j - 1];
				}
				resStr[0] = '-';
			}
			
			return FunctionResDeep(Merge3(Substr(str, 0, indexStart), resStr, Substr(str, indexFinish + 1, length - 1), indexStart, 16, length - indexFinish), length - (indexFinish - indexStart) + 16);
		}
	}
	printf_s("\n");
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

char* UpdateStr(int btnID) {
	switch (btnID)
	{
	case 0:
		return "1";
		break;
	case 1:
		return "2";
		break;
	case 2:
		return "3";
		break;
	case 6:
		return "4";
		break;
	case 7:
		return "5";
		break;
	case 8:
		return "6";
		break;
	case 12:
		return "7";
		break;
	case 13:
		return "8";
		break;
	case 14:
		return "9";
		break;
	case 19:
		return "0";
		break;
	case 18:
		return ".";
		break;
	case 3:
		return "sin(";
		break;
	case 4:
		return "cos(";
		break;
	case 5:
		return "tan(";
		break;
	case 9:
		return "+";
		break;
	case 10:
		return "-";
		break;
	case 11:
		return "/";
		break;
	case 15:
		return "*";
		break;
	case 16:
		return "^";
		break;
	case 17:
		return "sqrt(";
		break;
	case 20:
		return "(";
		break;
	case 21:
		return ")";
		break;
	default:
		return "";
		break;
	}
}

int UpdateLen(int btnID) {
	switch (btnID)
	{
	case 0:
		return 1;
		break;
	case 1:
		return 1;
		break;
	case 2:
		return 1;
		break;
	case 6:
		return 1;
		break;
	case 7:
		return 1;
		break;
	case 8:
		return 1;
		break;
	case 12:
		return 1;
		break;
	case 13:
		return 1;
		break;
	case 14:
		return 1;
		break;
	case 19:
		return 1;
		break;
	case 18:
		return 1;
		break;
	case 3:
		return 4;
		break;
	case 4:
		return 4;
		break;
	case 5:
		return 4;
		break;
	case 9:
		return 1;
		break;
	case 10:
		return 1;
		break;
	case 11:
		return 1;
		break;
	case 15:
		return 1;
		break;
	case 16:
		return 1;
		break;
	case 17:
		return 5;
		break;
	case 20:
		return 1;
		break;
	case 21:
		return 1;
		break;
	default:
		return 0;
		break;
	}
}

//int UpdateString(char* str, int length, int btnID) {
//	switch (btnID)
//	{
//		case 0:
//			str = Merge2(str, "1", length, 2);
//			return length + 1;
//			break;
//		case 1:
//			str = Merge2(str, "2", length, 1);
//			return length + 1;
//			break;
//		case 2:
//			str = Merge2(str, "3", length, 1);
//			return length + 1;
//			break;
//		case 6:
//			str = Merge2(str, "4", length, 1);
//			return length + 1;
//			break;
//		case 7:
//			str = Merge2(str, "5", length, 1);
//			return length + 1;
//			break;
//		case 8:
//			str = Merge2(str, "6", length, 1);
//			return length + 1;
//			break;
//		case 12:
//			str = Merge2(str, "7", length, 1);
//			return length + 1;
//			break;
//		case 13:
//			str = Merge2(str, "8", length, 1);
//			return length + 1;
//			break;
//		case 14:
//			str = Merge2(str, "9", length, 1);
//			return length + 1;
//			break;
//		case 19:
//			str = Merge2(str, "0", length, 1);
//			return length + 1;
//			break;
//		case 18:
//			str = Merge2(str, ".", length, 1);
//			return length + 1;
//			break;
//		case 3:
//			str = Merge2(str, "sin(", length, 4);
//			return length + 4;
//			break;
//		case 4:
//			str = Merge2(str, "cos(", length, 4);
//			return length + 4;
//			break;
//		case 5:
//			str = Merge2(str, "tan(", length, 4);
//			return length + 4;
//			break;
//		case 9:
//			str = Merge2(str, "+", length, 1);
//			return length += 1;
//			break;
//		case 10:
//			str = Merge2(str, "-", length, 1);
//			return length + 1;
//			break;
//		case 11:
//			str = Merge2(str, "/", length, 1);
//			return length + 1;
//			break;
//		case 15:
//			str = Merge2(str, "*", length, 1);
//			return length + 1;
//			break;
//		case 16:
//			str = Merge2(str, "^", length, 1);
//			return length + 1;
//			break;
//		case 17:
//			str = Merge2(str, "sqrt(", length, 5);
//			return length + 5;
//			break;
//		case 20:
//			str = Merge2(str, "(", length, 1);
//			return length + 1;
//			break;
//		case 21:
//			str = Merge2(str, ")", length, 1);
//			return length + 1;
//			break;
//		case 22:
//			if (length > 0) {
//				str = Substr(str, 0, length - 1);
//				return length - 1;
//			}
//			else {
//				return length;
//			}
//			break;
//		default:
//			return length;
//			break;
//	}
//}