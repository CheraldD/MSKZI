#include "Elleptic_Curve.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <clocale>
#include <limits>
#define CD 16
Digit g_p[CD], g_e[CD], g_s[CD], g_t[CD], g_h[CD], g_k[CD],
    g_d[CD], g_razn[CD], g_u[CD], g_v[CD], g_zero[CD], g_q[CD],
    g_p_1[CD];

using namespace std;
void test_euclid() { test(1); }
void test_ferma() { test(0); }

void displayMenu()
{
    system("clear");
    cout << "========================================================\n";
    cout << "     КРИПТОГРАФИЧЕСКИЕ ВЫЧИСЛЕНИЯ: ОБРАТНЫЙ ЭЛЕМЕНТ     \n";
    cout << "========================================================\n";
    cout << "  Методы, основанные на алгоритме Евклида:\n";
    cout << "    1. Тестовый запуск\n";
    cout << "    2. Вычисление для всех 40 вариантов\n";
    cout << "  Методы, основанные на теореме Ферма:\n";
    cout << "    3. Тестовый запуск\n";
    cout << "    4. Вычисление для всех 40 вариантов\n";
    cout << "  Сравнение производительности:\n";
    cout << "    5. Запустить тест производительности (1000 итераций)\n";
    cout << "--------------------------------------------------------\n";
    cout << "    0. Выход из программы\n";
    cout << "========================================================\n";
    cout << "Ваш выбор: ";
}

void pause_and_clear()
{
    cout << "\nНажмите Enter, чтобы вернуться в меню...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main()
{

    setlocale(LC_ALL, "");
    srand(time(NULL));
    Init();

    int choice;

    while (true)
    {
        displayMenu();
        cin >> choice;
        if (cin.fail())
        {
            cout << "\n[ОШИБКА] Пожалуйста, введите число из меню.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause_and_clear();
            continue;
        }

        cout << endl;

        switch (choice)
        {
        case 1:
            cout << "--- Запуск теста (Расширенный алгоритм Евклида) ---\n\n";
            test_euclid();
            break;
        case 2:
            cout << "--- Вычисление всех вариантов (Расширенный алгоритм Евклида) ---\n\n";
            compute_all_variants_eucl();
            break;
        case 3:
            cout << "--- Запуск теста (Модулярное возведение в степень) ---\n\n";
            test_ferma();
            break;
        case 4:
            cout << "--- Вычисление всех вариантов (Модулярное возведение в степень) ---\n\n";
            compute_all_variants_pow();
            break;
        case 5:
            runPerformanceTest();
            break;
        case 0:
            cout << "Завершение работы программы.\n";
            return 0;
        default:
            cout << "[ОШИБКА] Неверный пункт меню. Пожалуйста, попробуйте снова.\n";
            break;
        }
        pause_and_clear();
    }

    return 0;
}