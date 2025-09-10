# Сводка по коду проекта

**Сгенерировано:** 2025-09-10 17:40:00

## `Cript.cpp`

```cpp
#include "Cript.h"
#define CD 16

/*--------------------------------------------------------
Преобразование строки в число и обратно
--------------------------------------------------------*/
Digit hexStringToInt(string hex_pred)
{
	Digit res = 0;
	int deg;
	for (int i = 0; i < hex_pred.size(); i++)
	{
		if (hex_pred[hex_pred.size() - 1 - i] >= '0' && hex_pred[hex_pred.size() - 1 - i] <= '9')
		{
			deg = hex_pred[hex_pred.size() - 1 - i] - '0';
			res += deg * pow(16, i);
		}
		else
			switch ((hex_pred[hex_pred.size() - 1 - i]))
			{
			case ('A'):
				deg = 10;
				res += deg * pow(16, i);
				break;
			case ('B'):
				deg = 11;
				res += deg * pow(16, i);
				break;
			case ('C'):
				deg = 12;
				res += deg * pow(16, i);
				break;
			case ('D'):
				deg = 13;
				res += deg * pow(16, i);
				break;
			case ('E'):
				deg = 14;
				res += deg * pow(16, i);
				break;
			case ('F'):
				deg = 15;
				res += deg * pow(16, i);
				break;
			case ('a'):
				deg = 10;
				res += deg * pow(16, i);
				break;
			case ('b'):
				deg = 11;
				res += deg * pow(16, i);
				break;
			case ('c'):
				deg = 12;
				res += deg * pow(16, i);
				break;
			case ('d'):
				deg = 13;
				res += deg * pow(16, i);
				break;
			case ('e'):
				deg = 14;
				res += deg * pow(16, i);
				break;
			case ('f'):
				deg = 15;
				res += deg * pow(16, i);
				break;
			}
	}
	return res;
}
void StringToNumber(
	string str, /*Преобразуемая строка*/
	Digit Res[] /*Получаемое число*/
)
{
	for (int i = 0; i < CD; i++)
		Res[CD - 1 - i] = hexStringToInt(str.substr(i * 4, 4));
}
string NumToStringDigit(
	const Digit Numb[] /*Инвертируемое число*/
)
{
	stringstream srt;
	for (int i = 0; i < CD; i++)
		srt << setfill('0') << setw(4) << hex << Numb[CD - 1 - i];
	return srt.str();
}
/*--------------------------------------------------------
Инициализация констант
--------------------------------------------------------*/
void Init() {
	StringToNumber("7e7e82520f9f015faa1d0f18c14ab9fb35188275da3fd94206b74f34a48e0ecd", g_s); //s=(e-d) / 4
	StringToNumber("0100fe73f595ff158e974b44d478d9588744fe5c192ac47ea63075dce7a14aaa", g_t); //t=(e+d) / 6
	StringToNumber("7f7f80c60535007538b45a5d95c39353bc5d80d1f36a9dc0ace7c5118c2f5977", g_h); //t+s
	StringToNumber("7d7d83de1a09024a1b85c3d3ecd1e0a2add38419c11514c36086d957bcecc423", g_k); //s-t
	StringToNumber("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD97", g_p);
	StringToNumber("0000000000000000000000000000000000000000000000000000000000000001", g_e);
	StringToNumber("0605F6B7C183FA81578BC39CFAD518132B9DF62897009AF7E522C32D6DC7BFFB", g_d);
	StringToNumber("0000000000000000000000000000000000000000000000000000000000000269", g_razn);
	StringToNumber("000000000000000000000000000000000000000000000000000000000000000D", g_u);
	StringToNumber("60CA1E32AA475B348488C38FAB07649CE7EF8DBE87F22E81F92B2592DBA300E7", g_v);
	StringToNumber("0000000000000000000000000000000000000000000000000000000000000000", g_zero);
	StringToNumber("400000000000000000000000000000000FD8CDDFC87B6635C115AF556C360C67", g_q);
	StringToNumber("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD96", g_p_1);
}
/*--------------------------------------------------------
Операторы сравнения и присвоения
--------------------------------------------------------*/
void Assig(const Digit first[], Digit second[]) {
	for (int i = 0; i < CD; i++) {
		second[i] = first[i];
	}
}
bool Less(const Digit first[], const Digit second[]) {
	for (int i = 0; i < CD; i++)
	{
		if (first[CD - 1 - i] < second[CD - 1 - i])
			return true;
		if (first[CD - 1 - i] > second[CD - 1 - i])
			return false;
	}
	return false;
}
bool More(const Digit first[], const Digit second[]) {
	for (int i = 0; i < CD; i++)
	{
		if (first[CD - 1 - i] > second[CD - 1 - i])
			return true;
		if (first[CD - 1 - i] < second[CD - 1 - i])
			return false;
	}
	return false;
}
bool Equal(const Digit first[], const Digit second[]) {
	for (int i = 0; i < CD; i++)
	{
		if (first[CD - 1 - i] > second[CD - 1 - i])
			return false;
		if (first[CD - 1 - i] < second[CD - 1 - i])
			return false;
	}
	return true;
}
/*--------------------------------------------------------
Сложение длинных чисел (*pcf,Res) = first + second
--------------------------------------------------------*/
static void Add(
	Digit Res[], /* сумма (size цифр) */
	const Digit first[], /* первое слагаемое (size цифр) */
	const Digit second[], /* второе слагаемое (size цифр)*/
	Digit *pcf, /* флаг переноса (1 цифра), м.б. NULL */
	int size) /* размер чисел в цифрах */
{
	TwoDigit buf; /* для хранения промежуточного результата сложения */
	Digit cf = 0; /* для хранения промежуточного переноса */
	int i; /* идексная переменная цикла */
	for (i = 0; i < size; i++) /* организация цикла по i */
	{
		buf = (TwoDigit)first[i] + second[i] + cf;/* сложение i-х цифр и предыдущего переноса */
		Res[i] = LODIGIT(buf); /* i-я цифра Res - младшая цифра суммы */
		cf = HIDIGIT(buf); /* перенос - старшая цифра суммы */
	}
	if (pcf) *pcf = cf; /* если адрес pcf не 0, возвращаем перенос */
}
void Add( /* Сложение по модулю p*/
	const Digit first[], /* первое слагаемое (size цифр) */
	const Digit second[], /* второе слагаемое (size цифр)*/
	Digit Res[] /* сумма (size цифр) */
)
{
	TwoDigit buf; /* для хранения промежуточного результата сложения */
	Digit cf = 0; /* для хранения промежуточного переноса */
	int i; /* идексная переменная цикла */
	for (i = 0; i < CD; i++) /* организация цикла по i */
	{
		buf = (TwoDigit)first[i] + second[i] + cf;/* сложение i-х цифр и предыдущего переноса */
		Res[i] = LODIGIT(buf); /* i-я цифра Res - младшая цифра суммы */
		cf = HIDIGIT(buf); /* перенос - старшая цифра суммы */
	}
	if (cf!=0) {
		cf = 0;
		for (i = 0; i < CD; i++) /* организация цикла по i */
		{
			buf = (TwoDigit)Res[i] + g_razn[i] + cf;/* сложение i-х цифр и предыдущего переноса */
			Res[i] = LODIGIT(buf); /* i-я цифра Res - младшая цифра суммы */
			cf = HIDIGIT(buf); /* перенос - старшая цифра суммы */
		}
	}/* если адрес pcf не 0, возвращаем перенос */
}
void Add_q( /* Сложение по модулю p*/
	const Digit first[], /* первое слагаемое (size цифр) */
	const Digit second[], /* второе слагаемое (size цифр)*/
	Digit Res[] /* сумма (size цифр) */
)
{
	TwoDigit buf; /* для хранения промежуточного результата сложения */
	Digit cf = 0; /* для хранения промежуточного переноса */
	int i; /* идексная переменная цикла */
	for (i = 0; i < CD; i++) /* организация цикла по i */
	{
		buf = (TwoDigit)first[i] + second[i] + cf;/* сложение i-х цифр и предыдущего переноса */
		Res[i] = LODIGIT(buf); /* i-я цифра Res - младшая цифра суммы */
		cf = HIDIGIT(buf); /* перенос - старшая цифра суммы */
	}
	while (More(Res,g_q)) { 
		Digit *z = new Digit[CD];
		Sub(Res, g_q, z);
		Assig(z, Res);
		delete[] z;
	}
}



/*--------------------------------------------------------
Вычитание длинных чисел (*pcf,Res) = first - second
--------------------------------------------------------*/
static void Sub(
	Digit Res[], /* разность (size цифр) */
	const Digit first[], /* уменьшаемое (size цифр) */
	const Digit second[], /* вычитаемое (size цифр) */
	Digit *pcf, /* флаг заема разрядов (1 цифра), м.б. NULL */
	int size) /* размер чисел в цифрах */
{
	LongDigit buf; /* знаковая переменная для выделения заема разрядов */
	Digit cf = 0; /* для хранения промежуточного заема */
	int i; /* идексная переменная цикла */
	for (i = 0; i < size; i++) /* организация цикла по i */
	{
		buf = (LongDigit)first[i] - second[i] - cf;/* вычитание i-х цифр с учетом предыдущего заема */
		Res[i] = LODIGIT(buf); /* i-я цифра Res - младшая цифра разности buf */
		cf = HIDIGIT(buf); /* заем - старшая цифра разности buf */
		if (cf) cf = 1; /* если заем был, флагу заема присваеваем 1 */
	}
	if (pcf) *pcf = cf; /* если адрес pcf не 0, возвращаем заем */
}
void Sub(
	const Digit first[], /* уменьшаемое (size цифр) */
	const Digit second[], /* вычитаемое (size цифр) */
	Digit Res[] /* разность (size цифр) */
)
{
	Digit Res2[CD];
	LongDigit buf; /* знаковая переменная для выделения заема разрядов */
	Digit cf = 0; /* для хранения промежуточного заема */
	int i; /* идексная переменная цикла */
	if (Less(first, second)) {
		for (i = 0; i < CD; i++) /* организация цикла по i */
		{
			buf = (LongDigit)g_p[i] - second[i] - cf;/* вычитание i-х цифр с учетом предыдущего заема */
			Res2[i] = LODIGIT(buf); /* i-я цифра Res - младшая цифра разности buf */
			cf = HIDIGIT(buf); /* заем - старшая цифра разности buf */
			if (cf) cf = 1; /* если заем был, флагу заема присваеваем 1 */
		}
		Add(first, Res2, Res);
	}
	else {
		for (i = 0; i < CD; i++) /* организация цикла по i */
		{
			buf = (LongDigit)first[i] - second[i] - cf;/* вычитание i-х цифр с учетом предыдущего заема */
			Res[i] = LODIGIT(buf); /* i-я цифра Res - младшая цифра разности buf */
			cf = HIDIGIT(buf); /* заем - старшая цифра разности buf */
			if (cf) cf = 1; /* если заем был, флагу заема присваеваем 1 */
		}
	}
}
void Sub_q(
	const Digit first[], /* уменьшаемое (size цифр) */
	const Digit second[], /* вычитаемое (size цифр) */
	Digit Res[] /* разность (size цифр) */
)
{
	Digit Res2[CD];
	LongDigit buf; /* знаковая переменная для выделения заема разрядов */
	Digit cf = 0; /* для хранения промежуточного заема */
	int i; /* идексная переменная цикла */
	if (Less(first, second)) {
		for (i = 0; i < CD; i++) /* организация цикла по i */
		{
			buf = (LongDigit)g_q[i] - second[i] - cf;/* вычитание i-х цифр с учетом предыдущего заема */
			Res2[i] = LODIGIT(buf); /* i-я цифра Res - младшая цифра разности buf */
			cf = HIDIGIT(buf); /* заем - старшая цифра разности buf */
			if (cf) cf = 1; /* если заем был, флагу заема присваеваем 1 */
		}
		Add(first, Res2, Res);
	}
	else {
		for (i = 0; i < CD; i++) /* организация цикла по i */
		{
			buf = (LongDigit)first[i] - second[i] - cf;/* вычитание i-х цифр с учетом предыдущего заема */
			Res[i] = LODIGIT(buf); /* i-я цифра Res - младшая цифра разности buf */
			cf = HIDIGIT(buf); /* заем - старшая цифра разности buf */
			if (cf) cf = 1; /* если заем был, флагу заема присваеваем 1 */
		}
	}
}

/*--------------------------------------------------------
Деление длинных чисел
--------------------------------------------------------*/

/*--------------------------------------------------------
	Обнуление длинного числа num = 0
--------------------------------------------------------*/
static void Zero(
	Digit num[],                /* обнуляемое число (size цифр) */
	int size)                   /* размер числа в цифрах */
{
	int i;                      /* идексная переменная цикла */

	for (i = 0; i < size; i++)         /* организация цикла по i */
		num[i] = 0;               /* обнуление i-ой цифры числа num */
}

static void Assign(
	Digit num1[],               /* получатель (size цифр) */
	const Digit num2[],         /* источник (size цифр) */
	int size)                   /* размер чисел в цифрах */
{
	int i;                      /* идексная переменная цикла */
	for (i = 0; i < size; i++)         /* организация цикла по i */
		num1[i] = num2[i];        /* присвоение i-ой цифре числа num1 i-ой цифры числа num2 */
}

/*--------------------------------------------------------
	Умножение длинного числа на цифру (*pcf,Res) = num * x
--------------------------------------------------------*/
static void ShortMul(
	Digit Res[],                /* результат (size цифр) */
	const Digit num[],          /* первый сомножитель (size цифр) */
	Digit x,                    /* второй сомножитель (1 цифра) */
	Digit *pcf,                 /* перенос старшего разряда (1 цифра), м.б. NULL */
	int size)                   /* размер числа в цифрах */
{
	TwoDigit buf;               /* переменная для хранения промежуточного результата умножения двух слов */
	Digit cf = 0;                 /* переменная для хранения промежуточного результата переноса */
	int i;                      /* идексная переменная цикла */

	for (i = 0; i < size; i++)         /* организация цикла по i */
	{
		buf = (TwoDigit)num[i] * x + cf;/* buf - сумма реультата умножения и предыдущего переноса */
		Res[i] = LODIGIT(buf);    /* i-я цифра Res - младшая цифра buf */
		cf = HIDIGIT(buf);        /* cf - перенос (старшая цифра buf) */
	}
	if (pcf) *pcf = cf;             /* если адрес pcf не 0, возвращаем перенос */
}

/*--------------------------------------------------------
	Деление длинного числа на цифру Res = num/x, *pmod = num % x
--------------------------------------------------------*/
static void ShortDiv(
	Digit Res[],                /* частное (size цифр) */
	const Digit num[],          /* делимое  (size цифр) */
	Digit x,                    /* делитель (цифра) */
	Digit *pmod,                /* остаток (цифра), м.б. NULL */
	int size)                   /* размер длинных чисел в цифрах */
{
	TwoDigit buf = 0;             /* вспомогательная переменная */
	int i;                      /* идексная переменная цикла */

	if (!x) return;              /* если x равен 0 то бесславно завершаем деление */
	for (i = size - 1; i >= 0; i--)      /* организация цикла по i */
	{
		buf <<= sizeof(Digit) * 8;  /* старшая цифра buf - предыдущий остаток */
		buf |= num[i];            /* младшая цифра buf - i-я цифра числа num */
		Res[i] = LODIGIT(buf / x);  /* i-я цифра Res - результат деления */
		buf %= x;                 /* младшая цифра buf - остаток */
	}
	if (pmod) *pmod = LODIGIT(buf);/* если адрес pmod не 0, возвращаем остаток */
}
/*--------------------------------------------------------
	Деление длинных чисел Q = U/V, R = U % V
	Исключение деления на 0 не обрабатывается
--------------------------------------------------------*/
void Div(
	const Digit U[],            /* делимое (sizeU цифр) */
	const Digit V[],            /* делитель (sizeV цифр) */
	Digit Q[],                  /* частное (sizeU цифр), м.б. NULL */
	Digit R[],					/* остаток (sizeV цифр), м.б. NULL */
	int sizeU,
	int sizeV)                  
{
	Digit q, buf1, buf2;                /* для промежуточного хранения */
	Digit U2[MAX_DIV_OPERAND_SIZE + 1],   /* для нормализованного U */
		V2[MAX_DIV_OPERAND_SIZE + 1];   /* для нормализованного V */
	TwoDigit inter;                     /* для промежуточных операций */
	int i, j, k;                          /* индексные переменные */
	Digit d;                            /* нормализующий множитель */

	for (int i = 0; i < 65; i++) {
		U2[i] = 0;
		V2[i] = 0;
	}
/*--- Проверки, подготовка: */
	if (R) Zero(R, sizeV);                /* если адрес остатка R не 0, обнуляем остаток */
	if (Q) Zero(Q, sizeU);                /* если адрес частного Q не 0, обнуляем частное */

	for (i = sizeV - 1; (i >= 0)&(!V[i]); i--);  /* анализ делителя, отсекаем старшие незначащие нули */
	sizeV = i + 1;                          /* новый размер делителя */
	if (!sizeV) return;                  /* исключение "Деление на ноль" (просто уходим) */

	for (k = sizeU - 1; (k >= 0)&(!U[k]); k--);  /* анализ делимого, отсекаем старшие незначащие нули */
	sizeU = k + 1;                          /* новый размер делимого */

	if (sizeV > sizeU)                     /* если делитель больше делимого, то */
	{
		if (R) Assign(R, U, sizeU);        /* остаток равен делимому */
		return;                        /* уходим */
	}
	else if (sizeV == 1)                   /* если делитель - 1 цифра, то */
	{
		ShortDiv(Q, U, V[0], R, sizeU);     /* применяем упрощенный алгоритм */
		return;                        /* уходим */
	}

	/*--- Нормализация: */
	d = (Digit)(((TwoDigit)MAXDIGIT + 1) / ((TwoDigit)V[sizeV - 1] + 1)); /* нормализующий множитель */
	if (d != 1)                        /* если d не 1, */
	{
		ShortMul(V2, V, d, &buf1, sizeV);   /* умножаем V на d */
		V2[sizeV] = buf1;
		ShortMul(U2, U, d, &buf1, sizeU);   /* умножаем U на d */
		U2[sizeU] = buf1;
	}
	else
	{                                   /* если d == 1, */
		Assign(V2, V, sizeV);             /* V2 = V */
		V2[sizeV] = 0;
		Assign(U2, U, sizeU);             /* U2 = U */
		U2[sizeU] = 0;
	}
	/*--- Основной цикл */
	for (j = sizeU; j >= sizeV; j--)           /* организация главного цикла по j (sizeU-sizeV раз) */
	{
		/*--- Очередная цифра частного */
		inter = MAKE_TWO_DIGIT(U2[j], U2[j - 1]); /* пригодится */
		if (U2[j] == V2[sizeV - 1])          /* если старшие цифры равны, */
			q = MAXDIGIT;                 /* цифра частного q = MAXDIGIT */
		else                            /* иначе */
			q = (Digit)(inter / V2[sizeV - 1]);/* j-ю цифру частного q находим делением */
										/* если q великоват, */


	/*--- Вычитание кратного делителя */
		ShortMul(R, V2, q, &buf1, sizeV);   /* умножаем V на q */
		Sub(U2 + j - sizeV, U2 + j - sizeV, R, &buf2, sizeV);/* вычитаем результат умножения */
		inter = (LongDigit)U2[j] - buf1 - buf2;
		U2[j] = LODIGIT(inter);

		/*--- Коррекция остатка и частного */
		if (HIDIGIT(inter))              /* если результат шага отрицательный, */
		{                               /* компенсирующее сложение */
			Add(U2 + j - sizeV, U2 + j - sizeV, V2, &buf2, sizeV);
			U2[j] += buf2;
			q--;                        /* коррекция цифры частного q на 1 */
		}
		if (Q)                           /* если адрес частного Q не 0, */
			Q[j - sizeV] = q;               /* запоминаем j-ю цифру частного q */
	}
	/*--- Завершение */
	if (R)                               /* если адрес остатка R не 0, */
	{
		ShortDiv(R, U2, d, NULL, sizeV);    /* денормализация остатка R */
	}
}
void Mod_Div(const Digit U[],            /* делимое (sizeU цифр) */
	const Digit V[],				/* делитель (sizeV цифр) */
	Digit Q[])						/* Остаток */
           
{	Digit *cel = new Digit[CD];
	Div(U, V, cel, Q, CD,CD);
	delete[] cel;
}
void Int_Div(const Digit U[],            /* делимое (sizeU цифр) */
	const Digit V[],				/* делитель (sizeV цифр) */
	Digit Q[])						/* Целая часть */
                 
{
	Digit *mod = new Digit[CD];
	Div(U, V, Q, mod,CD,CD);
	delete [] mod;
}


/*--------------------------------------------------------
	Умножение чисел
--------------------------------------------------------*/

void Mult(const Digit first[], /*Первый множитель*/
	const Digit second[], /*Второй множитель*/
	Digit Res[] /*Произведение*/
)
{
	TwoDigit buf; /* переменная для хранения промежуточного результата умножения двух слов */
	Digit cf = 0; /* переменная для хранения промежуточного результата переноса */
	int i, j; /* идексная переменная цикла */
	Digit *Res2 = new Digit[2*CD];
	for (i = 0; i < 2*CD; i++) { Res2[i] = 0; }
	for (i = 0; i < CD; i++)
	{
		cf = 0;
		for (j = 0; j < CD; j++) /* организация цикла по i */
		{
			buf = (TwoDigit)first[i] * second[j] + Res2[i + j] + cf;/* buf - сумма реультата умножения и предыдущего переноса */
			Res2[i + j] = LODIGIT(buf); /* i-я цифра Res - младшая цифра buf */
			cf = HIDIGIT(buf); /* cf - перенос (старшая цифра buf) */
		}
		Res2[i + CD] = cf;
	}
	
	Digit *cel = new Digit[2*CD];
	Div(Res2, g_p, cel, Res, 2*CD, CD);
//	cout << NumToStringDigit(cel) << endl;
//	cout << NumToStringDigit(Res) << endl;
	delete[] cel;
	delete[] Res2;

}
void Mult_q(const Digit first[], /*Первый множитель*/
	const Digit second[], /*Второй множитель*/
	Digit Res[] /*Произведение*/
)
{
	TwoDigit buf; /* переменная для хранения промежуточного результата умножения двух слов */
	Digit cf = 0; /* переменная для хранения промежуточного результата переноса */
	int i, j; /* идексная переменная цикла */
	Digit *Res2 = new Digit[2 * CD];
	for (i = 0; i < 2 * CD; i++) { Res2[i] = 0; }
	for (i = 0; i < CD; i++)
	{
		cf = 0;
		for (j = 0; j < CD; j++) /* организация цикла по i */
		{
			buf = (TwoDigit)first[i] * second[j] + Res2[i + j] + cf;/* buf - сумма реультата умножения и предыдущего переноса */
			Res2[i + j] = LODIGIT(buf); /* i-я цифра Res - младшая цифра buf */
			cf = HIDIGIT(buf); /* cf - перенос (старшая цифра buf) */
		}
		Res2[i + CD] = cf;
	}
	Digit *cel = new Digit[2 * CD];

	Div(Res2, g_q, cel, Res, 2 * CD, CD);
	delete[] cel;
	delete[] Res2;
}
```

