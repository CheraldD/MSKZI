#pragma once
#include <chrono>
#include <limits>
#include <string> 
#include "Elleptic_Curve.h"
void test(bool flag);
void compute_all_variants_eucl();
void compute_all_variants_pow();
void runPerformanceTest();
void compute_obr_eucl(std::string pr_dig, std::string name);
void compute_obr_pow(std::string pr_dig, std::string name);
void printResult(const std::string &original_hex, const Digit inverse[], const std::string &test_name);