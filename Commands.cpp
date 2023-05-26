#include "Commands.h"

int numOfSections(Node<mainNode>* head)
{
	int result = 0;
	Node<mainNode>* tmp = head;
	for (int i = 0; i < head->getListLen(); i++)
	{
		result += tmp->data.licznikZaj;
		tmp = tmp->next;
	}

	return result;
}

int numOfSelAtr(Node<mainNode>* head, int num, char w)
{
	if (num < 1 || num > numOfSections(head))
		return NULL;

	sekcja tmp = findSectionNum(head, num);

	if (w == 'S')
		return tmp.selektory->getListLen();

	if (w == 'A')
		return tmp.atrybuty->getListLen();

	return NULL;
}

char* findSelectorNum(Node<mainNode>* head, int sectionNum, int selectorNum)
{
	if (sectionNum < 1 || selectorNum < 1 || sectionNum > numOfSections(head))
		return NULL;

	Node<char*>* tmp = findSectionNum(head, sectionNum).selektory;

	if (tmp->getListLen() < selectorNum)
		return NULL;

	for (int i = 1; i < selectorNum; i++)
	{
		tmp = tmp->next;
	}

	return tmp->data;
}

char* findAttributeName(Node<mainNode>* head, int sectionNum, char* attributeName)
{
	if (sectionNum < 1 || sectionNum > numOfSections(head))
		return NULL;

	Node<atrVal>* tmp = findSectionNum(head, sectionNum).atrybuty;
	int tmpLen = tmp->getListLen();
	for (int i = 0; i < tmpLen; i++)
	{
		if (compareCharTab(attributeName, tmp->data.atrybut))
			return tmp->data.wartosc;
		tmp = tmp->next;
	}

	return NULL;
}

int countAttributeAppearances(Node<mainNode>* head, char* attributeName)
{
	int cnt = 0;

	Node<mainNode>* tmp = head;
	int headLen = head->getListLen();
	for (int i = 0; i < headLen; i++)
	{
		for (int j = 0; j < T; j++)
		{
			Node<atrVal>* tmp2 = tmp->data.sekcje[j].atrybuty;
			int tmp2Len = tmp2->getListLen();
			for (int k = 0; k < tmp2Len; k++)
			{
				if (compareCharTab(attributeName, tmp2->data.atrybut))
					cnt++;

				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}

	return cnt;
}

int countSelectorAppearances(Node<mainNode>* head, char* selectorName)
{
	int cnt = 0;

	Node<mainNode>* tmp = head;
	int headLen = head->getListLen();
	for (int i = 0; i < headLen; i++)
	{
		for (int j = 0; j < T; j++)
		{
			Node<char*>* tmp2 = tmp->data.sekcje[j].selektory;
			int tmp2Len = tmp2->getListLen();
			for (int k = 0; k < tmp2Len; k++)
			{
				if (compareCharTab(selectorName, tmp2->data))
					cnt++;

				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}

	return cnt;
}

char* findAttributeForSelector(Node<mainNode>* head, char* attributeName, char* selectorName)
{
	Node<mainNode>* tail = head->getLast();
	int headLen = head->getListLen();

	for (int i = 0; i < headLen; i++)
	{
		for (int j = T-1; j >= 0; j--)
		{
			Node<char*>* selectors = tail->data.sekcje[j].selektory;
			int selectorsLen = selectors->getListLen();

			for (int k = 0; k < selectorsLen; k++)
			{
				if (compareCharTab(selectorName, selectors->data))
				{
					Node<atrVal>* attributes = tail->data.sekcje[j].atrybuty;
					int attrLen = attributes->getListLen();

					for (int l = 0; l < attrLen; l++)
					{
						if (compareCharTab(attributeName, attributes->data.atrybut))
							return attributes->data.wartosc;

						attributes = attributes->next;
					}
				}

				selectors = selectors ->next;
			}
		}
		tail = tail->prev;
	}

	return NULL;
}

Node<mainNode>* deleteSection(Node<mainNode>* head, int num)
{
	if (head == NULL)
		return head;

	Node<mainNode>* tmp = head;
	int licznik = tmp->data.licznikZaj;
	while (licznik < num && tmp->next != NULL)
	{
		licznik += tmp->data.licznikZaj;
		tmp = tmp->next;
	}

	licznik -= tmp->data.licznikZaj;

	int index = 0;
	while (licznik != num)
	{
		if (tmp->data.sekcje[index].selektory != NULL)
			licznik++;

		index++;
	}
	index--;

	sekcja* sectionToDelete = &(tmp->data.sekcje[index]);

	Node<char*>* selectorsToDelete = sectionToDelete->selektory;

	int selectorsLen = selectorsToDelete->getListLen();

	for (int i = 0; i < selectorsLen; i++)
	{
		delete[] selectorsToDelete->data;

		selectorsToDelete = selectorsToDelete->removeFirst();
	}

	sectionToDelete->selektory = selectorsToDelete;	

	Node<atrVal>* attributesToDelete = sectionToDelete->atrybuty;
	int attributesLen = attributesToDelete->getListLen();

	for (int i = 0; i < attributesLen; i++)
	{
		delete[] attributesToDelete->data.atrybut;
		delete[] attributesToDelete->data.wartosc;
		
		attributesToDelete = attributesToDelete->removeFirst();
	}
	sectionToDelete->atrybuty = attributesToDelete;


	tmp->data.licznikZaj--;

	if (tmp->data.licznikZaj == 0)
	{
		delete[] tmp->data.sekcje;
		head = head->removeNode(tmp);
	}

	return head;
}

Node<mainNode>* deleteAttribute(Node<mainNode>* head, char* attrName, int sectionNum)
{
	if (sectionNum < 1 || sectionNum > numOfSections(head))
		return head;

	Node<atrVal>* tmp = findSectionNum(head, sectionNum).atrybuty;
	int tmpLen = tmp->getListLen();
	if (tmpLen == 1)
		return deleteSection(head, sectionNum);

	for (int i = 0; i < tmpLen; i++)
	{
		if (compareCharTab(attrName, tmp->data.atrybut))
		{
			delete[] tmp->data.atrybut;
			delete[] tmp->data.wartosc;
			tmp = tmp->removeNode(tmp);
			return head;
		}

		tmp = tmp->next;
	}

	return head;
}