## `Cript.h`

```cpp
#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <sstream>
using namespace std;
typedef unsigned long int TwoDigit;
typedef unsigned short int Digit;
typedef long int LongDigit;
#define CD 16
#define RANDOM true
#define NotRANDOM false
#define MAX_DIV_OPERAND_SIZE 64
#define MAXDIGIT 0xFFFF
#define LODIGIT(twodigit) (Digit)(twodigit)
#define HIDIGIT(twodigit) (Digit)((twodigit)>>(sizeof(Digit)*8))
#define MAKE_TWO_DIGIT(digit1,digit2) (((TwoDigit) (digit1) << (sizeof(Digit) * 8)) | (digit2))
extern Digit g_p[CD], g_e[CD], g_s[CD], g_t[CD], g_h[CD], g_k[CD], g_d[CD], g_razn[CD], g_u[CD], g_v[CD], g_zero[CD], g_q[CD], g_p_1[CD]; //���������� ����������

void Init();
void StringToNumber(string str, Digit Res[]);
string NumToStringDigit(const Digit Numb[]);
void Assig(const Digit first[], Digit second[]);
bool Less(const Digit first[], const Digit second[]);
bool More(const Digit first[], const Digit second[]);
bool Equal(const Digit first[], const Digit second[]);
void Add(const Digit first[], const Digit second[], Digit Res[]);
void Add_q(const Digit first[], const Digit second[], Digit Res[]);
void Sub(const Digit first[], const Digit second[], Digit Res[]);
void Sub_q(const Digit first[], const Digit second[], Digit Res[]);
void Mod_Div(const Digit U[], const Digit V[], Digit Q[]);
void Int_Div(const Digit U[], const Digit V[], Digit Q[]);
void Mult(const Digit first[], const Digit second[], Digit Res[]);
void Mult_q(const Digit first[], const Digit second[], Digit Res[]);
```

