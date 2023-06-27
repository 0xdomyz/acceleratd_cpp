#ifndef GUARD_PICTURES_H
#define GUARD_PICTURES_H

#include "Ptr.h"
#include <string>
#include <vector>

class Picture;

// private classes for use in the implementation only
class Pic_base
{
    friend std::ostream &operator<<(std::ostream &, const Picture &);
    friend class Frame_Pic;
    friend class HCat_Pic;
    friend class VCat_Pic;
    friend class String_Pic;
    friend Picture reframe(const Picture &, const char &, const char &, const char &);

    // no public interface
    typedef std::vector<std::string>::size_type ht_sz;
    typedef std::string::size_type wd_sz;

    virtual wd_sz width() const = 0;
    virtual ht_sz height() const = 0;
    virtual void display(std::ostream &, ht_sz, bool) const = 0;
    virtual void reframe_p(const char &, const char &, const char &) = 0;

protected:
    static void pad(std::ostream &os, wd_sz beg, wd_sz end);
};

class String_Pic : public Pic_base
{
    friend class Picture;

    std::vector<std::string> data;
    String_Pic(const std::vector<std::string> &v) : data(v) {}

    wd_sz width() const;
    ht_sz height() const { return data.size(); }
    void display(std::ostream &, ht_sz, bool) const;
    void reframe_p(const char &corner_c, const char &sides_c, const char &top_bot_c){};
};

class Frame_Pic : public Pic_base
{
    friend Picture frame(const Picture &);
    friend Picture frame(const Picture &, const char &, const char &, const char &);

    Ptr<Pic_base> p;
    char corner, sides, top_bottom;
    Frame_Pic(const Ptr<Pic_base> &pic) : p(pic), corner('*'), sides('|'), top_bottom('-') {}
    Frame_Pic(const Ptr<Pic_base> &pic, const char &cor, const char &side, const char &top) : p(pic), corner(cor), sides(side), top_bottom(top) {}
    void reframe_p(const char &corner_c, const char &sides_c, const char &top_bot_c)
    {
        corner = corner_c;
        sides = sides_c;
        top_bottom = top_bot_c;

        p->reframe_p(corner_c, sides_c, top_bot_c);
    }

    wd_sz width() const { return p->width() + 4; }
    ht_sz height() const { return p->height() + 4; }
    void display(std::ostream &, ht_sz, bool) const;
};

class VCat_Pic : public Pic_base
{
    friend Picture vcat(const Picture &, const Picture &);

    Ptr<Pic_base> top, bottom;
    VCat_Pic(const Ptr<Pic_base> &t, const Ptr<Pic_base> &b) : top(t), bottom(b) {}
    void reframe_p(const char &corner_c, const char &sides_c, const char &top_bot_c)
    {
        top->reframe_p(corner_c, sides_c, top_bot_c);
        bottom->reframe_p(corner_c, sides_c, top_bot_c);
    };

    wd_sz width() const
    {
        return std::max(top->width(), bottom->width());
    };
    ht_sz height() const
    {
        return top->height() + bottom->height();
    };
    void display(std::ostream &, ht_sz, bool) const;
};

class HCat_Pic : public Pic_base
{
    friend Picture hcat(const Picture &, const Picture &);

    Ptr<Pic_base> left, right;
    HCat_Pic(const Ptr<Pic_base> &l, const Ptr<Pic_base> &r) : left(l), right(r) {}
    void reframe_p(const char &corner_c, const char &sides_c, const char &top_bot_c)
    {
        left->reframe_p(corner_c, sides_c, top_bot_c);
        right->reframe_p(corner_c, sides_c, top_bot_c);
    };

    wd_sz width() const { return left->width() + right->width(); }
    ht_sz height() const
    {
        return std::max(left->height(), right->height());
    }
    void display(std::ostream &, ht_sz, bool) const;
};

// public interface class and operations
class Picture
{
    friend std::ostream &operator<<(std::ostream &, const Picture &);
    friend Picture frame(const Picture &);
    friend Picture frame(const Picture &, const char &, const char &, const char &);
    friend Picture hcat(const Picture &, const Picture &);
    friend Picture vcat(const Picture &, const Picture &);
    friend Picture reframe(const Picture &, const char &, const char &, const char &);

public:
    Picture(const std::vector<std::string> & = std::vector<std::string>());

private:
    Picture(Pic_base *ptr) : p(ptr){};
    Ptr<Pic_base> p;
};

// nonmember functions
Picture frame(const Picture &pic);
Picture frame(const Picture &pic, const char &, const char &, const char &);
Picture hcat(const Picture &, const Picture &);
Picture vcat(const Picture &, const Picture &);
Picture reframe(const Picture &pic, const char &corner_c, const char &sides_c, const char &top_bot_c);

// overloaded output operator
std::ostream &operator<<(std::ostream &, const Picture &);

#endif