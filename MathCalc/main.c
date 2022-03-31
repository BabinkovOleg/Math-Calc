#include "mathFunctions.h"
#include <stdlib.h>
#include <Windows.h>
#include <malloc.h>

#define MAX_LENGTH_OF_FUNCTION 50
#define ERR_ALLOC "Allocation failed;("

int main(void) {
	char* functionStr = StringAlloc(MAX_LENGTH_OF_FUNCTION);
	int strLenght = 0;

	printf_s("Enter your task :\nExamples : (124+(1293-213))	sqrt(7+(3-2))	(3*(5+4))	sin((3.14/2))\n");

	strLenght = InputString(functionStr, MAX_LENGTH_OF_FUNCTION);

	printf_s("Result : %.15f\n", FunctionResDeep(functionStr, strLenght - 1));

	free(functionStr);
	system("pause");
	return 0;
}