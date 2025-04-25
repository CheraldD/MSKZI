#pragma once
#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <random>
using namespace std;
class keygen {
    uint32_t rlz1 = 0b1000011111010001011;
    std::bitset<118> initial_rlz2{ std::string("1111111001110010011000011001010100010010000101111111110101001010000000110001101111111011111011110010010000101111001101") };
public:
    uint8_t generate_psp();
    vector<uint32_t> key;
    void generate_key();

};