## `Elleptic_Curve.h`

```cpp
#pragma once 

#include <string>
#include <vector>
#include "Cript.h"
#include "bignum_algorithms.h"
#include "app_logic.h"

#define CD 16

struct EVCL {
    Digit a1[CD], a2[CD], a3[CD];
};

extern std::vector<std::string> variants;
extern Digit g_p[CD], g_e[CD], g_s[CD], g_t[CD], g_h[CD],
             g_k[CD], g_d[CD], g_razn[CD], g_u[CD], g_v[CD], g_zero[CD],
             g_q[CD], g_p_1[CD];

void Init();
void rev(Digit prym[], Digit obr[]);
void rev_mod(Digit ch[], Digit res[]);
void test(bool flag);
void compute_all_variants_eucl();
void compute_all_variants_pow();
void runPerformanceTest();
```

## `Makefile`

```makefile
# Имя исполняемого файла
TARGET = lab1

# Компилятор C++
CXX = g++

# Флаги компилятора: -std=c++11 для поддержки современного стандарта C++,
# -Wall для вывода всех предупреждений, -Wextra для дополнительных предупреждений.
# -g добавляет отладочную информацию.
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Каталог для временных файлов сборки (объектных файлов)
BUILD_DIR = build

# Автоматический поиск всех исходных .cpp файлов
SRCS = $(wildcard *.cpp)

# Формирование списка объектных файлов.
# Для каждого исходного файла создается соответствующий .o файл в каталоге BUILD_DIR
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))

# Цель по умолчанию: собрать исполняемый файл
all: $(TARGET)

# Правило для линковки исполняемого файла.
# Оно зависит от всех объектных файлов, которые теперь лежат в BUILD_DIR.
$(TARGET): $(OBJS)
	@echo "Linking target: $@"
	$(CXX) $(CXXFLAGS) -o $@ $^

# Шаблонное правило для компиляции .cpp в .o.
# Говорит, как из файла `some_name.cpp` создать файл `build/some_name.o`
# | $(BUILD_DIR) - это order-only prerequisite. Оно гарантирует,
# что папка $(BUILD_DIR) будет создана до начала компиляции.
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@echo "Compiling $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Правило для создания каталога сборки, если он не существует
$(BUILD_DIR):
	@mkdir -p $@

# "Чистая" цель: удаление исполняемого файла и каталога сборки
clean:
	@echo "Cleaning project..."
	@rm -f $(TARGET)
	@rm -rf $(BUILD_DIR)

# Цель для полной пересборки проекта
re: clean all

# Объявление "фантомных" целей, которые не являются реальными файлами
.PHONY: all clean re
```

