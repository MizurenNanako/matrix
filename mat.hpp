#ifndef _mat_hpp
#define _mat_hpp

#include <vector>
#include <stdexcept>
#include <ostream>

template <typename T>
class mat_t
{
    // definition
private:
    class index_helper
    {
    private:
        const size_t _i;
        mat_t &_mat;

    public:
        explicit index_helper(size_t i, mat_t &mat) : _i{i}, _mat{mat} {}
        ~index_helper() = default;
        T &operator[](size_t j) const;
    };

    // data
private:
    size_t _width;
    size_t _height;
    size_t _index_size;
    std::vector<T> _data;

    // method
public:
    mat_t(size_t width = 0, size_t height = 0);
    ~mat_t() = default;

    std::pair<size_t, size_t> &&get_size();
    mat_t<T>::index_helper operator[](size_t i) const;

private:
    inline size_t __pos(size_t i, size_t j) const
    {
        return i + j * _width;
    }
    T &__at(size_t i, size_t j) const;
};

#include "mat.cpp"

#endif //_mat_h