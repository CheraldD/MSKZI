# Сводка по коду проекта

**Сгенерировано:** 2025-09-26 16:32:19

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
string NumToStringDigit(const Digit Numb[] /*Инвертируемое число*/)
{
	stringstream srt;
	srt << std::uppercase; // Устанавливаем флаг один раз

	for (int i = 0; i < CD; i++)
		srt << setfill('0') << setw(4) << hex << Numb[CD - 1 - i];
		
	return srt.str();
}
/*--------------------------------------------------------
Инициализация констант
--------------------------------------------------------*/
void Init()
{
	StringToNumber("7e7e82520f9f015faa1d0f18c14ab9fb35188275da3fd94206b74f34a48e0ecd", g_s); // s=(e-d) / 4
	StringToNumber("0100fe73f595ff158e974b44d478d9588744fe5c192ac47ea63075dce7a14aaa", g_t); // t=(e+d) / 6
	StringToNumber("7f7f80c60535007538b45a5d95c39353bc5d80d1f36a9dc0ace7c5118c2f5977", g_h); // t+s
	StringToNumber("7d7d83de1a09024a1b85c3d3ecd1e0a2add38419c11514c36086d957bcecc423", g_k); // s-t
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
void Assig(const Digit first[], Digit second[])
{
	for (int i = 0; i < CD; i++)
	{
		second[i] = first[i];
	}
}
bool Less(const Digit first[], const Digit second[])
{
	for (int i = 0; i < CD; i++)
	{
		if (first[CD - 1 - i] < second[CD - 1 - i])
			return true;
		if (first[CD - 1 - i] > second[CD - 1 - i])
			return false;
	}
	return false;
}
bool More(const Digit first[], const Digit second[])
{
	for (int i = 0; i < CD; i++)
	{
		if (first[CD - 1 - i] > second[CD - 1 - i])
			return true;
		if (first[CD - 1 - i] < second[CD - 1 - i])
			return false;
	}
	return false;
}
bool Equal(const Digit first[], const Digit second[])
{
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
	Digit Res[],		  /* сумма (size цифр) */
	const Digit first[],  /* первое слагаемое (size цифр) */
	const Digit second[], /* второе слагаемое (size цифр)*/
	Digit *pcf,			  /* флаг переноса (1 цифра), м.б. NULL */
	int size)			  /* размер чисел в цифрах */
{
	TwoDigit buf;			   /* для хранения промежуточного результата сложения */
	Digit cf = 0;			   /* для хранения промежуточного переноса */
	int i;					   /* идексная переменная цикла */
	for (i = 0; i < size; i++) /* организация цикла по i */
	{
		buf = (TwoDigit)first[i] + second[i] + cf; /* сложение i-х цифр и предыдущего переноса */
		Res[i] = LODIGIT(buf);					   /* i-я цифра Res - младшая цифра суммы */
		cf = HIDIGIT(buf);						   /* перенос - старшая цифра суммы */
	}
	if (pcf)
		*pcf = cf; /* если адрес pcf не 0, возвращаем перенос */
}
void Add(					   /* Сложение по модулю p*/
		 const Digit first[],  /* первое слагаемое (size цифр) */
		 const Digit second[], /* второе слагаемое (size цифр)*/
		 Digit Res[]		   /* сумма (size цифр) */
)
{
	TwoDigit buf;			 /* для хранения промежуточного результата сложения */
	Digit cf = 0;			 /* для хранения промежуточного переноса */
	int i;					 /* идексная переменная цикла */
	for (i = 0; i < CD; i++) /* организация цикла по i */
	{
		buf = (TwoDigit)first[i] + second[i] + cf; /* сложение i-х цифр и предыдущего переноса */
		Res[i] = LODIGIT(buf);					   /* i-я цифра Res - младшая цифра суммы */
		cf = HIDIGIT(buf);						   /* перенос - старшая цифра суммы */
	}
	if (cf != 0)
	{
		cf = 0;
		for (i = 0; i < CD; i++) /* организация цикла по i */
		{
			buf = (TwoDigit)Res[i] + g_razn[i] + cf; /* сложение i-х цифр и предыдущего переноса */
			Res[i] = LODIGIT(buf);					 /* i-я цифра Res - младшая цифра суммы */
			cf = HIDIGIT(buf);						 /* перенос - старшая цифра суммы */
		}
	} /* если адрес pcf не 0, возвращаем перенос */
}
void Add_q(						 /* Сложение по модулю p*/
		   const Digit first[],	 /* первое слагаемое (size цифр) */
		   const Digit second[], /* второе слагаемое (size цифр)*/
		   Digit Res[]			 /* сумма (size цифр) */
)
{
	TwoDigit buf;			 /* для хранения промежуточного результата сложения */
	Digit cf = 0;			 /* для хранения промежуточного переноса */
	int i;					 /* идексная переменная цикла */
	for (i = 0; i < CD; i++) /* организация цикла по i */
	{
		buf = (TwoDigit)first[i] + second[i] + cf; /* сложение i-х цифр и предыдущего переноса */
		Res[i] = LODIGIT(buf);					   /* i-я цифра Res - младшая цифра суммы */
		cf = HIDIGIT(buf);						   /* перенос - старшая цифра суммы */
	}
	while (More(Res, g_q))
	{
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
	Digit Res[],		  /* разность (size цифр) */
	const Digit first[],  /* уменьшаемое (size цифр) */
	const Digit second[], /* вычитаемое (size цифр) */
	Digit *pcf,			  /* флаг заема разрядов (1 цифра), м.б. NULL */
	int size)			  /* размер чисел в цифрах */
{
	LongDigit buf;			   /* знаковая переменная для выделения заема разрядов */
	Digit cf = 0;			   /* для хранения промежуточного заема */
	int i;					   /* идексная переменная цикла */
	for (i = 0; i < size; i++) /* организация цикла по i */
	{
		buf = (LongDigit)first[i] - second[i] - cf; /* вычитание i-х цифр с учетом предыдущего заема */
		Res[i] = LODIGIT(buf);						/* i-я цифра Res - младшая цифра разности buf */
		cf = HIDIGIT(buf);							/* заем - старшая цифра разности buf */
		if (cf)
			cf = 1; /* если заем был, флагу заема присваеваем 1 */
	}
	if (pcf)
		*pcf = cf; /* если адрес pcf не 0, возвращаем заем */
}
void Sub(
	const Digit first[],  /* уменьшаемое (size цифр) */
	const Digit second[], /* вычитаемое (size цифр) */
	Digit Res[]			  /* разность (size цифр) */
)
{
	Digit Res2[CD];
	LongDigit buf; /* знаковая переменная для выделения заема разрядов */
	Digit cf = 0;  /* для хранения промежуточного заема */
	int i;		   /* идексная переменная цикла */
	if (Less(first, second))
	{
		for (i = 0; i < CD; i++) /* организация цикла по i */
		{
			buf = (LongDigit)g_p[i] - second[i] - cf; /* вычитание i-х цифр с учетом предыдущего заема */
			Res2[i] = LODIGIT(buf);					  /* i-я цифра Res - младшая цифра разности buf */
			cf = HIDIGIT(buf);						  /* заем - старшая цифра разности buf */
			if (cf)
				cf = 1; /* если заем был, флагу заема присваеваем 1 */
		}
		Add(first, Res2, Res);
	}
	else
	{
		for (i = 0; i < CD; i++) /* организация цикла по i */
		{
			buf = (LongDigit)first[i] - second[i] - cf; /* вычитание i-х цифр с учетом предыдущего заема */
			Res[i] = LODIGIT(buf);						/* i-я цифра Res - младшая цифра разности buf */
			cf = HIDIGIT(buf);							/* заем - старшая цифра разности buf */
			if (cf)
				cf = 1; /* если заем был, флагу заема присваеваем 1 */
		}
	}
}
void Sub_q(
	const Digit first[],  /* уменьшаемое (size цифр) */
	const Digit second[], /* вычитаемое (size цифр) */
	Digit Res[]			  /* разность (size цифр) */
)
{
	Digit Res2[CD];
	LongDigit buf; /* знаковая переменная для выделения заема разрядов */
	Digit cf = 0;  /* для хранения промежуточного заема */
	int i;		   /* идексная переменная цикла */
	if (Less(first, second))
	{
		for (i = 0; i < CD; i++) /* организация цикла по i */
		{
			buf = (LongDigit)g_q[i] - second[i] - cf; /* вычитание i-х цифр с учетом предыдущего заема */
			Res2[i] = LODIGIT(buf);					  /* i-я цифра Res - младшая цифра разности buf */
			cf = HIDIGIT(buf);						  /* заем - старшая цифра разности buf */
			if (cf)
				cf = 1; /* если заем был, флагу заема присваеваем 1 */
		}
		Add(first, Res2, Res);
	}
	else
	{
		for (i = 0; i < CD; i++) /* организация цикла по i */
		{
			buf = (LongDigit)first[i] - second[i] - cf; /* вычитание i-х цифр с учетом предыдущего заема */
			Res[i] = LODIGIT(buf);						/* i-я цифра Res - младшая цифра разности buf */
			cf = HIDIGIT(buf);							/* заем - старшая цифра разности buf */
			if (cf)
				cf = 1; /* если заем был, флагу заема присваеваем 1 */
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
	Digit num[], /* обнуляемое число (size цифр) */
	int size)	 /* размер числа в цифрах */
{
	int i; /* идексная переменная цикла */

	for (i = 0; i < size; i++) /* организация цикла по i */
		num[i] = 0;			   /* обнуление i-ой цифры числа num */
}

static void Assign(
	Digit num1[],		/* получатель (size цифр) */
	const Digit num2[], /* источник (size цифр) */
	int size)			/* размер чисел в цифрах */
{
	int i;					   /* идексная переменная цикла */
	for (i = 0; i < size; i++) /* организация цикла по i */
		num1[i] = num2[i];	   /* присвоение i-ой цифре числа num1 i-ой цифры числа num2 */
}

/*--------------------------------------------------------
	Умножение длинного числа на цифру (*pcf,Res) = num * x
--------------------------------------------------------*/
static void ShortMul(
	Digit Res[],	   /* результат (size цифр) */
	const Digit num[], /* первый сомножитель (size цифр) */
	Digit x,		   /* второй сомножитель (1 цифра) */
	Digit *pcf,		   /* перенос старшего разряда (1 цифра), м.б. NULL */
	int size)		   /* размер числа в цифрах */
{
	TwoDigit buf; /* переменная для хранения промежуточного результата умножения двух слов */
	Digit cf = 0; /* переменная для хранения промежуточного результата переноса */
	int i;		  /* идексная переменная цикла */

	for (i = 0; i < size; i++) /* организация цикла по i */
	{
		buf = (TwoDigit)num[i] * x + cf; /* buf - сумма реультата умножения и предыдущего переноса */
		Res[i] = LODIGIT(buf);			 /* i-я цифра Res - младшая цифра buf */
		cf = HIDIGIT(buf);				 /* cf - перенос (старшая цифра buf) */
	}
	if (pcf)
		*pcf = cf; /* если адрес pcf не 0, возвращаем перенос */
}

/*--------------------------------------------------------
	Деление длинного числа на цифру Res = num/x, *pmod = num % x
--------------------------------------------------------*/
static void ShortDiv(
	Digit Res[],	   /* частное (size цифр) */
	const Digit num[], /* делимое  (size цифр) */
	Digit x,		   /* делитель (цифра) */
	Digit *pmod,	   /* остаток (цифра), м.б. NULL */
	int size)		   /* размер длинных чисел в цифрах */
{
	TwoDigit buf = 0; /* вспомогательная переменная */
	int i;			  /* идексная переменная цикла */

	if (!x)
		return;						/* если x равен 0 то бесславно завершаем деление */
	for (i = size - 1; i >= 0; i--) /* организация цикла по i */
	{
		buf <<= sizeof(Digit) * 8; /* старшая цифра buf - предыдущий остаток */
		buf |= num[i];			   /* младшая цифра buf - i-я цифра числа num */
		Res[i] = LODIGIT(buf / x); /* i-я цифра Res - результат деления */
		buf %= x;				   /* младшая цифра buf - остаток */
	}
	if (pmod)
		*pmod = LODIGIT(buf); /* если адрес pmod не 0, возвращаем остаток */
}
/*--------------------------------------------------------
	Деление длинных чисел Q = U/V, R = U % V
	Исключение деления на 0 не обрабатывается
--------------------------------------------------------*/
void Div(
	const Digit U[], /* делимое (sizeU цифр) */
	const Digit V[], /* делитель (sizeV цифр) */
	Digit Q[],		 /* частное (sizeU цифр), м.б. NULL */
	Digit R[],		 /* остаток (sizeV цифр), м.б. NULL */
	int sizeU,
	int sizeV)
{
	Digit q, buf1, buf2;				/* для промежуточного хранения */
	Digit U2[MAX_DIV_OPERAND_SIZE + 1], /* для нормализованного U */
		V2[MAX_DIV_OPERAND_SIZE + 1];	/* для нормализованного V */
	TwoDigit inter;						/* для промежуточных операций */
	int i, j, k;						/* индексные переменные */
	Digit d;							/* нормализующий множитель */

	for (int i = 0; i < 65; i++)
	{
		U2[i] = 0;
		V2[i] = 0;
	}
	/*--- Проверки, подготовка: */
	if (R)
		Zero(R, sizeV); /* если адрес остатка R не 0, обнуляем остаток */
	if (Q)
		Zero(Q, sizeU); /* если адрес частного Q не 0, обнуляем частное */

	for (i = sizeV - 1; (i >= 0) & (!V[i]); i--)
		;		   /* анализ делителя, отсекаем старшие незначащие нули */
	sizeV = i + 1; /* новый размер делителя */
	if (!sizeV)
		return; /* исключение "Деление на ноль" (просто уходим) */

	for (k = sizeU - 1; (k >= 0) & (!U[k]); k--)
		;		   /* анализ делимого, отсекаем старшие незначащие нули */
	sizeU = k + 1; /* новый размер делимого */

	if (sizeV > sizeU) /* если делитель больше делимого, то */
	{
		if (R)
			Assign(R, U, sizeU); /* остаток равен делимому */
		return;					 /* уходим */
	}
	else if (sizeV == 1) /* если делитель - 1 цифра, то */
	{
		ShortDiv(Q, U, V[0], R, sizeU); /* применяем упрощенный алгоритм */
		return;							/* уходим */
	}

	/*--- Нормализация: */
	d = (Digit)(((TwoDigit)MAXDIGIT + 1) / ((TwoDigit)V[sizeV - 1] + 1)); /* нормализующий множитель */
	if (d != 1)															  /* если d не 1, */
	{
		ShortMul(V2, V, d, &buf1, sizeV); /* умножаем V на d */
		V2[sizeV] = buf1;
		ShortMul(U2, U, d, &buf1, sizeU); /* умножаем U на d */
		U2[sizeU] = buf1;
	}
	else
	{						  /* если d == 1, */
		Assign(V2, V, sizeV); /* V2 = V */
		V2[sizeV] = 0;
		Assign(U2, U, sizeU); /* U2 = U */
		U2[sizeU] = 0;
	}
	/*--- Основной цикл */
	for (j = sizeU; j >= sizeV; j--) /* организация главного цикла по j (sizeU-sizeV раз) */
	{
		/*--- Очередная цифра частного */
		inter = MAKE_TWO_DIGIT(U2[j], U2[j - 1]); /* пригодится */
		if (U2[j] == V2[sizeV - 1])				  /* если старшие цифры равны, */
			q = MAXDIGIT;						  /* цифра частного q = MAXDIGIT */
		else									  /* иначе */
			q = (Digit)(inter / V2[sizeV - 1]);	  /* j-ю цифру частного q находим делением */
												  /* если q великоват, */

		/*--- Вычитание кратного делителя */
		ShortMul(R, V2, q, &buf1, sizeV);					  /* умножаем V на q */
		Sub(U2 + j - sizeV, U2 + j - sizeV, R, &buf2, sizeV); /* вычитаем результат умножения */
		inter = (LongDigit)U2[j] - buf1 - buf2;
		U2[j] = LODIGIT(inter);

		/*--- Коррекция остатка и частного */
		if (HIDIGIT(inter)) /* если результат шага отрицательный, */
		{					/* компенсирующее сложение */
			Add(U2 + j - sizeV, U2 + j - sizeV, V2, &buf2, sizeV);
			U2[j] += buf2;
			q--; /* коррекция цифры частного q на 1 */
		}
		if (Q)				  /* если адрес частного Q не 0, */
			Q[j - sizeV] = q; /* запоминаем j-ю цифру частного q */
	}
	/*--- Завершение */
	if (R) /* если адрес остатка R не 0, */
	{
		ShortDiv(R, U2, d, NULL, sizeV); /* денормализация остатка R */
	}
}
void Mod_Div(const Digit U[], /* делимое (sizeU цифр) */
			 const Digit V[], /* делитель (sizeV цифр) */
			 Digit Q[])		  /* Остаток */

{
	Digit *cel = new Digit[CD];
	Div(U, V, cel, Q, CD, CD);
	delete[] cel;
}
void Int_Div(const Digit U[], /* делимое (sizeU цифр) */
			 const Digit V[], /* делитель (sizeV цифр) */
			 Digit Q[])		  /* Целая часть */

{
	Digit *mod = new Digit[CD];
	Div(U, V, Q, mod, CD, CD);
	delete[] mod;
}

/*--------------------------------------------------------
	Умножение чисел
--------------------------------------------------------*/

void Mult(const Digit first[],	/*Первый множитель*/
		  const Digit second[], /*Второй множитель*/
		  Digit Res[]			/*Произведение*/
)
{
	TwoDigit buf; /* переменная для хранения промежуточного результата умножения двух слов */
	Digit cf = 0; /* переменная для хранения промежуточного результата переноса */
	int i, j;	  /* идексная переменная цикла */
	Digit *Res2 = new Digit[2 * CD];
	for (i = 0; i < 2 * CD; i++)
	{
		Res2[i] = 0;
	}
	for (i = 0; i < CD; i++)
	{
		cf = 0;
		for (j = 0; j < CD; j++) /* организация цикла по i */
		{
			buf = (TwoDigit)first[i] * second[j] + Res2[i + j] + cf; /* buf - сумма реультата умножения и предыдущего переноса */
			Res2[i + j] = LODIGIT(buf);								 /* i-я цифра Res - младшая цифра buf */
			cf = HIDIGIT(buf);										 /* cf - перенос (старшая цифра buf) */
		}
		Res2[i + CD] = cf;
	}

	Digit *cel = new Digit[2 * CD];
	Div(Res2, g_p, cel, Res, 2 * CD, CD);
	//	cout << NumToStringDigit(cel) << endl;
	//	cout << NumToStringDigit(Res) << endl;
	delete[] cel;
	delete[] Res2;
}
void Mult_q(const Digit first[],  /*Первый множитель*/
			const Digit second[], /*Второй множитель*/
			Digit Res[]			  /*Произведение*/
)
{
	TwoDigit buf; /* переменная для хранения промежуточного результата умножения двух слов */
	Digit cf = 0; /* переменная для хранения промежуточного результата переноса */
	int i, j;	  /* идексная переменная цикла */
	Digit *Res2 = new Digit[2 * CD];
	for (i = 0; i < 2 * CD; i++)
	{
		Res2[i] = 0;
	}
	for (i = 0; i < CD; i++)
	{
		cf = 0;
		for (j = 0; j < CD; j++) /* организация цикла по i */
		{
			buf = (TwoDigit)first[i] * second[j] + Res2[i + j] + cf; /* buf - сумма реультата умножения и предыдущего переноса */
			Res2[i + j] = LODIGIT(buf);								 /* i-я цифра Res - младшая цифра buf */
			cf = HIDIGIT(buf);										 /* cf - перенос (старшая цифра buf) */
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
extern std::vector<std::vector<std::string>> ed_variants;
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
    cout << "    8. Тест: Сложение и удвоение точек (Вейерштрасс)\n";
    cout << "    9. Сложение точек в форме Вейерштрасса (Вариант 20)\n";
    cout << "   10. Сложение точек (Вариант 20, через Эдвардса)\n";
    cout << "   11. Тест: Сложение/удвоение (через Эдвардса)\n";
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
        case 8:
            cout << "--- Тест операций сложения/удвоения точек на кривой Вейерштрасса ---\n\n";
            test_add_points_vey();
            break;
        case 9:
            test_variant_20_addition();
            break;
        case 10:
            test_edwards_addition_for_variant_20();
            break;
        // Добавьте новый case
        case 11:
            test_add_points_edv_from_vey();
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
    std::cout << "        СЛОЖЕНИЕ ТОЧЕК НА КРИВОЙ ВЕЙЕРШТРАССА (ВАРИАНТ 20)      " << std::endl;
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
void compute_all_variants_ed();
void runPerformanceTest();
void compute_obr_eucl(std::string pr_dig, std::string name);
void compute_obr_pow(std::string pr_dig, std::string name);
void printResult(const std::string &original_hex, const Digit inverse[], const std::string &test_name);
void test_add_points_vey();
void test_add_points_edv_from_vey(); 
void test_variant_20_addition();
void test_edwards_addition_for_variant_20();
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

        // Освобождение памяти
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
```

## `bignum_algorithms.h`

```cpp
#pragma once
#include "Elleptic_Curve.h"

struct edv_points
{
    Digit u[CD], v[CD];
};
struct vey_points
{
    Digit x[CD], y[CD];
};
// Алгоритм на основе Евклида
void rev(Digit prym[], Digit obr[]);

// Алгоритм на основе теоремы Ферма
void rev_mod(Digit ch[], Digit res[]);

edv_points VeyToEdv(Digit x[], Digit y[]);
vey_points EdvToVey(Digit u[], Digit v[]);

vey_points Add_Vey(
    vey_points p_1,
    vey_points p_2,
    Digit x_res[], /* Координата х итоговой точки */
    Digit y_res[]  /* Координата y итоговой точки */
);
void Add_edv(
    edv_points p_1,
    edv_points p_2,
    Digit x_res[],    /* Координата х итоговой точки */
    Digit y_res[] /* Координата y итоговой точки */);
```

## `globals.cpp`

```cpp
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
std::vector<std::vector<std::string>> ed_variants{
    {// Вариант 1
     "5655981fbea13e5803b5146892a00ca5f59bbb358a24e5d0f4816b46fd872db0",
     "496b8e94237a36a4b7bc6990cfc9aa0ecc4fd00b23189477c63abd139b29b050",
     "c7ca518e3ef9ad61579287c9523fc9a91c9aead6f36d7ef0e49e9314edfab1b4",
     "b248bee0b70825b311795b8ea2030f7a8d210b87b4216859784722261438b028"},
    {// Вариант 2
     "6e25cb3cd4a8a16ba5983bd26d30231ebf65c9619f70a2289788ca0def028de1",
     "7544f0ae68e82091e8375468178d984daf22221a803e1e7e9daf5d30c95331d1",
     "5fcbfe0130206400e2ef3054f5486d2760277bcb2a502e9f3bd18846331fca2d",
     "b584cbd2fbf014defdf15037c268444dda3e879a55f4df315c8b1e4ab37220c1"},
    {// Вариант 3
     "3508bea1bde4908b6c2572d32da08ff7f5741780e20e0a966e0f4ea20eac30b5",
     "45e1798bc02b54c4dabcb8233c66eb778acd6dc44b2a21b140d22b7a8a49ac8f",
     "0072eed242c7703f05481b4a9c341948305a42ff89f0314991660909d8dcd8b7",
     "7c072bda7f21d70cc4bb573ae7eb6773f0339d7624a7763f5e2b252b81dfb149"},
    {// Вариант 4
     "2a350c8ea39912219b67e3f2cc3fa3a79e0c24f851ed88727b428ea7b6690f35",
     "0ef2c74f541f216344f32de39591fc00164f14f35298a2966ed605f9603e668a",
     "264836695a460dae5a1c8e7a342c4a4737ec10138ed425ffccb52d29708f5e62",
     "3ef34361604ee65df5caad6cdd41970e2d73df8383325b511314db24c748c6d1"},
    {// Вариант 5
     "1d40c1676805f9518be1fb4c7ae460d3608581e477b07c2d0e7e1e265a6b3347",
     "8291ace380fd8832baca29613ab5626c302d13348f204d727d30897a8e1f8934",
     "dabde3d3cdf37b92712d0bf66ae5e2160b4841c9deaf2198c1868fbe4c4c2524",
     "fb29a174cf79d33d8d0fee713750fc7b1d4a0b6086a2182c8c6b2879f21a9c98"},
    {
        // Вариант 6
        "2f7d6d0cd92656105d00c7636ef0d00e63a4af79909ef7e60671f0f3be2e5687", // x_A
        "2aae99d9bec842e2d837eb87cae1cd897fe2061528e4345a18d4d52ce4091b00", // y_A
        "fb7e76ffc26be53e9858bb15e3c4580f287511bbb72a718b417853d16a83fba9", // x_B
        "8bdc9fee69b7903c98f8761967173b54dfd976c7282d53446255e10e913709e8"  // y_B
    },
    {
        // Вариант 7
        "697b6d2daa6288d434f61fd813abc3242af464b21a74176f67241ae3d18b6f3d", // x_A
        "9b6f68866aaa1775f8a9049142abba163c1e3538f8e32f8dab4af2148a170c74", // y_A
        "84fa08690151695409788989f3d21340a72a6d820e02a33aa1787b56d3a0c795", // x_B
        "071aa92c8a2cb0438ef722d21849299552f5d58a5830f26ad79ad65e3f8481ee"  // y_B
    },
    {
        // Вариант 8
        "b216b37b9cc0f195906e3432c2a29c9f9a62ad46656bb509ac21801c1b03af1e", // x_A
        "41a41af5f12805c26877356b6744cc1535f9f985021be36de6ae53e6d764a6b4", // y_A
        "7b104442f1af36cf5685cfc7684c7c1fa240edfcdf053f71d7224f85aa6e8141", // x_B
        "45aabc4fb72b218b8f81044d5e839a64e65046d3514f666e6c3917949b8903d7"  // y_B
    },
    {
        // Вариант 9
        "12d99c1046f546f4ef4788617cb45ac037b961f4116c51217ef737a6e96b09f0", // x_A
        "d43c2ae4238ba290830eba9cf1d3c0307b84d400b291f3a59c8b7269fe87de6b", // y_A
        "10bb1dc7432010dc5d14d40ad6b13c6fb06de817e0aa2589104ab4e72b2a5f92", // x_B
        "dd0debf02ebb15aa7b04a810caf9022f6151e5b3654842de8a9f513de70a7b43"  // y_B
    },
    {
        // Вариант 10
        "5c2a559d1759ac120ed164f483394d50aaa955df43d2b3f6f1d6e4edb5b4647a", // x_A
        "d9d8db567242513d0ffc32b84159c852957e8cd871c4b111e21f0cdc967c4cb1", // y_A
        "1b92f7a3dbdc941dbb844197a79815cd4c93196100ea4fd3e226b9dd7597a3fe", // x_B
        "394d654fc8303797fd38d4d80aabebe0d4e7b1baabf66a6ca057c0df4b3366c4"  // y_B
    },
    {
        // Вариант 11
        "d405ed33759057b77ce6827cb6b7dc2bbc1a37f18eb24931917a8caa8ed0e0b3", // x_A
        "430f8208ddf32a70d6fca6bce899679046bfcc1d51bd5c9abf49a9ab3ea990b9", // y_A
        "da88cd5d4e38126339dd0360aa51278bb891d72302495988c4478e7bbfab0c29", // x_B
        "38f49756aee9f19293c4aeed2aa13fc113c6ae915a357f2dae5ee13bfa020107"  // y_B
    },
    {
        // Вариант 12
        "1fca8b91e2774568a928db2ad8af6803dd5d59df94856816674250fe3b946789", // x_A
        "2ee2d5b18d83a5461208201635df201d963dc02214a3e70ead3d967f11706d2c", // y_A
        "c9cbaeefaabc51147130fc6fa1adbe72140e35c5911b7d54b12beecdf5848943", // x_B
        "3c2e34cdfa1e6e76d6cc57ec871a26fb5b23d01c540e6f0d8f77f4d81fe3f613"  // y_B
    },
    {
        // Вариант 13
        "43e52883e2331cc8b94e16b6f4a78464ebeb0592a510860c85309a53844e48cd", // x_A
        "a06d100ce3e672dec6545d010350aa1f6b35a11beed6a92f2a021be374ab5b11", // y_A
        "182f29adadafa136a9635ed9d2688245885eece8b6327cd67b87d7e099243d23", // x_B
        "d7f1e9c9c09f80c8d201c47524095b9cd0571e969eeedd3154ba59fb7db710f7"  // y_B

    },
    {
        // Вариант 14
        "1a0f23dac76071e6f29112a4623f2ee48250a919d05f6b174dd749ef0242b7de", // x_A
        "5bee822353dfe0468080c18214252cfb4b178dae2441fe3af3011f27b1f17ce7", // y_A
        "3c9c274336b21af8a659d6360d27bf754fdbbc388ca09482916d41c2ac218bc8", // x_B
        "eb073ac056d069bd0fea34bd1db2a52204256091c3e2a65e53066a832aa463b9"  // y_B
    },
    {
        // Вариант 15
        "3680967cbae326099d4b1f59da76495c835900a4b15bf58fe816eeae9a6c731b", // x_A
        "3ba5b103438c5819e2fb1c8fa0a82235e1f25c47a1f6fb60f920f5a75ccb5b06", // y_A
        "a6529203be8b7be4eb5bc8d5bb2039e7f30cd5f96080afc441d68be27a0ca8f8", // x_B
        "5e984e973dd41eba318ec4f6621d1224ba3cd7ce00228f794f00865bb8928dda"  // y_B
    },
    {
        // Вариант 16
        "7c62f4ff84427d9c84074d745167bf0a1e1b5b2fa400836b4b991bec29bf999f", // x_A
        "08ee3d6e617b30d21acddeaea988a09a02e8fae6fe1b498e2efa951e9eb1b0f2", // y_A
        "f3d579efdb90172f52f9db2996cbc45f1b70fb3042c1c38717d995c5df469397", // x_B
        "9268e964b814d81b031f66aa309fdd3ccb9be1620cc58c142e4906f0a5809ec1"  // y_B
    },
    {
        // Вариант 17
        "33109bdf2c06340eff491a1677a8b5d36bc265bd708c863f00f21924989c75e1", // x_A
        "410e4c4fcd8a27472c72f5e10e62608f8c4838945d77a6eea6fbf72c241f3818", // y_A
        "7f60f457bd3e3b12e90da792a7c7eb680b36a88bb399c571653adb54bc0aaf2d", // x_B
        "b3aba99266d64b30b2dc7e121081b1dc32be2293cf47ff402ae64361ebdcc1fd"  // y_B

    },
    {
        // Вариант 18
        "644c9718f80b40d73557912bf11e538b4b4c1afdd011b3b54c9fbe67011f60d9", // x_A
        "298410a9d8b4d12c131eca5ac158a14a96802b112ef903615777375b218949da", // y_A
        "96a6b56a4bde04e3623fdf7a2920c22c72d61cff83273c996773f6eefa2b16b9", // x_B
        "d3931048534475a1efd3208e185601b4c07ef3baaf1db673d65814f9d16af6d1"  // y_B
    },
    {
        // Вариант 19
        "eeb02a91e4b70f9e64dacfc93142f3d040c882d37ffcc0e4b3604369d326848e", // x_A
        "601b3d6e6ba613752f241aa646fb1009082a99d1e23fb59dd246ed41ab46cd50", // y_A
        "097254064117c5f60349be07d28537bc7818aaf125538cf58ae1f897adabb273", // x_B
        "93b2f78fa5acad7526b8c703519b5b64846a60243b8ca7a9e42e9f9b00cdbccc"  // y_B
    },
    {
        // Вариант 20
        "94ef5bfa8686b475d8e5722b270e9c4fc636dff68671e66982292d0e543a1e50", // x_A
        "49251fec3d7b04c91d47b76077414aa0ff6c64fff8f947461f6802f68921427a", // y_A
        "4afc8d2a703bd0ed2f55f741fc12ad71b8cfd2d78b70758cbf844ce79e83781f", // x_B
        "fc5c10486f70c07cffe06f1c64a094028a574e85ac112cefb94a0772d2381fec"  // y_B
    }

};
Digit g_p[CD], g_e[CD], g_s[CD], g_t[CD], g_h[CD],
    g_k[CD], g_d[CD], g_razn[CD], g_u[CD], g_v[CD], g_zero[CD],
    g_q[CD], g_p_1[CD];
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