## `Source.cpp`

```cpp
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
    // Используйте system("clear") для Linux/macOS или system("cls") для Windows
    // system("clear"); 
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
    cout << "    6. Тест: Преобразование Вейерштрасс -> Эдвардс\n";
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
        // --- ДОБАВЛЕННЫЙ БЛОК ДЛЯ ВЫЗОВА ВАШЕГО ТЕСТА ---
        case 6:
            cout << "--- Тест преобразования координат (Вейерштрасс -> Эдвардс) ---\n\n";
            test_transit(); // Вызываем вашу новую тестовую функцию
            break;
        // ----------------------------------------------
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
```

## `app_logic.cpp`

```cpp
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
void test_transit(){
    edv_points Res1;
    edv_points Res2;
    std::vector<std::string> test_nums_1{
        "91E38443A5E82C0D880923425712B2BB658B9196932E02C78B2582FE742DAA28",
        "32879423AB1A0375895786C4BB46E9565FDE0B5344766740AF268ADB32322E5C"};
    std::vector<std::string> test_nums_2{
        "e8c6740e58d616ca220db7da0d9c3e19b53e86e38bf3e8747774631452ec174c",
        "0b837a5e560a29a2327b575f29b4be8baef4bc947fcc2ed4f3264bc434309381"};
    std::vector<std::string> results_1{
        "000000000000000000000000000000000000000000000000000000000000000D",
        "60CA1E32AA475B348488C38FAB07649CE7EF8DBE87F22E81F92B2592DBA300E7"};
    std::vector<std::string> results_2{
        "f6870d679448ae3e512aeb35b000e44c35b4758e9ce0a6edb374f7d4d6e092b9",
        "18c8d703e7fa38aa7330bd29659ab19660a732d31e359363c8ce62ffaeca5592"};
    Digit x_1[CD];
    Digit y_1[CD];
    StringToNumber(test_nums_1[0], x_1);
    StringToNumber(test_nums_1[1], x_1);
    Digit x_2[CD];
    Digit y_2[CD];
    StringToNumber(test_nums_1[0], x_2);
    StringToNumber(test_nums_1[1], x_2);
    Res1=VeyToEdv(x_1,y_1);
    Res2=VeyToEdv(x_2,y_2);
    if (NumToStringDigit(Res1.u)!=results_1[0])
    {
        std::cout<<"Ошибка в вычислениях точки эдвардса u для 1 набора"<<std::endl;
    }
    if (NumToStringDigit(Res1.v)!=results_1[1])
    {
        std::cout<<"Ошибка в вычислениях точки эдвардса v для 1 набора"<<std::endl;
    }
    if (NumToStringDigit(Res2.u)!=results_2[0])
    {
        std::cout<<"Ошибка в вычислениях точки эдвардса u для 1 набора"<<std::endl;
    }
    if (NumToStringDigit(Res2.v)!=results_2[1])
    {
        std::cout<<"Ошибка в вычислениях точки эдвардса v для 1 набора"<<std::endl;
    }
    
}
```

