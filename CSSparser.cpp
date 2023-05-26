#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "TwoWayList.h"
#include "Functions.h"
#include "Commands.h"
#include "Controllers.h"
using namespace std;
const int BufforSize = 4000;

int main()
{
	char bufor[BufforSize];
	Node<mainNode>* main = NULL;
	int ktoraToSekcja = 0, i = 0;

	while (cin.get(bufor[i]))
	{
		if(bufor[0]=='?')
			skipBadChars2(bufor, &i);
		else
			skipBadChars(bufor, &i);

		i++;
		bool commandMode = false;

		recieveInput(bufor, &i, &commandMode);

		if (bufor[i] != '}')
			commandMode = true;
		
		if (!commandMode)
		{
			Node<char*>* selectors = NULL;
			Node<atrVal>* attributes = NULL;
			int j = 0;
			while (j < i)
			{

				if (bufor[j] == '{')
				{
					j++;
					attributes = handleAttributes(bufor, &j, attributes);

					if (ktoraToSekcja % T == 0)
					{
						sekcja* sectionTab = new sekcja[T]{};
						mainNode wezel = { sectionTab, 0 };
						main = main->addLast(wezel);
					}

					if (attributes->getListLen())
					{
						Node<mainNode>* tmp = main->getLast();
						tmp->data.sekcje[ktoraToSekcja % T].selektory = selectors;
						tmp->data.sekcje[ktoraToSekcja % T].atrybuty = attributes;
						tmp->data.licznikZaj++;
						ktoraToSekcja++;
					}
				}

				else
					selectors = handleSelectors(bufor, &j, selectors);
			}
		}

		else
			handleCommands(main, bufor, i);

		i = 0;
	}

	cleanMemory(main);

	return 0;
}