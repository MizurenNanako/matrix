#ifndef _liner_output_hpp
#define _liner_output_hpp

template <typename Y>
class liner_output
{
    friend std::ostream &operator<<(std::ostream &out, const Y &m)
    {
        out << "[";
        auto x = m.begin();
        auto e = m.end();
        --e;
        while (x != e)
            out << *x << ", ", ++x;
        return out << *e << "]";
    }
};
#endif //_liner_output_hpp
