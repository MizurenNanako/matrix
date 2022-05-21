#ifndef _mat_hpp
#define _mat_hpp

#include <vector>
#include <stdexcept>
#include <ostream>
#include <functional>

template <typename T>
class mat_t
{
    // slice
private:
    class pretty_t;
    template <typename Y, typename _M, typename _T>
    class hslice_base;
    class hslice;
    class chslice;
    template <typename Y, typename _M, typename _T>
    class vslice_base;
    class vslice;
    class cvslice;

    // data
private:
    size_t _width;
    size_t _height;
    size_t _index_size;
    std::vector<T> _data;

    // method
public:
    explicit mat_t(size_t width = 0, size_t height = 0);
    mat_t(const mat_t &copy);
    mat_t(mat_t &&move);
    mat_t(const std::initializer_list<std::initializer_list<T>> &init);
    ~mat_t() = default;

    inline std::pair<size_t, size_t> get_size() { return std::make_pair(_width, _height); }
    inline mat_t<T>::hslice begin() { return mat_t<T>::hslice(0, *this); }
    inline mat_t<T>::chslice begin() const { return mat_t<T>::chslice(0, *this); }
    inline mat_t<T>::hslice end() { mat_t<T>::hslice(_height, *this); }
    inline mat_t<T>::chslice end() const { return mat_t<T>::chslice(_height, *this); }

    inline mat_t<T>::hslice horizontal_slice(size_t i) { return mat_t<T>::hslice(i, *this); }
    inline mat_t<T>::chslice horizontal_slice(size_t i) const { return mat_t<T>::chslice(i, *this); }
    inline mat_t<T>::vslice vertical_slice(size_t j) { return mat_t<T>::vslice(j, *this); }
    inline mat_t<T>::cvslice vertical_slice(size_t j) const { return mat_t<T>::cvslice(j, *this); }

    inline mat_t<T>::hslice operator[](size_t i) { return horizontal_slice(i); }
    inline mat_t<T>::chslice operator[](size_t i) const { return horizontal_slice(i); }

    inline mat_t<T> &for_each(const std::function<void(T &)> &f)
    {
        std::for_each(_data.begin(), _data.end(), f);
        return *this;
    }

#define __OPEQ_HELPER(op) return for_each([&rhs](T &i) { i op rhs; })
    // arthmatic assignment operators
    inline mat_t<T> &operator+=(const T &rhs) { __OPEQ_HELPER(+=); }
    inline mat_t<T> &operator-=(const T &rhs) { __OPEQ_HELPER(-=); }
    inline mat_t<T> &operator*=(const T &rhs) { __OPEQ_HELPER(*=); }
    inline mat_t<T> &operator/=(const T &rhs) { __OPEQ_HELPER(/=); }
#undef __OPEQ_HELPER
#define __OP_HELPER(op) return mat_t(*this) op rhs
    // arthmatic operators
    inline mat_t<T> operator+(const T &rhs) { __OP_HELPER(+=); }
    inline mat_t<T> operator-(const T &rhs) { __OP_HELPER(-=); }
    inline mat_t<T> operator*(const T &rhs) { __OP_HELPER(*=); }
    inline mat_t<T> operator/(const T &rhs) { __OP_HELPER(/=); }
#undef __OP_HELPER

    template <typename U>
    friend std::ostream &operator<<(std::ostream &, const mat_t<U> &);
    const pretty_t pretty() { return pretty_t(this); }

private:
    inline size_t __pos(size_t i, size_t j) const { return i * _width + j; }
    T &__at(size_t i, size_t j);
    const T &__get(size_t i, size_t j) const;
};

#include "mat.tpp"
#include "mat_pretty.tpp"

#endif //_mat_h