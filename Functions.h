#pragma once
#include "TwoWayList.h"

bool compareCharTab(char* a, char* b);

int skipSpaces(char* tab, int* count);

int skipBadChars(char* tab, int* count);

int skipBadChars2(char* tab, int* count);

int skipNewlineAndSpaces(char* tab, int* count);

sekcja findSectionNum(Node<mainNode>* head, int num);

int charToInt(char* number, int numLen);

int getNumber(char* tab, int* count);

char* getName(char* tab, int* count, char limiter);