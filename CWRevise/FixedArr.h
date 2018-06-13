// задание 2 - 29.03.2016

#ifndef HSE_FIXEDARR_H
#define HSE_FIXEDARR_H
#include<utility>
#include<ostream>
#include<iostream>
#include<stdexcept>
// ... другие include директивы ...


// рассматривается упрощенный шаблон класса FixedArray< >,
// основанный на использовании массива, размер которого
// (значение N) не меняется в процессе работы
template<typename T, std::size_t N>
class FixedArr
{
    public:
      // конструктор по умолчанию
      FixedArr( )
      {
          if(N <= 0){
              throw std::out_of_range("Non positive size!");
          }
         std::cout << "Ctor\n";
          fArr= new T[aSize = N];
      }

      // конструктор копирования
      FixedArr(const FixedArr& right): FixedArr( )
      {
         std::cout << "CCtor\n";
         for (size_t i=0; i < aSize; ++i)
            fArr[i] = right.fArr[i];
      }

      // конструктор перемещения
      FixedArr(FixedArr&& right): fArr(nullptr)
      {
          std::cout << "MCtor\n";
      	 if(this != &right){
          fArr = right.fArr;
          aSize = right.aSize;
          right.fArr = nullptr;
          right.aSize = 0;
         }
      }

      // деструктор
      virtual ~FixedArr( )
      {
         std::cout << "Dtor\n";
         aSize = 0;
         delete[ ] fArr;
      }

      FixedArr& operator=(FixedArr&& right)
      {
         if(this != &right){
             fArr = right.fArr;
             aSize = right.aSize;
             right.fArr = nullptr;
             right.aSize = 0;
         }
         return *this;
      }

      FixedArr& operator=(const FixedArr &right)
      {
      	 if (&right != this )
         {
            FixedArr<T,N> tmp(right);
            this -> swap(tmp);
         }
         return *this;
      }

      T& operator[ ](int index)
      {
         if(index < 0 || index >= aSize)
             throw std::out_of_range("Invalid index!");
          return fArr[index];
      }

      void fill(const T& value)
      {
         for(size_t i = 0; i < aSize; i++){
             fArr[i] = value;
         }
      }

      void swap(FixedArr& other)
      {
         if(other.aSize != aSize)
             throw std::out_of_range("Other has no same size as mine!");
          for(int i = 0; i < aSize; i++){
              std::swap(fArr[i], other.fArr[i]);
          }

      }

      void reverse( )
      {
         std::size_t iterations = aSize/2;
         for(std::size_t i = 0; i < iterations; ++i)
            std::swap(fArr[i], fArr[aSize-i-1]);
      }

      T& front( )
      {
          return fArr[0];
      }
      T& back( )
      {
         return fArr[aSize - 1];
      }

      typedef T* arr_iterator;
      arr_iterator begin( ) const
      {
      	 return fArr;
      }
      arr_iterator end( ) const
      {
      	 return fArr+N;
      }

        size_t size(){
            return aSize;
        }

      template<typename T1, std::size_t N1>
      friend std::ostream& operator<<(std::ostream& out, const FixedArr<T1,N1>& obj);

    private:
      std::size_t aSize;    // хранится значение N
      T* fArr;
};

template<typename T1, std::size_t N1>
std::ostream& operator<<(std::ostream& out, const FixedArr<T1,N1>& obj)
{
    // вывод по 10 элементов в одной строке (переменная num).
    int num = 0;
    for(auto& i : obj)
    {
       out << i << " ";
       ++num;
       if(num/11)
       {
          std::cout << std::endl;
	  num = 0;
       }
    }
    std::cout << std::endl;
    return out;
}

#endif

