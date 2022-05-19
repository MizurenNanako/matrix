#ifndef _mat_hpp
#error Do not intend to include this file
#endif

#define _mat_tpp
#include "mat.hpp"

#include <algorithm>

// mat_t

template <typename T>
mat_t<T>::mat_t(size_t width, size_t height)
    : _width{width}, _height{height},
      _index_size{width * height + 1}
{
}

template <typename T>
mat_t<T>::mat_t(const mat_t &copy)
    : _width{copy._width}, _height{copy._height},
      _index_size{copy._index_size},
      _data{copy._data}
{
}

template <typename T>
mat_t<T>::mat_t(mat_t &&move)
    : _width{move._width}, _height{move._height},
      _index_size{move._index_size},
      _data{std::move(move._data)}
{
}

template <typename T>
mat_t<T>::mat_t(const std::initializer_list<std::initializer_list<T>> &init)
    : _width{(*init.begin()).size()},
      _height{init.size()}
{
    _index_size = _width * _height + 1;
    _data.reserve(_index_size);
    for (const auto &x : init)
    {
        auto p = x.begin();
        int i = 0;
        while (i < _width && p != x.end())
        {
            _data.push_back(*p);
            ++i;
            ++p;
        }
        while (i < _width)
        {
            _data.push_back(0);
            ++i;
        }
    }
}

template <typename T>
T &mat_t<T>::__at(size_t i, size_t j)
{
    size_t &&pos = __pos(i, j);
    if (pos < _index_size)
    {
        if (_data.size() < _index_size)
            _data.resize(_index_size);
        return _data[__pos(i, j)];
    }
    throw(std::invalid_argument("Invalid index in mat_t __at()"));
}

template <typename T>
const T &mat_t<T>::__get(size_t i, size_t j) const
{
    size_t &&pos = __pos(i, j);
    if (pos < _index_size)
    {
        return _data[__pos(i, j)];
    }
    throw(std::invalid_argument("Invalid index in mat_t __get()"));
}

/*******************************************************************/
/*******************************************************************/

template <typename T>
mat_t<T> mat_t<T>::operator+=(const T &rhs)
{
    std::for_each(_data.begin(), _data.end(), [&rhs](T &i)
                  { i += rhs; });
    return *this;
}
template <typename T>
mat_t<T> mat_t<T>::operator-=(const T &rhs)
{
    std::for_each(_data.begin(), _data.end(), [&rhs](T &i)
                  { i -= rhs; });
    return *this;
}
template <typename T>
mat_t<T> mat_t<T>::operator*=(const T &rhs)
{
    std::for_each(_data.begin(), _data.end(), [&rhs](T &i)
                  { i *= rhs; });
    return *this;
}

/*******************************************************************/
/*******************************************************************/

// index helper base
template <typename T>
class mat_t<T>::index_helper_base
{
private:
    using me_t = mat_t<T>::index_helper_base;

protected:
    size_t _i;
    size_t _h;
    size_t _w;

public:
    index_helper_base(size_t i, size_t h, size_t w)
        : _i{i}, _h{h}, _w{w} {}
    inline me_t &operator++()
    {
        if (++_i > _h)
            throw(std::range_error("Iterator out of range in mat_t"));
        return *this;
    }
    inline me_t &operator--()
    {
        if (--_i > _h)
            throw(std::range_error("Iterator out of range in mat_t"));
        return *this;
    }
    inline bool operator!=(const me_t &rhs)
    {
        return !(_i == rhs._i);
    }
};

#define _____helper_impl(C)                                            \
    inline C T &operator[](size_t j) const                             \
    {                                                                  \
        return _mat.__get(base::_i, j);                                \
    }                                                                  \
    inline C T *begin() const                                          \
    {                                                                  \
        return _mat._data.data() + _mat.__pos(base::_i, 0);            \
    }                                                                  \
    inline C T *end() const                                            \
    {                                                                  \
        return _mat._data.data() + _mat.__pos(base::_i + 1, 0);        \
    }                                                                  \
    inline me_t &operator*() { return *this; }                         \
                                                                       \
    friend std::ostream &operator<<(std::ostream &out, const me_t &me) \
    {                                                                  \
        out << "[";                                                    \
        C T *x = me.begin();                                           \
        C T *e = me.end() - 1;                                         \
        while (x != e)                                                 \
        {                                                              \
            out << *(x++) << ", ";                                     \
        }                                                              \
        return out << *e << "]";                                       \
    }

// index helper

template <typename T>
class mat_t<T>::index_helper : public index_helper_base
{
private:
    using me_t = mat_t<T>::index_helper;
    using base = mat_t<T>::index_helper_base;
    mat_t &_mat;

public:
    explicit index_helper(size_t i, mat_t &mat)
        : _mat{mat}, index_helper_base{i, mat._height, mat._width}
    {
    }
    ~index_helper() = default;
    _____helper_impl();
};

// const index helper

template <typename T>
class mat_t<T>::index_helper_const : public index_helper_base
{
private:
    using me_t = mat_t<T>::index_helper_const;
    using base = mat_t<T>::index_helper_base;
    const mat_t &_mat;

public:
    explicit index_helper_const(size_t i, const mat_t &mat)
        : _mat{mat}, index_helper_base{i, mat._height, mat._width}
    {
    }
    ~index_helper_const() = default;
    _____helper_impl(const);
};

#undef _____helper_impl

// ostream support of mat_t

template <typename T>
std::ostream &operator<<(std::ostream &out, const mat_t<T> &m)
{
    using i1 = typename mat_t<T>::index_helper_const;
    auto helper =
        [](std::ostream &out, i1 &me)
        -> std::ostream &
    {
        out << "[";
        const T *x = me.begin();
        const T *e = me.end() - 1;
        while (x != e)
        {
            out << *(x++) << ", ";
        }
        return out << *e << "]";
    };

    out << "[";
    i1 x = m.begin();
    i1 e = m.end();
    --e;
    while (x != e)
    {
        helper(out, x) << ", ";
        ++x;
    }
    return helper(out, e) << "]";
}
