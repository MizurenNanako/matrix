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
    template <typename MorT>
    class pretty_t;
    class tran_helper_t;
    template <typename Y, typename _M, typename _T>
    class hslice_base;
    class hslice;
    class chslice;
    template <typename Y, typename _M, typename _T>
    class vslice_base;
    class vslice;
    class cvslice;
    using hsbi = typename mat_t<T>::hslice::iterator;
    using chsbi = typename mat_t<T>::chslice::iterator;
    using vsbi = typename mat_t<T>::vslice::iterator;
    using cvsbi = typename mat_t<T>::cvslice::iterator;

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

    /*No need to overload assignment operators, compliers know it.*/

    inline std::pair<size_t, size_t> get_size() { return std::make_pair(_width, _height); }

    inline hsbi begin() { return hsbi(0, *this); }
    inline chsbi begin() const { return chsbi(0, *this); }
    inline hsbi end() { return hsbi(_height, *this); }
    inline chsbi end() const { return chsbi(_height, *this); }

    inline mat_t<T>::hslice horizontal_slice(size_t i) { return mat_t<T>::hslice(i, *this); }
    inline mat_t<T>::chslice horizontal_slice(size_t i) const { return mat_t<T>::chslice(i, *this); }
    inline mat_t<T>::vslice vertical_slice(size_t j) { return mat_t<T>::vslice(j, *this); }
    inline mat_t<T>::cvslice vertical_slice(size_t j) const { return mat_t<T>::cvslice(j, *this); }

    inline mat_t<T>::hslice operator[](size_t i) { return horizontal_slice(i); }
    inline mat_t<T>::chslice operator[](size_t i) const { return horizontal_slice(i); }

    inline mat_t<T> &for_each(const std::function<void(T &)> &f) { return std::for_each(_data.begin(), _data.end(), f), *this; }

#define __OP_HELPER(op) return for_each([&rhs](T &i) { i op rhs; })
    // arthmatic assignment operators
    inline mat_t<T> &operator+=(const T &rhs) { __OP_HELPER(+=); }
    inline mat_t<T> &operator-=(const T &rhs) { __OP_HELPER(-=); }
    inline mat_t<T> &operator*=(const T &rhs) { __OP_HELPER(*=); }
    inline mat_t<T> &operator/=(const T &rhs) { __OP_HELPER(/=); }
#undef __OP_HELPER
#define __OP_HELPER(op) return mat_t(*this) op rhs
    // arthmatic operators
    inline mat_t<T> operator+(const T &rhs) { __OP_HELPER(+=); }
    inline mat_t<T> operator-(const T &rhs) { __OP_HELPER(-=); }
    inline mat_t<T> operator*(const T &rhs) { __OP_HELPER(*=); }
    inline mat_t<T> operator/(const T &rhs) { __OP_HELPER(/=); }
#undef __OP_HELPER
    // matrix assignment operators
    mat_t<T> &operator+=(const mat_t<T> &rhs);
    mat_t<T> &operator-=(const mat_t<T> &rhs);
    // matrix operators
    inline mat_t<T> operator+(const mat_t<T> &rhs) { return mat_t(*this) += rhs; }
    inline mat_t<T> operator-(const mat_t<T> &rhs) { return mat_t(*this) -= rhs; }
    mat_t<T> operator*(const mat_t<T> &rhs);

    template <typename U>
    friend std::ostream &operator<<(std::ostream &, const mat_t<U> &);
    inline const pretty_t<mat_t<T>> pretty() const { return pretty_t<mat_t<T>>(*this); }
    inline const tran_helper_t tran() const { return tran_helper_t(*this); }

private:
    inline size_t __pos(size_t i, size_t j) const { return i * _width + j; }
    T &__at(size_t i, size_t j);
    const T &__get(size_t i, size_t j) const;
};

#include "mat.tpp"
#include "mat_utils.tpp"

#endif //_mat_h