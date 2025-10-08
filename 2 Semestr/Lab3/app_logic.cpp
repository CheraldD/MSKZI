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
void run_add_test(
    const std::string& x1_str, const std::string& y1_str,
    const std::string& x2_str, const std::string& y2_str,
    const std::string& x_expected_str, const std::string& y_expected_str,
    const std::string& test_name)
{
    std::cout << "--- " << test_name << " ---" << std::endl;

    // Вывод входных данных для конкретной операции
    std::cout << "  Входные данные:" << std::endl;
    std::cout << "    P1.x = " << x1_str << std::endl;
    std::cout << "    P1.y = " << y1_str << std::endl;
    // Для операции удвоения P1 и P2 будут одинаковыми
    if (x1_str != x2_str) {
        std::cout << "    P2.x = " << x2_str << std::endl;
        std::cout << "    P2.y = " << y2_str << std::endl;
    }
    std::cout << "  -----------------------------------" << std::endl;

    // 1. Подготовка входных точек
    vey_points p1, p2;
    StringToNumber(x1_str, p1.x);
    StringToNumber(y1_str, p1.y);
    StringToNumber(x2_str, p2.x);
    StringToNumber(y2_str, p2.y);

    // 2. Выполнение операции сложения
    Digit x_res_dummy[CD], y_res_dummy[CD];
    vey_points result = Add_Vey(p1, p2, x_res_dummy, y_res_dummy);

    // 3. Преобразование результата в строки
    std::string x_calculated_str = NumToStringDigit(result.x);
    std::string y_calculated_str = NumToStringDigit(result.y);

    // 4. Сравнение и вывод результатов
    std::cout << "  Результат вычислений:" << std::endl;
    std::cout << "    Ожидаемый X: " << x_expected_str << std::endl;
    std::cout << "    Полученный X:  " << x_calculated_str << std::endl;
    std::cout << "    Ожидаемый Y: " << y_expected_str << std::endl;
    std::cout << "    Полученный Y:  " << y_calculated_str << std::endl;

    bool success = (x_calculated_str == x_expected_str) && (y_calculated_str == y_expected_str);

    if (success) {
        std::cout << "  Проверка: УСПЕШНО" << std::endl << std::endl;
    } else {
        std::cout << "  Проверка: ПРОВАЛЕНО!" << std::endl << std::endl;
    }
}


