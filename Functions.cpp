#include "Functions.h"

bool compareCharTab(char* a, char* b)
{
	int i = 0;
	while (a[i] != '\0' || b[i] != '\0')
	{
		if (a[i] != b[i])
			return false;
		i++;
	}

	return true;
}

int skipSpaces(char* tab, int* count)
{
	while (tab[*count] == 32)
		(*count)++;

	return *count;
}

int skipBadChars(char* tab, int* count)
{
	if (tab[*count] < 32)
		(*count)--;

	return *count;
}

int skipBadChars2(char* tab, int* count)
{
	if (tab[*count] < 32 && tab[*count]!=10)
		(*count)--;

	return *count;
}

int skipNewlineAndSpaces(char* tab, int* count)
{
	while (tab[*count] == 32 || tab[*count] == 10)
		(*count)++;

	return *count;
}

sekcja findSectionNum(Node<mainNode>* head, int num)
{
	Node<mainNode>* tmp = head;
	int licznik = tmp->data.licznikZaj;
	while (licznik < num && tmp->next != NULL)
	{
		tmp = tmp->next;
		licznik += tmp->data.licznikZaj;
	}

	licznik -= tmp->data.licznikZaj;

	int index = 0;
	while (licznik != num)
	{
		if (tmp->data.sekcje[index].atrybuty != NULL)
			licznik++;

		index++;
	}
	index--;

	return tmp->data.sekcje[index];
}

int charToInt(char* number, int numLen)
{
	int result = 0;
	for (int i = 0; i < numLen; i++)
	{
		result *= 10;
		result += number[i] - '0';
	}

	return result;
}

int getNumber(char* tab, int* count)
{
	int start = *count;
	while (tab[*count] != ',' && tab[*count] != '\n')
		(*count)++;

	char* liczbaChar = new char[*count - start];

	for (int i = start; i < *count; i++)
		liczbaChar[i - start] = tab[i];

	int liczba = charToInt(liczbaChar, *count - start);

	delete[] liczbaChar;

	return liczba;
}

char* getName(char* tab, int* count, char limiter)
{
	int start = *count;
	while (tab[*count] != limiter)
	{
		(*count)++;
	}

	char* name = new char[*count - start + 1];

	for (int i = start; i < *count; i++)
		name[i - start] = tab[i];
	name[*count - start] = '\0';

	return name;
}

