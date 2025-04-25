#include "keygen.h"
uint8_t keygen::generate_psp()
{
    const uint shift_rlz1 = 0x01 << (19 - 12 - 1);
    const uint shift_rlz2 = 85 - 1;
    uint last_bit_idx = 118 - 1;
    uint tap_bit_idx = shift_rlz2;
    uint8_t res = 0;
    for (int i = 0; i < 8; i++)
    {
        unsigned int bit1_rlz1 = (rlz1 & 0x01) ^ ((rlz1 & shift_rlz1) >> (19 - 12 - 1));
        rlz1 = (rlz1 >> 1) | (bit1_rlz1 << (19 - 1));
        uint bit1_rlz2 = initial_rlz2[last_bit_idx] ^ initial_rlz2[tap_bit_idx];
        initial_rlz2 >>= 1;
        initial_rlz2.set(117, bit1_rlz2);
        res = (res << 1) | (bit1_rlz1 ^ bit1_rlz2);
    }
    return res;
}
void keygen::generate_key()
{   
    std::ofstream fout("key.key", std::ios::binary);
    if (!fout) {
        throw std::runtime_error("Cannot open key.key for writing");
    }
    std::vector<uint8_t> block56;
    for (int i = 0; i < 7; ++i) {
        block56.push_back(generate_psp());
    }
    uint32_t block32 = 0;
    for (int i = 0; i < 4; ++i) {
        block32 |= (static_cast<uint32_t>(block56[i]) << (8 * i));
    }
    for (int i = 0; i < 4; ++i) {
        fout.write(reinterpret_cast<char*>(block56.data()), block56.size());
    }
    fout.write(reinterpret_cast<char*>(&block32), sizeof(block32));
    fout.close();
}