#ifndef _mat_hpp
#define _mat_hpp

#include <vector>
#include <stdexcept>
#include <ostream>

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

    inline std::pair<size_t, size_t> &&get_size() { return std::make_pair(_width, _height); }
    inline mat_t<T>::hslice operator[](size_t i) { return mat_t<T>::hslice(i, *this); }
    inline mat_t<T>::chslice operator[](size_t i) const { return mat_t<T>::chslice(i, *this); }
    inline mat_t<T>::hslice begin() { return mat_t<T>::hslice(0, *this); }
    inline mat_t<T>::chslice begin() const { return mat_t<T>::chslice(0, *this); }
    inline mat_t<T>::hslice end() { mat_t<T>::hslice(_height, *this); }
    inline mat_t<T>::chslice end() const { return mat_t<T>::chslice(_height, *this); }

    inline mat_t<T>::vslice vertical_slice(size_t j) { return mat_t<T>::vslice(j, *this); }
    inline mat_t<T>::cvslice vertical_slice(size_t j) const { return mat_t<T>::cvslice(j, *this); }

    // arthmatic operators
    mat_t<T> operator+=(const T &rhs);
    mat_t<T> operator-=(const T &rhs);
    mat_t<T> operator*=(const T &rhs);

    template <typename U>
    friend std::ostream &operator<<(std::ostream &, const mat_t<U> &);
    const pretty_t pretty() { return pretty_t(this); }

private:
    inline size_t __pos(size_t i, size_t j) const { return i * _width + j; }
    T &__at(size_t i, size_t j);
    const T &__get(size_t i, size_t j) const;
};

#ifndef _mat_tpp
#include "mat.tpp"
#endif

template <typename T>
class mat_t<T>::pretty_t
{
private:
    const mat_t<T> &_rmat;
    inline static std::ostream &setw(std::ostream &out, int w)
    {
        out.width(w);
        return out;
    }
    static constexpr auto pretty_helper = [](std::ostream &out, const auto &me)
        -> std::ostream &
    {
        out << "[";
        const T *x = me.begin();
        const T *e = me.end() - 1;
        while (x != e)
            setw(out, 5) << *(x++) << ",";
        return setw(out, 5) << *e << "]";
    };

public:
    pretty_t(const mat_t<T> *mat) : _rmat{*mat} {}
    friend std::ostream &operator<<(std::ostream &out, const pretty_t &me)
    {
        out << "\t\b[";
        auto x = me._rmat.begin();
        auto e = me._rmat.end();
        --e;
        while (x != e)
        {
            pretty_helper(out, x) << ",\n\t";
            ++x;
        }
        return pretty_helper(out, e) << "]\n";
    }
};

#endif //_mat_h