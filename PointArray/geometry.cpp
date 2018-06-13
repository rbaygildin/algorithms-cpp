/*
 * ФИО: Ярных Роман Вячеславович
 * Группа: БПИ141
 * Подгруппа: 2
 * Дата: 18.01.2016
 * Проект: реализация динамического массива
 * Номер проекта: 11
 * Среда: Clion (Mac Os X)
 * Язык программирования: C++11
 * Компилятор: gcc (g++)
 */

#include <string.h>
#include <stdexcept>
#include "geometry.h"

using namespace std;

/*
 * Инициализатор типа Point
 * int x: координата x
 * int y: координата y
 */
Point::Point(int x, int y)
{
    _x = x;
    _y = y;
}

/*
 * Получить координату x
 */
int Point::getX() const
{
    return _x;
}

/*
 * Получить координату y
 */
int Point::getY() const
{
    return _y;
}

/*
 * Установить координату x
 * const int new_x: новая координата x
 */
void Point::setX(const int new_x)
{
    _x = new_x;
}

/*
 * Установить координату y
 * const int new_x: новая координата y
 */
void Point::setY(const int new_y)
{
    _y = new_y;
}

/*
 * Инициализатор пустого динамического массива
 */
PointArray::PointArray()
{
    _storage = new Point[0];
    _size = 0;
}

/*
 * Создание динамического массива из существующего массива
 * const Point* points: исходный массив точек Point
 * int size: размер исходного массива
 */
PointArray::PointArray(const Point *const points, const int size)
{
    _storage = new Point[0];
    resize(size);

    //копируем элементы исходного массива во внутренний динамический массив
    for(int i = 0; i < _size; i++)
        _storage[i] = points[i];
}

/*
 * Создание копии объекта PointArray
 * const PointArray &pv: исходный объект PointArray
 */
PointArray::PointArray(const PointArray &pv):PointArray()
{
    //_storage = new Point[0];

    //изменим размер текущего динамического массива
    resize(pv.getSize());

    //копируем элементы исходного массива PointArray в новый динамический массива
    for(int i = 0; i < _size; i++)
    {
        Point* temp = (Point*)pv.get(i);
        _storage[i] = *temp;
    }
}

/*
 * Деструктор PointArray
 */
PointArray::~PointArray()
{
    //удалим динамический массив
    if(_storage != nullptr)
        delete[] _storage;
}

/*
 * Положить элемент в конец динамического массива
 * const Point &p: объект Point
 */
void PointArray::push_back(const Point &p) {

    //увеличим размер массива на единицу
    resize(_size + 1);
    //добавим элемент в конец массива
    _storage[_size - 1] = p;
}

/*
 * Вставить новое элемент на указанную позицию в динамическом массива
 * const int position: позиция вставки элемента
 * const Point &p: объект Point
 */
void PointArray::insert(const int position, const Point &p)
{

    if(position < 0 || position >= _size)
        throw range_error("Position should be in range [0; size - 1]!");
    resize(_size + 1);
    Point oldObject = _storage[position];
    _storage[position] = p;
    int i = position;
    while(++i < _size)
    {
        Point temp = _storage[i];
        _storage[i] = oldObject;
        oldObject = temp;
    }
}

/*
 * Удалить элемент из динамического массива
 * const int position: позиция удаляемого элемента
 */
void PointArray::remove(const int position)
{
    if(position < 0 || position >= _size)
        throw range_error("Position should be in range [0; size - 1]!");
    int i = position;
    do
    {
        _storage[i] = _storage[i + 1];
    }while(++i < _size - 1);
    resize(_size - 1);
}

/*
 * Получить длину динамического массива
 */
const int PointArray::getSize() const
{
    return _size;
}

/*
 * Очистить динамический массива
 */
void PointArray::clear()
{
    resize(0);
}

/*
 * Получить элемент с указанием его позиции
 * const int position: позиция элемента
 */
Point* PointArray::get(const int position)
{
    if(position < 0 || position >= _size)
        throw range_error("Position should be in range [0; size - 1]!");
    return &_storage[position];
}

/*
 * Получить элемент с указанием его позиции
 * const int position: позиция элемента
 */
const Point* PointArray::get(const int position) const
{
    if(position < 0 || position >= _size)
        throw range_error("Position should be in range [0; size - 1]!");
    return (const Point*)&_storage[position];
}

/*
 * Изменить длину динамического массива
 * const int n: новая длина динамического массива
 */
void PointArray::resize(int n) {
    //создаем временный массив
    if (n > 0) {
        Point *newArray = new Point[n];
        //копируем элементы текущего массива во временный
        memcpy(newArray, _storage, sizeof(Point) * n);
        //удаляем текущий
        delete[] _storage;
        //присваиваем переменной текущего массива указатель на новый массив
        _storage = newArray;
        //устанавливаем новый размер
        _size = n;
    }
    else {
        _size = 0;
        _storage = nullptr;
    }
}
