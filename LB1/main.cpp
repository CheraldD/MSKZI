#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <random>
using namespace std;
uint generate_psp(const uint length, bool flag) {
    ofstream oFile("PSP.txt",ios::out);
    uint rlz1 = 0b1000011111010001011;
    const uint shift_rlz1 = 0x01 << (19 - 12 - 1);
    bitset<118> initial_rlz2(string("1111111001110010011000011001010100010010000101111111110101001010000000110001101111111011111011110010010000101111001101"));
    const uint shift_rlz2 = 85 - 1;
    uint last_bit_idx = 118 - 1;
    uint tap_bit_idx = shift_rlz2;
    uint res = 0;
    for (int i = 0; i < length; i++) {
        unsigned int bit1_rlz1 = (rlz1 & 0x01) ^ ((rlz1 & shift_rlz1) >> (19 - 12 - 1));
        rlz1 = (rlz1 >> 1) | (bit1_rlz1 << (19 - 1));
        uint bit1_rlz2 = initial_rlz2[last_bit_idx] ^ initial_rlz2[tap_bit_idx];
        initial_rlz2 >>= 1;
        initial_rlz2.set(117, bit1_rlz2);
        if (flag){
            oFile << bitset<1>(bit1_rlz1 ^ bit1_rlz2);
        }
        res = (res << 1) | (bit1_rlz1 ^ bit1_rlz2);
    }
    return res;
}
void mask_file(string inputFile,string outputFile){
    ifstream iFile(inputFile,ios::binary);
    ofstream oFile(outputFile, ios::binary);
    uint8_t byte;
    uint8_t psp = static_cast<uint8_t>(generate_psp(8,0));
    while (iFile.read(reinterpret_cast<char*>(&byte), sizeof(byte)) || iFile.gcount()) {
        uint8_t res = byte^psp;
        oFile.write(reinterpret_cast<char*>(&res), sizeof(res));
    }
    iFile.close();
    oFile.close();
}
/*void demask_file(string inputFile,string outputFile){
    ifstream iFile(inputFile,ios::binary);
    ofstream oFile(outputFile);
    uint8_t byte;
    uint8_t psp = static_cast<uint8_t>(generate_psp(8));
    while (iFile.read(reinterpret_cast<char*>(&byte), sizeof(byte)) || iFile.gcount()) {
        uint8_t res = byte^psp;
        oFile.write(reinterpret_cast<char*>(&res), sizeof(res));
    }
    iFile.close();
    oFile.close();
}*/
int main() {
    uint length;
    uint type;
    cout << "Выберите тип операции: 1 - генерация псп, 2 - маскирование файла, 3 - демаскирование файла"<<endl;
    cin >> type;
    std::string input;
    std::string res;
    switch(type){
        case 1:
            cout << "Ввведите длину желаемой последовательности: ";
            cin>>length;
            generate_psp(length,true);
            cout<<"ПСП записана в файл PSP.txt"<<endl;
            break;
        case 2:
            cout << "Ввведите имя маскируемого файла: ";
            cin>>input;
            cout << "Ввведите имя результирующего файла: ";
            cin>>res;
            mask_file(input,res);
            break;
        case 3:
            cout << "Ввведите имя демаскируемого файла: ";
            cin>>input;
            cout << "Ввведите имя результирующего файла: ";
            cin>>res;
            mask_file(input,res);
            break;
        default:
            cout << "Ошибочная операция"<<endl;
            exit(0);
            break;

    }
    return 0;
}
