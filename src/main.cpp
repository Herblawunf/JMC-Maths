#include "../include/include.h"
#include <iostream>
#include <string>

using namespace std;

int main() {

    std::vector<double> v = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    Matrix<double> m = {4, 4, v};

    std::vector<std::complex<double>> eigen = m.eigenvalues();

    print(eigen);

   return 0;
}
