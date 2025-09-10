#pragma once
#include "Elleptic_Curve.h"

struct edv_points{
    Digit u[CD], v[CD];
};
struct vey_points{
    Digit x[CD], y[CD];
};
// Алгоритм на основе Евклида
void rev(Digit prym[], Digit obr[]);

// Алгоритм на основе теоремы Ферма
void rev_mod(Digit ch[], Digit res[]);

edv_points VeyToEdv(Digit x[], Digit y[]);
vey_points EdvToVey(Digit u[], Digit v[]);