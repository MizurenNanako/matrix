#include "mat.hpp"

// mat_t

template <typename T>
mat_t<T>::mat_t(size_t width, size_t height)
    : _width{width}, _height{height},
      _index_size{width * height + 1}
{
}

/* template <typename T>
mat_t<T>::~mat_t()
{
} */

template <typename T>
std::pair<size_t, size_t> &&mat_t<T>::get_size()
{
    return std::make_pair(_width, _height);
}

template <typename T>
typename mat_t<T>::index_helper mat_t<T>::operator[](size_t i) const
{
    return mat_t<T>::index_helper(i, *this);
}

template <typename T>
T &mat_t<T>::__at(size_t i, size_t j) const
{
    size_t &&pos = __pos(i, j);
    if (pos < _index_size)
    {
        if (_data.size() < _index_size)
            _data.resize(_index_size);
        return _data[__pos(i, j)];
    }
    throw(std::invalid_argument("Invalid index in mat_t __get()"));
}

// index helper

template <typename T>
T &mat_t<T>::index_helper::operator[](size_t j) const
{
    return _mat.__at(_i, j);
}
