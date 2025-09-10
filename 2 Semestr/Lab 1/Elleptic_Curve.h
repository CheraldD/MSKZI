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