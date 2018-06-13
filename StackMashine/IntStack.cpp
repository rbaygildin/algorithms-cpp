#include "IntStack.h"
#include <stdexcept>
using namespace std;

/*
 * ФИО: Ярных Роман Вячеславович
 * Группа: БПИ141
 * Подгруппа: 2
 * Дата: 25.01.2016
 * Проект: реализация стека целых чисел
 * Номер проекта: 12
 * Среда: Clion (Mac Os X)
 * Язык программирования: C++11
 * Компилятор: gcc (g++)
 */

/*
 * Конструктор стека целых чисел с указанием его размера (или емкостью)
 * параметры:
 * size_t sz - фиксированный размер стека (емкость стека)
 */
IntStack::IntStack(size_t sz) {
    _stack = new int[(_ssize = sz + 1)];
    _head = 0;
}

/*
 * Деструктор стека целых чисел
 */
IntStack::~IntStack() {
    delete[] _stack;
}

/*
 * Добавить на вершину стека новый элемент
 * параметры:
 * int el - добавляемый элемент
 * исключения:
 * logic_error - исключение, выбрасываемое в случае, если добавление нового элемента
 * не возможно из-за полной занятости стека
 */
void IntStack::push(int el) {
    if(_head == _ssize - 1)
        throw logic_error("You cant't push new element in stack 'cause the stack is full!");
    _stack[++_head] = el;
}

/*
 * Получить элемент с вершины, удалив из стека
 * возвращаемое значение:
 * int - элемент стека
 */
int IntStack::pop() {
    if(_head == 0)
        throw logic_error("Stack is empty!");
    return _stack[_head--];
}

/*
 * Получить элемент с вершины стека, не удаляя из самого стека
 * возвращаемое значение:
 * int - элемент стека
 */
int IntStack::top() {
    if(_head == 0)
        throw logic_error("Stack is empty!");
    return _stack[_head];
}

/*
 * Очистить стек
 */
void IntStack::clear() {
    _head = 0;
}
