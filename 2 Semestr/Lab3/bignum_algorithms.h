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