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
        encrypt(fin, "output.enc");
    }
    else
    {
        decrypt(fin, "decrypted.txt");
    }
    fin.close();
}
void magma::encrypt(std::ifstream &in, std::string filename)
{
    std::ofstream fout(filename, std::ios::binary);
    while (true)
    {
        uint32_t newR;
        uint32_t newL;
        try
        {
            uint64_t file_block = read_file(in, true);
            uint32_t R = static_cast<uint32_t>(file_block & 0xFFFFFFFF);
            uint32_t L = static_cast<uint32_t>(file_block >> 32);

            for (int i = 0; i < 24; ++i)
            {
                uint32_t F = round(R, i % 8);
                uint32_t tmp = R;
                uint32_t newR = F ^ L;
                uint32_t newL = R;
            }
            for (int i = 7; i >= 0; --i)
            {
                uint32_t F = round(R, i);
                uint32_t tmp = R;
                newR = F ^ L;
                newL = R;
            }

            fout.write(reinterpret_cast<char *>(&newL), sizeof(newL));
            fout.write(reinterpret_cast<char *>(&newR), sizeof(newR));
        }
        catch (...)
        {
            break;
        }
    }
    fout.close();
}

void magma::decrypt(std::ifstream &in, std::string filename)
{
    std::ofstream fout(filename, std::ios::binary);
    while (true)
    {
        uint32_t newR;
        uint32_t newL;
        try
        {
            uint64_t file_block = read_file(in, false);
            uint32_t R = static_cast<uint32_t>(file_block & 0xFFFFFFFF);
            uint32_t L = static_cast<uint32_t>(file_block >> 32);

            for (int i = 0; i < 8; ++i)
            {
                uint32_t F = round(R, i);
                uint32_t tmp = R;
                uint32_t newR = F ^ L;
                uint32_t newL = R;
            }
            for (int i = 23; i >= 0; --i)
            {
                uint32_t F = round(R, i % 8);
                uint32_t tmp = R;
                newR = F ^ L;
                newL = R;
            }

            fout.write(reinterpret_cast<char *>(&newL), sizeof(newL));
            fout.write(reinterpret_cast<char *>(&newR), sizeof(newR));
        }
        catch (...)
        {
            break;
        }
    }
    fout.close();
    namespace fs = std::filesystem;
    uintmax_t dec_size = fs::file_size("decrypted.txt");
    if (dec_size == 0)
        return;
    std::ifstream fin2("decrypted.txt", std::ios::binary);
    fin2.seekg(dec_size - 1);
    uint8_t pad_len = 0;
    fin2.read(reinterpret_cast<char *>(&pad_len), 1);
    fin2.close();

    if (pad_len > 0 && pad_len <= 8)
    {
        fs::resize_file("decrypted.txt", dec_size - pad_len);
    }
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
uint64_t magma::read_file(std::ifstream &in, bool encryption_mode)
{
    constexpr size_t BLOCK_SIZE = 8;
    uint64_t value = 0;

    std::streampos pos = in.tellg();
    size_t remaining = static_cast<size_t>(file_size - pos);

    if (remaining >= BLOCK_SIZE)
    {
        in.read(reinterpret_cast<char *>(&value), BLOCK_SIZE);
        if (!in)
        {
            if (in.eof())
                throw std::runtime_error("Достигнут конец файла");
            else
                throw std::runtime_error("Ошибка чтения из файла");
        }
    }
    else if (remaining > 0)
    {
        uint8_t buffer[BLOCK_SIZE] = {0};
        in.read(reinterpret_cast<char *>(buffer), remaining);
        if (!in && !in.eof())
            throw std::runtime_error("Ошибка чтения из файла");

        if (encryption_mode)
        {
            uint8_t pad_len = static_cast<uint8_t>(BLOCK_SIZE - remaining);
            for (size_t i = remaining; i < BLOCK_SIZE; ++i)
            {
                buffer[i] = pad_len;
            }
        }

        std::memcpy(&value, buffer, BLOCK_SIZE);
    }
    else
    {
        throw std::runtime_error("Достигнут конец файла");
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
void magma::test_ciphertext_resilience(std::string ciphertext_path, std::string oversized_path)
{
    namespace fs = std::filesystem;
    std::ifstream fin(ciphertext_path, std::ios::binary);
    if (!fin)
    {
        std::cerr << "[!] Не удалось открыть " << ciphertext_path << "\n";
        return;
    }
    std::vector<char> data{std::istreambuf_iterator<char>(fin),
                           std::istreambuf_iterator<char>()};
    fin.close();
    std::vector<std::pair<std::string, std::vector<char>>> variants;
    if (data.size() > 1)
    {
        auto v = data;
        v.erase(v.begin() + 1);
        variants.emplace_back("corrupt_del1.enc", std::move(v));
    }
    if (data.size() > 20)
    {
        auto v = data;
        v.erase(v.begin() + 5, v.begin() + 5 + 7); // удаляем 7 байт
        variants.emplace_back("corrupt_del_non64.enc", std::move(v));
    }
    if (data.size() > 16)
    {
        auto v = data;
        v.erase(v.begin() + 8, v.begin() + 8 + 8); // удаляем 8 байт
        variants.emplace_back("corrupt_del64.enc", std::move(v));
    }
    {
        auto v = data;
        std::vector<char> pad(8, 0xAA);
        v.insert(v.begin() + 8, pad.begin(), pad.end());
        variants.emplace_back("corrupt_add64.enc", std::move(v));
    }
    if (data.size() >= 16)
    {
        auto v = data;
        for (size_t i = 0; i < 8; ++i)
            std::swap(v[i], v[8 + i]);
        variants.emplace_back("corrupt_swap64.enc", std::move(v));
    }
    for (auto &[name, buf] : variants)
    {
        std::ofstream fout(name, std::ios::binary);
        fout.write(buf.data(), buf.size());
        fout.close();

        std::cout << "[*] Расшифровка варианта: " << name << " -> decrypted_" << name << std::endl;
        fin.open(name, std::ios::binary);
        file_size = fs::file_size(name);
        decrypt(fin, "decrypted_" + name + ".txt");
        fin.close();
    }
    std::cout << "[*] Пробуем зашифровать большой файл (>20Кб): " << oversized_path << std::endl;
    fin.open(oversized_path, std::ios::binary);
    get_file_size(fin);
    encrypt(fin, "big_output.enc");
    fin.close();
    std::cout << "[*] Запуск скрипта сравнения хеш-сумм..." << std::endl;
    int result = std::system("./check_hashes.sh");
    if (result != 0)
    {
        std::cerr << "[!] Скрипт завершился с ошибкой: " << result << std::endl;
    }
}