#pragma once

char* StringAlloc(int length);
char* Substr(char* originStr, int left, int right);
char* Merge2(char* str1, char* str2, int length1, int length2);
char* Merge3(char* str1, char* str2, char* str3, int length1, int length2, int length3);
int InputString(char* str, int maxLenght);
int AddBrackets(char** str, int length);
int FindChar(char* str, char ch, int length);
int FindCharR(char* str, char ch, int length);
int CountOfChar(char* str, char ch, int lenght);

//double Atoi(char* str, int length);