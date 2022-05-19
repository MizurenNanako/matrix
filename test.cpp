#include <iostream>
#include "mat.hpp"

int main()
{
    mat_t<int> m{
        {1, 2, 3},
        {4, 5},
        {6},
    };

    // std::cout << m[0][0] << " "
    //   << m[1][1] << std::endl;

    std::cout << m << std::endl;

    std::cout << m[1] << std::endl;

    // std::vector<int> v;
    // v.begin();

    mat_t<int> n;
    return 0;
}