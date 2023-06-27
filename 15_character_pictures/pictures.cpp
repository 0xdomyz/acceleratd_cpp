#include "pictures.h"
#include <iostream>

using namespace std;

// Nonmember functions

Picture frame(const Picture &pic)
{
    return new Frame_Pic(pic.p);
}

Picture frame(const Picture &pic, const char &cor, const char &side, const char &top)
{
    return new Frame_Pic(pic.p, cor, side, top);
}

Picture hcat(const Picture &l, const Picture &r)
{
    return new HCat_Pic(l.p, r.p);
}

Picture vcat(const Picture &t, const Picture &b)
{
    return new VCat_Pic(t.p, b.p);
}

Picture reframe(const Picture &pic, const char &corner_c, const char &sides_c, const char &top_bot_c)
{
    Picture p = pic;
    p.p->reframe(corner_c, sides_c, top_bot_c);
    return p;
}

Picture::Picture(const vector<string> &v) : p(new String_Pic(v)) {}

ostream &operator<<(ostream &os, const Picture &picture)
{
    const Pic_base::ht_sz ht = picture.p->height();
    for (Pic_base::ht_sz i = 0; i != ht; ++i)
    {
        picture.p->display(os, i, false);
        os << endl;
    }
    return os;
}

// pic_base

Pic_base::wd_sz String_Pic::width() const
{
    Pic_base::wd_sz n = 0;
    for (Pic_base::ht_sz i = 0; i != data.size(); ++i)
        n = max(n, data[i].size());
    return n;
}

void Pic_base::pad(ostream &os, wd_sz beg, wd_sz end)
{
    while (beg != end)
    {
        os << " ";
        ++beg;
    }
}

// string_pic

void String_Pic::display(ostream &os, ht_sz row, bool do_pad) const
{
    wd_sz start = 0;
    // write the row if we're still in range
    if (row < height())
    {
        os << data[row];
        start = data[row].size();
    }
    // pad the output if necessary
    if (do_pad)
        pad(os, start, width());
}

// vcat_pic
void VCat_Pic::display(ostream &os, ht_sz row, bool do_pad) const
{
    wd_sz w = 0;
    if (row < top->height())
    {
        // we are in the top subpicture
        top->display(os, row, do_pad);
        w = top->width();
    }
    else if (row < height())
    {
        // we are in the bottom subpicture
        bottom->display(os, row - top->height(), do_pad);
        w = bottom->width();
    }
    if (do_pad)
        pad(os, w, width());
}

// hcat_pic
void HCat_Pic::display(ostream &os, ht_sz row, bool do_pad) const
{
    left->display(os, row, do_pad || row < right->height());
    right->display(os, row, do_pad);
}

// frame_pic
void Frame_Pic::display(ostream &os, ht_sz row, bool do_pad) const
{
    if (row >= height())
    {
        // out of range
        if (do_pad)
            pad(os, 0, width());
    }
    else
    {
        if (row == 0 || row == height() - 1)
        {
            // top or bottom row
            os << corner;
            os << string(width() - 2, top_bottom);
            os << corner;
        }
        else if (row == 1 || row == height() - 2)
        {
            // second from top or bottom row
            os << sides;
            pad(os, 1, width() - 1);
            os << sides;
        }
        else
        {
            // interior row
            os << sides << " ";
            p->display(os, row - 2, true);
            os << " " << sides;
        }
    }
}
