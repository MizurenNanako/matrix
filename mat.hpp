#ifndef _mat_hpp
#define _mat_hpp

#include <vector>
#include <stdexcept>
#include <ostream>

template <typename T>
class mat_t
{
    // helper
private:
    class index_helper_base;
    class index_helper;
    class index_helper_const;

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

    inline std::pair<size_t, size_t> &&get_size()
    {
        return std::make_pair(_width, _height);
    }
    inline mat_t<T>::index_helper operator[](size_t i)
    {
        return mat_t<T>::index_helper(i, *this);
    }
    inline mat_t<T>::index_helper_const operator[](size_t i) const
    {
        return mat_t<T>::index_helper_const(i, *this);
    }
    inline mat_t<T>::index_helper begin()
    {
        return mat_t<T>::index_helper(0, *this);
    }
    inline mat_t<T>::index_helper_const begin() const
    {
        return mat_t<T>::index_helper_const(0, *this);
    }
    inline mat_t<T>::index_helper end()
    {
        mat_t<T>::index_helper(_height, *this);
    }
    inline mat_t<T>::index_helper_const end() const
    {
        return mat_t<T>::index_helper_const(_height, *this);
    }

    template <typename U>
    friend std::ostream &operator<<(std::ostream &out, const mat_t<U> &m);

private:
    inline size_t __pos(size_t i, size_t j) const
    {
        return i + j * _width;
    }
    T &__at(size_t i, size_t j);
    const T &__get(size_t i, size_t j) const;
};

#ifndef _mat_tpp
#include "mat.tpp"
#endif

#endif //_mat_h