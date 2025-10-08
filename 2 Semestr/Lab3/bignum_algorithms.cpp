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
void fast_power(Digit a[], const Digit step[], Digit res[])
{

    Assig(g_e, res);
    Digit bufer[CD];
    Assig(a, bufer);
    for (int i = 0; i <= 16 * CD - 1; i++) // Проходим по 256 битам числа
    {
        Digit current = step[(int)(i / 16)]; // Считаем текущую цифру
        if ((current >> (i % 16)) & 0x0001)
        {                        // Проверяем, что nекущий бит равен 1
            Mult(res, bufer, a); // Умножаем результирующую переменную на значение буфера
            Assig(a, res);       // заносим результат в переменную res
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
    fast_power(ch, p_minus_2, res);
}

edv_points VeyToEdv(Digit x[], Digit y[])
{
    edv_points Res;
    Digit *u = new Digit[CD];
    Digit *v = new Digit[CD];
    Digit *y_obr = new Digit[CD];
    Digit *x_minus_t = new Digit[CD];
    Digit *x_minus_t_minus_s = new Digit[CD];
    Digit *x_minus_t_plus_s = new Digit[CD];
    Digit *x_minus_t_plus_s_obr = new Digit[CD];
    Sub(x, g_t, x_minus_t);
    Sub(x_minus_t, g_s, x_minus_t_minus_s);
    Add(x_minus_t, g_s, x_minus_t_plus_s);
    rev(x_minus_t_plus_s, x_minus_t_plus_s_obr);
    rev(y, y_obr);
    Mult(x_minus_t_minus_s, x_minus_t_plus_s_obr, v);
    Mult(x_minus_t, y_obr, u);
    Assig(u, Res.u);
    Assig(v, Res.v);
    // std::cout<<"U: "<<NumToStringDigit(u)<<std::endl;
    // std::cout<<"V: "<<NumToStringDigit(v)<<std::endl;
    delete[] u;
    delete[] v;
    delete[] y_obr;
    delete[] x_minus_t;
    delete[] x_minus_t_minus_s;
    delete[] x_minus_t_plus_s;
    delete[] x_minus_t_plus_s_obr;
    return Res;
}
vey_points EdvToVey(Digit u[], Digit v[])
{
    vey_points Res;
    Digit *x = new Digit[CD];
    Digit *y = new Digit[CD];
    Digit *v_plus_1 = new Digit[CD];
    Digit *v_minus_1 = new Digit[CD];
    Digit *s_times_v_plus_1 = new Digit[CD];
    Digit *u_times_v_minus_1 = new Digit[CD];
    Digit *v_minus_1_obr = new Digit[CD];
    Digit *u_times_v_minus_1_obr = new Digit[CD];
    Digit *partial_x = new Digit[CD];
    Add(g_e, v, v_plus_1);
    Sub(g_e, v, v_minus_1);
    Mult(g_s, v_plus_1, s_times_v_plus_1);
    Mult(u, v_minus_1, u_times_v_minus_1);
    rev(v_minus_1, v_minus_1_obr);
    rev(u_times_v_minus_1, u_times_v_minus_1_obr);
    Mult(s_times_v_plus_1, v_minus_1_obr, partial_x);
    Add(partial_x, g_t, x);
    Mult(s_times_v_plus_1, u_times_v_minus_1_obr, y);
    Assig(x, Res.x);
    Assig(y, Res.y);
    // std::cout<<"X: "<<NumToStringDigit(x)<<std::endl;
    // std::cout<<"Y: "<<NumToStringDigit(y)<<std::endl;
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
vey_points Add_Vey(
    vey_points p_1,
    vey_points p_2,
    Digit x_res[], /* Координата х итоговой точки */
    Digit y_res[]  /* Координата y итоговой точки */
)
{
    Digit *k1 = new Digit[CD];
    Digit *k2 = new Digit[CD];
    StringToNumber("0000000000000000000000000000000000000000000000000000000000000002", k1);
    StringToNumber("0000000000000000000000000000000000000000000000000000000000000003", k2);
    Digit *a = new Digit[CD];
    StringToNumber("C2173F1513981673AF4892C23035A27CE25E2013BF95AA33B22C656F277E7335", a);
    vey_points Res;
    if (Equal(p_1.x, p_2.x))
    {

        Digit *lambda_double = new Digit[CD];
        Digit *x1_square = new Digit[CD];
        Digit *y1_double = new Digit[CD];
        Mult(p_1.x, p_1.x, x1_square);
        Mult(p_1.y, k1, y1_double);
        Digit *y1_double_obr = new Digit[CD];
        rev(y1_double, y1_double_obr);
        Digit *x1_square_triple = new Digit[CD];
        Mult(x1_square, k2, x1_square_triple);
        Digit *x1_square_triple_plus_a = new Digit[CD];
        Add(x1_square_triple, a, x1_square_triple_plus_a);
        Mult(x1_square_triple_plus_a, y1_double_obr, lambda_double);

        Digit *x3 = new Digit[CD];
        Digit *y3 = new Digit[CD];
        Digit *x1_double = new Digit[CD];
        Digit *lambda_double_square = new Digit[CD];
        Digit *x1_minus_x3 = new Digit[CD];
        Digit *x1_minus_x3_times_lambda = new Digit[CD];
        Mult(p_1.x, k1, x1_double);
        Mult(lambda_double, lambda_double, lambda_double_square);
        Sub(lambda_double_square, x1_double, x3);
        Sub(p_1.x, x3, x1_minus_x3);
        Mult(x1_minus_x3, lambda_double, x1_minus_x3_times_lambda);
        Sub(x1_minus_x3_times_lambda, p_1.y, y3);
        Assig(x3, Res.x);
        Assig(y3, Res.y);

        // Освобождение памяти
        delete[] k1;
        delete[] k2;
        delete[] a;
        delete[] lambda_double;
        delete[] x1_square;
        delete[] y1_double;
        delete[] y1_double_obr;
        delete[] x1_square_triple;
        delete[] x1_square_triple_plus_a;
        delete[] x3;
        delete[] y3;
        delete[] x1_double;
        delete[] lambda_double_square;
        delete[] x1_minus_x3;
        delete[] x1_minus_x3_times_lambda;

        return Res;
    }
    else
    {
        Digit *lambda_add = new Digit[CD];
        Digit *y2_minus_y1 = new Digit[CD];
        Digit *x2_minus_x1 = new Digit[CD];
        Sub(p_2.y, p_1.y, y2_minus_y1);
        Sub(p_2.x, p_1.x, x2_minus_x1);
        Digit *x2_minus_x1_obr = new Digit[CD];
        rev(x2_minus_x1, x2_minus_x1_obr);
        Mult(y2_minus_y1, x2_minus_x1_obr, lambda_add);
        Digit *lambda_add_square = new Digit[CD];
        Digit *lambda_add_square_minus_x1 = new Digit[CD];
        Digit *x3 = new Digit[CD];
        Digit *y3 = new Digit[CD];
        Digit *x1_minus_x3 = new Digit[CD];
        Digit *x1_minus_x3_times_lambda = new Digit[CD];
        Mult(lambda_add, lambda_add, lambda_add_square);
        Sub(lambda_add_square, p_1.x, lambda_add_square_minus_x1);
        Sub(lambda_add_square_minus_x1, p_2.x, x3);
        Sub(p_1.x, x3, x1_minus_x3);
        Mult(lambda_add, x1_minus_x3, x1_minus_x3_times_lambda);
        Sub(x1_minus_x3_times_lambda, p_1.y, y3);
        Assig(x3, Res.x);
        Assig(y3, Res.y);

        delete[] k1;
        delete[] k2;
        delete[] a;
        delete[] lambda_add;
        delete[] y2_minus_y1;
        delete[] x2_minus_x1;
        delete[] x2_minus_x1_obr;
        delete[] lambda_add_square;
        delete[] lambda_add_square_minus_x1;
        delete[] x3;
        delete[] y3;
        delete[] x1_minus_x3;
        delete[] x1_minus_x3_times_lambda;

        return Res;
    }
}
void Add_edv(
    edv_points p_1,
    edv_points p_2,
    Digit x_res[], /* Координата х итоговой точки */
    Digit y_res[] /* Координата y итоговой точки */)
{
    Digit *u3 = new Digit[CD];
    Digit *v3 = new Digit[CD];

    Digit *u1_times_v2 = new Digit[CD];
    Digit *u2_times_v1 = new Digit[CD];
    Digit *u1_times_v2_plus_u2_times_v1 = new Digit[CD];
    Digit *u1_times_u2 = new Digit[CD];
    Digit *v1_times_v2 = new Digit[CD];
    Digit *u1_times_u2_times_v1_times_v2 = new Digit[CD];
    Digit *u1_times_u2_times_v1_times_v2_times_d = new Digit[CD];
    Digit *one_plus_u1_times_u2_times_v1_times_v2_times_d = new Digit[CD];
    Digit *one_plus_u1_times_u2_times_v1_times_v2_times_d_obr = new Digit[CD];

    Mult(p_1.u, p_2.v, u1_times_v2);
    Mult(p_2.u, p_1.v, u2_times_v1);
    Add(u1_times_v2, u2_times_v1, u1_times_v2_plus_u2_times_v1);
    Mult(p_1.u, p_2.u, u1_times_u2);
    Mult(p_1.v, p_2.v, v1_times_v2);
    Mult(u1_times_u2, v1_times_v2, u1_times_u2_times_v1_times_v2);
    Mult(g_d, u1_times_u2_times_v1_times_v2, u1_times_u2_times_v1_times_v2_times_d);
    Add(g_e, u1_times_u2_times_v1_times_v2_times_d, one_plus_u1_times_u2_times_v1_times_v2_times_d);
    rev(one_plus_u1_times_u2_times_v1_times_v2_times_d, one_plus_u1_times_u2_times_v1_times_v2_times_d_obr);
    Mult(u1_times_v2_plus_u2_times_v1, one_plus_u1_times_u2_times_v1_times_v2_times_d_obr, u3);

    Digit *one_minus_u1_times_u2_times_v1_times_v2_times_d = new Digit[CD];
    Digit *one_minus_u1_times_u2_times_v1_times_v2_times_d_obr = new Digit[CD];
    Sub(g_e, u1_times_u2_times_v1_times_v2_times_d, one_minus_u1_times_u2_times_v1_times_v2_times_d);
    rev(one_minus_u1_times_u2_times_v1_times_v2_times_d, one_minus_u1_times_u2_times_v1_times_v2_times_d_obr);

    Digit *v1_times_v2_minus_u1_times_u2 = new Digit[CD];
    Sub(v1_times_v2, u1_times_u2, v1_times_v2_minus_u1_times_u2);
    Mult(v1_times_v2_minus_u1_times_u2, one_minus_u1_times_u2_times_v1_times_v2_times_d_obr, v3);

    Assig(u3, x_res);
    Assig(v3, y_res);

    // Освобождение памяти
    delete[] u3;
    delete[] v3;
    delete[] u1_times_v2;
    delete[] u2_times_v1;
    delete[] u1_times_v2_plus_u2_times_v1;
    delete[] u1_times_u2;
    delete[] v1_times_v2;
    delete[] u1_times_u2_times_v1_times_v2;
    delete[] u1_times_u2_times_v1_times_v2_times_d;
    delete[] one_plus_u1_times_u2_times_v1_times_v2_times_d;
    delete[] one_plus_u1_times_u2_times_v1_times_v2_times_d_obr;
    delete[] one_minus_u1_times_u2_times_v1_times_v2_times_d;
    delete[] one_minus_u1_times_u2_times_v1_times_v2_times_d_obr;
    delete[] v1_times_v2_minus_u1_times_u2;
}