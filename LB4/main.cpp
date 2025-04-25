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
    return 0;
}
