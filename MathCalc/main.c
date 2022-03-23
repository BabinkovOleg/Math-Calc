#include "mathFunctions.h"
#include <stdlib.h>
#include <Windows.h>
#include <malloc.h>

#define MAX_LENGTH_OF_FUNCTION 50
#define ERR_ALLOC "Allocation failed;("

int main(void) {
	char* functionStr = StringAlloc(MAX_LENGTH_OF_FUNCTION);
	int strLenght = 0;

	strLenght = InputString(functionStr, MAX_LENGTH_OF_FUNCTION);

	for (int i = 0; i < strLenght; ++i) {
		printf_s("%c", functionStr[i]);
	}

	printf_s("%d %d\n", FindChar(functionStr, 'k', strLenght), FindCharL(functionStr, 'k', strLenght));

	free(functionStr);
	system("pause");
	return 0;
}