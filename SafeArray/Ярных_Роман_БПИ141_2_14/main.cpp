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

#include <iostream>
#include <fstream>

using namespace std;

#include "course.h"
#include "safearray.h"

void initCourses(safearray<course>&);
void displayMenu(safearray<course>&);

const int NUM_COURSES = 10;
const int QUIT        = 99;

int main(int argc, char* argv[])
{
    //course courses[NUM_COURSES];
    safearray<course> courses(NUM_COURSES);

    try
    {
        initCourses(courses);
        int choice = 0;
        while (choice != QUIT)
        {
            displayMenu(courses);
            cout << "Enter number of course to see more information on\n";
            cin >> choice;
            cin.clear();    // Defence from non int
            cin.sync();
            cout << "\n";
            if (choice >= 1 && choice <= NUM_COURSES) {
                cout << courses[choice - 1] << "\n\n";
            }
        }
        return EXIT_SUCCESS;
    }
    catch (out_of_range exception)
    {
        cerr << "Courses number is invalid!" << endl;
        exit(EXIT_FAILURE);
    }
}

void displayMenu(safearray<course>& courses)
{

    for (int i = 1; i <= NUM_COURSES; i++) 
    {
        cout << i << ". " << courses[i - 1].name << "\n";
    } 
    cout << "99. Quit\n";
}

void initCourses(safearray<course>& courses)
{
    ifstream inf("courses.txt");
    if (! inf) 
    {
        cerr << "Could not open courses.txt" << endl;
        exit(EXIT_FAILURE);
    }
 
    for (int i = 0; i < NUM_COURSES; i++) 
    {
        course course_instance;
        courses[i] = course_instance;
        inf >> courses[i];
    } 
    inf.close();
}

