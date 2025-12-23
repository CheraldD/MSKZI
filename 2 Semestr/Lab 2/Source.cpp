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

// Русифицированное меню
void displayMenu()
{
    system("clear");
    cout << "\n//==================================================//\n";
    cout << "//   ЛАБОРАТОРНАЯ: АРИФМЕТИКА ЭЛЛИПТИЧЕСКИХ КРИВЫХ   //\n";
    cout << "//==================================================//\n\n";

    cout << "  ОБРАТНЫЙ ЭЛЕМЕНТ ПО МОДУЛЮ\n";
    cout << "  ------------------------------------------\n";
    cout << "  [1] Алгоритм Евклида (Тест)\n";
    cout << "  [2] Алгоритм Евклида (Все варианты)\n";
    cout << "  [3] Малая теорема Ферма (Тест)\n";
    cout << "  [4] Малая теорема Ферма (Все варианты)\n";
    cout << "  [5] Сравнение производительности\n\n";

    cout << "  ПРЕОБРАЗОВАНИЕ КООРДИНАТ\n";
    cout << "  ------------------------------------------\n";
    cout << "  [6] Вейерштрасс <-> Эдвардс (Тест)\n";
    cout << "  [7] Вейерштрасс <-> Эдвардс (Все варианты)\n\n";
    
    cout << "  ------------------------------------------\n";
    cout << "  [0] Выход\n\n";
    cout << "> Ваш выбор: ";
}

// Русифицированная пауза
void pause_and_clear()
{
    cout << "\n\n... нажмите Enter для продолжения ...";
    // Очищаем буфер перед ожиданием нового ввода
    if (cin.peek() != '\n') {
       cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.get();
}


int main()
{
    setlocale(LC_ALL, "Russian"); // Установка русской локали
    srand(time(NULL));
    Init(); // Инициализация

    int choice;

    while (true)
    {
        displayMenu();
        cin >> choice;

        if (cin.fail() || cin.peek() != '\n')
        {
            cout << "\n\n  (!) Ошибка: Введите одно корректное число из меню.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause_and_clear();
            continue;
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер после успешного ввода

        cout << endl;
        
        switch (choice)
        {
        case 1:
            cout << ">> Выполняется: Алгоритм Евклида (Тест)\n\n";
            test_euclid();
            break;
        case 2:
            cout << ">> Выполняется: Алгоритм Евклида (Все варианты)\n\n";
            compute_all_variants_eucl();
            break;
        case 3:
            cout << ">> Выполняется: Малая теорема Ферма (Тест)\n\n";
            test_ferma();
            break;
        case 4:
            cout << ">> Выполняется: Малая теорема Ферма (Все варианты)\n\n";
            compute_all_variants_pow();
            break;
        case 5:
            cout << ">> Выполняется: Тест производительности\n\n";
            runPerformanceTest();
            break;
        case 6:
            cout << ">> Выполняется: Преобразование координат (Тест)\n\n";
            test_transit(); 
            break;
        case 7:
            cout << ">> Выполняется: Преобразование координат (Все варианты)\n\n";
            compute_all_variants_ed();
            break;
        case 0:
            cout << ">> Завершение программы. Удачи!\n";
            return 0;
        default:
            cout << "  (!) Ошибка: Неверный пункт меню. Попробуйте снова.\n";
            break;
        }
        pause_and_clear();
    }

    return 0;
}