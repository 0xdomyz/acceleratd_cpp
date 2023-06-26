#ifndef GUARD_REF_COUNTER_H
#define GUARD_REF_COUNTER_H

#include <stdexcept>

class RefCounter
{

public:
    RefCounter() : count(new size_t(1)) {}
    RefCounter(const RefCounter &rc) : count(rc.count) { ++*count; }
    RefCounter &operator=(const RefCounter &rhs)
    {
        if (this != &rhs)
        {
            if (last())
            {
                delete count;
            }
            else
            {
                --*count;
            }

            count = rhs.count;
            ++*count;
        }
        return *this;
    }
    ~RefCounter()
    {
        if (last())
        {
            delete count;
        }
        else
        {
            --*count;
        }
    }
    bool last() const { return *count == 1; }

private:
    size_t *count;
};

#endif
