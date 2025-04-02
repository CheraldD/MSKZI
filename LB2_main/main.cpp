#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <string>
#include <random>
#include <map>
#include "sequence_analys.h"
using namespace std;
uint length = 0;
int main()
{
    SequenceAnalyzer analyzer;
    uint type;
    cout << "Выберите тип операции: 1 - генерация псп, 2 - маскирование файла, 3 - демаскирование файла" << endl;
    cin >> type;
    std::string input;
    std::string res;
    switch (type)
    {
    case 1:
        cout << "Ввведите длину желаемой последовательности: ";
        cin >> length;
        analyzer.generate_psp(length, true);
        analyzer.calculcate_static_char(analyzer.sequence,false,"");
        cout << "ПСП записана в файл PSP.txt" << endl;
        break;
    case 2:
        cout << "Ввведите имя маскируемого файла: ";
        cin >> input;
        cout << "Ввведите имя результирующего файла: ";
        cin >> res;
        cout<<endl;
        cout<<"Маскируемый файл"<<endl;
        analyzer.calculcate_static_char(analyzer.sequence,true,input);
        analyzer.mask_file(input, res);
        cout<<endl;
        cout<<"Маскированный файл"<<endl;
        analyzer.calculcate_static_char(analyzer.sequence,true,res);
        break;
    case 3:
        cout << "Ввведите имя демаскируемого файла: ";
        cin >> input;
        cout << "Ввведите имя результирующего файла: ";
        cin >> res;
        analyzer.mask_file(input, res);
        break;
    default:
        cout << "Ошибочная операция" << endl;
        exit(0);
        break;
    }
    return 0;
}
