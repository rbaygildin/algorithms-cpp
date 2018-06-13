/*
 * ФИО: Ярных Роман Вячеславович
 * Группа: БПИ141
 * Подгруппа: 2
 * Дата: 12.04.2016
 * Проект: реализация поиска зараженных клеток-соседей
 * Номер проекта: 21
 * Среда: Clion (Mac OS X)
 * Язык программирования: C++11
 * Компилятор: gcc (g++)
 */

#include <iostream>
#include <fstream>
#include <iomanip>      // std::setw() if needed
#include <stdexcept>

#include "grid.h"

// According to new restrictions of C++ standards, an explicit definition of static consts is a need
const bool grid::NOT_INFECTED = false;      // = false;
const bool grid::INFECTED = true;
const bool grid::NEIGHBORHOOD = true;// = true;



// Students may need to alter the constructor
grid::grid(const std::string& fileName)
{
  
    std::ifstream grid_file;

    try
    {
        grid_file.open(fileName.c_str());

        // check if it's all ok
        if (!grid_file.good())
            throw std::runtime_error("File cannot be open");

        // opened correctly
        grid_file >> _rows;
        grid_file >> _cols;

        _area = new std::vector<bool>(_rows * _cols, grid::NOT_INFECTED);
        _nbhoods = new bool*[_rows];
        for(int i = 0; i < _rows; i++)
        {
            _nbhoods[i] = new bool[_cols];
        }

        int blob_row;
        int blob_col;

        while (!grid_file.eof() && grid_file.good())
        {
            grid_file >> blob_row;
            grid_file >> blob_col;

            _area->operator[](indexof(blob_row, blob_col)) = INFECTED;
        }
    }
    catch (...)
    {
        // always tries to properly close the file!
        grid_file.close();
        throw;              // dispatch further
    }
  
    grid_file.close();
}

// Students may need to alter the destructor
grid::~grid () 
{
  delete _area;
  for(int i = 0; i < _rows; i++)
  {
      delete[] _nbhoods[i];
  }
  delete[] _nbhoods;
}


// Students will need to alter this function to display the
// plus signs (+) next to the cells that belong to
// a counted colony.
std::ostream& operator << (std::ostream& stream, const grid& ob) 
{

    for (int row = 0; row < ob._rows; ++row) 
    {     
        for (int col=0; col < ob._cols; col++) 
        {
            stream << ob._area->operator[](ob.indexof(row, col));
            if(ob._nbhoods[row][col] == grid::NEIGHBORHOOD)
            {
                stream << "+";
                stream << "  ";
            }
            else
                stream << "   ";
        }

        stream << std::endl;
    }
    stream << std::endl;
    
    return stream;
}

// Students have to replace the return statement in this function with their
// recursive implementation of this method */
int grid::count (int row, int col)
{
    if (!checkIndex(row, col))
        throw std::invalid_argument("Index out of range");
    int count_ = 0;
    if((_area->operator[](indexof(row, col))) == INFECTED && (_nbhoods[row][col] != grid::NEIGHBORHOOD))
    {
        count_ = 1;
        _nbhoods[row][col] = grid::NEIGHBORHOOD;
        //left
        if(col > 0)
        {
            count_ += count(row, col - 1);
        }
        //up
        if(row > 0)
        {
            count_ += count(row - 1, col);
        }
        //right
        if(col < (_cols - 1))
        {
            count_ += count(row, col + 1);
        }
        //down
        if(row < (_rows - 1))
        {
            count_ += count(row + 1, col);
        }
        //diagonal left-up
        if((row > 0) && (col > 0))
        {
            count_ += count(row - 1, col - 1);
        }
        //diagonal left-down
        if((row < (_rows - 1)) && (col > 0))
        {
            count_ += count(row + 1, col - 1);
        }
        //diagonal right-up
        if((row > 0) && (col < (_cols - 1)))
        {
            count_ += count(row - 1, col + 1);
        }
        //diagonal right-down
        if((row < (_rows - 1)) && (col < (_cols - 1)))
        {
            count_ += count(row + 1, col + 1);
        }
    }
    return count_;
}


// Students may need to alter this function
int grid::getCount (int row, int col)
{
    int count_ = count(row,col);
    return count_;
}



// Students do not need to alter function indexof.
int grid::indexof(int row, int col) const
{
    if (!checkIndex(row, col))
        throw std::invalid_argument("Index out of range");

    return row *_cols + col;
}

// Students do not need to alter function infected.
bool grid::infected(int row, int col) const 
{
    return (_area->operator[](indexof(row, col)) == INFECTED);
}


// Students do not need to alter this function w/o any special reasons.
bool grid::checkIndex(int row, int col) const
{
    return !(row >= _rows || row < 0 || col >= _cols || col < 0);
}
