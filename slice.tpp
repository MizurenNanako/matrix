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
    hslice_base(size_t i, _M &mat)
        : _i{i}, _rmat{mat} {}
    inline Y &operator++()
    {
        if (++_i > _rmat._height)
            throw(std::range_error("Slice out of height range in mat_t"));
        return *reinterpret_cast<Y *>(this);
    }
    inline Y &operator--()
    {
        if (--_i > _rmat._height)
            throw(std::range_error("Slice out of height range in mat_t"));
        return *reinterpret_cast<Y *>(this);
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

template <typename T>
class mat_t<T>::hslice
    : public hslice_base<mat_t<T>::hslice, mat_t<T>, T>
{
private:
    using base = mat_t<T>::hslice_base<mat_t<T>::hslice, mat_t<T>, T>;

public:
    explicit hslice(size_t i, mat_t &mat)
        : base::hslice_base{i, mat} {}
    ~hslice() = default;
};

template <typename T>
class mat_t<T>::chslice
    : public hslice_base<mat_t<T>::chslice, const mat_t<T>, const T>
{
private:
    using base = mat_t<T>::hslice_base<mat_t<T>::chslice, const mat_t<T>, const T>;

public:
    explicit chslice(size_t i, const mat_t &mat)
        : base::hslice_base{i, mat} {}
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

private:
    _M &_rmat;

protected:
    size_t _j;

public:
    vslice_base(size_t j, _M &mat)
        : _j{j}, _rmat{mat} {}
    inline Y &operator++()
    {
        if (++_j > _rmat._width)
            throw(std::range_error("Slice out of width range in mat_t"));
        return *reinterpret_cast<Y *>(this);
    }
    inline Y &operator--()
    {
        if (--_j > _rmat._width)
            throw(std::range_error("Slice out of width range in mat_t"));
        return *reinterpret_cast<Y *>(this);
    }
    inline bool operator!=(const Y &rhs)
    {
        return (_j != rhs._j);
    }
    inline _T &operator[](size_t i) const
    {
        return _rmat.__get(i, _j);
    }
    inline viter_t begin() const
    {
        // TODO!!!
        return viter_t{0, _j, _rmat};
    }
    inline viter_t end() const
    {
        // TODO!!!
        return viter_t{_rmat._height, _j, _rmat};
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
    explicit viter_t(size_t i, size_t j, _M &mat)
        : _p{&mat.__at(i, j)},
          _h{mat._height},
          _w{mat._width} {}
    ~viter_t() = default;

    inline bool operator!=(const me_t &rhs)
    {
        return (_p != rhs._p);
    }
    inline T &operator*()
    {
        return *_p;
    }
    inline me_t &operator++()
    {
        _p += _w;
        return *this;
    }
    inline me_t &operator--()
    {
        _p -= _w;
        return *this;
    }
};
