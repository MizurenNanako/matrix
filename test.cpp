#include <iostream>
#include "mat.hpp"

int main()
{
    mat_t<double> m{
        {1, 2, 3},
        {4, 5},
        {6},
    };

    // std::cout << m[0][0] << " "
    //   << m[1][1] << std::endl;

    std::cout << m << std::endl;

    m += 2;

    std::cout << m << std::endl;

    auto n{m};

    m *= 0.5;

    std::cout << m << std::endl;
    std::cout << n << std::endl;

    return 0;
}