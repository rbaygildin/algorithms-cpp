/*
 * ФИО: Ярных Роман Вячеславович
 * Группа: БПИ141
 * Подгруппа: 2
 * Дата: 10.02.2016
 * Проект: реализация стека с возможностью поиска минимума за O(1)
 * Номер проекта: 16
 * Среда: Clion (Mac Os X)
 * Язык программирования: C++11
 * Компилятор: gcc (g++)
 */

#include <stdexcept>
#include "NiceStack.h"
using namespace std;

template <class T>
NiceStack<T>::NiceStack(size_t capacity) {
    m_capacity = capacity + 1;
    iHead = 0;
}

template <class T>
size_t NiceStack<T>::size() const {
    return iHead;
}

template <class T>
NiceStack<T>::~NiceStack(void) {
    storage.clear();
}

template <class T>
void NiceStack<T>::push(T newelement) throw (out_of_range){
    if(iHead >= m_capacity)
        throw out_of_range("Stack is full!");
    if(iHead == 1){
        TypeElementStack current(newelement, newelement);
        storage.push_back(current);
    }
    else {
        TypeElementStack previous = storage.at(iHead);
        TypeElementStack current;
        current.first = newelement;
        if (previous.second > newelement) {
            current.second = newelement;
        }
        else {
            current.second = previous.second;
        }
        storage.push_back(current);
    }
}


template <class T>
T NiceStack<T>::pop(void) throw (out_of_range){
    if(iHead == 0)
        throw out_of_range("Stack is empty!");
    iHead--;
    T e = storage.back().first;
    storage.pop_back();
    return  e;
}


template <class T>
T NiceStack<T>::getMinimum(void) throw (out_of_range){
    if(iHead == 0)
        throw out_of_range("Stack is empty");
    return storage.at(iHead).second;
}