## `app_logic.h`

```cpp
#pragma once
#include <chrono>
#include <limits>
#include <string> 
#include "Elleptic_Curve.h"
void test(bool flag);
void test_transit();
void compute_all_variants_eucl();
void compute_all_variants_pow();
void runPerformanceTest();
void compute_obr_eucl(std::string pr_dig, std::string name);
void compute_obr_pow(std::string pr_dig, std::string name);
void printResult(const std::string &original_hex, const Digit inverse[], const std::string &test_name);
```

## `bignum_algorithms.cpp`

```cpp
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
    delete[] u;
    delete[] v;
    delete[] y_obr;
    delete[] x_minus_t;
    delete[] x_minus_t_minus_s;
    delete[] x_minus_t_plus_s;
    delete[] x_minus_t_plus_s_obr;
    return Res;
}
```

## `bignum_algorithms.h`

```cpp
#pragma once
#include "Elleptic_Curve.h"
std::vector<std::string> variants{
    "07b4dc57b882bbdadfeac30c98060cb7edac68d3c85a2c983f61ebbb4328c7a2",
    "b1e2506a61369776b0db764b5232fb01d1a19d11143250930bd581f81b6b3f29",
    "e827d5a312e16d6eafdb3ce14d8b141954b73b011d88e30c743e3aec0c9ca377",
    "2b288901879a8dc92a6fccd0f19f655f51b5a7dc2c488990a28690fd44570756",
    "1e6fe3d3cb040a908661fc429f1bd5006e5c71670f80e2b548b345907a171384",
    "fc2e5913f75d27837a5c9a7524323a735bf8a88065f86f65915e6691aab4ed83",
    "5d732ba8d820d356cfc405df08bca38d383569b92f5b3eeab11a364e6d5d0f01",
    "81ef462a5ea2480a75035e399e5aed33f5596331ee0546a65e919761daf6bf19",
    "34a9f245fb1ca75952f68509c7dc1f8ce1fad63e3b7a142fa41fc453b4065e67",
    "637b8184e24494f710418a1a905743b88dc32806540965acf24e53179c770ee6",
    "575ae6b97798a5877f52978e1a30ea9da05deb4d9d1635dab8284143fde82f7c",
    "2020768ba8ac82d81d4b39d1cff408778e5eddea10bd7453c2d969b62193c365",
    "91f9fb8802cdbbea95f328cdd54a4d14926cf8f1fc931f77d02408e57e71a719",
    "ae8fe01f95486b762d65e180dd2fafcc6bcf3e5e5684058a12d32acd66f91704",
    "3be4da2e9311694404bfc521180181923e82646664b392aa7779c770c9922836",
    "fe28c041fd69ef209038be06f1f157c327d53d028b6b5c65607a565a1a2b4a15",
    "99cd7ba5fce78b8455e13965f2ee2c7a2a873f03b6895d9037ddeef8879e40b0",
    "eb077499a363a026c570062bae86755ce944dfa6a6db157c55b09be4932a3977",
    "f100b96d936c817c395794850b9914c28475ae6feb2f501322dd3283cb3a3f8d",
    "1de5f99a4ded640dc702de10a6e9f7bc640f8db372c974cde2beeea095d81719",
    "56a9a4ee38984fe1c07a357a0a31820c141cfaf5012f1436e24fb6b74d215e55",
    "07f6e40c9da4c7b6729fd739eff6d1a5f6e209f0df109d2891f55ebfbe19eb02",
    "9cec4dfe35d8f6f6d9b474f616c63ddedb6cceda3c561a75fba71223a48f96f4",
    "3509754ab34fbbbc41cf477cf5063c14171ffe788646c0c8237c4e818e95c7ac",
    "cf2f53add6085d220892c159c612945bc25514a95afdb785deeb9e0690804a6e",
    "4240d8d00f0aae5b3dfa730b32004779f30dbca1d86652e23fb9d167dea4188a",
    "dc7633c2cebc6057a02d3a81e6e9e43556fd6f8acfadb86ea2c4f424402edbe1",
    "051a3239e8c6b6a42eabd4b24c85d88f3bd50ae119ac47ecfe9a795461b0a3b8",
    "c862eee3016e87ee611ef4c41865cfced425246b9925f0bcafdedf8af546a3b2",
    "6419095866cf2cdc5459ba454349bdb5cf2dff3c821de36e469c61b5073b1e9f",
    "421cdb00d570546241d4f3ac97c5356baf1b8456dec0160f92096d73671fe976",
    "8cda632cb86269f5af684e02d52aec32b7874cc290753f7fefb4f5f7fb36a0a2",
    "41bd5e2c7968e5b35f6a5d1cf45f595f4c93695be311ae5c04d74e5b3b59e0fc",
    "18802a56016854dfd1053afbe7f73f031f6ed88455cc517bb899d4e6c2262192",
    "769cad0303c6a7c249c5dcff618c57d423f28e9f1ff8779430c4cf46855a955b",
    "2a9f380b6973ef144b6c77d965ac0962bed5e59f9e9ca15dfd27dd8b47c9a876",
    "b7d0aefad7bea4aff6a3659a7c29d32090eda26edb6bf49676afe8b89be6cc96",
    "abd5d6766fa130c157a3bbf95c5bb3ea76e5431ee9fa03d1003d368a944ce3ea",
    "a841d72fd8343492d853abb6039bfdcd242185e60dae802626c358424d79d47b",
    "07c9459a16953c7b395bf0703d2f335342c4a0a6c6fe6eb4e360b06806260561"};
extern Digit g_p[CD], g_e[CD], g_s[CD], g_t[CD], g_h[CD],
    g_k[CD], g_d[CD], g_razn[CD], g_u[CD], g_v[CD], g_zero[CD],
    g_q[CD], g_p_1[CD];
struct edv_points{
    Digit u[CD], v[CD];
};
// Алгоритм на основе Евклида
void rev(Digit prym[], Digit obr[]);

// Алгоритм на основе теоремы Ферма
void rev_mod(Digit ch[], Digit res[]);

edv_points VeyToEdv(Digit x[], Digit y[]);
```

