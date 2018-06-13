//ФИО: Ярных Роман Вячеславович
//Группа: БПИ141
//Подгруппа: 2
//Дата: 15.12.2015
//Проект: реализация алгоритма Бойера-Мура
//Номер проекта: 10
//Среда: Clion (Mac Os X)
//Язык программирования: C++11
//Компилятор: gcc (g++)

#include <iostream>
#include <vector>

using namespace std;

int* evaluateShift(char f, char e, string s);
vector<int> findOccurrences(string text, string pattern, vector<int>& comp_pos);

int main() {
    string text, pattern;
    cout << "Input string text" << endl;
    cin >> text;
    cout << "Input string pattern" << endl;
    cin >> pattern;
    vector<int> comp_pos;
    if(text.size() < pattern.size()){
        cout << "Text length should be not smaller than pattern length" << endl;
        return 0;
    }
    vector<int> occurences = findOccurrences(text, pattern, comp_pos);
    cout << "Pattern occurences in text at the positions:" << endl;
    for(int i = 0; i < occurences.size(); i++)
        cout << occurences[i] << " " << endl;
    cout << " " << endl;
    cout << "Positions at which strings compare to each other:" << endl;
    for_each(comp_pos.begin(), comp_pos.end(), [](int pos){
        cout << pos << " ";
    });
    return 0;
}

//Поиск позиций вхождения подстроки в исходной строке
//** параметры **
//string text - исходная строка
//string pattern - строка, вхождения которой нужно найти в исходной строке
//** возвращаемое значение **
//vector<int> - вектор позиций вхождения
vector<int> findOccurrences(string text, string pattern, vector<int>& comp_pos){
    comp_pos.clear();
    int text_len = (int)text.size();
    int pattern_len = (int)pattern.size();
    vector<int> occurrences;
    int* shifts = evaluateShift('a', 'z', pattern);
    int cur = 0;
    while(cur <= text_len - pattern_len){
        //bool found = true;
        int pcur = pattern_len - 1;
        int k = cur;
        //while(pcur >= 0 && found){
        while(pcur >= 0 && text[k] == pattern[pcur])
            comp_pos.insert(comp_pos.begin(), k), pcur--, k--;
        if(pcur < 0)
            occurrences.push_back(k), cur++;
        else
            cur = cur + ((pcur - shifts[text[k] - 'a']) > 1 ? pcur - shifts[text[k] - 'a'] : 1);
        /*
            comp_pos.insert(comp_pos.begin(), k);
            if(text[k] != pattern[pcur]){
                found = false;
                cur = cur + shifts[(int)text[pcur]] - 1;
            }
            k--;
            pcur--;
            */
        //}

        /*
        if(found) {
            occurrences.push_back(k + 1);
        }
         */
        //if(k < text_len - pattern_len)
            //occurrences.push_back(k + 1);
    }
    reverse(comp_pos.begin(), comp_pos.end());
    delete[] shifts;
    return occurrences;
}

//Вычисление смещений символов алфавита в исходной строке
//** параметры **
//char f - начальный символ алфавита
//char e - конечный символ алфавита
//string s - исходная строка
//** возвращаемое значение **
//int* - массив смещений
int* evaluateShift(char f, char e, string s){
    int m = (int)(e - f) + 1;
    int* shifts = new int[m];
    int len = (int)s.size();
    for(int i = 0; i < m; i++){
        shifts[i] = len;
    }
    for(int i = 0; i < len; i++){
        shifts[(int)(s[i] - f)] = i;
    }
    return shifts;
}