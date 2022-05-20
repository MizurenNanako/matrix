#include <iostream>
#include "mat.hpp"

int main()
{
    mat_t<double> m{
        {1, 2, 3},
        {4, 5, -1, -2},
        {6},
        // {9, 8, 7},
    };

    auto s = m.vertical_slice(1);
    auto r = m[1];

    std::cout << s << std::endl;
    std::cout << r << std::endl;
    std::cout << m[2][0] << std::endl;

    return 0;
}