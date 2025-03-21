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
using namespace std;
uint length=0;
vector<uint32_t> p1(2);
vector<uint32_t> p2(4);
vector<uint32_t> p3(8);
vector<uint32_t> p4(16);
vector<uint8_t> lengths{0, 1, 2, 3};
const vector<uint8_t> len{1, 2, 3, 4};
uint64_t c = 0;
uint rlz1 = 0b1000011111010001011;
bitset<118> initial_rlz2(string("1111111001110010011000011001010100010010000101111111110101001010000000110001101111111011111011110010010000101111001101"));
vector<bool> sequence{};
void count_freq(uint bit)
{
    p1[bit] += 1;
    p2[c & 0x03] += 1;
    p3[c & 0x07] += 1;
    p4[c & 0x0F] += 1;
    c = (c << 1) | bit;
}
void clear_vectors(){
    p1 = vector<uint32_t>(2, 0);
    p2 = vector<uint32_t>(4, 0);
    p3 = vector<uint32_t>(8, 0);
    p4 = vector<uint32_t>(16, 0);
    c = 0;
    length=0;
    sequence.clear();
}
vector<double> calculate_freq(vector<uint32_t> &p, uint8_t len)
{
    vector<double> freq(p.size());
    uint64_t total = length - len;
    if (total == 0)
        total = 1;
    for (size_t i = 0; i < p.size(); i++)
    {
        freq[i] = static_cast<double>(p[i]) / total;
    }
    return freq;
}

void print_result_rel_freq(const vector<double> &p, const string &name, const uint8_t len)
{
    cout << name << " :" << endl;
    for (size_t i = 0; i < p.size(); i++)
    {
        cout << bitset<4>(i).to_string().substr(4 - len) << ": " << p[i] << endl;
    }
}

void calculate_all_freq()
{
    print_result_rel_freq(calculate_freq(p1, lengths[0]), "p1", len[0]);
    print_result_rel_freq(calculate_freq(p2, lengths[1]), "p2", len[1]);
    print_result_rel_freq(calculate_freq(p3, lengths[2]), "p3", len[2]);
    print_result_rel_freq(calculate_freq(p4, lengths[3]), "p4", len[3]);
}

uint generate_psp(const uint length, bool flag)
{
    ofstream oFile("PSP.txt", ios::out);
    const uint shift_rlz1 = 0x01 << (19 - 12 - 1);
    const uint shift_rlz2 = 85 - 1;
    uint last_bit_idx = 118 - 1;
    uint tap_bit_idx = shift_rlz2;
    uint res = 0;

    for (int i = 0; i < length; i++)
    {
        unsigned int bit1_rlz1 = (rlz1 & 0x01) ^ ((rlz1 & shift_rlz1) >> (19 - 12 - 1));
        rlz1 = (rlz1 >> 1) | (bit1_rlz1 << (19 - 1));
        uint bit1_rlz2 = initial_rlz2[last_bit_idx] ^ initial_rlz2[tap_bit_idx];
        initial_rlz2 >>= 1;
        initial_rlz2.set(117, bit1_rlz2);
        uint bit = bit1_rlz1 ^ bit1_rlz2;
        if (flag)
        {
            count_freq(bit);
            sequence.push_back(bit);
        }
        res = (res << 1) | (bit);
    }

    return res;
}

int countOnes(uint32_t n) {
    return std::bitset<32>(n).count();
}

std::map<int, uint32_t> createFrequencyMap(const std::vector<uint32_t>& p) {
    std::map<int, uint32_t> freqMap;

    for (size_t i = 0; i < p.size(); ++i) {
        int onesCount = countOnes(static_cast<uint32_t>(i));
        freqMap[onesCount] += p[i];
    }

    return freqMap;
}
void printFrequencyMap(const std::map<int, uint32_t>& freqMap,uint8_t len) {
    for (const auto& [onesCount, sum] : freqMap) {
        std::cout << "Ones: " << onesCount << ", rel_freq: " << static_cast<double>(sum)/(length-len)<< '\n';
    }
}
void print_ones_freq(){
    cout<<"p2: "<<endl;
    printFrequencyMap(createFrequencyMap(p2),len[1]);
    cout<<"p3: "<<endl;
    printFrequencyMap(createFrequencyMap(p3),len[2]);
    cout<<"p4: "<<endl;
    printFrequencyMap(createFrequencyMap(p4),len[3]);
}
double autocorrelation(int shift, const vector<bool>& sequence) {
    int match = 0, size = sequence.size();
    for (int i = 0; i < size - shift; i++)
        if (sequence[i] == sequence[i + shift])
            match++;

    return ((double)match -(size-match))/ (double(match)+(size-match));
}
void print_0_to_32_akf(){
    cout<<"АКФ"<<endl;
    
    for (int i = 0; i < 32; i++)
    {
        cout<<i<<": "<<autocorrelation(i,sequence)<<endl;
    }
    cout<<"________________________________________________________________________"<<endl;
}
void mask_file(string inputFile, string outputFile)
{
    ifstream iFile(inputFile, ios::binary);
    ofstream oFile(outputFile, ios::binary);
    uint8_t byte;
    uint8_t psp = static_cast<uint8_t>(generate_psp(8, false));
    while (iFile.read(reinterpret_cast<char *>(&byte), sizeof(byte)))
    {
        uint8_t res = byte ^ psp;
        oFile.write(reinterpret_cast<char *>(&res), sizeof(res));
    }
    iFile.close();
    oFile.close();
}
void print_freq()
{
    for (int i = 0; i < 2; i++)
    {
        cout << "p1: " << p1[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << "p2: " << p2[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << "p3: " << p3[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 16; i++)
    {
        cout << "p4: " << p4[i] << " ";
    }
    cout << endl;
}
uint get_file_size(const string& filename)
{
    ifstream file(filename, ios::binary | ios::ate);  
    if (!file)
    {
        cerr << "Не удалось открыть файл!" << endl;
        return 0; 
    }
    uint temp = static_cast<uint>(file.tellg());
    file.close();
    return temp;  
}
void file_characteristic(string inputFile)
{
    length=get_file_size(inputFile)*8;
    cout<<length<<endl;
    ifstream iFile(inputFile, ios::binary);
    if (!iFile)
    {
        cerr << "Не удалось открыть файл!" << endl;
        return;
    }
    uint8_t word;
    while (iFile.read(reinterpret_cast<char*>(&word), sizeof(word)))
    {
        for (int i = 7; i >= 0; --i) 
        {
            uint8_t temp = (word >> i) & 1;
            sequence.push_back(temp);
            count_freq(static_cast<uint>(temp));
        }
    }
    iFile.close();
}
void calculcate_static_char(vector<bool> &seq,bool flag,string input){
    if(flag){
        file_characteristic(input);
    }
    print_freq();
    calculate_all_freq();
    print_ones_freq();
    print_0_to_32_akf();
    clear_vectors();
}
int main()
{
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
        generate_psp(length, true);
        calculcate_static_char(sequence,0,input);
        break;
    case 2:
        cout << "Ввведите имя маскируемого файла: ";
        cin >> input;
        cout << "Ввведите имя результирующего файла: ";
        cin >> res;
        calculcate_static_char(sequence,1,input);
        mask_file(input, res);
        calculcate_static_char(sequence,1,res);
        break;
    case 3:
        cout << "Ввведите имя демаскируемого файла: ";
        cin >> input;
        cout << "Ввведите имя результирующего файла: ";
        cin >> res;
        mask_file(input, res);
        break;
    default:
        cout << "Ошибочная операция" << endl;
        exit(0);
        break;
    }
    return 0;
}
