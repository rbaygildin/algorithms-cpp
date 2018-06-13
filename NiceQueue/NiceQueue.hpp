/*
 * ФИО: Ярных Роман Вячеславович
 * Группа: БПИ141
 * Подгруппа: 2
 * Дата: 10.02.2016
 * Проект: реализация очереди с возможностью поиска минимума за O(1)
 * Номер проекта: 16
 * Среда: Clion (Mac Os X)
 * Язык программирования: C++11
 * Компилятор: gcc (g++)
 */

#include "NiceQueue.h"
using namespace std;

template <class T>
NiceQueue<T>::NiceQueue(size_t capacity) :
        m_capacity(capacity), inStack(capacity), outStack(capacity){}

template <class T>
size_t NiceQueue<T>::size(void) const
{
    return outStack.size();
}

template <class T>
void NiceQueue<T>::enq(T newelement) throw (out_of_range)
{
    inStack.push(newelement);
}

template <class T>
T NiceQueue<T>::deq(void) throw (out_of_range)
{
    if(outStack.size() == 0)
        while(inStack.size() > 0)
            outStack.push(inStack.pop());
    return outStack.pop();
}

template <class T>
T NiceQueue<T>::getMinimum(void)
{
    if((inStack.size() == 0) || (outStack.size() == 0))
        return inStack.size() != 0 ? inStack.getMinimum() : outStack.getMinimum();
    else
        return min(inStack.getMinimum(), outStack.getMinimum());
}

template <class T>
NiceQueue<T>::~NiceQueue()
{
    inStack.~NiceStack();
    outStack.~NiceStack();
}
