#ifndef _mat_pretty_tpp
#define _mat_pretty_tpp

#ifndef _mat_hpp
#error Do not include this file directly, include mat.hpp instead.
#endif

#include "mat.hpp"

template <typename T>
class mat_t<T>::pretty_t
{
private:
    const mat_t<T> &_rmat;
    inline static std::ostream &setw(std::ostream &out, int w) { return out.width(w), out; }
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
            pretty_helper(out, x) << ",\n\t", ++x;
        return pretty_helper(out, e) << "]\n";
    }
};

#endif