/*
 * ФИО: Ярных Роман Вячеславович
 * Группа: БПИ141
 * Подгруппа: 2
 * Дата: 01.02.2016
 * Проект: реализация безопасного массива
 * Номер проекта: 14
 * Среда: Clion (Mac Os X)
 * Язык программирования: C++11
 * Компилятор: gcc (g++)
 */


#ifndef SAFEARRAY_H
#define SAFEARRAY_H
#include <stdexcept>

using namespace std;

template <class T>
class safearray {

  private:
    T *_storage;
    int _capacity;
  
  public:
    safearray() : _storage(nullptr), _capacity(0) {} // default constructor
    safearray(int); // single param constructor
    ~safearray(void); // destructor
    T& operator[] (int) throw(out_of_range);
};

template <class T>
safearray<T>::safearray(int i) {
    _capacity = i;
    _storage = new T[_capacity];
}

template <class T>
safearray<T>::~safearray() {
    delete [] _storage;
}

template <class T>
T& safearray<T>::operator[](int i) throw(out_of_range){
    if(i < 0)
        throw out_of_range("Index must be non negative!");
    if(i >= _capacity)
        throw out_of_range("Index is out of available array range!");
    return _storage[i];
}
#endif

