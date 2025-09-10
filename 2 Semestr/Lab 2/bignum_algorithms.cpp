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

edv_points VeyToEdv(Digit x[], Digit y[]){
    edv_points Res;
    Digit *u = new Digit[CD];
    Digit *v = new Digit[CD];
    Digit *y_obr = new Digit[CD];
    Digit *x_minus_t = new Digit[CD];
    Digit *x_minus_t_minus_s = new Digit[CD];
    Digit *x_minus_t_plus_s = new Digit[CD];
    Digit *x_minus_t_plus_s_obr = new Digit[CD];
    Sub(x,g_t,x_minus_t);
    Sub(x_minus_t,g_s,x_minus_t_minus_s);
    Add(x_minus_t,g_s,x_minus_t_plus_s);
    rev(x_minus_t_plus_s,x_minus_t_plus_s_obr);
    rev(y,y_obr);
    Mult(x_minus_t_minus_s,x_minus_t_plus_s_obr,v);
    Mult(x_minus_t,y_obr,u);
    Assig(u,Res.u);
    Assig(v,Res.v);
    //std::cout<<"U: "<<NumToStringDigit(u)<<std::endl;
    //std::cout<<"V: "<<NumToStringDigit(v)<<std::endl;
    delete[] u;
    delete[] v;
    delete[] y_obr;
    delete[] x_minus_t;
    delete[] x_minus_t_minus_s;
    delete[] x_minus_t_plus_s;
    delete[] x_minus_t_plus_s_obr;
    return Res;
}
vey_points EdvToVey(Digit u[], Digit v[]){
    vey_points Res;
    Digit *x = new Digit[CD];
    Digit *y = new Digit[CD];
    Digit *v_plus_1 = new Digit[CD];
    Digit *v_minus_1 = new Digit[CD];
    Digit *s_times_v_plus_1 = new Digit[CD];
    Digit *u_times_v_minus_1 = new Digit[CD];
    Digit *v_minus_1_obr = new Digit[CD];
    Digit *u_times_v_minus_1_obr = new Digit[CD];
    Digit *partial_x= new Digit[CD];
    Add(g_e,v,v_plus_1);
    Sub(g_e,v,v_minus_1);
    Mult(g_s,v_plus_1,s_times_v_plus_1);
    Mult(u,v_minus_1,u_times_v_minus_1);
    rev(v_minus_1,v_minus_1_obr);
    rev(u_times_v_minus_1,u_times_v_minus_1_obr);
    Mult(s_times_v_plus_1,v_minus_1_obr,partial_x);
    Add(partial_x,g_t,x);
    Mult(s_times_v_plus_1,u_times_v_minus_1_obr,y);
    Assig(x,Res.x);
    Assig(y,Res.y);
    //std::cout<<"X: "<<NumToStringDigit(x)<<std::endl;
    //std::cout<<"Y: "<<NumToStringDigit(y)<<std::endl;
    delete[] x;
    delete[] y;
    delete[] v_plus_1;
    delete[] v_minus_1;
    delete[] s_times_v_plus_1;
    delete[] u_times_v_minus_1;
    delete[] v_minus_1_obr;
    delete[] u_times_v_minus_1_obr;
    delete[] partial_x;
    return Res;
}