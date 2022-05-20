#define _slice_tpp
#include "mat.hpp"

template <typename T>
template <typename Y, typename _M, typename _T>
class mat_t<T>::hslice_base
{
private:
    _M &_rmat;

protected:
    size_t _i;

public:
    hslice_base(size_t i, _M &mat)
        : _i{i}, _rmat{mat} {}
    inline Y &operator++()
    {
        if (++_i > _rmat._height)
            throw(std::range_error("Slice out of height range in mat_t"));
        return *reinterpret_cast<Y*>(this);
    }
    inline Y &operator--()
    {
        if (--_i > _rmat._height)
            throw(std::range_error("Slice out of height range in mat_t"));
        return *reinterpret_cast<Y*>(this);
    }
    inline bool operator!=(const Y &rhs)
    {
        return (_i != rhs._i);
    }
    inline _T &operator[](size_t j) const
    {
        return _rmat.__get(_i, j);
    }
    inline _T *begin() const
    {
        return _rmat._data.data() + _rmat.__pos(_i, 0);
    }
    inline _T *end() const
    {
        return _rmat._data.data() + _rmat.__pos(_i + 1, 0);
    }
    inline Y &operator*() { return *this; }

    friend std::ostream &operator<<(std::ostream &out, const Y &me)
    {
        out << "[";
        _T *x = me.begin();
        _T *e = me.end() - 1;
        while (x != e)
            out << *(x++) << ", ";
        return out << *e << "]";
    }
};
/* 
template <typename T>
template <typename Y, typename _M, typename _T>
class mat_t<T>::vslice_base
{
private:
    using me_t = mat_t<T>::vslice_base;

protected:
    size_t _j;
    size_t _h;
    size_t _w;

public:
    vslice_base(size_t j, size_t h, size_t w)
        : _j{j}, _h{h}, _w{w} {}
    ~vslice_base() = default;
    inline me_t &operator++()
    {
        if (++_j > _w)
            throw(std::range_error("Slice out of width range in mat_t"));
        return *this;
    }
    inline me_t &operator--()
    {
        if (--_j > _w)
            throw(std::range_error("Slice out of width range in mat_t"));
        return *this;
    }
    inline bool operator!=(const me_t &rhs)
    {
        return (_j != rhs._j);
    }
}; */

// #define _____hslice_impl(C)                                            \
//     inline C T &operator[](size_t j) const                             \
//     {                                                                  \
//         return _mat.__get(base::_i, j);                                \
//     }                                                                  \
//     inline C T *begin() const                                          \
//     {                                                                  \
//         return _mat._data.data() + _mat.__pos(base::_i, 0);            \
//     }                                                                  \
//     inline C T *end() const                                            \
//     {                                                                  \
//         return _mat._data.data() + _mat.__pos(base::_i + 1, 0);        \
//     }                                                                  \
//     inline me_t &operator*() { return *this; }                         \
//                                                                        \
//     friend std::ostream &operator<<(std::ostream &out, const me_t &me) \
//     {                                                                  \
//         out << "[";                                                    \
//         C T *x = me.begin();                                           \
//         C T *e = me.end() - 1;                                         \
//         while (x != e)                                                 \
//         {                                                              \
//             out << *(x++) << ", ";                                     \
//         }                                                              \
//         return out << *e << "]";                                       \
//     }

template <typename T>
class mat_t<T>::hslice
    : public hslice_base<mat_t<T>::hslice, mat_t<T>, T>
{
private:
    using me_t = mat_t<T>::hslice;
    using base = mat_t<T>::hslice_base<mat_t<T>::hslice, mat_t<T>, T>;

public:
    explicit hslice(size_t i, mat_t &mat)
        : base::hslice_base{i, mat}
    {
    }
    ~hslice() = default;
    // _____hslice_impl();
};

template <typename T>
class mat_t<T>::chslice
    : public hslice_base<mat_t<T>::chslice, const mat_t<T>, const T>
{
private:
    using me_t = mat_t<T>::chslice;
    using base = mat_t<T>::hslice_base<mat_t<T>::chslice, const mat_t<T>, const T>;

public:
    explicit chslice(size_t i, const mat_t &mat)
        : base::hslice_base{i, mat}
    {
    }
    ~chslice() = default;
    // _____hslice_impl(const);
};

#undef _____hslice_impl