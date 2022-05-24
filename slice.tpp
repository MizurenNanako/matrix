#ifndef _slice_tpp

#ifndef _mat_hpp
#error Do not include this file directly, include mat.hpp instead.
#endif

#define _slice_tpp
#include "mat.hpp"

/****************************************************/
/**                   horizontal                   **/
/****************************************************/

template <typename T>
template <typename Y, typename _M, typename _T>
class mat_t<T>::hslice_base
{
private:
    _M &_rmat;

protected:
    size_t _i;

public:
    class iterator;
    hslice_base(size_t i, _M &mat) : _rmat{mat}, _i{i} {}
    inline bool operator!=(const Y &rhs) { return (_i != rhs._i); }
    inline _T &operator[](size_t j) const { return _rmat.__at(_i, j); }
    inline _T *begin() const { return _rmat._data.data() + _rmat.__pos(_i, 0); }
    inline _T *end() const { return _rmat._data.data() + _rmat.__pos(_i + 1, 0); }
    inline iterator operator&() const { return iterator(_i, _rmat); }
    friend std::ostream &operator<<(std::ostream &out, const Y &me)
    {
        out << "[";
        auto *x = me.begin();
        auto *e = me.end() - 1;
        while (x != e)
            out << *(x++) << ", ";
        return out << *e << "]";
    }
};

template <typename T>
template <typename Y, typename _M, typename _T>
class mat_t<T>::hslice_base<Y, _M, _T>::iterator
{
private:
    using me_t = mat_t<T>::hslice_base<Y, _M, _T>::iterator;
    size_t _i;
    _M &_rmat;

public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = size_t;
    using value_type = Y;
    using pointer = Y *;
    using reference = Y &;
    iterator(size_t i, _M &mat) : _i{i}, _rmat{mat} {}
    inline me_t operator+(size_t rhs) { return iterator(_i + rhs, _rmat); }
    inline me_t &operator++() { return ++_i, *reinterpret_cast<me_t *>(this); }
    inline me_t &operator+=(size_t rhs) { return _i += rhs, *reinterpret_cast<me_t *>(this); }
    inline me_t operator++(int) { return iterator(_i++, _rmat); }
    inline size_t operator-(const me_t &rhs) { return _i - rhs._i; }
    inline me_t operator-(size_t rhs) { return iterator(_i - rhs, _rmat); }
    inline me_t &operator--() { return --_i, *reinterpret_cast<me_t *>(this); }
    inline me_t &operator-=(size_t rhs) { return _i -= rhs, *reinterpret_cast<me_t *>(this); }
    inline me_t operator--(int) { return iterator(_i--, _rmat); }
    inline bool operator!=(const me_t &rhs) const { return (_i != rhs._i) || (&_rmat != &rhs._rmat); }
    inline Y operator*() const { return _rmat.horizontal_slice(_i); }
};

template <typename T>
class mat_t<T>::hslice
    : public hslice_base<mat_t<T>::hslice, mat_t<T>, T>
{
private:
    using base = mat_t<T>::hslice_base<mat_t<T>::hslice, mat_t<T>, T>;

public:
    explicit hslice(size_t i, mat_t &mat) : base::hslice_base{i, mat} {}
    ~hslice() = default;
};

template <typename T>
class mat_t<T>::chslice
    : public hslice_base<mat_t<T>::chslice, const mat_t<T>, const T>
{
private:
    using base = mat_t<T>::hslice_base<mat_t<T>::chslice, const mat_t<T>, const T>;

public:
    explicit chslice(size_t i, const mat_t &mat) : base::hslice_base{i, mat} {}
    ~chslice() = default;
};

/****************************************************/
/**                    vertical                    **/
/****************************************************/

