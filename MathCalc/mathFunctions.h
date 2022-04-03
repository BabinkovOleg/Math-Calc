#pragma once

char* StringAlloc(int length);
int InputString(char* str, int maxLenght);
char* Substr(char* originStr, int left, int right);
int FindChar(char* str, char ch, int length);
int FindCharR(char* str, char ch, int length);
int CountOfChar(char* str, char ch, int lenght);
double Atoi(char* str, int length);
double FunctionRes(char* str, int length);
double FunctionResDeep(char* str, int length);
char* Merge3(char* str1, char* str2, char* str3, int length1, int length2, int length3);
char* Merge2(char* str1, char* str2, int length1, int length2);

//int UpdateString(char* str, int length, int btnID);
char* UpdateStr(int btnID);
int UpdateLen(int btnID);