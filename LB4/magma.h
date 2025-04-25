#pragma once
#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <random>
#include <iomanip>
#include <cstring>

#include "keygen.h"
class magma{
    public:
    keygen generator;
    const vector<vector<uint8_t>> S_BOX = {
        {12,  4,  6,  2, 10,  5, 11,  9, 14,  8, 13,  7,  0,  3, 15,  1}, 
        { 6,  8,  2,  3,  9, 10,  5, 12,  1, 14,  4,  7, 11, 13,  0, 15}, 
        {11,  3,  5,  8,  2, 15, 10, 13, 14,  1,  7,  4, 12,  9,  6,  0}, 
        {12,  8,  2,  1, 13,  4, 15,  6,  7,  0, 10,  5,  3, 14,  9, 11}, 
        { 7, 15,  5, 10,  8,  1,  6, 13,  0,  9,  3, 14, 11,  4,  2, 12}, 
        { 5, 13, 15,  6,  9,  2, 12, 10, 11,  7,  8,  1,  4,  3, 14,  0}, 
        { 8, 14,  2,  5,  6,  9,  1, 12, 15,  4, 11,  0, 13, 10,  3,  7}, 
        { 1,  7, 14, 13,  0,  5,  8,  3,  4, 15, 10,  6,  9, 12, 11,  2}  
    };
    uint64_t file_block;
    uint64_t file_size;
    std::ifstream fin;
    std::vector<uint32_t> key;
    uint64_t read_file(std::ifstream& in);
    void encrypt();
    void decrypt();
    uint32_t round(uint32_t right,int n);
    uint32_t substitution(uint32_t input);
    vector <uint32_t> read_key(std::string filename);
    uint64_t get_file_size(std::ifstream& in);
    void file_open(std::string file_path,bool flag);
    magma();
};