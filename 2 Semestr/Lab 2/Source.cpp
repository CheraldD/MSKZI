#include "Elleptic_Curve.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <clocale>
#include <limits>

using namespace std;

// Ваши вспомогательные функции
void test_euclid() { test(1); }
void test_ferma() { test(0); }

// Обновленная функция для отображения меню
void displayMenu()
{
    system("clear"); 
    cout << "=================================================================\n";
    cout << "           ЛАБОРАТОРНАЯ РАБОТА: ЭЛЛИПТИЧЕСКИЕ КРИВЫЕ            \n";
    cout << "=================================================================\n";
    cout << "  ЧАСТЬ 1: НАХОЖДЕНИЕ ОБРАТНОГО ЭЛЕМЕНТА\n";
    cout << "  --------------------------------------------\n";
    cout << "  Алгоритм Евклида:\n";
    cout << "    1. Тестовый запуск\n";
    cout << "    2. Вычисление для всех вариантов\n\n";
    cout << "  Теорема Ферма:\n";
    cout << "    3. Тестовый запуск\n";
    cout << "    4. Вычисление для всех вариантов\n\n";
    cout << "  Сравнение производительности:\n";
    cout << "    5. Запустить тест (1000 итераций)\n";
    cout << "\n";
    cout << "  ЧАСТЬ 2: ОПЕРАЦИИ С КРИВЫМИ\n";
    cout << "  --------------------------------------------\n";
    cout << "    6. Тест: Преобразование Вейерштрасс -> Эдвардс и обратно\n";
    cout << "    7. Все варианты: Преобразование Вейерштрасс -> Эдвардс и обратно\n";
    cout << "=================================================================\n";
    cout << "    0. Выход из программы\n";
    cout << "-----------------------------------------------------------------\n";
    cout << "Ваш выбор: ";
}

void pause_and_clear()
{
    cout << "\nНажмите Enter, чтобы вернуться в меню...";
    // Очищаем буфер ввода перед ожиданием
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));
    Init(); // Инициализация глобальных констант

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

        // Обновленный switch с новым case
        switch (choice)
        {
        case 1:
            cout << "--- Тест (Расширенный алгоритм Евклида) ---\n\n";
            test_euclid();
            break;
        case 2:
            cout << "--- Все варианты (Расширенный алгоритм Евклида) ---\n\n";
            compute_all_variants_eucl();
            break;
        case 3:
            cout << "--- Тест (Модулярное возведение в степень) ---\n\n";
            test_ferma();
            break;
        case 4:
            cout << "--- Все варианты (Модулярное возведение в степень) ---\n\n";
            compute_all_variants_pow();
            break;
        case 5:
            runPerformanceTest();
            break;
        case 6:
            cout << "--- Тест преобразования координат (Вейерштрасс -> Эдвардс) ---\n\n";
            test_transit(); 
            break;
        case 7:
            cout << "--- Все варианты преобразования координат (Вейерштрасс -> Эдвардс) ---\n\n";
            compute_all_variants_ed();
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