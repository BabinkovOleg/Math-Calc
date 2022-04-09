#include "mathFunctions.h"
#include "stringFunctions.h"

#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <malloc.h>

#define RES_STR_LENGTH 30
#define ERR_ALLOC "Allocation failed;("

double FunctionRes(char* str, int length) {
	length = AddBrackets(&str, length);
	if (str[1] == '-' && CountOfChar(str, '+', length) + CountOfChar(str, '*', length) + CountOfChar(str, '/', length) + CountOfChar(str, 's', length) + CountOfChar(str, 'c', length) + CountOfChar(str, 't', length) + CountOfChar(str, '^', length) == 0) {
		return atof(Substr(str, 1, length - 2));
	}
	else if (str[0] == '-') {
		return atof(Substr(str, 0, length - 1));
	}
	

	int indexOfOperator = -1;

	if (FindChar(str, 's', length) != -1 && FindChar(str, 'q', length) != -1) {
		indexOfOperator = FindChar(str, 's', length);

		int indexOfLeftBracket = FindChar(str, '(', length), indexOfRightBracket = FindCharR(str, ')', length);
		return sqrt(FunctionRes(Substr(str, indexOfLeftBracket + 1, indexOfRightBracket - 1), length - 6));
	}

	if (FindChar(str, 's', length) != -1 && FindChar(str, 'i', length) != -1) {
		indexOfOperator = FindChar(str, 's', length);
		int indexOfLeftBracket = FindChar(str, '(', length), indexOfRightBracket = FindCharR(str, ')', length);
		
		return sin(FunctionRes(Substr(str, indexOfLeftBracket , indexOfRightBracket ), length - 3));
	}

	if (FindChar(str, 'c', length) != -1 && FindChar(str, 'o', length) != -1) {
		indexOfOperator = FindChar(str, 'c', length);
		int indexOfLeftBracket = FindChar(str, '(', length), indexOfRightBracket = FindCharR(str, ')', length);
		
		/*str = Substr(str, indexOfLeftBracket, indexOfRightBracket);
		double a = FunctionRes(str, length - 3);*/
		double a = FunctionRes(Substr(str, indexOfLeftBracket , indexOfRightBracket), length - 3);

		return cos(a);
	}

	if (FindChar(str, 't', length) != -1 && FindChar(str, 'a', length) != -1) {
		indexOfOperator = FindChar(str, 't', length);
		int indexOfLeftBracket = FindChar(str, '(', length), indexOfRightBracket = FindCharR(str, ')', length);

		return tan(FunctionRes(Substr(str, indexOfLeftBracket, indexOfRightBracket), length - 3));
	}

	if (FindChar(str, '/', length) != -1) {
		indexOfOperator = FindChar(str, '/', length);
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

	if (FindChar(str, '+', length) != -1) {
		indexOfOperator = FindChar(str, '+', length);
		double a = FunctionRes(Substr(str, 1, indexOfOperator - 1), indexOfOperator);
		double b = FunctionRes(Substr(str, indexOfOperator + 1, length - 2), length - indexOfOperator - 1);
		
		return a + b;
	}

	if (FindChar(str, '^', length) != -1) {
		indexOfOperator = FindChar(str, '^', length);
		double a = FunctionRes(Substr(str, FindChar(str, '(', length), indexOfOperator - 1), indexOfOperator - FindChar(str, '(', length));
		double b = FunctionRes(Substr(str, indexOfOperator + 1, FindChar(str, ')', length)), length - indexOfOperator - 1);
		
		return pow(a, b);
	}

	if (FindChar(str, '-', length) != -1) {
		indexOfOperator = FindChar(str, '-', length);
		double a = FunctionRes(Substr(str, 1, indexOfOperator - 1), indexOfOperator);
		double b = FunctionRes(Substr(str, indexOfOperator + 1, length - 2), length - indexOfOperator - 1);
		
		return a - b;
	}

	if (FindChar(str, '*', length) != -1) {
		indexOfOperator = FindChar(str, '*', length);
		double a = FunctionRes(Substr(str, 1, indexOfOperator - 1), indexOfOperator);
		double b = FunctionRes(Substr(str, indexOfOperator + 1, length - 2), length - indexOfOperator - 1);
		
		return a * b;
	}

	if (CountOfChar(str, '(', length) == 0)
		return atof(str);
	else
		return atof(Substr(str, 1, length - 1));
}

double FunctionResDeep(char* str, int length) {
	length = AddBrackets(&str, length);
	if ((FindChar(str, '-', length) == 0) || CountOfChar(str, '+', length) + CountOfChar(str, '-', length) + CountOfChar(str, '*', length) + CountOfChar(str, '/', length) + CountOfChar(str, 's', length) + CountOfChar(str, 'c', length) + CountOfChar(str, 't', length) + CountOfChar(str, '^', length) == 0) {
		if (CountOfChar(str, '(', length) == 0)
			return atof(str);
		else
			return atof(Substr(str, 1, length - 1));
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
		if (str[i] == 'n' && str[i - 1] == 'a') {
			deep[i] = currentDeep + 1;
			deep[i - 1] = currentDeep + 1;
			deep[i - 2] = currentDeep + 1;
		}
		if (str[i] == 't' && str[i - 1] == 'r') {
			deep[i] = currentDeep + 1;
			deep[i - 1] = currentDeep + 1;
			deep[i - 2] = currentDeep + 1;
			deep[i - 3] = currentDeep + 1;
		}
		if (str[i] == 'n' && str[i - 1] == 'i') {
			deep[i] = currentDeep + 1;
			deep[i - 1] = currentDeep + 1;
			deep[i - 2] = currentDeep + 1;
		}
		if (str[i] == 's' && str[i - 1] == 'o') {
			deep[i] = currentDeep + 1;
			deep[i - 1] = currentDeep + 1;
			deep[i - 2] = currentDeep + 1;
		}
		if (str[i] == ')') {
			--currentDeep;
		}
	}

	//for (int i = 0; i < length; ++i) printf_s("%d", deep[i]);

	for (int i = 0; i < length; ++i) {
		if (deep[i] == max) {
			int indexStart = i, indexFinish = i - 1;
			while (deep[i] == max && i < length) {
				++indexFinish;
				++i;
			}
			double res = FunctionRes(Substr(str, indexStart, indexFinish), indexFinish - indexStart + 1);
			char* resStr = StringAlloc(RES_STR_LENGTH);
			
			int dec = 0, sign = 0;
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
			
			return FunctionResDeep(Merge3(Substr(str, 0, indexStart), resStr , Substr(str, indexFinish + 1, length - 1), indexStart, 16, length - indexFinish), length - (indexFinish - indexStart) + 16);
		}
	}
	printf_s("\n");
	free(deep);
	return 0;
}