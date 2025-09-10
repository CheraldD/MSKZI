#include "bignum_algorithms.h"
#include "Elleptic_Curve.h"
bool dlina(Digit elem[])
{
    for (int i = 0; i < CD; i++) // проходим по цифрам
    {
        if (elem[i] != 0)
        {
            return false;
        } // если встретилась
        // ненулевая цифра, то возвращаем false, иначе true
    }
    return true;
}
EVCL gcd(EVCL X)
{
    if (dlina(X.a2))
    {
        Assig(g_e, X.a2);
        Assig(g_zero, X.a3);
        return X;
    }
    EVCL params_for_next_call;
    Digit remainder[CD];
    Assig(X.a2, params_for_next_call.a1);
    Mod_Div(X.a1, X.a2, remainder);
    Assig(remainder, params_for_next_call.a2);
    EVCL prev_result = gcd(params_for_next_call);
    EVCL result;
    Assig(prev_result.a1, result.a1);
    Assig(prev_result.a3, result.a2);
    Digit *quotient = new Digit[CD];
    Digit *term = new Digit[CD];
    Int_Div(X.a1, X.a2, quotient);        
    Mult(quotient, prev_result.a3, term); 
    Sub(prev_result.a2, term, result.a3);
    delete[] quotient;
    delete[] term;
    return result;
}
void fast_power(Digit a[], const Digit step[],Digit res[])
{
   
    Assig(g_e, res);
    Digit bufer[CD];
    Assig(a, bufer);
    for (int i = 0; i <= 16 * CD - 1; i++) // Проходим по 256 битам числа
    {
        Digit current = step[(int)(i / 16)]; // Считаем текущую цифру
        if ((current >> (i % 16)) & 0x0001)
        { // Проверяем, что nекущий бит равен 1
            Mult(res, bufer, a); // Умножаем результирующую переменную на значение буфера
            Assig(a, res); // заносим результат в переменную res
        }
        Mult(bufer, bufer, a); // возводим значение буфера в квадрат
        Assig(a, bufer);
    }
}
void rev(Digit prym[], Digit obr[])
{
    EVCL A;            // Объявляется структура
    Assig(prym, A.a1); // Прямой элемент заносится первым  значением
    Assig(g_p, A.a2);  // Модуль заносится вторым и третим значением
    Assig(g_p, A.a3);
    A = gcd(A);       // Вызывается рекурсивная функция
    Assig(A.a2, obr); // Второй элемент в структуре – искомое значение
}
void rev_mod(Digit ch[], Digit res[])
{
    Digit p_minus_2[CD];
    Sub(g_p, g_e, p_minus_2);
    Sub(p_minus_2, g_e, p_minus_2);
    fast_power(ch, p_minus_2,res);
}