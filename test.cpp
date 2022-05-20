#include <iostream>
#include "mat.hpp"

int main()
{
    mat_t<double> m{
        {1, 2, 3},
        {4, 5, -1, -2},
        {6},
        {9, -3, 7},
        {8, 7},
    };

    // m *= 2;

    // auto s = m.vertical_slice(1);
    // auto r = m[1];

    // std::cout << m << std::endl;
    std::cout << "m:" << m.pretty() << std::endl;
    // std::cout << s << std::endl;
    // std::cout << r << std::endl;
    // std::cout << m[3][1] << std::endl;

    // std::cout << m[3][4] << std::endl; //error
    // std::cout << m[5][0] << std::endl; // error

    return 0;
}