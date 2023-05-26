#pragma once
#include "Functions.h"
#include "TwoWayList.h"

int numOfSections(Node<mainNode>* head);

int numOfSelAtr(Node<mainNode>* head, int num, char w);

char* findSelectorNum(Node<mainNode>* head, int sectionNum, int selectorNum);

char* findAttributeName(Node<mainNode>* head, int sectionNum, char* attributeName);

int countAttributeAppearances(Node<mainNode>* head, char* attributeName);

int countSelectorAppearances(Node<mainNode>* head, char* selectorName);

char* findAttributeForSelector(Node<mainNode>* head, char* attributeName, char* selectorName);

Node<mainNode>* deleteSection(Node<mainNode>* head, int num);

Node<mainNode>* deleteAttribute(Node<mainNode>* head, char* attrName, int sectionNum);