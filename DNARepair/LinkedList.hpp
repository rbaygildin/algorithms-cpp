/*
 * ФИО: Ярных Роман Вячеславович
 * Группа: БПИ141
 * Подгруппа: 2
 * Дата: 10.02.2016
 * Проект: реализация LinkedList
 * Номер проекта: 17
 * Среда: Clion (Mac Os X)
 * Язык программирования: C++11
 * Компилятор: gcc (g++)
 */

#include "LinkedList.h"
#include <stdexcept>

template <class T>
LinkedList<T>::LinkedList() 
{
	pPreHead = new Node<T>;
	pPreHead->next = nullptr;
}

template <class T> 
LinkedList<T>::~LinkedList()
{
	Node<T> *current = pPreHead;
	while(current != nullptr){
		Node<T> *temp = current->next;
		delete current;
		current = temp;
	}
}

template <class T>
Node<T> *LinkedList<T>::getPreHead(void) {
	return pPreHead;
}

template <class T>
T &LinkedList<T>::operator[](int i) {
	if(i < 0)
		throw out_of_range("Index can not be negative!");
	Node<T> *temp = pPreHead->next;
	int it = -1;
	while(++it != i)
		temp = temp->next;
	return temp->value;
}

template <class T>
int LinkedList<T>::size() {
	Node<T> *current = pPreHead->next;
	int size_ = 0;
	while(current != nullptr) {
		size_++;
		current = current->next;
	}
	return size_;
}

template <class T>
void LinkedList<T>::addElementToEnd(T &value) {
	Node<T> *end = pPreHead;
	while(end->next != nullptr)
		end = end->next;
	Node<T> *newNode = new Node<T>;
	newNode->value = value;
	newNode->next = nullptr;
	end->next = newNode;
}

template <class T>
void LinkedList<T>::deleteNodes(Node<T> *pNodeBefore, Node<T> *pNodeLast) {
	if(pNodeBefore == nullptr || pNodeBefore->next == nullptr || pNodeLast == nullptr)
		throw invalid_argument("Arguments can not equal null!");
	Node<T> *current = pNodeBefore->next;
	while(current != pNodeLast){
		Node<T> *temp = current->next;
		delete current;
		current = temp;
	}
	delete current;
}
template <class T>
void LinkedList<T>::deleteNextNode(Node<T> *pNodeBefore) {
	if(pNodeBefore == nullptr || pNodeBefore->next == nullptr)
		throw invalid_argument("Argument can not equal null!");
	delete pNodeBefore->next;
}

template <class T>
void LinkedList<T>::addNodesToEnd(Node<T> *pNodeBefore, Node<T> *pNodeLast) {
	if(pNodeBefore == nullptr || pNodeBefore->next == nullptr || pNodeLast == nullptr)
		throw invalid_argument("Arguments can not equal null!");
	Node<T> *end = pPreHead;
	while(end->next != nullptr)
		end = end->next;
	Node<T> *current = pNodeBefore->next;
	end->next = current;
	pNodeBefore->next = pNodeLast->next;
	while(current != pNodeLast){
		current = current->next;
	}
	current->next = nullptr;
}

template <class T>
void LinkedList<T>::addNodeToEnd(Node<T> *pNodeBefore) {
	if(pNodeBefore == nullptr || pNodeBefore->next == nullptr)
		throw invalid_argument("Argument can not equal null!");
	Node<T> *end = pPreHead;
	while(end->next != nullptr)
		end = end->next;
	end->next = pNodeBefore->next;
	pNodeBefore->next = end->next->next;
	end->next->next = nullptr;
}

template <class T>
void LinkedList<T>::moveNodesAfter(Node<T> *pNode, Node<T> *pNodeBefore, Node<T> *pNodeLast) {
	if(pNode == nullptr || pNodeBefore == nullptr || pNodeBefore->next == nullptr || pNodeLast == nullptr)
		throw invalid_argument("Arguments can not equal null!");
	Node<T> *current = pNodeBefore->next;
	Node<T> *afterNode = pNode->next;
	pNode->next = current;
	pNodeBefore->next = pNodeLast->next;
	while(current != pNodeLast){
		current = current->next;
	}
	current->next = afterNode;
}

template <class T>
void LinkedList<T>::moveNodeAfter(Node<T> *pNode, Node<T> *pNodeBefore) {
	if(pNode == nullptr || pNodeBefore == nullptr || pNodeBefore->next == nullptr)
		throw invalid_argument("Arguments can not equal null!");
	Node<T> *nextNode = pNodeBefore->next;
	pNodeBefore->next = nextNode->next;
	nextNode->next = pNode->next;
	pNode->next = nextNode;
}




