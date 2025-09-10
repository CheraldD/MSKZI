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