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

    auto s = m.vertical_slice(1);

    std::cout << s << std::endl;

    return 0;
}