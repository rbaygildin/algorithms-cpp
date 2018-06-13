/*
 * ФИО: Ярных Роман Вячеславович
 * Группа: БПИ141
 * Подгруппа: 2
 * Дата: 10.02.2016
 * Проект: реализация расширенной версии SafeArray
 * Номер проекта: 15
 * Среда: Clion (Mac Os X)
 * Язык программирования: C++11
 * Компилятор: gcc (g++)
 */

#ifndef ENHANCEDSAFEARRAY_ENHANCEDSAFEARRAY_H_H
#define ENHANCEDSAFEARRAY_ENHANCEDSAFEARRAY_H_H

#include <string.h>
#include "safearray.h"
using namespace std;

//EnhancedSafeArray declaration

/**
 * Extended version (subclass) of safe array with opportunity to
 * call copy constructor of current instance, get its size and compare with others
 */
template <class T>
class EnhancedSafeArray : public SafeArray<T>{
public:
    EnhancedSafeArray();
    EnhancedSafeArray(int n);
    EnhancedSafeArray(const EnhancedSafeArray& obj);
    size_t size() const;
    bool operator ==(const EnhancedSafeArray& another) const;
    EnhancedSafeArray& operator=(const EnhancedSafeArray& obj);

private:
    using SafeArray<T>::storage;
    using SafeArray<T>::count;
};
//end: EnhancedSafeArray declaration

//EnhancedSafeArray implementation
/**
 * Default constructor
 */
template <class T>
EnhancedSafeArray<T>::EnhancedSafeArray() : SafeArray<T>() { }

/**
 * Constructor with opportunity to set the size of array
 */
template <class T>
EnhancedSafeArray<T>::EnhancedSafeArray(int n) : SafeArray<T>(n) {}

/**
 * Deep copy constructor
 */
template <class T>
EnhancedSafeArray<T>::EnhancedSafeArray(const EnhancedSafeArray &obj) {
    count = obj.count;
    storage = new T[count];
    memcpy(storage, obj.storage, sizeof(T) * count);
}

/**
 * Size of array
 */
template <class T>
size_t EnhancedSafeArray<T>::size() const {
    return count;
}

/**
 * Compare current instance with another for equality of inner arrays sizes and their contents
 */
template <class T>
bool EnhancedSafeArray<T>::operator==(const EnhancedSafeArray<T> &obj) const {
    if(count != obj.count)
        return false;
    for(int i = 0; i < count; i++)
        if(storage[i] != obj.storage[i])
            return false;
    return true;
}

/**
 * Overloaded operator=
 */
template <class T>
EnhancedSafeArray<T>& EnhancedSafeArray<T>::operator=(const EnhancedSafeArray<T> &obj){
    if(this != &obj){
        if(count != 0)
            delete[] storage;
        count = obj.count;
        storage = new T[count];
        memcpy(storage, obj.storage, sizeof(T) * count);
    }
    return *this;
}
//end: EnhancedSafeArray implementation

#endif //ENHANCEDSAFEARRAY_ENHANCEDSAFEARRAY_H_H