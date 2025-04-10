#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <random>
using namespace std;
// 2, A, 5, B, 9, E, 8, D, C, 4, 6, 7, 0, 3, F, 1
uint64_t a = 0x123456789abcdef;
char S[16] = {0x02, 0x0A, 0x05, 0x0B, 0x09, 0x0E, 0x08, 0x0D,
              0x0C, 0x04, 0x06, 0x07, 0x00, 0x03, 0x0F, 0x01};
uint8_t s[256] = {
    0xA7, 0x3D, 0x59, 0xE4, 0x81, 0xF2, 0xBE, 0x92, 0x04, 0x7B, 0xC5, 0x1F, 0xD9, 0x68, 0xAB, 0x36,
    0xE1, 0x6A, 0xFC, 0x20, 0x5E, 0x8F, 0x9C, 0xB8, 0x2D, 0xC1, 0x47, 0x10, 0x73, 0xDA, 0x89, 0xF4,
    0x31, 0x65, 0xAD, 0x9F, 0xCB, 0x2A, 0xEE, 0x77, 0x4F, 0xB6, 0x98, 0x3C, 0xD0, 0x52, 0x6E, 0x13,
    0xAF, 0x08, 0x42, 0x75, 0xB3, 0x96, 0x24, 0xE7, 0x19, 0xD4, 0xF1, 0x58, 0x87, 0x0B, 0xC9, 0xA2,
    0x50, 0xE8, 0x14, 0x3A, 0x6F, 0x9D, 0x21, 0xBF, 0x85, 0xCC, 0x11, 0xF9, 0x7F, 0x43, 0xD2, 0xA6,
    0x5D, 0xE0, 0x28, 0x9B, 0x47, 0xB2, 0x7A, 0x01, 0xDC, 0x69, 0xF7, 0x35, 0x8E, 0xC0, 0x16, 0xA8,
    0x63, 0xB0, 0xDF, 0x4C, 0xF5, 0x22, 0x78, 0x93, 0x0A, 0xCD, 0x5B, 0xE6, 0x80, 0x27, 0x34, 0xFA,
    0xC6, 0x41, 0xB7, 0x0F, 0xA5, 0xDA, 0x9E, 0x3B, 0x12, 0x71, 0xF0, 0x68, 0x2E, 0x54, 0x86, 0xCB,
    0x7C, 0x04, 0x30, 0xEB, 0xD1, 0x9A, 0x25, 0xF3, 0x6C, 0xBA, 0x53, 0xA1, 0x8D, 0x7E, 0x45, 0xC3,
    0x1A, 0xD6, 0xF6, 0x0E, 0xB5, 0x67, 0x29, 0x90, 0x55, 0xFE, 0x88, 0x3E, 0xC4, 0x76, 0x20, 0xAB,
    0xE5, 0x0C, 0x9F, 0x44, 0x68, 0xB1, 0x33, 0x5F, 0xD8, 0x91, 0xE3, 0x1D, 0xFA, 0x72, 0xCA, 0x86,
    0x4E, 0xA9, 0x57, 0x02, 0xBC, 0xEF, 0x39, 0x7D, 0x11, 0x60, 0x83, 0xC8, 0xA4, 0x2C, 0xF8, 0x95,
    0xDD, 0x37, 0x5A, 0x18, 0x82, 0xB9, 0x6B, 0xE9, 0xC7, 0x2F, 0xF2, 0x46, 0x70, 0x14, 0xAD, 0x98,
    0xDB, 0x7F, 0x62, 0xE2, 0x4A, 0x15, 0x9C, 0xA0, 0xD5, 0xF0, 0x23, 0x89, 0x6D, 0xB4, 0xC2, 0x0D,
    0x3F, 0x74, 0xEA, 0x5C, 0x97, 0x21, 0xCF, 0xB8, 0x0A, 0x66, 0x49, 0xD7, 0x13, 0xF5, 0xAE, 0x35,
    0xC1, 0x87, 0x61, 0x32, 0xBF, 0x4D, 0xEC, 0x09, 0x26, 0xA3, 0xF4, 0x50, 0x7A, 0xD3, 0xBE, 0x8C};
uint64_t subsitute(uint64_t a)
{
    uint64_t inp = a;
    uint8_t temp = 0;
    uint64_t res = 0;
    for (int i = 0; i < 16; i++)
    {
        temp = S[inp & 0b1111];
        res |= (uint64_t)temp << (4 * i);
        inp >>= 4;
    }
    return res;
}
uint64_t subsitute_8bit(uint64_t a)
{
    uint64_t inp = a;
    uint64_t res = 0;
    uint8_t temp = 0;
    for (int i = 0; i < 8; i++)
    {
        temp = s[inp & 0xFF];
        res |= (uint64_t)temp << (8 * i);
        inp >>= 8;
    }
    return res;
}
uint8_t rotate(uint8_t vec,int p){
    return (vec>>p)|(vec<<(8-p));
}
uint64_t cycle_rotate(uint64_t a){
    uint64_t inp = a;
    uint8_t temp = 0;
    uint64_t res =0;
    for (int i = 0; i < 8; i++)
    {
        temp=rotate(inp&0xFF,5);
        res |= (uint64_t)temp << (8 * i);
        inp >>= 8;
    }
    return res;
}
uint8_t combination(uint8_t vec){
    uint8_t x1=(vec&0b11110000)>>4;
    uint8_t x2=vec&0b1111;
    x1=subsitute(x1);
    x2=subsitute(x2);
    uint8_t x=(x1<<4)|x2;
    return rotate(x,5);
}
void change_file(string inputFile,string outputFile){
    ifstream iFile(inputFile, ios::binary);
    ofstream oFile(outputFile, ios::binary); 
    uint8_t word;
    while (iFile.read(reinterpret_cast<char*>(&word), sizeof(word)))
    {
        uint8_t result=combination(word);
        oFile.write(reinterpret_cast<const char*>(&result), sizeof(result));
    }
    iFile.close();
    oFile.close();
    cout<<"Измененный файл записан в "<<outputFile<<endl;
}
int main()
{
    cout << "    До 4 битовой подстановки: " << bitset<64>(a).to_string() << endl;
    cout << " После 4 битовой подстановки: " << bitset<64>(subsitute(a)).to_string() << endl;
    cout << " После 8 битовой подстановки: " << bitset<64>(subsitute_8bit(a)).to_string() << endl;
    cout << "После 8 битовой перестановки: " << bitset<64>(cycle_rotate(a)).to_string() << endl;
    change_file("data.txt","res.txt");
    return 0;
}
