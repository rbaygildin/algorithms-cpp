/*
 * ФИО: Ярных Роман Вячеславович
 * Группа: БПИ141
 * Подгруппа: 2
 * Дата: 10.02.2016
 * Проект: реализация DNAElement
 * Номер проекта: 17
 * Среда: Clion (Mac Os X)
 * Язык программирования: C++11
 * Компилятор: gcc (g++)
 */

#include "DNAElement.h"
using namespace std;

void DNAElement::readString(string description) {
    const char *str = description.c_str();
    while(!isalnum(*str)) str++;
    const char* end = str + strlen(str) - 1;
    string descNew(str, end + 1);
    if(descNew.size() != 4
       || !isalpha(descNew[0])
       || !isdigit(descNew[1])
       || descNew[2] != ':'
       || descNew[3] != 'A'
       && descNew[3] != 'C'
       && descNew[3] != 'T'
       && descNew[3] != 'G')
        throw invalid_argument("Argument is not DNA element!");
    id = string(1, descNew.at(0));
    number = descNew.at(1) - '0';
    base = string(1, descNew.at(3));
}
