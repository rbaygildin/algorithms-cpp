/*
 * ФИО: Ярных Роман Вячеславович
 * Группа: БПИ141
 * Подгруппа: 2
 * Дата: 10.02.2016
 * Проект: реализация DNARepair
 * Номер проекта: 17
 * Среда: Clion (Mac Os X)
 * Язык программирования: C++11
 * Компилятор: gcc (g++)
 */

#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "DNARepairer.h"

using namespace std;

typedef LinkedList<DNAElement> DNA;
typedef Node<DNAElement> NodeDNA;

void DNARepairer::repairDNA()
{
	int n = DNAStorage.size();
	for(char id = 'a'; id != 'z'; id++){
		DNA currentDNA = DNAStorage[id - 'a'];
		for(int k = 0; k < n; k++){
			if(k == (id - 'a'))
				continue;
			NodeDNA *dnaElement = DNAStorage[k].getPreHead()->next;
			NodeDNA *prevDNAElement = DNAStorage[k].getPreHead();
			while(prevDNAElement != nullptr && prevDNAElement->next != nullptr){
				if(dnaElement->value.id == string(1, id))
					currentDNA.moveNodeAfter(currentDNA.getPreHead(), prevDNAElement);
				else{
					prevDNAElement = dnaElement;
					dnaElement = dnaElement->next;
				}
			}
		}
	}
}

void DNARepairer::printDNAStorage()
{
	Node<DNA>* dna = DNAStorage.getPreHead();
	while (dna->next != nullptr)
	{
		dna = dna->next;

		NodeDNA* dnaNode = dna->value.getPreHead();
		while (dnaNode->next != nullptr)
		{
			dnaNode = dnaNode->next;
			cout << dnaNode->value.id << "" << dnaNode->value.number << ":";
			cout << dnaNode->value.base << "  ";
		}
		cout << endl;
	}
}

void DNARepairer::readFile(string filename)
{
	int count;
	ifstream fin(filename);

	if (!fin)
		throw runtime_error("Can not open file!");

	string line;
	getline(fin,line);

	if(!line.size() || count_if(line.begin(), line.end(), static_cast<int(*)(int)>(std::isdigit)) != line.size())
		throw invalid_argument("First line must contain number of DNA!");

	count = atoi(line.c_str());
	int i = 0;

	Node<DNA>* dna =  DNAStorage.getPreHead();
	while (getline(fin,line))
	{
		i++;
		Node<DNA>* dnaNode = new Node<DNA>;

		istringstream istr(line);

		string strTmp;

		while (istr >> strTmp)
		{
			DNAElement tmpDNAElement;

			tmpDNAElement.readString(strTmp);

			dnaNode->value.addElementToEnd(tmpDNAElement);
		}
		dna->next = dnaNode;
		dna = dna->next;
	}
	if(i != count)
		throw invalid_argument("File contains not enough DNA!");
	fin.close();
}

LinkedList<LinkedList<DNAElement>> &DNARepairer::getDNAStorage(void) {
	return DNAStorage;
}
