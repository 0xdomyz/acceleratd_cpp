#ifndef GUARD_PTR_H
#define GUARD_PTR_H

#include <stdexcept>
#include "RefCounter.h"

template <class T>
T *clone(const T *tp)
{
    return tp->clone();
}

template <class T>
class Ptr
{
public:
    void make_unique()
    {
        if (*refptr != 1)
        {
            --*refptr;
            refptr = new size_t(1);
            p = p ? clone(p) : 0;
        }
    }

    Ptr() : p(0) {}
    Ptr(T *t) : p(t) {}
    Ptr(const Ptr &h) : refcnt(h.refcnt), p(h.p) {}
    Ptr &operator=(const Ptr &);
    ~Ptr();

    operator bool() const { return p; }

    T &operator*() const
    {
        if (p)
            return *p;
        throw std::runtime_error("unbound Ptr");
    };

    T *operator->() const
    {
        if (p)
            return p;
        throw std::runtime_error("unbound Ptr");
    };

private:
    T *p;
    RefCounter refcnt;
};

template <class T>
Ptr<T> &Ptr<T>::operator=(const Ptr &rhs)
{
    if (this != &rhs)
    {
        if (refcnt.last())
        {
            delete p;
        }
        refcnt = rhs.refcnt;
        p = rhs.p;
    }
    return *this;
}

template <class T>
Ptr<T>::~Ptr()
{
    if (refcnt.last())
    {
        delete p;
    }
}

#endif
