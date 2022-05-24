#include <iostream>
#include <algorithm>
#include "mat.hpp"

#include <map>

int main()
{
    std::cout << "Initializer test" << std::endl;
    mat_t<double> m{
        {1, 2, 3, 4},
        {4, 5, -1, -2},
        {0, -3, -1, 1},
    };
    std::cout << "m:" << m << std::endl;

    mat_t<double> n{
        {1, 2, 3},
        {4, 5, 2},
        {1, 2, 1},
        {4, 5, 0},
    };
    std::cout << "n:" << n << std::endl;

    __pretty_output_elem_width = 4;
    std::cout << "\nPretty output test" << std::endl;
    std::cout << "m:" << m.pretty() << std::endl;
    std::cout << "n:" << n.pretty() << std::endl;

    std::cout << "Matrix multiply test" << std::endl;
    auto q = m * n;
    std::cout << "q=m×n:" << q.pretty() << std::endl;
    std::cout << "q×m:" << (q * m).pretty() << std::endl;
    try
    {
        std::cout << "m×q:" << (m * q).pretty() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught:" << std::endl;
        std::cout << e.what() << std::endl;
    }

    std::cout << "\nLiner multiply test" << std::endl;
    m *= 2;
    std::cout << "m:" << m.pretty() << std::endl;

    std::cout << "Tranpose test" << std::endl;
    std::cout << "trn(m):" << m.tran() << std::endl;
    std::cout << "trn(m):" << m.tran().pretty() << std::endl;

    mat_t<double> d = m.tran();
    std::cout << "trn(m):" << d.pretty() << std::endl;

    std::cout << "Slice test" << std::endl;
    auto s = n.vertical_slice(1);
    std::cout << "vertical slice of n on pos 1:\n"
              << s << std::endl;
    auto r = m.vertical_slice(1);
    std::cout << "vertical slice of m on pos 1:\n"
              << r << std::endl;
    auto p = m.horizontal_slice(0);
    std::cout << "horizontal slice of m on pos 0:\n"
              << p << std::endl;

    std::cout << "\nIterator test" << std::endl;
    std::cout << "\nIteration output of slices of n:" << std::endl;
    for (const auto &x : n)
    {
        std::cout << x << std::endl;
    }

    std::cout << "\noperator[][] test" << std::endl;
    std::cout << "n[3][1]=" << n[3][1] << std::endl;

    std::cout << "\nget_size() test" << std::endl;
    auto [w, h] = m.get_size();
    std::cout << "size: w=" << w << ", h=" << h << std::endl;

    std::cout << "\nSTL test" << std::endl;
    std::cout << "\nSort vertical slice 1 of m:" << std::endl;
    std::cout << "before:\nm:" << m.pretty() << std::endl;
    std::sort(m.vertical_slice(1).begin(),
              m.vertical_slice(1).end());
    std::cout << "after:\nm:" << m.pretty() << std::endl;
    return 0;
}