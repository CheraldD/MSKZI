#pragma once
#include <chrono>
#include <limits>
#include <string> 
#include <algorithm>
#include <cctype>
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
void test_scalar_multiplication();
void test_multiplication_variant_20();