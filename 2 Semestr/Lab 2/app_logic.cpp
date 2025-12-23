#include "app_logic.h"
#include "bignum_algorithms.h"

// Русифицированный вывод результата
void printResult(const std::string &original_hex, const Digit inverse[], const std::string &title)
{
    if (!title.empty()) {
        cout << "● " << title << "\n";
    }
    cout << "  ВХОД : " << original_hex << "\n";
    cout << "  ВЫХОД: " << NumToStringDigit(inverse) << "\n";
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
        Digit pr[CD], obr[CD];
        StringToNumber(test_nums[i], pr);
        
        if(flag) rev(pr, obr);
        else rev_mod(pr, obr);
        
        printResult(test_nums[i], obr, "Тестовый случай #" + to_string(i + 1));
        
        if (results[i] == NumToStringDigit(obr)) {
            cout << "  СТАТУС: [OK]\n\n";
        } else {
            cout << "  СТАТУС: [СБОЙ]\n";
            cout << "  ОЖИДАЛОСЬ: " << results[i] << "\n\n";
        }
    }
}

void compute_all_variants_eucl()
{
    for (int i = 0; i < variants.size(); i += 2)
    {
        cout << "//======== ВАРИАНТ #" << (i / 2) + 1 << " ========//\n\n";
        compute_obr_eucl(variants[i], "Число 1");
        cout << "\n";
        compute_obr_eucl(variants[i + 1], "Число 2");
        cout << "\n";
    }
}
void compute_all_variants_pow()
{
    for (int i = 0; i < variants.size(); i += 2)
    {
        cout << "//======== ВАРИАНТ #" << (i / 2) + 1 << " ========//\n\n";
        compute_obr_pow(variants[i], "Число 1");
        cout << "\n";
        compute_obr_pow(variants[i + 1], "Число 2");
        cout << "\n";
    }
}

void runPerformanceTest()
{
    const int iterations = 1000;
    const int total_computations = iterations * variants.size();
    
    cout << "ТЕСТ ПРОИЗВОДИТЕЛЬНОСТИ\n";
    cout << "--------------------------------\n";
    cout << "Итераций на число: " << iterations << "\n";
    cout << "Всего вычислений:    " << total_computations << "\n";
    cout << "Выполняется тест, пожалуйста, подождите...\n\n";

    Digit pr[CD], obr[CD];
    auto start_euclid = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        for (const auto& num_str : variants) {
            StringToNumber(num_str, pr);
            rev(pr, obr); 
        }
    }
    auto end_euclid = std::chrono::high_resolution_clock::now();

    auto start_ferma = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        for (const auto& num_str : variants) {
            StringToNumber(num_str, pr);
            rev_mod(pr, obr); 
        }
    }
    auto end_ferma = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_euclid = end_euclid - start_euclid;
    std::chrono::duration<double, std::milli> duration_ferma = end_ferma - start_ferma;

    cout << "РЕЗУЛЬТАТЫ\n";
    cout << "--------------------------------\n";
    cout.precision(2); 
    cout << fixed;    
    cout << "  - Алгоритм Евклида.........: " << duration_euclid.count() << " мс\n";
    cout << "  - Малая теорема Ферма......: " << duration_ferma.count() << " мс\n\n";

    double diff = abs(duration_euclid.count() - duration_ferma.count());
    if (duration_euclid.count() < duration_ferma.count()) {
        cout << "  >> Вывод: Алгоритм Евклида оказался быстрее на " << diff << " мс.\n";
    } else {
        cout << "  >> Вывод: Метод на основе теоремы Ферма оказался быстрее на " << diff << " мс.\n";
    }
    cout << "--------------------------------\n";
}

void compute_obr_eucl(std::string pr_dig, std::string name)
{
    Digit pr[CD], obr[CD];
    StringToNumber(pr_dig, pr);
    rev(pr, obr);
    printResult(pr_dig, obr, name);
}

void compute_obr_pow(std::string pr_dig, std::string name){
    Digit pr[CD], obr[CD];
    StringToNumber(pr_dig, pr);
    rev_mod(pr, obr);
    printResult(pr_dig, obr, name);
}

void test_transit()
{
    std::vector<std::string> v_x1 = {"91E38443A5E82C0D880923425712B2BB658B9196932E02C78B2582FE742DAA28", "32879423AB1A0375895786C4BB46E9565FDE0B5344766740AF268ADB32322E5C"};
    process_and_print_single_point(v_x1[0], v_x1[1], "Базовая точка");
}

bool process_and_print_single_point(const std::string& x_str, const std::string& y_str, const std::string& point_name)
{
    vey_points P_vey_initial;
    StringToNumber(x_str, P_vey_initial.x);
    StringToNumber(y_str, P_vey_initial.y);

    edv_points P_edv_intermediate = VeyToEdv(P_vey_initial.x, P_vey_initial.y);
    vey_points P_vey_final = EdvToVey(P_edv_intermediate.u, P_edv_intermediate.v);
   
    cout << "\n> Обработка точки: " << point_name << "\n";
    cout << "-------------------------------------------\n";
    cout << "  (1) Исходная (Вейерштрасс):\n";
    cout << "      x: " << x_str << "\n";
    cout << "      y: " << y_str << "\n\n";

    cout << "  (2) Прямое -> Эдвардс:\n";
    cout << "      u: " << NumToStringDigit(P_edv_intermediate.u) << "\n";
    cout << "      v: " << NumToStringDigit(P_edv_intermediate.v) << "\n\n";

    cout << "  (3) Обратное -> Вейерштрасс:\n";
    cout << "      x': " << NumToStringDigit(P_vey_final.x) << "\n";
    cout << "      y': " << NumToStringDigit(P_vey_final.y) << "\n\n";

    bool is_success = Equal(P_vey_initial.x, P_vey_final.x) && 
                      Equal(P_vey_initial.y, P_vey_final.y);

    if (is_success) {
        cout << "  ПРОВЕРКА: [OK] Исходная и конечная точки совпадают.\n";
    } else {
        cout << "  ПРОВЕРКА: [СБОЙ] Точки не совпадают!\n";
    }
    cout << "-------------------------------------------\n";
    
    return is_success;
}

void compute_all_variants_ed()
{
    if (ed_variants.empty()) {
        cout << "[!] Внимание: Вектор 'ed_variants' пуст. Обработка невозможна.\n";
        return;
    }

    for (size_t i = 0; i < ed_variants.size(); ++i)
    {
       cout << "\n//================= ВАРИАНТ #" << i + 1 << " =================//\n";
        process_and_print_single_point(ed_variants[i][0], ed_variants[i][1], "Точка А");
        process_and_print_single_point(ed_variants[i][2], ed_variants[i][3], "Точка B");
    }
}