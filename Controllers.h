#pragma once
#include "Commands.h"
#include "TwoWayList.h"

void handleCommands(Node<mainNode>* head, char* bufor, int i);

void numCom(Node<mainNode>* head, char* bufor, int i, int* j);

void textCom(Node<mainNode>* head, char* bufor, int i, int* j);

void numSCom(Node<mainNode>* head, char* bufor, int i, int* j, int l);

void numACom(Node<mainNode>* head, char* bufor, int* j, int l);

void numDCom(Node<mainNode>* head, char* bufor, int* j, int l);

void recieveInput(char* bufor, int* i, bool* commandMode);

Node<char*>* handleSelectors(char* bufor, int* j, Node<char*>* selectors);

Node<atrVal>* handleAttributes(char* bufor, int* j, Node<atrVal>* attributes);

void cleanMemory(Node<mainNode>* head);