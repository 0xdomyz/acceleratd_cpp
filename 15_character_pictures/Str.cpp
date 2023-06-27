#include "Str.h"

template <>
Vec<char> *clone(const Vec<char> *vp)
{
    // std::cout << "Vec<char> *clone(const Vec<char> *vp)" << std::endl;
    return new Vec<char>(*vp);
}

// as implemented in §12.3.2/216 and §12.3.3/219
std::ostream &operator<<(std::ostream &os, const Str &s)
{
    for (Str::size_type i = 0; i != s.size(); ++i)
        os << s[i];
    return os;
};

Str operator+(const Str &s, const Str &t)
{
    Str r = s;
    r += t;
    return r;
};
