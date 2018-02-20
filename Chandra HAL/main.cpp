#include <iostream>

#include "inertial.h"

int main(void) {
    chandra::drivers::InertialTransform<double,3> transform;

    std::cout << transform.c << '\n';
    std::cout << "gain = ";
    transform.A.dump();
    std::cout << '\n';
    std::cout << "offset = ";
    transform.x0.dump();
    std::cout << '\n';

    return 0;
}
