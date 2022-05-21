#ifndef _mat_tpp

#ifndef _mat_hpp
#error Do not include this file directly, include mat.hpp instead.
#endif

#define _mat_tpp
#include "mat.hpp"

#include <algorithm>

#include "slice.tpp"

// mat_t

template <typename T>
mat_t<T>::mat_t(size_t width, size_t height) : _width{width}, _height{height}, _index_size{width * height} { _data.reserve(_index_size + 1); }
template <typename T>
mat_t<T>::mat_t(const mat_t &copy) : _width{copy._width}, _height{copy._height}, _index_size{copy._index_size}, _data{copy._data} {}
template <typename T>
mat_t<T>::mat_t(mat_t &&move) : _width{move._width}, _height{move._height}, _index_size{move._index_size}, _data{std::move(move._data)} {}
template <typename T>
mat_t<T>::mat_t(const std::initializer_list<std::initializer_list<T>> &init) : _width{(*init.begin()).size()}, _height{init.size()}
{
    for (const auto &x : init)
        if (_width < x.size())
            _width = x.size();
    _index_size = _width * _height;
    _data.reserve(_index_size + 1);
    for (const auto &x : init)
    {
        auto p = x.begin();
        int i = 0;
        while (i < _width && p != x.end())
            _data.push_back(*p), ++i, ++p;
        while (i < _width)
            _data.push_back(0), ++i;
    }
}

template <typename T>
T &mat_t<T>::__at(size_t i, size_t j)
{
    if (i >= _height)
        throw(std::out_of_range("i in mat_t __at(i, j) out of range."));
    if (j >= _width)
        throw(std::out_of_range("j in mat_t __at(i, j) out of range."));
    if (_data.size() < _index_size)
        _data.resize(_index_size);
    return _data[__pos(i, j)];
}

template <typename T>
const T &mat_t<T>::__get(size_t i, size_t j) const
{
    if (i >= _height)
        throw(std::out_of_range("i in mat_t __get(i, j) out of range."));
    if (j >= _width)
        throw(std::out_of_range("j in mat_t __get(i, j) out of range."));
    return _data[__pos(i, j)];
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const mat_t<T> &m)
{
    out << "[";
    auto x = m.begin();
    auto e = m.end();
    --e;
    while (x != e)
        out << *x << ", ", ++x;
    return out << *e << "]";
}

#endif