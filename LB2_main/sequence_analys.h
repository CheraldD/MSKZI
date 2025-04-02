#pragma once
#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <map>
#include <string>

class SequenceAnalyzer
{
public:
    uint length = 0;
    std::vector<uint32_t> p1 = std::vector<uint32_t>(2, 0);
    std::vector<uint32_t> p2 = std::vector<uint32_t>(4, 0);
    std::vector<uint32_t> p3 = std::vector<uint32_t>(8, 0);
    std::vector<uint32_t> p4 = std::vector<uint32_t>(16, 0);
    uint64_t c = 0;
    uint rlz1 = 0b1000011111010001011;
    std::bitset<118> initial_rlz2;
    std::vector<bool> sequence;
    const std::vector<uint8_t> lengths{0, 1, 2, 3};
    const std::vector<uint8_t> len{1, 2, 3, 4};

    void count_freq(std::vector<bool> &sequence);
    void clear_vectors();
    std::vector<double> calculate_freq(std::vector<uint32_t> &p, uint8_t len);
    void print_result_rel_freq(const std::vector<double> &p, const std::string &name, const uint8_t len);
    void calculate_all_freq();
    uint generate_psp(const uint length, bool flag);
    int countOnes(uint32_t n);
    std::map<int, uint32_t> createFrequencyMap(const std::vector<uint32_t> &p);
    void printFrequencyMap(const std::map<int, uint32_t> &freqMap, uint8_t len);
    double autocorrelation(int shift, const std::vector<bool> &sequence);
    void print_0_to_32_akf();    
    void file_characteristic(const std::string &inputFile);
    void mask_file(const std::string &inputFile, const std::string &outputFile);
    void print_freq();
    void print_ones_freq();
    void calculcate_static_char(std::vector<bool> &seq, bool flag, const std::string &input);
    uint get_file_size(const std::string &filename);
    void printVector(const std::vector<bool> &vec);
};