// Основная функция для запуска всех тестов из скриншота
// (ДОБАВЛЕН ВЫВОД ИСХОДНЫХ ДАННЫХ ДЛЯ КАЖДОГО ПРИМЕРА)
void test_add_points_vey() {
    std::cout << "============================================================" << std::endl;
    std::cout << "         ТЕСТИРОВАНИЕ ОПЕРАЦИЙ НА КРИВОЙ ВЕЙЕРШТРАССА        " << std::endl;
    std::cout << "============================================================" << std::endl << std::endl;

    // --- Контрольный пример 1 ---
    std::cout << "--------------- Контрольный пример 1 ---------------" << std::endl;
    std::string a1_x = "91E38443A5E82C0D880923425712B2BB658B9196932E02C78B2582FE742DAA28";
    std::string a1_y = "32879423AB1A0375895786C4BB46E9565FDE0B5344766740AF268ADB32322E5C";
    std::string b1_x = "E8C6740E58D616CA220DB7DA0D9C3E19B53E86E38BF3E8747774631452EC174C";
    std::string b1_y = "0B837A5E560A29A2327B575F29B4BE8BAEF4BC947FCC2ED4F3264BC434309381";
    std::string c1_x = "5655981FBEA13E5803B5146892A00CA5F59BBB358A24E5D0F4816B46FD872DB0";
    std::string c1_y = "496B8E94237A36A4B7BC6990CFC9AA0ECC4FD00B23189477C63ABD139B29B050";
    std::string d1_x = "E8C6740E58D616CA220DB7DA0D9C3E19B53E86E38BF3E8747774631452EC174C";
    std::string d1_y = "0B837A5E560A29A2327B575F29B4BE8BAEF4BC947FCC2ED4F3264BC434309381";
    
    // Вывод общих данных для примера
    std::cout << "Исходные данные примера:" << std::endl;
    std::cout << "  Точка А1.x: " << a1_x << std::endl;
    std::cout << "  Точка А1.y: " << a1_y << std::endl;
    std::cout << "  Точка B1.x: " << b1_x << std::endl;
    std::cout << "  Точка B1.y: " << b1_y << std::endl << std::endl;

    run_add_test(a1_x, a1_y, b1_x, b1_y, c1_x, c1_y, "Тест C1 = A1 + B1 (сложение)");
    run_add_test(a1_x, a1_y, a1_x, a1_y, d1_x, d1_y, "Тест D1 = 2 * A1 (удвоение)");

    // --- Контрольный пример 2 ---
    std::cout << "--------------- Контрольный пример 2 ---------------" << std::endl;
    std::string a2_x = "1D40C1676805F9518BE1FB4C7AE460D3608581E477B07C2D0E7E1E265A6B3347";
    std::string a2_y = "8291ACE380FD8832BACA29613AB5626C302D13348F204D727D30897A8E1F8934";
    std::string b2_x = "C9CBAEEFAABC51147130FC6FA1ADBE72140E35C5911B7D54B12BEECDF5848943";
    std::string b2_y = "3C2E34CDFA1E6E76D6CC57EC871A26FB5B23D01C540E6F0D8F77F4D81FE3F613";
    std::string c2_x = "644C9718F80B40D73557912BF11E538B4B4C1AFDD011B3B54C9FBE67011F60D9";
    std::string c2_y = "298410A9D8B4D12C131ECA5AC158A14A96802B112EF903615777375B218949DA";
    std::string d2_x = "1B92F7A3DBDC941DBB844197A79815CD4C93196100EA4FD3E226B9DD7597A3FE";
    std::string d2_y = "394D654FC8303797FD38D4D80AABEBE0D4E7B1BAABF66A6CA057C0DF4B3366C4";
    
    // Вывод общих данных для примера
    std::cout << "Исходные данные примера:" << std::endl;
    std::cout << "  Точка А2.x: " << a2_x << std::endl;
    std::cout << "  Точка А2.y: " << a2_y << std::endl;
    std::cout << "  Точка B2.x: " << b2_x << std::endl;
    std::cout << "  Точка B2.y: " << b2_y << std::endl << std::endl;

    run_add_test(a2_x, a2_y, b2_x, b2_y, c2_x, c2_y, "Тест C2 = A2 + B2 (сложение)");
    run_add_test(a2_x, a2_y, a2_x, a2_y, d2_x, d2_y, "Тест D2 = 2 * A2 (удвоение)");

    std::cout << "============================================================" << std::endl;
    std::cout << "                     ТЕСТИРОВАНИЕ ЗАВЕРШЕНО                   " << std::endl;
    std::cout << "============================================================" << std::endl;
}