## `mycrypto.cpp`

```cpp
#include "mycrypto.h"
ByteBlock::ByteBlock(size_t size_, BYTE init_value) :
	amount_of_bytes(size_)
{
	if (!size_) pBlocks = nullptr;
	else {
		pBlocks = new BYTE[size_];
		memset(pBlocks, init_value, size_);
	}
}
ByteBlock::ByteBlock(BYTE * pBlocks_, size_t size_) :
	amount_of_bytes(size_)
{
	pBlocks = new BYTE[size_];
	memcpy(pBlocks, pBlocks_, size_);
}
ByteBlock::ByteBlock(ByteBlock && rhs) :
	pBlocks(rhs.pBlocks), amount_of_bytes(rhs.amount_of_bytes)
{
	rhs.pBlocks = nullptr;
	rhs.amount_of_bytes = 0;
}
ByteBlock::~ByteBlock() {
	if (pBlocks) {
		memset(pBlocks, 0, amount_of_bytes);
		delete[] pBlocks;
	}
}
void ByteBlock::operator = (ByteBlock && rhs) {
	if (this == &rhs) return;
	if (pBlocks) {
		memset(pBlocks, 0, amount_of_bytes);
		delete[] pBlocks;
	}
	pBlocks = rhs.pBlocks;
	amount_of_bytes = rhs.amount_of_bytes;
	rhs.pBlocks = nullptr;
	rhs.amount_of_bytes = 0;
}
BYTE * ByteBlock::byte_ptr() {
	return pBlocks;
}
const BYTE * ByteBlock::byte_ptr() const {
	return pBlocks;
}
BYTE & ByteBlock::operator [] (size_t index) {
	return *(pBlocks + index);
}
BYTE ByteBlock::operator [] (size_t index) const {
	return *(pBlocks + index);
}
bool ByteBlock::operator == (const ByteBlock & lhs) const {
	return pBlocks == lhs.pBlocks;
}
bool ByteBlock::operator != (const ByteBlock & lhs) const {
	return !(*this == lhs);
}
void ByteBlock::reset(const BYTE * pBlocks_, size_t size_) {
	if (pBlocks) {
		memset(pBlocks, 0, amount_of_bytes);
		delete[] pBlocks;
	}
	if (size_ && pBlocks_) {
		pBlocks = new BYTE[size_];
		memcpy(pBlocks, pBlocks_, size_);
		amount_of_bytes = size_;
	}
	else {
		pBlocks = nullptr;
		amount_of_bytes = 0;
	}
}
size_t ByteBlock::size() const {
	return amount_of_bytes;
};
ByteBlock ByteBlock::deep_copy() const {
	return ByteBlock(pBlocks, amount_of_bytes);
}
ByteBlock ByteBlock::operator () (size_t begin, size_t length)
const {
	ByteBlock tmp;
	tmp.reset(pBlocks + begin, length);
	return tmp;
}
void swap(ByteBlock & lhs, ByteBlock & rhs) {
	BYTE * p = lhs.pBlocks;
	size_t s = lhs.amount_of_bytes;
	lhs.pBlocks = rhs.pBlocks;
	lhs.amount_of_bytes = rhs.amount_of_bytes;
	rhs.pBlocks = p;
	rhs.amount_of_bytes = s;
}
vector<ByteBlock> split_blocks(const ByteBlock & src, size_t
	length) {
	vector<ByteBlock> tmp;
	int amount = src.size() / length;
	int tail = src.size() % length;
	for (int i = 0; i < amount; i++)
		tmp.push_back(src(i * length, length));
	if (tail)
		tmp.push_back(src(amount * length, tail));
	return tmp;
}
ByteBlock join_blocks(const vector<ByteBlock> & blocks) {
	if (blocks.empty()) return ByteBlock();
	size_t size_vector = blocks.size();
	size_t size_block = blocks[0].size();
	size_t size_last = blocks[size_vector - 1].size();
	size_t size_byteblock = (size_vector - 1) * size_block +
		size_last;
	ByteBlock tmp(size_byteblock);
	for (int i = 0; i < size_vector - 1; i++) {
		memcpy(
			tmp.byte_ptr() + i * size_block,
			blocks[i].byte_ptr(),
			size_block
		);
	}
	memcpy(
		tmp.byte_ptr() + (size_vector - 1) * size_block,
		blocks[size_vector - 1].byte_ptr(),
		size_last
	);
	return tmp;
}
void xor_blocks(ByteBlock & to_assign, const ByteBlock & lhs,
	const ByteBlock & rhs) {
	size_t result_size = lhs.size() > rhs.size() ? rhs.size() :
		lhs.size();
	ByteBlock tmp(result_size);
	for (size_t i = 0; i < result_size; i++)
		tmp[i] = lhs[i] ^ rhs[i];
	to_assign = std::move(tmp);
}
inline char to_hex_literal(BYTE number) {
	if (number < 10) return '0' + number;
	if (number < 16) return 'a' + number - 10;
	throw std::invalid_argument("to_hex_literal: " +
		std::to_string(number));
}
inline BYTE from_hex_literal(char symbol) {
	if (isdigit(symbol)) return symbol - '0';
	if (symbol >= 'a' && symbol <= 'f') return symbol - 'a' + 10;
	if (symbol >= 'A' && symbol <= 'F') return symbol - 'A' + 10;
	throw std::invalid_argument("from_hex_literal: " +	std::to_string(symbol));
}
string hex_representation(const ByteBlock & bb) {
	stringstream ss;
	for (int i = 0; i < bb.size(); i++) {
		ss << to_hex_literal(bb[i] >> 4);
		ss << to_hex_literal(bb[i] & 0xF);
	}
	string result;
	getline(ss, result);
	return result;
}
ByteBlock hex_to_bytes(const string & s) {
	if (s.size() % 2) throw std::invalid_argument("length of hexstring must be even number");
	int size = s.size() / 2;
	ByteBlock result(size);
	for (int i = 0; i < size; i++) {
		result[i] = from_hex_literal(s[2 * i]) << 4;
		result[i] += from_hex_literal(s[2 * i + 1]);
	}
	return result;
}

```

