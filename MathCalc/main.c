//#include "mathFunctions.h"
//#include <stdlib.h>
//#include <Windows.h>
//#include <malloc.h>
//
//#define ACCURACY "10"
//#define MAX_LENGTH_OF_FUNCTION 50
//#define ERR_ALLOC "Allocation failed;("
//
//int main(void) {
//	char* functionStr = StringAlloc(MAX_LENGTH_OF_FUNCTION);
//	int strLenght = 0;
//	printf_s("Examples : (124+(1293-213))    sqrt((7+(3-2)))    (3*(5+4))    sin((3.14/2))\nEnter your tasks :\n");
//	while (functionStr[0] != '\n') {
//		strLenght = InputString(functionStr, MAX_LENGTH_OF_FUNCTION);
//		if (functionStr[0] != '\n') {
//			printf_s("Result : %." ACCURACY "f+-10^(-" ACCURACY ")\n", FunctionResDeep(functionStr, strLenght - 1));
//		}
//	}
//		
//	free(functionStr);
//	system("pause");
//	return 0;
//}

#include "raylib.h"
#include "mathFunctions.h"
#include "stringFunctions.h"
#include "buttonActions.h"

#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

#define ACCURACY "10"
#define MAX_LENGTH_OF_FUNCTION 250
#define ERR_ALLOC "Allocation failed;("

#define NUM_FRAMES  3       // Number of frames (rectangles) for the button sprite texture
#define NUM_BUTTONS 24		// 0-9 // . // +-/* // sin(cos(tan( // sqrt( // () // ^ // = // backspace
#define NUM_ROWS 4
#define NUM_COLUMNS 6
#define HEIGHT_RESULT_RECT 100.0f

int main(void)
{
	const int screenWidth = 882;
	const int screenHeight = 420;

	InitWindow(screenWidth, screenHeight, "OleGalculator");

	Texture2D buttons = LoadTexture("resources/buttons.png"); // Load button texture // 18 * 147 x 3 * 80
	
	float frameHeight = (float)buttons.height / NUM_FRAMES;
	float frameWidth = (float)buttons.width / NUM_BUTTONS;

	Rectangle sourceRec = { 0, 0, frameWidth, frameHeight };

	Rectangle* btnsBounds = (Rectangle*)malloc(sizeof(Rectangle) * NUM_BUTTONS);

	for (int i = 0; i < NUM_BUTTONS; ++i) {
		btnsBounds[i].x = frameWidth * (i % NUM_COLUMNS);
		btnsBounds[i].y = HEIGHT_RESULT_RECT + frameHeight * (i / NUM_COLUMNS);
		btnsBounds[i].width = frameWidth;
		btnsBounds[i].height = frameHeight;
	}

	int* btnsState = (int*)malloc(sizeof(int) * NUM_BUTTONS);
	int btnAction = -1;

	for (int i = 0; i < NUM_BUTTONS; ++i) {
		btnsState[i] = 0;					// Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
	}
	
	char* result = StringAlloc(MAX_LENGTH_OF_FUNCTION);
	sprintf_s(result, MAX_LENGTH_OF_FUNCTION, "0.0");
	char* functionStr = StringAlloc(MAX_LENGTH_OF_FUNCTION);
	int functionLength = 0;
	functionStr[0] = '\0';

	Vector2 mousePoint = { 0.0f, 0.0f };

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		mousePoint = GetMousePosition();

		btnAction = -1;

		for (int i = 0; i < NUM_BUTTONS; ++i) {
			if (CheckCollisionPointRec(mousePoint, (Rectangle) { btnsBounds[i].x + 1.0f, btnsBounds[i].y + 1.0f, btnsBounds[i].width - 2.0f, btnsBounds[i].height - 2.0f })) {
				if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnsState[i] = 2;
				else btnsState[i] = 1;

				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = i;
			}
			else btnsState[i] = 0;
		}

		if (btnAction >= 0 && btnAction < NUM_BUTTONS - 2) {
			functionStr = Merge2(functionStr, UpdateStr(btnAction), functionLength, UpdateLen(btnAction));
			functionLength += UpdateLen(btnAction);
			functionStr[functionLength] = '\0';
		}
		if (btnAction == NUM_BUTTONS - 2 && functionLength > 0) {
			functionStr = Substr(functionStr, 0, functionLength - 2);
			functionLength -= 1;
			functionStr[functionLength] = '\0';
		}
		if (btnAction == NUM_BUTTONS - 1) {
			sprintf_s(result, MAX_LENGTH_OF_FUNCTION, "Result : %." ACCURACY "f+-10^(-" ACCURACY ")\n", FunctionResDeep(Merge3("(", functionStr, ")", 1, functionLength, 1), functionLength + 2));
		}

		BeginDrawing();

		ClearBackground(RAYWHITE);

		for (int i = 0; i < NUM_BUTTONS; ++i) {
			sourceRec.y = btnsState[i] * frameHeight;
			sourceRec.x = i * frameWidth;
			DrawTextureRec(buttons, sourceRec, (Vector2) { btnsBounds[i].x, btnsBounds[i].y }, WHITE);
		}

		DrawText(functionStr, 10, 10, 40, BLACK);
		DrawText(result, 10, 60, 40, BLACK);

		EndDrawing();
	}

	UnloadTexture(buttons);

	free(btnsBounds);
	free(btnsState);
	//free(functionStr);		//Error when close window idk why
	free(result);

	CloseWindow();

	return 0;
}