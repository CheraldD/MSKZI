#include "magma.h"
magma::magma()
{
    generator.generate_key();
    key = read_key("key.key");
}
void magma::file_open(std::string file_path, bool flag)
{
    fin.open(file_path, std::ios::binary);
    if (!fin)
    {
        std::cerr << "Cannot open file\n";
        return;
    }
    get_file_size(fin);
    if (flag == 0)
    {
        encrypt();
    }
    else
    {
        decrypt();
    }
    fin.close();
}
void magma::encrypt()
{
    std::ofstream fout("output.enc", std::ios::binary);
    while (true)
    {
        try
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    uint64_t file_block = read_file(fin);
                    uint32_t R = static_cast<uint32_t>(file_block & 0xFFFFFFFF);
                    uint32_t L = static_cast<uint32_t>(file_block >> 32);
                    uint32_t F = round(R, j);
                    uint32_t newR = F ^ L;
                    uint32_t newL = R;
                    fout.write(reinterpret_cast<char *>(&newL), sizeof(newL));
                    fout.write(reinterpret_cast<char *>(&newR), sizeof(newR));
                }
            }
            for (int i = 7; i >= 0; i--)
            {
                uint64_t file_block = read_file(fin);
                uint32_t R = static_cast<uint32_t>(file_block & 0xFFFFFFFF);
                uint32_t L = static_cast<uint32_t>(file_block >> 32);
                uint32_t F = round(R, i);
                uint32_t newR = F ^ L;
                uint32_t newL = R;
                fout.write(reinterpret_cast<char *>(&newL), sizeof(newL));
                fout.write(reinterpret_cast<char *>(&newR), sizeof(newR));
            }
        }
        catch (...)
        {
            break;
        }
    }
    fout.close();
}
void magma::decrypt()
{
    std::ofstream fout("decrypted.txt", std::ios::binary);
    while (true)
    {
        try
        {
            for (int i = 0; i < 8; i++)
            {
                uint64_t file_block = read_file(fin);
                uint32_t R = static_cast<uint32_t>(file_block & 0xFFFFFFFF);
                uint32_t L = static_cast<uint32_t>(file_block >> 32);
                uint32_t F = round(R, i);
                uint32_t newR = F ^ L;
                uint32_t newL = R;
                fout.write(reinterpret_cast<char *>(&newL), sizeof(newL));
                fout.write(reinterpret_cast<char *>(&newR), sizeof(newR));
            }
            for (int i = 0; i < 3; i++)
            {
                for (int j = 7; j >= 0; j--)
                {
                    uint64_t file_block = read_file(fin);
                    uint32_t R = static_cast<uint32_t>(file_block & 0xFFFFFFFF);
                    uint32_t L = static_cast<uint32_t>(file_block >> 32);
                    uint32_t F = round(R, j);
                    uint32_t newR = F ^ L;
                    uint32_t newL = R;
                    fout.write(reinterpret_cast<char *>(&newL), sizeof(newL));
                    fout.write(reinterpret_cast<char *>(&newR), sizeof(newR));
                }
            }
        }
        catch (...)
        {
            break;
        }
    }
    fout.close();
}
uint32_t magma::round(uint32_t right, int n)
{
    right = right + key[n];
    right = substitution(right);
    right = (right << 11) | (right >> (32 - 11));
    return right;
}
uint32_t magma::substitution(uint32_t input)
{
    uint32_t output = 0;
    for (int i = 0; i < 8; i++)
    {
        uint8_t nibble = (input >> (i * 4)) & 0xF;
        uint8_t substituted = S_BOX[7 - i][nibble];
        output |= (substituted << (i * 4));
    }
    return output;
}
uint64_t magma::read_file(std::ifstream &in)
{
    uint64_t value = 0;
    in.read(reinterpret_cast<char *>(&value), sizeof(value));
    if (!in)
    {
        if (in.eof())
            throw std::runtime_error("Достигнут конец");
        else
            throw std::runtime_error("Ошибка чтения");
    }
    return value;
}

std::vector<uint32_t> magma::read_key(std::string filename)
{
    std::vector<uint32_t> key;
    std::ifstream fin(filename, std::ios::binary);
    if (!fin)
    {
        std::cerr << "Ошибка при открытии файла!" << std::endl;
        return key;
    }
    uint32_t temp;
    for (int i = 0; i < 8; i++)
    {
        fin.read(reinterpret_cast<char *>(&temp), sizeof(temp));
        if (fin)
        {
            key.push_back(temp);
        }
        else
        {
            std::cerr << "Ошибка при чтении файла!" << std::endl;
            break;
        }
    }
    fin.close();
    return key;
}
uint64_t magma::get_file_size(std::ifstream &in)
{
    in.seekg(0, std::ios::end);
    file_size = in.tellg();
    if (file_size > 20480)
    {
        std::cerr << "Размер файла больше 20Кб, зашифрование невозможно" << std::endl;
        return 1;
    }
    in.seekg(0, std::ios::beg);
    std::cout << "File size: " << file_size << " bytes" << std::endl;
}