void test_variant_20_addition()
{
    std::cout << "============================================================" << std::endl;
    std::cout << "        СЛОЖЕНИЕ И УДВОЕНИЕ ТОЧЕК (ВАРИАНТ 20)      " << std::endl;
    std::cout << "============================================================" << std::endl << std::endl;

    // --- Данные из Варианта 20 ---
    std::string ax_str = "7C62F4FF84427D9C84074D745167BF0A1E1B5B2FA400836B4B991BEC29BF999F";
    std::string ay_str = "08EE3D6E617B30D21ACDDEAEA988A09A02E8FAE6FE1B498E2EFA951E9EB1B0F2";

    std::string bx_str = "4AFC8D2A703BD0ED2F55F741FC12AD71B8CFD2D78B70758CBF844CE79E83781F";
    std::string by_str = "FC5C10486F70C07CFFE06F1C64A094028A574E85AC112CEFB94A0772D2381FEC";
    
    // 1. Вывод исходных данных
    std::cout << "Исходные данные:" << std::endl;
    std::cout << "  Точка A.x: " << ax_str << std::endl;
    std::cout << "  Точка A.y: " << ay_str << std::endl;
    std::cout << "  Точка B.x: " << bx_str << std::endl;
    std::cout << "  Точка B.y: " << by_str << std::endl << std::endl;

    // 2. Подготовка точек для вычислений
    vey_points pointA, pointB;
    StringToNumber(ax_str, pointA.x);
    StringToNumber(ay_str, pointA.y);
    StringToNumber(bx_str, pointB.x);
    StringToNumber(by_str, pointB.y);

    // --- Сложение точек C = A + B ---
    // 3. Вызов функции сложения
    // x_res и y_res не используются для возврата значения, но требуются сигнатурой
    Digit dummy_x[CD], dummy_y[CD]; 
    vey_points result_point = Add_Vey(pointA, pointB, dummy_x, dummy_y);

    // 4. Преобразование результата в строку для вывода
    std::string result_x_str = NumToStringDigit(result_point.x);
    std::string result_y_str = NumToStringDigit(result_point.y);

    // 5. Вывод результата
    std::cout << "Результат сложения C = A + B:" << std::endl;
    std::cout << "  Точка C.x: " << result_x_str << std::endl;
    std::cout << "  Точка C.y: " << result_y_str << std::endl << std::endl;

    // --- УДВОЕНИЕ ТОЧКИ A (D = 2 * A) ---
    std::cout << "------------------------------------------------------------" << std::endl << std::endl;

    // 1. Вызов функции удвоения (сложение точки с самой собой)
    vey_points doubled_point_A = Add_Vey(pointA, pointA, dummy_x, dummy_y);

    // 2. Преобразование результата в строку для вывода
    std::string doubled_ax_str = NumToStringDigit(doubled_point_A.x);
    std::string doubled_ay_str = NumToStringDigit(doubled_point_A.y);
    
    // 3. Вывод результата удвоения
    std::cout << "Результат удвоения D = 2 * A:" << std::endl;
    std::cout << "  Точка D.x: " << doubled_ax_str << std::endl;
    std::cout << "  Точка D.y: " << doubled_ay_str << std::endl << std::endl;
    
    std::cout << "============================================================" << std::endl;
    std::cout << "                       ВЫЧИСЛЕНИЯ ЗАВЕРШЕНЫ                    " << std::endl;
    std::cout << "============================================================" << std::endl;
}
void run_edv_add_test_from_vey(
    const std::string& x1_str, const std::string& y1_str,
    const std::string& x2_str, const std::string& y2_str,
    const std::string& x_expected_str, const std::string& y_expected_str,
    const std::string& test_name)
{
    std::cout << "--- " << test_name << " (через форму Эдвардса) ---" << std::endl;

    // --- ЭТАП 1: Подготовка и конвертация Вейерштрасс -> Эдвардс ---
    vey_points p1_vey, p2_vey;
    StringToNumber(x1_str, p1_vey.x);
    StringToNumber(y1_str, p1_vey.y);
    StringToNumber(x2_str, p2_vey.x);
    StringToNumber(y2_str, p2_vey.y);
    
    edv_points p1_edv = VeyToEdv(p1_vey.x, p1_vey.y);
    edv_points p2_edv = VeyToEdv(p2_vey.x, p2_vey.y);

    std::cout << "  [1] Промежуточные точки (Эдвардс):" << std::endl;
    std::cout << "      P1.u: " << NumToStringDigit(p1_edv.u) << std::endl;
    std::cout << "      P2.u: " << NumToStringDigit(p2_edv.u) << std::endl;

    // --- ЭТАП 2: Сложение точек в форме Эдвардса ---
    Digit result_edv_u[CD];
    Digit result_edv_v[CD];
    Add_edv(p1_edv, p2_edv, result_edv_u, result_edv_v);

    std::cout << "  [2] Результат сложения (Эдвардс):" << std::endl;
    std::cout << "      C.u: " << NumToStringDigit(result_edv_u) << std::endl;

    // --- ЭТАП 3: Обратная конвертация Эдвардс -> Вейерштрасс ---
    vey_points final_result_vey = EdvToVey(result_edv_u, result_edv_v);

    // --- ЭТАП 4: Сравнение и вывод ---
    std::string x_calculated_str = NumToStringDigit(final_result_vey.x);
    std::string y_calculated_str = NumToStringDigit(final_result_vey.y);
    
    std::cout << "  [3] Итоговый результат (Вейерштрасс):" << std::endl;
    std::cout << "      Ожидаемый X: " << x_expected_str << std::endl;
    std::cout << "      Полученный X:  " << x_calculated_str << std::endl;
    std::cout << "      Ожидаемый Y: " << y_expected_str << std::endl;
    std::cout << "      Полученный Y:  " << y_calculated_str << std::endl;

    bool success = (x_calculated_str == x_expected_str) && (y_calculated_str == y_expected_str);

    if (success) {
        std::cout << "  Проверка: УСПЕШНО" << std::endl << std::endl;
    } else {
        std::cout << "  Проверка: ПРОВАЛЕНО!" << std::endl << std::endl;
    }
}


