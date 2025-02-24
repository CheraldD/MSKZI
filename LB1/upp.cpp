#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <random>
using namespace std;

bitset<118> rlz2(bitset<118> rlz, const unsigned int tap, uint length, uint rlz_len, ofstream &file) {
    const uint shift = tap - 1;
    for (uint i = 0; i < length; i++) {
        uint last_bit_idx = rlz_len - 1;
        uint tap_bit_idx = shift;
        uint bit1 = rlz[last_bit_idx] ^ rlz[tap_bit_idx];
        rlz >>= 1;
        rlz.set(117, bit1);
        file << i + 1 << "\t" << rlz.to_string() << "\t" << bit1 << endl;
    }
    return rlz;
}

unsigned int rlz1(const unsigned int tap, uint rlz1, uint length, uint rlz1_len, ofstream &file) {
    file << "Шаг\tСостояние генератора\tГенерируемый бит\n";
    const uint shift = 0x01 << (rlz1_len - tap - 1);
    for (uint i = 0; i < length; i++) {
        unsigned int bit1 = (rlz1 & 0x01) ^ ((rlz1 & shift) >> (rlz1_len - tap - 1));
        rlz1 = (rlz1 >> 1) | (bit1 << (rlz1_len - 1));
        file << i + 1 << "\t" << bitset<19>(rlz1).to_string() << "\t" << bit1 << endl;
    }
    return 1;
}

uint generate_psp(const uint length) {
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
        res = (res << 1) | (bit1_rlz1 ^ bit1_rlz2);
    }
    return res;
}
void mask_file(string inputFile,string outputFile, uint length){
    ifstream iFile(inputFile,ios::binary);
    ofstream oFile(outputFile, ios::binary);
    uint8_t byte;
    while (iFile.read(reinterpret_cast<char*>(&byte), sizeof(byte)) || iFile.gcount()) {
        uint8_t psp = static_cast<uint8_t>(generate_psp(length));
        uint8_t res = byte^psp;
        oFile.write(reinterpret_cast<char*>(&res), sizeof(res));
    }
    iFile.close();
    oFile.close();
}
void demask_file(string inputFile,string outputFile, uint length){
    ifstream iFile(inputFile,ios::binary);
    ofstream oFile(outputFile);
    uint8_t byte;
    while (iFile.read(reinterpret_cast<char*>(&byte), sizeof(byte)) || iFile.gcount()) {
        uint8_t psp = static_cast<uint8_t>(generate_psp(length));
        uint8_t res = byte^psp;
        oFile.write(reinterpret_cast<char*>(&res), sizeof(res));
    }
    iFile.close();
    oFile.close();
}
int main() {
    uint length;
    cout << "Введите количество бит в последовательности: ";
    cin >> length;
    string input_file = "data.txt";
    string output_file = "output.bin";
    mask_file(input_file,output_file,length);
    input_file = "output.bin";
    output_file = "dat.txt";
    mask_file(input_file,output_file,length);
    return 0;
}
