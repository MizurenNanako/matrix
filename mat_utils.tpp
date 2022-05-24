#ifndef _mat_utils_tpp
#define _mat_utils_tpp

#ifndef _mat_hpp
#error Do not include this file directly, include mat.hpp instead.
#endif

#include "mat.hpp"

static size_t __pretty_output_elem_width = 3;

template <typename T>
template <typename MorT>
class mat_t<T>::pretty_t
{
private:
    const MorT &_rmat;
    inline static std::ostream &setw(std::ostream &out, int w) { return out.width(w), out; }
    static constexpr auto pretty_helper = [](std::ostream &out, const auto &me)
        -> std::ostream &
    {
        out << "[";
        auto x = (*me).begin();
        auto e = (*me).end() - 1;
        while (x != e)
            setw(out, __pretty_output_elem_width) << *x << ",", ++x;
        return setw(out, __pretty_output_elem_width) << *e << "]";
    };

public:
    pretty_t(const MorT &mat) : _rmat{mat} {}
    friend std::ostream &operator<<(std::ostream &out, const pretty_t &me)
    {
        out << "\t\b[";
        auto x = me._rmat.begin();
        auto e = me._rmat.end();
        --e;
        while (x != e)
            pretty_helper(out, x) << ",\n\t", ++x;
        return pretty_helper(out, e) << "]\n";
    }
};

template <typename T>
class mat_t<T>::tran_t
{
private:
    const mat_t<T> &_rmat;

public:
    tran_t(const mat_t<T> &mat) : _rmat{mat} {}
    ~tran_t() = default;
    inline size_t width() const { return _rmat._height; }
    inline size_t height() const { return _rmat._width; }
    inline mat_t<T>::cvsbi begin() const { return mat_t<T>::cvsbi(0, _rmat); }
    inline mat_t<T>::cvsbi end() const { return mat_t<T>::cvsbi(_rmat._width, _rmat); }
    inline mat_t<T>::chslice horizontal_slice(size_t i) const { return mat_t<T>::cvslice(i, _rmat); }
    inline mat_t<T>::cvslice vertical_slice(size_t j) const { return mat_t<T>::chslice(j, _rmat); }
    inline mat_t<T>::chslice operator[](size_t i) const { return horizontal_slice(i); }
    friend std::ostream &operator<<(std::ostream &out, const tran_t &m)
    {
        out << "[";
        auto x = m.begin();
        auto e = m.end();
        --e;
        while (x != e)
            out << *x << ", ", ++x;
        return out << *e << "]";
    }
    inline const pretty_t<tran_t> pretty() const
    {
        return pretty_t<tran_t>(*this);
    }
};

#endif