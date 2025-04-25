#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <random>
#include <iomanip>
using namespace std;
// 2, A, 5, B, 9, E, 8, D, C, 4, 6, 7, 0, 3, F, 1
uint8_t S[16] = {0x02, 0x0A, 0x05, 0x0B, 0x09, 0x0E, 0x08, 0x0D,
                 0x0C, 0x04, 0x06, 0x07, 0x00, 0x03, 0x0F, 0x01};
uint8_t S_star[256] = {};
uint8_t S_combined[256] = {};
uint64_t subsitute(uint64_t a, uint8_t vec[])
{
    uint64_t inp = a;
    uint8_t temp = 0;
    uint64_t res = 0;
    for (int i = 0; i < 16; i++)
    {
        temp = vec[inp & 0b1111];
        res |= (uint64_t)temp << (4 * i);
        inp >>= 4;
    }
    return res;
}
uint8_t rotate(uint8_t vec, int p)
{
    return ((vec >> p) | (vec << (8 - p)));
}


uint8_t combination(uint8_t vec){
    uint8_t x1=(vec&0b11110000)>>4;
    uint8_t x2=vec&0b1111;
    x1=S[x1];
    x2=S[x2];
    uint8_t x=(x1<<4)|x2;
    return rotate(x,5);
}
void print_tables()
{
    cout << "Таблица S (4-битная):" << endl;
    for (int i = 0; i < 16; ++i)
    {
        cout << hex << uppercase << setw(2) << setfill('0') << i << ": "
             << setw(2) << (int)(S[i]) << endl;
    }

    cout << "\nТаблица S_star (8-битная подстановка):" << endl;
    for (int i = 0; i < 256; ++i)
    {
        if (i % 16 == 0)
            cout << endl
                 << hex << uppercase << setw(2) << setfill('0') << i << ": ";
        cout << setw(2) << (int)(uint8_t)S_star[i] << " ";
    }

    cout << "\n\nТаблица S_combined (S_star после сдвига):" << endl;
    for (int i = 0; i < 256; ++i)
    {
        if (i % 16 == 0)
            cout << endl
                 << hex << uppercase << setw(2) << setfill('0') << i << ": ";
        cout << setw(2) << (int)(uint8_t)S_combined[i] << " ";
    }

    cout << endl;
}
uint64_t cycle_rotate(uint64_t a)
{
    uint64_t inp = a;
    uint8_t temp = 0;
    uint64_t res = 0;
    for (int i = 0; i < 8; i++)
    {
        temp = rotate(inp & 0xFF, 5);
        res |= (uint64_t)temp << (8 * i);
        inp >>= 8;
    }
    return res;
}
void init_tables()
{
    for (uint x1 = 0; x1 < 16; ++x1)
    {
        for (uint x2 = 0; x2 < 16; ++x2)
        {
            S_star[(x1 << 4) | x2] = (S[x1] << 4) | S[x2];
        }
    }
    for (uint i = 0; i < 256; ++i)
    {
        S_combined[i] = rotate(S_star[i], 5);
    }
}
uint64_t subsitute_8bit(uint64_t a)
{
    uint64_t inp = a;
    uint64_t res = 0;
    uint8_t temp = 0;
    for (int i = 0; i < 8; i++)
    {
        temp = S_star[inp & 0xFF];
        res |= (uint64_t)temp << (8 * i);
        inp >>= 8;
    }
    return res;
}
void change_file_S(string inputFile, string outputFile)
{
    ifstream iFile(inputFile, ios::binary);
    ofstream oFile(outputFile, ios::binary);
    uint8_t word;
    while (iFile.read(reinterpret_cast<char *>(&word), sizeof(word)))
    {
        uint8_t result = combination(word);
        oFile.write(reinterpret_cast<const char *>(&result), sizeof(result));
    }
    iFile.close();
    oFile.close();
    cout << "Измененный файл записан в " << outputFile << endl;
}
void change_file_S_combined(string inputFile, string outputFile)
{
    ifstream iFile(inputFile, ios::binary);
    ofstream oFile(outputFile, ios::binary);
    uint8_t word;
    while (iFile.read(reinterpret_cast<char *>(&word), sizeof(word)))
    {
        uint8_t result = S_combined[word];
        oFile.write(reinterpret_cast<const char *>(&result), sizeof(result));
    }
    iFile.close();
    oFile.close();
    cout << "Измененный файл записан в " << outputFile << endl;
}
void print_binary(uint64_t a)
{
    for (int i = 63; i >= 0; --i)
    {
        cout << ((a >> i) & 1);
        if (i % 8 == 0)
            cout << ' ';
    }
    cout << endl;
}
uint64_t comb(uint64_t a)
{
    uint64_t inp = a;
    uint8_t temp = 0;
    uint64_t res = 0;
    for (int i = 0; i < 8; i++)
    {
        temp = inp & 0xFF;
        temp = combination(temp);
        res |= (uint64_t)temp << (8 * i);
        inp >>= 8;
    }
    return res;
}
int main()
{
    uint64_t a = 0x0123456789abcdef;
    init_tables();
    print_tables();
    cout << "    До 4 битовой подстановки: " << hex << a << endl;
    cout << " После 4 битовой подстановки: " << hex << subsitute(a, S) << endl;
    cout << " После 8 битовой подстановки: " << hex << subsitute_8bit(a) << endl;
    cout << "После 8 битовой перестановки: " << hex << cycle_rotate(a) << endl;
    cout << "После 8 битовой комбинации операций: " << hex << comb(a) << endl;
    change_file_S("data.txt", "res.txt");
    change_file_S_combined("data.txt", "ress.txt");
    return 0;
}
