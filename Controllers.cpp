#include "Controllers.h"

void handleCommands(Node<mainNode>* head, char* bufor, int i)
{
	int j = 0;
	skipNewlineAndSpaces(bufor, &j);
	j += 4;
	while (j < i)
	{
		skipNewlineAndSpaces(bufor, &j);
		while (j < i && bufor[j] != '\n')
		{
			if (bufor[j] == '?')
				cout << "? == " << numOfSections(head) << endl;

			else if (bufor[j] > '0' && bufor[j] <= '9')
				numCom(head, bufor, i, &j);


			else if (bufor[j] == '*')
				j += 3;

			else
				textCom(head, bufor, i, &j);

			j++;
		}
	}
}

void numCom(Node<mainNode>* head, char* bufor, int i, int* j)
{
	int l = getNumber(bufor, j);

	(*j)++;

	if (bufor[*j] == 'S')
	{
		numSCom(head, bufor, i, j, l);
	}

	else if (bufor[*j] == 'A')
	{
		numACom(head, bufor, j, l);
	}

	else if (bufor[*j] == 'D')
	{
		numDCom(head, bufor, j, l);
	}

	else
	{
		while (bufor[*j] != '\n' && *j < i)
			(*j)++;
	}
}

void textCom(Node<mainNode>* head, char* bufor, int i, int*j)
{
	char* sthName = getName(bufor, j, ',');
	(*j)++;

	if (bufor[*j] == 'A' && bufor[*j + 2] == '?')
		cout << sthName << ",A,? == " << countAttributeAppearances(head, sthName) << endl;

	else if (bufor[*j] == 'S' && bufor[*j + 2] == '?')
		cout << sthName << ",S,? == " << countSelectorAppearances(head, sthName) << endl;

	else if (bufor[*j] == 'E')
	{
		*j += 2;
		char* attrName = getName(bufor, j, '\n');
		char* result = findAttributeForSelector(head, attrName, sthName);
		if (result)
			cout << sthName << ",E," << attrName << " == " << result << endl;
	}

	while (bufor[*j] != '\n' && *j < i)
		(*j)++;
}

void numSCom(Node<mainNode>* head, char* bufor, int i, int* j, int l)
{
	*j += 2;
	if (bufor[*j] == '?')
	{
		int count = numOfSelAtr(head, l, 'S');
		if (count)
			cout << l << ",S,? == " << count << endl;
	}

	else if (bufor[*j] > '0' && bufor[*j] <= '9')
	{
		int l2 = getNumber(bufor, j);
		char* output = findSelectorNum(head, l, l2);
		if (output)
			cout << l << ",S," << l2 << " == " << output << endl;

	}

	else
	{
		while (bufor[*j] != '\n' && *j < i)
			(*j)++;
	}
}

void numACom(Node<mainNode>* head, char* bufor, int* j, int l)
{
	*j += 2;
	if (bufor[*j] == '?')
	{
		int count = numOfSelAtr(head, l, 'A');
		if (count)
			cout << l << ",A,? == " << count << endl;
	}

	else
	{
		char* attributeName = getName(bufor, j, '\n');
		char* value = findAttributeName(head, l, attributeName);
		if (value)
			cout << l << ",A," << attributeName << " == " << value << endl;

	}
}

void numDCom(Node<mainNode>* head, char* bufor, int* j, int l)
{
	*j += 2;
	if (bufor[*j] == '*')
	{
		head = deleteSection(head, l);
		cout << l << ",D,* == deleted" << endl;
	}

	else
	{
		char* attrName = getName(bufor, j, '\n');
		head = deleteAttribute(head, attrName, l);
		cout << l << ",D," << attrName << " == deleted" << endl;
		
	}
}

void recieveInput(char* bufor, int *i, bool* commandMode)
{
	while (cin.get(bufor[*i]) && !(*commandMode) && bufor[*i] != '}')
	{
		if (*i > 2 && bufor[*i] == '*' && bufor[*i - 1] == '*' && bufor[*i - 2] == '*' && bufor[*i - 3] == '*')
			(*commandMode) = true;

		if (bufor[0] == '?')
			skipBadChars2(bufor, i);
		else
			skipBadChars(bufor, i);

		(*i)++;
	}
}

Node<char*>* handleSelectors(char* bufor, int* j, Node<char*>* selectors)
{
	while (bufor[*j] != '{')
	{
		int start = *j;
		while (bufor[*j] != ',' && bufor[*j] != '{')
		{
			(*j)++;
		}

		while (*j > 0 && bufor[*j - 1] == ' ')
			(*j)--;

		char* selektor = new char[*j - start + 1];

		for (int k = start; k < *j + 1; k++)
			selektor[k - start] = bufor[k];
		selektor[*j - start] = '\0';

		Node<char*>* tmp = selectors;
		bool repeated = false;
		for (int k = 0; k < selectors->getListLen(); k++)
		{
			if (compareCharTab(tmp->data, selektor))
			{
				repeated = true;
				break;
			}
			tmp = tmp->next;
		}

		if (!repeated)
		{
			selectors = selectors->addLast(selektor);
		}


		while (bufor[*j] == ',' || bufor[*j] == ' ')
			(*j)++;
	}

	return selectors;
}

Node<atrVal>* handleAttributes(char* bufor, int* j, Node<atrVal>* attributes)
{
	while (bufor[*j] != '}')
	{
		skipSpaces(bufor, j);
		int start = *j;
		while (bufor[*j] != ':')
		{
			(*j)++;
		}
		char* atrybut = new char[*j - start + 1];

		for (int k = start; k < *j; k++)
			atrybut[k - start] = bufor[k];
		atrybut[*j - start] = '\0';

		(*j)++;

		skipSpaces(bufor, j);

		start = *j;
		while (bufor[*j] != ';' && bufor[*j] != '}')
		{
			(*j)++;
		}

		if (bufor[*j] == '}')
			(*j)--;

		char* wartosc = new char[*j - start + 1];

		for (int k = start; k < *j; k++)
			wartosc[k - start] = bufor[k];
		wartosc[*j - start] = '\0';

		Node<atrVal>* tmp = attributes;
		bool repeated = false;
		for (int k = 0; k < attributes->getListLen(); k++)
		{
			if (compareCharTab(tmp->data.atrybut, atrybut))
			{
				repeated = true;
				break;
			}
			tmp = tmp->next;
		}

		if (repeated)
		{
			tmp->data.wartosc = wartosc;
		}

		else
		{
			atrVal paraAtrWart;
			paraAtrWart.atrybut = atrybut;
			paraAtrWart.wartosc = wartosc;
			attributes = attributes->addLast(paraAtrWart);
		}

		(*j)++;
	}

	return attributes;
}

void cleanMemory(Node<mainNode>* head)
{
	int sectionCount = numOfSections(head);
	for (int i = 0; i < sectionCount * T; i++)
	{
		head = deleteSection(head, 1);
	}
}