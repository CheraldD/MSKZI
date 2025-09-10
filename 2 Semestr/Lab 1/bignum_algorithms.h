#pragma once
#include "Elleptic_Curve.h"

// Алгоритм на основе Евклида
void rev(Digit prym[], Digit obr[]);

// Алгоритм на основе теоремы Ферма
void rev_mod(Digit ch[], Digit res[]);