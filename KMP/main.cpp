//ФИО: Ярных Роман Вячеславович
//Группа: БПИ141
//Подгруппа: 2
//Дата: 15.12.2015
//Проект: реализация алгоритма Кнута-Морриса-Пратта
//Номер проекта: 9
//Среда: Clion (Mac Os X)
//Язык программирования: C++11
//Компилятор: gcc (g++)

#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long ULONG;

void getImprovedBorders(string, vector<ULONG>, vector<ULONG>&);
void getBorders(string, vector<ULONG>&);
vector<ULONG> findOccurences(string, string, vector<ULONG>&, vector<ULONG>&, vector<ULONG>&);

int main() {
    string text, pattern;
    cout << "Input string text" << endl;
    cin >> text;
    cout << "Input string pattern" << endl;
    cin >> pattern;
    vector<ULONG> br, brs, comp_pos;
    vector<ULONG> occurences = findOccurences(text, pattern, br, brs, comp_pos);
    cout << "Pattern occurences in text at the positions:" << endl;
    for_each(occurences.begin(), occurences.end(), [](ULONG pos){
        cout << pos << " ";
    });
    cout << " " << endl;
    cout << "Pattern borders" << endl;
    for(ULONG i = 0; i < br.size(); i++)
        cout << br[i] << " ";
    cout << " " << endl;
    return 0;
}

//Поиск позиций вхождений строки pattern в строку text
//** параметры **
//string text - исходная строка
//string pattern - подстрока
//vector<ULONG>& br - вектор блоков подстроки
//vector<ULONG>& brs - вектор улучшенных блоков подстроки
//vector<ULONG>& comp_pos - вектор позиций сравнений строки и подстроки
//** возвращаемое значение **
//vector<ULONG> - вектор позиций вхождений
vector<ULONG > findOccurences(string text, string pattern, vector<ULONG>& br, vector<ULONG>& brs, vector<ULONG>& comp_pos) {
    vector<ULONG> occurences;
    getBorders(pattern, br);
    getImprovedBorders(pattern, br, brs);
    unsigned long int len = text.size();
    unsigned long int pattern_len = pattern.size();
    for(unsigned long i = 0, q = 0; i < len; i++){
        while(q > 0 && pattern[q] != text[i])
            q = br[q - 1];
        if(pattern[q] == text[i])
            q++;
        if(q == pattern_len)
            occurences.push_back(i - pattern_len + 1);
    }
    return occurences;
}

//Поиск блоков в строке
//** параметры **
//string s - исходная строка
//vector<ULONG>& br - вектор блоков строки
void getBorders(string s, vector<ULONG>& br) {
    unsigned long len = s.size();
    br.clear();
    br.resize(len);
    br[0] = 0;
    for(unsigned long i = 1; i < len; i++){
        ULONG k = br[i - 1];
        while((k > 0) && (s[i] != s[k] || i == len || k == len))
            k = br[k - 1];
        if(s[i] == s[k] && i != len && k != len)
            k++;
        br[i] = k;
    }
}

//Поиск улучшенных блоков в строке
//** параметры **
//string s - исходная строка
//vector<ULONG> br - вектор блоков строки
//vector<ULONG>& br - вектор улучшенных блоков строки
void getImprovedBorders(string s, vector<ULONG> br, vector<ULONG>& brs) {
    unsigned long len = br.size();
    brs.clear();
    brs.resize(len);
    brs[0] = 0;
    s = s + "#";
    for(unsigned long i = 1; i < len; i++){
        if(s[br[i] - 1] != s[i + 1])
            brs[i] = br[i];
        else
            brs[i] = brs[br[i] - 1];
    }
}