## `mycrypto.h`

```cpp
#pragma once
#pragma once
#include <stdexcept>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <vector>
#include <map>
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
typedef unsigned char BYTE;
typedef unsigned short int WORD;
class ByteBlock {
	BYTE * pBlocks;
	size_t amount_of_bytes;
public:
	ByteBlock(size_t size_ = 0, BYTE init_value = 0);
	ByteBlock(BYTE * pBlocks_, size_t size_);
	ByteBlock(ByteBlock && rhs);
	~ByteBlock();
	void operator = (ByteBlock && rhs);
	BYTE * byte_ptr();
	const BYTE * byte_ptr() const;
	BYTE & operator [] (size_t index);
	BYTE operator [] (size_t index) const;
	bool operator == (const ByteBlock & lhs) const;
	bool operator != (const ByteBlock & lhs) const;
	void reset(const BYTE * pBlocks_, size_t size_);
	size_t size() const;
	ByteBlock deep_copy() const;
	ByteBlock operator () (size_t begin, size_t length) const;
	friend void swap(ByteBlock & lhs, ByteBlock & rhs);
};
vector<ByteBlock> split_blocks(const ByteBlock & src, size_t
	length);
ByteBlock join_blocks(const vector<ByteBlock> & blocks);
void xor_blocks(ByteBlock & to_assign, const ByteBlock & lhs,
	const ByteBlock & rhs);
string hex_representation(const ByteBlock & bb);
ByteBlock hex_to_bytes(const string & s);

```