// Адаптированная главная тестовая функция
void test_add_points_edv_from_vey() {
    std::cout << "============================================================" << std::endl;
    std::cout << "     ТЕСТИРОВАНИЕ ОПЕРАЦИЙ ЧЕРЕЗ КОНВЕРТАЦИЮ В ЭДВАРДСА      " << std::endl;
    std::cout << "============================================================" << std::endl << std::endl;

    // --- Контрольный пример 1 ---
    std::cout << "--------------- Контрольный пример 1 ---------------" << std::endl;
    std::string a1_x = "91E38443A5E82C0D880923425712B2BB658B9196932E02C78B2582FE742DAA28";
    std::string a1_y = "32879423AB1A0375895786C4BB46E9565FDE0B5344766740AF268ADB32322E5C";
    std::string b1_x = "E8C6740E58D616CA220DB7DA0D9C3E19B53E86E38BF3E8747774631452EC174C";
    std::string b1_y = "0B837A5E560A29A2327B575F29B4BE8BAEF4BC947FCC2ED4F3264BC434309381";
    std::string c1_x = "5655981FBEA13E5803B5146892A00CA5F59BBB358A24E5D0F4816B46FD872DB0";
    std::string c1_y = "496B8E94237A36A4B7BC6990CFC9AA0ECC4FD00B23189477C63ABD139B29B050";
    std::string d1_x = "E8C6740E58D616CA220DB7DA0D9C3E19B53E86E38BF3E8747774631452EC174C";
    std::string d1_y = "0B837A5E560A29A2327B575F29B4BE8BAEF4BC947FCC2ED4F3264BC434309381";
    
    // Вызываем нового помощника
    run_edv_add_test_from_vey(a1_x, a1_y, b1_x, b1_y, c1_x, c1_y, "Тест C1 = A1 + B1");
    run_edv_add_test_from_vey(a1_x, a1_y, a1_x, a1_y, d1_x, d1_y, "Тест D1 = 2 * A1");

    // --- Контрольный пример 2 ---
    std::cout << "--------------- Контрольный пример 2 ---------------" << std::endl;
    std::string a2_x = "1D40C1676805F9518BE1FB4C7AE460D3608581E477B07C2D0E7E1E265A6B3347";
    std::string a2_y = "8291ACE380FD8832BACA29613AB5626C302D13348F204D727D30897A8E1F8934";
    std::string b2_x = "C9CBAEEFAABC51147130FC6FA1ADBE72140E35C5911B7D54B12BEECDF5848943";
    std::string b2_y = "3C2E34CDFA1E6E76D6CC57EC871A26FB5B23D01C540E6F0D8F77F4D81FE3F613";
    std::string c2_x = "644C9718F80B40D73557912BF11E538B4B4C1AFDD011B3B54C9FBE67011F60D9";
    std::string c2_y = "298410A9D8B4D12C131ECA5AC158A14A96802B112EF903615777375B218949DA";
    std::string d2_x = "1B92F7A3DBDC941DBB844197A79815CD4C93196100EA4FD3E226B9DD7597A3FE";
    std::string d2_y = "394D654FC8303797FD38D4D80AABEBE0D4E7B1BAABF66A6CA057C0DF4B3366C4";

    // Вызываем нового помощника
    run_edv_add_test_from_vey(a2_x, a2_y, b2_x, b2_y, c2_x, c2_y, "Тест C2 = A2 + B2");
    run_edv_add_test_from_vey(a2_x, a2_y, a2_x, a2_y, d2_x, d2_y, "Тест D2 = 2 * A2");

    std::cout << "============================================================" << std::endl;
    std::cout << "                     ТЕСТИРОВАНИЕ ЗАВЕРШЕНО                   " << std::endl;
    std::cout << "============================================================" << std::endl;
}
void test_edwards_addition_for_variant_20()
{
    std::cout << "============================================================" << std::endl;
    std::cout << "    ТЕСТ: СЛОЖЕНИЕ (ЭДВАРДС) С КОНВЕРТАЦИЕЙ (ВАРИАНТ 20)    " << std::endl;
    std::cout << "============================================================" << std::endl << std::endl;

    // --- Данные из Варианта 20 (вход в форме Вейерштрасса) ---
    std::string ax_str = "7C62F4FF84427D9C84074D745167BF0A1E1B5B2FA400836B4B991BEC29BF999F";
    std::string ay_str = "08EE3D6E617B30D21ACDDEAEA988A09A02E8FAE6FE1B498E2EFA951E9EB1B0F2";

    std::string bx_str = "4AFC8D2A703BD0ED2F55F741FC12AD71B8CFD2D78B70758CBF844CE79E83781F";
    std::string by_str = "FC5C10486F70C07CFFE06F1C64A094028A574E85AC112CEFB94A0772D2381FEC";

    std::cout << "[1] Исходные точки в форме Вейерштрасса:" << std::endl;
    std::cout << "    A.x: " << ax_str << std::endl;
    std::cout << "    A.y: " << ay_str << std::endl;
    std::cout << "    B.x: " << bx_str << std::endl;
    std::cout << "    B.y: " << by_str << std::endl << std::endl;

    // --- ЭТАП 1: Конвертация Вейерштрасс -> Эдвардс ---
    vey_points pointA_vey, pointB_vey;
    StringToNumber(ax_str, pointA_vey.x);
    StringToNumber(ay_str, pointA_vey.y);
    StringToNumber(bx_str, pointB_vey.x);
    StringToNumber(by_str, pointB_vey.y);

    edv_points pointA_edv = VeyToEdv(pointA_vey.x, pointA_vey.y);
    edv_points pointB_edv = VeyToEdv(pointB_vey.x, pointB_vey.y);

    std::cout << "[2] Точки после конвертации в форму Эдвардса:" << std::endl;
    std::cout << "    A.u: " << NumToStringDigit(pointA_edv.u) << std::endl;
    std::cout << "    A.v: " << NumToStringDigit(pointA_edv.v) << std::endl;
    std::cout << "    B.u: " << NumToStringDigit(pointB_edv.u) << std::endl;
    std::cout << "    B.v: " << NumToStringDigit(pointB_edv.v) << std::endl << std::endl;
    
    // --- ЭТАП 2: Сложение точек в форме Эдвардса ---
    Digit result_edv_u[CD];
    Digit result_edv_v[CD];
    Add_edv(pointA_edv, pointB_edv, result_edv_u, result_edv_v);

    std::cout << "[3] Результат сложения C = A + B в форме Эдвардса:" << std::endl;
    std::cout << "    C.u: " << NumToStringDigit(result_edv_u) << std::endl;
    std::cout << "    C.v: " << NumToStringDigit(result_edv_v) << std::endl << std::endl;

    // --- ЭТАП 3: Обратная конвертация Эдвардс -> Вейерштрасс ---
    vey_points final_result_vey = EdvToVey(result_edv_u, result_edv_v);

    std::cout << "[4] Итоговый результат после обратной конвертации в Вейерштрасса:" << std::endl;
    std::cout << "    C.x: " << NumToStringDigit(final_result_vey.x) << std::endl;
    std::cout << "    C.y: " << NumToStringDigit(final_result_vey.y) << std::endl << std::endl;
    
    std::cout << "============================================================" << std::endl;
    std::cout << "                       ВЫЧИСЛЕНИЯ ЗАВЕРШЕНЫ                    " << std::endl;
    std::cout << "============================================================" << std::endl;
}