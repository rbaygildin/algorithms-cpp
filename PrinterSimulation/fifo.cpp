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

#include <fstream>
#include "fifo.h"

bool replaceSubstring(string&, string, string);

fifo::fifo(int seconds_per_page) : simulator(seconds_per_page){};

fifo::~fifo(){}

void fifo::simulate(string file) {
    loadworkload(file);
    ofstream simulation;
    replaceSubstring(file, ".run", ".out");
    simulation.open(file);
    simulation << "FIFO Simulation" << endl << endl;
    int counter = 0;
    int nextPrintTime = 0;
    size_t printedJobCount = workload.size();
    size_t jobCount = workload.size();
    while(printedJobCount > 0){
        if(!workload.empty()) {
            event printEvent = workload.front();
            printQueue.push(workload.front());
            simulation << "Arriving: " << printEvent.getjob().getnumpages()
            << " page" << (printEvent.getjob().getnumpages() > 1 ? "s" : "")
            << " from user " << printEvent.getjob().getuser()
            << " at " << printEvent.arrival_time() << " seconds" << endl;
            workload.pop();
        }
        if((counter >= nextPrintTime) && (printQueue.size() > 0)){
            event printEvent = printQueue.front();
            job printJob = printEvent.getjob();
            simulation << "Servicing: " << printEvent.getjob().getnumpages()
                          << " page" << (printEvent.getjob().getnumpages() > 1 ? "s" : "")
                          << " from user " << printEvent.getjob().getuser()
                          << " at " << counter << " seconds" << endl;
            nextPrintTime = counter + printJob.getnumpages() * seconds_per_page;
            printQueue.pop();
            printedJobCount--;
        }
        counter++;
    }
    simulation << "\nTotal jobs: " << jobCount << endl;

}

bool replaceSubstring(string &source, string sub, string replaceString){
    size_t startPos = source.find(sub);
    if(startPos == string::npos)
        return false;
    source.replace(startPos, sub.length(), replaceString);
    return true;
}