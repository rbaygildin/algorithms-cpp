//
// Created by egdeveloper on 14.12.15.
//

#include "KMPSolver.h"

vector<ULONG> KMPSolver::borders;
vector<ULONG> KMPSolver::improved_borders;
vector<ULONG> KMPSolver::comp_positions;

vector<ULONG> _getImprovedBorders(string s, vector<ULONG> br);
vector<ULONG> _getBorders(string s);

vector<ULONG > KMPSolver::findOccurences(string text, string pattern) {
    vector<ULONG> occurences;
    borders = _getBorders(pattern);
    improved_borders = _getImprovedBorders(pattern, borders);
    unsigned long int len = text.size();
    unsigned long int pattern_len = pattern.size();
    for(unsigned long i = 0, q = 0; i < len; i++){
        while(q > 0 && pattern[q] != text[i])
            q = borders[q - 1];
        if(pattern[q] == text[i])
            q++;
        if(q == pattern_len)
            occurences.push_back(i - pattern_len + 1);
    }
    return occurences;
}

vector<ULONG> _getBorders(string s) {
    unsigned long len = s.size();
    vector<ULONG> p_table(len);

    p_table[0] = 0;

    for(unsigned long i = 1; i < len; i++){
        ULONG k = p_table[i - 1];
        while((k > 0) && (s[i] != s[k] || i == len || k == len))
            k = p_table[k - 1];
        if(s[i] == s[k] && i != len && k != len)
            k++;
        p_table[i] = k;
    }
    return p_table;
}

vector<ULONG> _getImprovedBorders(string s, vector<ULONG> br) {
    unsigned long len = br.size();
    vector<ULONG> brs(len);
    brs[0] = 0;
    s = s + "#";
    for(unsigned long i = 1; i < len; i++){
        if(s[br[i] - 1] != s[i + 1])
            brs[i] = br[i];
        else
            brs[i] = brs[br[i] - 1];
    }
    return brs;
}

vector<ULONG> KMPSolver::getBorders() {
    return borders;
}

vector<ULONG> KMPSolver::getImprovedBorders() {
    return improved_borders;
}

vector<ULONG> KMPSolver::getCompPositions() {
    return comp_positions;
}