template <typename T>
template <typename Y, typename _M, typename _T>
class mat_t<T>::vslice_base
{
private:
    class viter_t;
    _M &_rmat;

protected:
    size_t _j;

public:
    class iterator;
    vslice_base(size_t j, _M &mat) : _rmat{mat}, _j{j} {}
    inline bool operator!=(const Y &rhs) const { return (_j != rhs._j); }
    inline _T &operator[](size_t i) const { return _rmat.__at(i, _j); }
    inline viter_t begin() const { return viter_t{0, _j, _rmat}; }
    inline viter_t end() const { return viter_t{_rmat._height, _j, _rmat}; }
    // inline Y &operator*() const { return *this; }
    inline iterator operator&() const { return iterator(_j, _rmat); }
    friend std::ostream &operator<<(std::ostream &out, const Y &me)
    {
        out << "[";
        auto x = me.begin();
        auto e = me.end() - 1;
        while (x != e)
            out << *x << ", ", ++x;
        return out << *e << "]";
    }
};

template <typename T>
template <typename Y, typename _M, typename _T>
class mat_t<T>::vslice_base<Y, _M, _T>::iterator
{
private:
    using me_t = mat_t<T>::vslice_base<Y, _M, _T>::iterator;
    _M &_rmat;
    size_t _j;

public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = size_t;
    using value_type = Y;
    using pointer = Y *;
    using reference = Y &;
    iterator(size_t j, _M &mat) : _rmat{mat}, _j{j} {}
    inline me_t operator+(size_t rhs) { return iterator(_j + rhs, _rmat); }
    inline me_t &operator++() { return ++_j, *reinterpret_cast<me_t *>(this); }
    inline me_t &operator+=(size_t rhs) { return _j += rhs, *reinterpret_cast<me_t *>(this); }
    inline me_t operator++(int) { return iterator(_j++, _rmat); }
    inline size_t operator-(const me_t &rhs) { return _j - rhs._j; }
    inline me_t operator-(size_t rhs) { return iterator(_j - rhs, _rmat); }
    inline me_t &operator--() { return --_j, *reinterpret_cast<me_t *>(this); }
    inline me_t &operator-=(size_t rhs) { return _j -= rhs, *reinterpret_cast<me_t *>(this); }
    inline me_t operator--(int) { return iterator(_j--, _rmat); }
    inline bool operator!=(const me_t &rhs) const { return (_j != rhs._j) || (&_rmat != &rhs._rmat); }
    inline Y operator*() const { return _rmat.vertical_slice(_j); }
};

template <typename T>
template <typename Y, typename _M, typename _T>
class mat_t<T>::vslice_base<Y, _M, _T>::viter_t
{
private:
    using me_t = mat_t<T>::vslice_base<Y, _M, _T>::viter_t;
    size_t _h;
    size_t _w;
    _T *_p;

public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = size_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    explicit viter_t(size_t i, size_t j, _M &mat) : _h{mat._height}, _w{mat._width}, _p{mat._data.data() + mat.__pos(i, j)} {}
    explicit viter_t(_T *p, size_t h, size_t w) : _h{h}, _w{w}, _p{p} {}
    ~viter_t() = default;
    inline bool operator==(const me_t &rhs) const { return (_p == rhs._p); }
    inline bool operator!=(const me_t &rhs) const { return (_p != rhs._p); }
    inline _T &operator*() const { return *_p; }
    inline me_t &operator++() { return _p += _w, *this; }
    inline me_t &operator--() { return _p -= _w, *this; }
    inline me_t operator+(size_t rhs) { return viter_t{_p + rhs * _w, _h, _w}; }
    inline me_t operator-(size_t rhs) { return viter_t{_p - rhs * _w, _h, _w}; }
    inline size_t operator-(const me_t &rhs) { return (_p - rhs._p) / _w; }
    inline bool operator<(const me_t &rhs) { return _p < rhs._p; }
};

template <typename T>
class mat_t<T>::vslice
    : public vslice_base<mat_t<T>::vslice, mat_t<T>, T>
{
private:
    using base = mat_t<T>::vslice_base<mat_t<T>::vslice, mat_t<T>, T>;

public:
    explicit vslice(size_t j, mat_t &mat) : base::vslice_base{j, mat} {}
    ~vslice() = default;
};

template <typename T>
class mat_t<T>::cvslice
    : public vslice_base<mat_t<T>::cvslice, const mat_t<T>, const T>
{
private:
    using base = mat_t<T>::vslice_base<mat_t<T>::cvslice, const mat_t<T>, const T>;

public:
    explicit cvslice(size_t j, const mat_t &mat) : base::vslice_base{j, mat} {}
    ~cvslice() = default;
};

#endif