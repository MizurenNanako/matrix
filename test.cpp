#include <iostream>
#include <algorithm>
#include "mat.hpp"

#include <map>

int main()
{
    mat_t<double> m{
        {1, 2, 3},
        {4, 5, -1, -2},
        {6},
        {-5},
        {1},
    };

    m *= 2;

    // auto s = m.vertical_slice(1);
    // auto r = m[1];

    // std::cout << m << std::endl;
    std::cout << "m:" << m.pretty() << std::endl;
    // std::cout << s << std::endl;
    // std::cout << r << std::endl;
    // std::cout << m[3][1] << std::endl;

    // std::cout << m[3][4] << std::endl; //error
    // std::cout << m[4][0] << std::endl; // error

    auto [w, h] = m.get_size();
    std::cout << "size: w=" << w << ", h=" << h << std::endl;

    auto n = m / 2;
    std::cout << "n:" << n.pretty() << std::endl;
    std::cout << "m:" << m.pretty() << std::endl;

    std::sort(m[1].begin(), m[1].end());
    std::cout << "m:" << m.pretty() << std::endl;

    auto &&vs = n.vertical_slice(0);
    std::sort(vs.begin(), vs.end());
    std::cout << "n:" << n.pretty() << std::endl;

    return 0;
}