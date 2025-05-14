#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <random>
#include <iomanip>
#include "keygen.h"
#include "magma.h"
using namespace std;

int main()
{
    magma cipher;
    cipher.file_open("data.txt",false);
    cipher.file_open("output.enc",true);
    cipher.test_ciphertext_resilience("output.enc","oversize.txt");
    return 0;
}
