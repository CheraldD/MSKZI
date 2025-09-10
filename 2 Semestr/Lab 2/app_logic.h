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