#include "app_logic.h"
#include "bignum_algorithms.h"
void printResult(const std::string &original_hex, const Digit inverse[], const std::string &test_name)
{
    if (!test_name.empty())
    {
        cout << "--- " << test_name << " ---" << endl;
    }

    cout << "Исходное число:             " << original_hex << endl;

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
void test_transit()
{
    // Точки на кривой Вейерштрасса (вход для VeyToEdv)
    std::vector<std::string> test_nums_vey_1 {
        "91E38443A5E82C0D880923425712B2BB658B9196932E02C78B2582FE742DAA28", // x1
        "32879423AB1A0375895786C4BB46E9565FDE0B5344766740AF268ADB32322E5C"  // y1
    };
    std::vector<std::string> test_nums_vey_2 {
        "E8C6740E58D616CA220DB7DA0D9C3E19B53E86E38BF3E8747774631452EC174C", // x2
        "0B837A5E560A29A2327B575F29B4BE8BAEF4BC947FCC2ED4F3264BC434309381"  // y2
    };

    // Ожидаемые/исходные точки на кривой Эдвардса
    std::vector<std::string> test_nums_edv_1 {
        "000000000000000000000000000000000000000000000000000000000000000D", // u1
        "60CA1E32AA475B348488C38FAB07649CE7EF8DBE87F22E81F92B2592DBA300E7"  // v1
    };
    std::vector<std::string> test_nums_edv_2 {
        "F6870D679448AE3E512AEB35B000E44C35B4758E9CE0A6EDB374F7D4D6E092B9", // u2
        "18C8D703E7FA38AA7330BD29659AB19660A732D31E359363C8CE62FFAECA5592"  // v2
    };

    bool all_tests_passed = true;

    cout << "=== ТЕСТ 1: Преобразование Вейерштрасс -> Эдвардс ===" << endl;

    cout << "--- Тестовый набор #1.1 (Базовая точка) ---" << endl;
    Digit x1_vey[CD], y1_vey[CD];
    StringToNumber(test_nums_vey_1[0], x1_vey);
    StringToNumber(test_nums_vey_1[1], y1_vey); 
    edv_points res1_edv = VeyToEdv(x1_vey, y1_vey);

    if (NumToStringDigit(res1_edv.u) == test_nums_edv_1[0] && NumToStringDigit(res1_edv.v) == test_nums_edv_1[1]) {
        cout << "  Результат: УСПЕШНО" << endl;
    } else {
        cout << "  Результат: ПРОВАЛЕНО!" << endl;
        all_tests_passed = false;
    }

    cout << "--- Тестовый набор #1.2 (Произвольная точка) ---" << endl;
    Digit x2_vey[CD], y2_vey[CD];
    StringToNumber(test_nums_vey_2[0], x2_vey); 
    StringToNumber(test_nums_vey_2[1], y2_vey); 
    edv_points res2_edv = VeyToEdv(x2_vey, y2_vey);
    
    if (NumToStringDigit(res2_edv.u) == test_nums_edv_2[0] && NumToStringDigit(res2_edv.v) == test_nums_edv_2[1]) {
        cout << "  Результат: УСПЕШНО" << endl;
    } else {
        cout << "  Результат: ПРОВАЛЕНО!" << endl;
        all_tests_passed = false;
    }
    cout << endl;

    cout << "=== ТЕСТ 2: Преобразование Эдвардс -> Вейерштрасс ===" << endl;
    
    cout << "--- Тестовый набор #2.1 (Базовая точка) ---" << endl;
    Digit u1_edv[CD], v1_edv[CD];
    StringToNumber(test_nums_edv_1[0], u1_edv);
    StringToNumber(test_nums_edv_1[1], v1_edv); 
    vey_points res1_vey = EdvToVey(u1_edv, v1_edv);

    if (NumToStringDigit(res1_vey.x) == test_nums_vey_1[0] && NumToStringDigit(res1_vey.y) == test_nums_vey_1[1]) {
        cout << "  Результат: УСПЕШНО" << endl;
    } else {
        cout << "  Результат: ПРОВАЛЕНО!" << endl;
        all_tests_passed = false;
    }

    cout << "--- Тестовый набор #2.2 (Произвольная точка) ---" << endl;
    Digit u2_edv[CD], v2_edv[CD];
    StringToNumber(test_nums_edv_2[0], u2_edv); 
    StringToNumber(test_nums_edv_2[1], v2_edv); 
    vey_points res2_vey = EdvToVey(u2_edv, v2_edv);
    
    if (NumToStringDigit(res2_vey.x) == test_nums_vey_2[0] && NumToStringDigit(res2_vey.y) == test_nums_vey_2[1]) {
        cout << "  Результат: УСПЕШНО" << endl;
    } else {
        cout << "  Результат: ПРОВАЛЕНО!" << endl;
        all_tests_passed = false;
    }
    cout << endl;

    if (all_tests_passed) {
        cout << "=================================================" << endl;
        cout << "ИТОГ: Все тесты преобразования координат пройдены!" << endl;
        cout << "=================================================" << endl;
    } else {
        cout << "=====================================================" << endl;
        cout << "ИТОГ: Обнаружены ошибки в преобразовании координат." << endl;
        cout << "=====================================================" << endl;
    }
}

bool process_and_print_single_point(const std::string& x_str, const std::string& y_str, const std::string& point_name)
{
    vey_points P_vey_initial;
    StringToNumber(x_str, P_vey_initial.x);
    StringToNumber(y_str, P_vey_initial.y);

    edv_points P_edv_intermediate = VeyToEdv(P_vey_initial.x, P_vey_initial.y);
    vey_points P_vey_final = EdvToVey(P_edv_intermediate.u, P_edv_intermediate.v);
   
    cout << "--- " << point_name << " ---" << endl;
    
    cout << "  [1] Исходная точка (Вейерштрасс):" << endl;
    cout << "    x = " << x_str << endl;
    cout << "    y = " << y_str << endl << endl;

    cout << "  [2] Промежуточная точка (Эдвардс):" << endl;
    cout << "    u = " << NumToStringDigit(P_edv_intermediate.u) << endl;
    cout << "    v = " << NumToStringDigit(P_edv_intermediate.v) << endl << endl;

    cout << "  [3] Конечная точка (снова Вейерштрасс):" << endl;
    cout << "    x' = " << NumToStringDigit(P_vey_final.x) << endl;
    cout << "    y' = " << NumToStringDigit(P_vey_final.y) << endl;

    
    bool is_success = Equal(P_vey_initial.x, P_vey_final.x) && 
                      Equal(P_vey_initial.y, P_vey_final.y);

    if (is_success) {
        cout << "  Проверка: УСПЕШНО (Исходная и конечная точки совпадают)" << endl;
    } else {
        cout << "  Проверка: ПРОВАЛЕНО!" << endl;
    }
    
    return is_success;
}
void compute_all_variants_ed()
{
    if (ed_variants.empty()) {
        cout << "[ИНФО] Вектор 'ed_variants' пуст. Демонстрация невозможна." << endl;
        return;
    }

    for (size_t i = 0; i < ed_variants.size(); ++i)
    {
       
        const std::string& x_A_str = ed_variants[i][0];
        const std::string& y_A_str = ed_variants[i][1];
        const std::string& x_B_str = ed_variants[i][2];
        const std::string& y_B_str = ed_variants[i][3];

        std::string variant_name = "Вариант #" + std::to_string(i + 1);
        cout << "========================== " << variant_name << " ==========================" << endl;

        process_and_print_single_point(x_A_str, y_A_str, "Точка А");
        cout << "--------------------------------------------------------" << endl;

        process_and_print_single_point(x_B_str, y_B_str, "Точка B");

        cout << "================================================================" << endl << endl;
    }
}