#ifndef _slice_tpp

#ifndef _mat_hpp
#error Do not include this file directly, include mat.hpp instead.
#endif

#define _slice_tpp
#include "mat.hpp"

/****************************************************/
/**                       all                      **/
/****************************************************/

#define __slice_iter_impl(dir, Dir)                                                                                \
    template <typename T>                                                                                          \
    template <typename Y, typename _M, typename _T>                                                                \
    class mat_t<T>::dir##slice_base<Y, _M, _T>::iterator                                                           \
    {                                                                                                              \
    private:                                                                                                       \
        using me_t = mat_t<T>::dir##slice_base<Y, _M, _T>::iterator;                                               \
        _M &_rmat;                                                                                                 \
        size_t _index;                                                                                             \
                                                                                                                   \
    public:                                                                                                        \
        using iterator_category = std::random_access_iterator_tag;                                                 \
        using difference_type = size_t;                                                                            \
        using value_type = Y;                                                                                      \
        using pointer = Y *;                                                                                       \
        using reference = Y &;                                                                                     \
        iterator(size_t i, _M &mat) : _rmat{mat}, _index{i} {}                                                     \
        inline me_t operator+(size_t rhs) { return iterator(_index + rhs, _rmat); }                                \
        inline me_t &operator++() { return ++_index, *reinterpret_cast<me_t *>(this); }                            \
        inline me_t &operator+=(size_t rhs) { return _index += rhs, *reinterpret_cast<me_t *>(this); }             \
        inline me_t operator++(int) { return iterator(_index++, _rmat); }                                          \
        inline size_t operator-(const me_t &rhs) { return _index - rhs._index; }                                   \
        inline me_t operator-(size_t rhs) { return iterator(_index - rhs, _rmat); }                                \
        inline me_t &operator--() { return --_index, *reinterpret_cast<me_t *>(this); }                            \
        inline me_t &operator-=(size_t rhs) { return _index -= rhs, *reinterpret_cast<me_t *>(this); }             \
        inline me_t operator--(int) { return iterator(_index--, _rmat); }                                          \
        inline bool operator!=(const me_t &rhs) const { return (_index != rhs._index) || (&_rmat != &rhs._rmat); } \
        inline Y operator*() const { return _rmat.Dir##_slice(_index); }                                           \
    };

/****************************************************/
/**                   horizontal                   **/
/****************************************************/

template <typename T>
template <typename Y, typename _M, typename _T>
class mat_t<T>::hslice_base : liner_output<mat_t<T>::hslice_base<Y, _M, _T>>
{
private:
    _M &_rmat;

protected:
    size_t _index;

public:
    class iterator;
    hslice_base(size_t i, _M &mat) : _rmat{mat}, _index{i} {}
    inline _T *begin() const { return _rmat._data.data() + _rmat.__pos(_index, 0); }
    inline _T *end() const { return _rmat._data.data() + _rmat.__pos(_index + 1, 0); }
    inline _T &operator[](size_t j) const { return _rmat.__at(_index, j); }
    inline bool operator!=(const Y &rhs) { return (_index != rhs._index); }
    inline iterator operator&() const { return iterator(_index, _rmat); }
};

__slice_iter_impl(h, horizontal);

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
class mat_t<T>::vslice_base : liner_output<mat_t<T>::vslice_base<Y, _M, _T>>
{
private:
    class viter_t;
    _M &_rmat;

protected:
    size_t _index;

public:
    class iterator;
    vslice_base(size_t j, _M &mat) : _rmat{mat}, _index{j} {}
    inline viter_t begin() const { return viter_t{0, _index, _rmat}; }
    inline viter_t end() const { return viter_t{_rmat._height, _index, _rmat}; }
    inline _T &operator[](size_t i) const { return _rmat.__at(i, _index); }
    inline bool operator!=(const Y &rhs) { return (_index != rhs._index); }
    inline iterator operator&() const { return iterator(_index, _rmat); }
};

__slice_iter_impl(v, vertical);

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