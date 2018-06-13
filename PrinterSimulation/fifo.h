/*
 * ФИО: Ярных Роман Вячеславович
 * Группа: БПИ141
 * Подгруппа: 2
 * Дата: 01.03.2016
 * Проект: реализация симулятора принтера
 * Номер проекта: 19
 * Среда: Clion (Mac OS X)
 * Язык программирования: C++11
 * Компилятор: gcc (g++)
 */

#ifndef PRINTERSIMULATION_FIFO_H
#define PRINTERSIMULATION_FIFO_H


#include "simulator.h"

class fifo : public simulator{
private:
    queue<event> printQueue;
public:
    fifo(int seconds_per_page);
    void simulate(string file);
    virtual ~fifo();
};


#endif //PRINTERSIMULATION_FIFO_H
