#include "app_logic.h"
#include "bignum_algorithms.h"
void printResult(const std::string &original_hex, const Digit inverse[], const std::string &test_name)
{
    if (!test_name.empty())
    {
        cout << "--- " << test_name << " ---" << endl;
    }

    cout << "Исходное число:             " << original_hex << endl;

    // Преобразуем найденный обратный элемент в строку для вывода
    string inverse_hex = NumToStringDigit(inverse);

    cout << "Найденный обратный элемент: " << inverse_hex << endl;
    cout << "----------------------------------------------------------------" << endl;
}
void test(bool flag)
{
    std::vector<std::string> test_nums{
        "cb6075cd06a5a3c7aebe4ec82e65f8fa44bdb635671c8383806fb26dc5041b4c",
        "0d0d243259539bd1aba2736c70fc717cba7d8629928a729204deb9eb170491a2",
        "11f8cd98f4cf819ec83791af9bf96496c93b66d596d798f91ac80583ab7739bc"};
    std::vector<std::string> results{
        "651944b867a5e1de457bcea5f2c715e8a12941687c4ae55ad87ae87d93e52981",
        "fafa9a56e96a23d2e84b48f982330e017c84cf1de7b7f15c98d4dfa498fcbae3",
        "be5871230a744f8bc953fdca085f79a3dc22b07131d915145b78052222a85d1f"};
    for (int i = 0; i < test_nums.size(); i++)
    {
        Digit pr[CD];
        Digit obr[CD];
        StringToNumber(test_nums[i], pr);
        if(flag){
            rev(pr, obr);
        }
        else{
            rev_mod(pr, obr);
        }
        printResult(test_nums[i], obr, "Тест #" + std::to_string(i + 1));
        if (results[i] == NumToStringDigit(obr))
        {
            std::cout << "Тест #" + std::to_string(i + 1) + " успешен!" << std::endl
                      << std::endl;
        }
        else
        {
            std::cout << "Тест #" + std::to_string(i + 1) + " провален!" << std::endl
                      << std::endl;
        }
    }
}
void compute_all_variants_eucl()
{
    std::cout<<"Вычисления методом расширенного алгоритма евклида"<<std::endl;
    for (int i = 0; i < variants.size(); i += 2)
    {
        int variant_number = (i / 2) + 1;
        std::string variant_name = "Вариант #" + std::to_string(variant_number);
        cout << "================== " << variant_name << " ==================" << endl;
        compute_obr_eucl(variants[i], "Первое число");
        compute_obr_eucl(variants[i + 1], "Второе число");
    }
}
void compute_all_variants_pow()
{
    std::cout<<"Вычисления методом модулярного возведения в степень"<<std::endl;
    for (int i = 0; i < variants.size(); i += 2)
    {
        int variant_number = (i / 2) + 1;
        std::string variant_name = "Вариант #" + std::to_string(variant_number);
        cout << "================== " << variant_name << " ==================" << endl;
        compute_obr_eucl(variants[i], "Первое число");
        compute_obr_eucl(variants[i + 1], "Второе число");
    }
}
void runPerformanceTest()
{
    const int iterations = 1000;
    const int total_computations = iterations * variants.size();
    cout << "================== ЗАПУСК ТЕСТА ПРОИЗВОДИТЕЛЬНОСТИ ==================" << endl;
    cout << "Количество итераций для каждого числа: " << iterations << endl;
    cout << "Всего вычислений для каждого метода: " << total_computations << endl;
    cout << "Пожалуйста, подождите..." << endl << endl;
    Digit pr[CD];
    Digit obr[CD];
    auto start_euclid = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i)
    {
        for (const auto& num_str : variants)
        {
            StringToNumber(num_str, pr);
            rev(pr, obr); 
        }
    }
    auto end_euclid = std::chrono::high_resolution_clock::now();
    auto start_ferma = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i)
    {
        for (const auto& num_str : variants)
        {
            StringToNumber(num_str, pr);
            rev_mod(pr, obr); 
        }
    }
    auto end_ferma = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_euclid = end_euclid - start_euclid;
    std::chrono::duration<double, std::milli> duration_ferma = end_ferma - start_ferma;
    cout << "====================== РЕЗУЛЬТАТЫ ЗАМЕРОВ ======================" << endl;
    cout << "Время выполнения " << total_computations << " операций:" << endl << endl;
    cout.precision(2); 
    cout << fixed;    
    cout << "  - Расширенный алгоритм Евклида: " << duration_euclid.count() << " мс" << endl;
    cout << "  - Метод на основе теоремы Ферма: " << duration_ferma.count() << " мс" << endl << endl;
    if (duration_euclid < duration_ferma) {
        cout << "Вывод: Расширенный алгоритм Евклида оказался быстрее на " 
             << duration_ferma.count() - duration_euclid.count() << " мс." << endl;
    } else {
        cout << "Вывод: Метод на основе теоремы Ферма оказался быстрее на " 
             << duration_euclid.count() - duration_ferma.count() << " мс." << endl;
    }
    cout << "==================================================================" << endl;
}
void compute_obr_eucl(std::string pr_dig, std::string name)
{
    Digit pr[CD];
    Digit obr[CD];
    StringToNumber(pr_dig, pr);
    rev(pr, obr);
    printResult(pr_dig, obr, name);
}
void compute_obr_pow(std::string pr_dig, std::string name){
    Digit pr[CD];
    Digit obr[CD];
    StringToNumber(pr_dig, pr);
    rev_mod(pr, obr);
    printResult(pr_dig, obr, name);
}