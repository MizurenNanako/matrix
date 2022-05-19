#include "mat.hpp"

int main()
{
    mat_t<int> m{2, 2};
    m[0][0] = 0;
    m[0][1] = 1;
    m[1][0] = 2;
    m[1][1] = 3;
    m[9][9] = 5;
    return 0;
}