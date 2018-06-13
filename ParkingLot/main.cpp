﻿/*
 * ФИО: Ярных Роман Вячеславович
 * Группа: БПИ141
 * Подгруппа: 2
 * Дата: 08.04.2016
 * Проект: реализация симулятора парковки автомобилей
 * Номер проекта: 20
 * Среда: Clion (Mac OS X)
 * Язык программирования: C++11
 * Компилятор: gcc (g++)
 */


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stack>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <queue>

#include "car.h"
using namespace std;


const int PARKING_SPOTS_PER_AISLE = 3;      ///< Determines a number of cars per an aisle
const int NUMBER_OF_AISLES = 5;             ///< Determines a number of aisls in the parking


/** \brief Defines an Aisle in some parking */
typedef std::stack<std::string> ParkAisle;

/** \brief Defines a parking containing some aisles */
typedef std::vector< ParkAisle > Parking;

/** \brief Defines a collection of cars most likely implemented as a vector of cars */
typedef std::vector<Car> Cars;



/** \brief Iterates through the vector of stacks, looking for the first stack that 
 *  does not contain three cars. If all five aisles (stacks) are full, output a message 
 *  indicating such; otherwise place the license plate into the first non-full stack.
 */
void handle_arrival(Cars& cars, Parking& parking_lot,
    const std::string& plate);


/** \brief Locates the departing vehicle from the \a cars vector using function \a find_car() and
 *  removes the departing car's license plate from the corresponding aisle.
 */
void handle_departure(Cars& cars, Parking& parking_lot, const std::string& plate);


/** \brief Returns a reference to the \a Car object stored in the vector \a cars 
 *  whose license plate equals the parameter \a plate.
 */
Car& find_car(Cars& cars, const std::string& plate);


//------------------------------------------------------------------------------


/** \brief Main entry point of the program
 *
 *  Should obtain at least 1 command line parameter, which is interpreted as the name of a 
 *  file with parking day's payload
 */
int main(int argc, char* argv[]) 
{
    try {
        if (argc < 2)       
        {                   
            std::cerr << "Usage:\n" << argv[0] << " data-file";
            return EXIT_FAILURE;
        }    

        std::ifstream inf(argv[1]);
        if (!inf) 
        {
            std::cerr << "Could not open " << argv[1];
            return EXIT_FAILURE;
        }

        Cars cars;
        Parking parking_lot(NUMBER_OF_AISLES);

        while (!inf.eof()) 
        {
        
            std::string action, plate;
            inf >> plate >> action;
        
            if (action == "arrives") 
            {
                handle_arrival(cars, parking_lot, plate);
            } 
            else if (action == "departs") 
            {
                handle_departure(cars, parking_lot, plate);            
            } else 
            {
                std::cerr << "Unknown action: " << action << std::endl;
            }
        
        }
        inf.close();    

        std::cout << "\nHere are all the cars that visited the lot today:\n";

        sort(cars.begin(), cars.end(), [](Car a, Car b){
            return a < b;
        });

        for_each(cars.begin(), cars.end(), [](Car a){
           cout << a.getPlate() << " moved " << a.getTimesMoved() << " times" << endl;
        });

        return EXIT_SUCCESS;        
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown exception caught!" << std::endl;
    }
    
    return EXIT_FAILURE;
}

//------------------------------------------------------------------------------

/** 
 *  This is essentially "parking" the car. For this
 *  arriving car, also add an entry of type \a Car to the vector \a cars. In this \a Car instance, 
 *  make sure to record properly the index of the aisle where this car is parked. 
 */
void handle_arrival(Cars& cars, Parking& parking_lot,
    const std::string& plate) 
{
    int aisleIndex = -1;
    auto aisleFound = find_if(parking_lot.begin(), parking_lot.end(), [&aisleIndex](ParkAisle parkAisle){
        aisleIndex++;
        if(parkAisle.size() < 3) {
            return true;
        }
        return false;
    });
    if(aisleFound != parking_lot.end()){
        parking_lot[aisleIndex].push(plate);
        Car car(plate, aisleIndex);
        cars.push_back(car);
        cout << plate + " arrives" << endl;
    }
    else{
        cout << plate << " cannot arrive 'cause parking lot is full" << endl;
    }
}

//------------------------------------------------------------------------------


/** 
 *  Another stack must be used to move, temporarily, any cars that may be in front of the
 *  departing car. Record the number of times a car is moved when accommodating the
 *  departure of another car. For the departing car, display the number of times it was moved
 *  while it was parked in the lot.
 */
void handle_departure(Cars& cars, Parking& parking_lot, const std::string& plate)
{
    Car car = find_car(cars, plate);
    ParkAisle parkAisle = parking_lot[car.getAisle()];
    queue<string> carsGentlemens;
    while(true){
        Car tempCar = find_car(cars, parkAisle.top());
        parkAisle.pop();
        if(tempCar == car){
            cout << plate + " departs" << endl;
            break;
        }
        else{
            int moved = tempCar.getTimesMoved();
            tempCar.setTimesMoved(++moved);
            cout << tempCar.getPlate() << " moved " << tempCar.getTimesMoved() << " times" << endl;
            carsGentlemens.push(tempCar.getPlate());
        }
    }
    while(!carsGentlemens.empty()){
        Car tempCar = find_car(cars, carsGentlemens.front());
        int moved = tempCar.getTimesMoved();
        tempCar.setTimesMoved(++moved);
        cout << tempCar.getPlate() << " moved " << tempCar.getTimesMoved() << " times" << endl;
        parkAisle.push(carsGentlemens.front());
        carsGentlemens.pop();
    }
}


//------------------------------------------------------------------------------


/** 
 *  Use the STL \a find() function to perform this task. To use the function correctly, you
 *  must supply it with three arguments. The first two arguments specify a range to search.
 *  The third argument is the value that the function attempts to find. This argument must be
 *  of type \a Car.
 *
 *  * http://www.cplusplus.com/reference/algorithm/find/
 */
Car& find_car(Cars& cars, const std::string& plate)
{
    auto foundCar = find_if(cars.begin(), cars.end(), [plate](Car car){
       return car.getPlate() == plate;
    });
    if(foundCar != cars.end())
        return *foundCar;
    else
        throw invalid_argument("Car " + plate + " not found!");
}
