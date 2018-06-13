//
// Created by egdeveloper on 14.12.15.
//

#ifndef KMP_KMPSOLVER_H
#define KMP_KMPSOLVER_H
#include <vector>
#include <string>

using namespace std;
typedef unsigned long ULONG;

class KMPSolver {
private:
    static vector<ULONG> borders, improved_borders;
    static vector<ULONG> comp_positions;
public:
    static vector<ULONG> findOccurences(string, string);
    static vector<ULONG> getBorders();
    static vector<ULONG> getImprovedBorders();
    static vector<ULONG> getCompPositions();
};


#endif //KMP_KMPSOLVER_H
