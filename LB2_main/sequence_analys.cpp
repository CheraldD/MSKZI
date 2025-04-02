#include "sequence_analys.h"
void SequenceAnalyzer::count_freq(std::vector<bool>& sequence) {
    for (int i = 0; i < sequence.size(); i++) {
        uint bit = sequence[i];
        p1[bit] += 1;
        p2[c & 0x03] += 1;
        p3[c & 0x07] += 1;
        p4[c & 0x0F] += 1;
        c = (c << 1) | bit;
    }
}

void SequenceAnalyzer::clear_vectors() {
    p1 = std::vector<uint32_t>(2, 0);
    p2 = std::vector<uint32_t>(4, 0);
    p3 = std::vector<uint32_t>(8, 0);
    p4 = std::vector<uint32_t>(16, 0);
    c = 0;
    length = 0;
    sequence.clear();
}

std::vector<double> SequenceAnalyzer::calculate_freq(std::vector<uint32_t>& p, uint8_t len) {
    std::vector<double> freq(p.size());
    uint64_t total = length - len;
    if (total == 0) total = 1;
    for (size_t i = 0; i < p.size(); i++) {
        freq[i] = static_cast<double>(p[i]) / total;
    }
    return freq;
}

void SequenceAnalyzer::print_result_rel_freq(const std::vector<double>& p, const std::string& name, const uint8_t len) {
    std::cout << name << " :" << std::endl;
    for (size_t i = 0; i < p.size(); i++) {
        std::cout << std::bitset<4>(i).to_string().substr(4 - len) << ": " << p[i] << std::endl;
    }
}

void SequenceAnalyzer::calculate_all_freq() {
    std::cout << "Относительные частоты последовательностей" << std::endl;
    print_result_rel_freq(calculate_freq(p1, lengths[0]), "p1", len[0]);
    print_result_rel_freq(calculate_freq(p2, lengths[1]), "p2", len[1]);
    print_result_rel_freq(calculate_freq(p3, lengths[2]), "p3", len[2]);
    print_result_rel_freq(calculate_freq(p4, lengths[3]), "p4", len[3]);
    std::cout << "________________________________________________________________________" << std::endl;
}

uint SequenceAnalyzer::generate_psp(const uint length, bool flag) {
    std::ofstream oFile("PSP.txt", std::ios::out);
    const uint shift_rlz1 = 0x01 << (19 - 12 - 1);
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
        uint bit = bit1_rlz1 ^ bit1_rlz2;
        if (flag) {
            sequence.push_back(bit);
        }
        res = (res << 1) | (bit);
    }

    return res;
}

int SequenceAnalyzer::countOnes(uint32_t n) {
    return std::bitset<32>(n).count();
}

std::map<int, uint32_t> SequenceAnalyzer::createFrequencyMap(const std::vector<uint32_t>& p) {
    std::map<int, uint32_t> freqMap;

    for (size_t i = 0; i < p.size(); ++i) {
        int onesCount = countOnes(static_cast<uint32_t>(i));
        freqMap[onesCount] += p[i];
    }

    return freqMap;
}

void SequenceAnalyzer::printFrequencyMap(const std::map<int, uint32_t>& freqMap, uint8_t len) {
    for (const auto& [onesCount, sum] : freqMap) {
        std::cout << "Ones: " << onesCount << ", rel_freq: " << static_cast<double>(sum) / (length - len) << '\n';
    }
}

double SequenceAnalyzer::autocorrelation(int shift, const std::vector<bool>& sequence) {
    int match = 0, size = sequence.size();
    for (int i = 0; i < size - shift; i++)
        if (sequence[i] == sequence[i + shift])
            match++;

    return ((double)match - (size - match)) / (double(match) + (size - match));
}

void SequenceAnalyzer::print_0_to_32_akf() {
    std::cout << "АКФ" << std::endl;

    for (int i = 0; i < 32; i++) {
        std::cout << i << ": " << autocorrelation(i, sequence) << std::endl;
    }
    std::cout << "________________________________________________________________________" << std::endl;
}

void SequenceAnalyzer::mask_file(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream iFile(inputFile, std::ios::binary);
    std::ofstream oFile(outputFile, std::ios::binary);
    uint8_t byte;
    uint8_t psp = static_cast<uint8_t>(generate_psp(8, false));
    while (iFile.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        uint8_t res = byte ^ psp;
        oFile.write(reinterpret_cast<char*>(&res), sizeof(res));
    }
    iFile.close();
    oFile.close();
}

void SequenceAnalyzer::print_freq() {
    std::cout << "Частоты появления последовательностей" << std::endl;
    for (int i = 0; i < 2; i++) {
        std::cout << "p1: " << p1[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << "p2: " << p2[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 8; i++) {
        std::cout << "p3: " << p3[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 16; i++) {
        std::cout << "p4: " << p4[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "________________________________________________________________________" << std::endl;
}

uint SequenceAnalyzer::get_file_size(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Не удалось открыть файл!" << std::endl;
        return 0;
    }
    uint temp = static_cast<uint>(file.tellg());
    file.close();
    return temp;
}

void SequenceAnalyzer::file_characteristic(const std::string& inputFile) {
    length = get_file_size(inputFile) * 8;
    std::ifstream iFile(inputFile, std::ios::binary);
    if (!iFile) {
        std::cerr << "Не удалось открыть файл!" << std::endl;
        return;
    }
    uint8_t word;
    while (iFile.read(reinterpret_cast<char*>(&word), sizeof(word))) {
        for (int i = 7; i >= 0; --i) {
            uint8_t temp = (word >> i) & 1;
            sequence.push_back(temp);
        }
    }
    iFile.close();
}

void SequenceAnalyzer::printVector(const std::vector<bool>& vec) {
    for (bool value : vec) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}
void SequenceAnalyzer::print_ones_freq(){
    std::cout<<"p2: "<<std::endl;
    printFrequencyMap(createFrequencyMap(p2),len[1]);
    std::cout<<"p3: "<<std::endl;
    printFrequencyMap(createFrequencyMap(p3),len[2]);
    std::cout<<"p4: "<<std::endl;
    printFrequencyMap(createFrequencyMap(p4),len[3]);
}
void SequenceAnalyzer::calculcate_static_char(std::vector<bool>& seq, bool flag, const std::string& input) {
    if (flag) {
        file_characteristic(input);
    }
    count_freq(seq);
    print_freq();
    calculate_all_freq();
    print_ones_freq();
    print_0_to_32_akf();
    clear_vectors();
}