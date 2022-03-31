#include "mathFunctions.h"
#include <stdlib.h>
#include <Windows.h>
#include <malloc.h>

#define ACCURACY "10"
#define MAX_LENGTH_OF_FUNCTION 50
#define ERR_ALLOC "Allocation failed;("

int main(void) {
	char* functionStr = StringAlloc(MAX_LENGTH_OF_FUNCTION);
	int strLenght = 0;
	printf_s("Examples : (124+(1293-213))    sqrt((7+(3-2)))    (3*(5+4))    sin((3.14/2))\nEnter your tasks :\n");
	while (functionStr[0] != '\n') {
		strLenght = InputString(functionStr, MAX_LENGTH_OF_FUNCTION);
		if (functionStr[0] != '\n') {
			printf_s("Result : %." ACCURACY "f+-10^(-" ACCURACY ")\n", FunctionResDeep(functionStr, strLenght - 1));
		}
	}
		
	free(functionStr);
	system("pause");
	return 0;
}

