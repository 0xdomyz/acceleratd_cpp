// g++ test_pictures.cpp pictures.cpp Str.cpp -o test_pictures && ./test_pictures

#include <iostream>
#include "Str.h"
#include "vec.h"
#include "pictures.h"

using namespace std;

int main()
{
    Vec<Str> vs;
    vs.push_back("Hello");
    vs.push_back("World");
    vs.push_back("!");

    // conversion from Vec<string> to Picture
    Picture p = vs;
    cout << "p:" << endl;
    cout << p << endl;
    cout << endl;

    // frame
    Picture framed = frame(vs);
    cout << "framed:" << endl;
    cout << framed << endl;
    cout << endl;

    // hcat
    // argument symmentry of nonmember functions
    Picture h_cated = hcat(frame(p), p);
    cout << "h_cated:" << endl;
    cout << h_cated << endl;
    cout << endl;

    Picture h_cated2 = hcat(p, frame(p));
    cout << "h_cated2:" << endl;
    cout << h_cated2 << endl;
    cout << endl;

    // vcat
    Picture v_cated = vcat(p, h_cated);
    cout << "v_cated:" << endl;
    cout << v_cated << endl;
    cout << endl;

    // then frame it
    Picture framed_v_cated = frame(v_cated);
    cout << "framed_v_cated:" << endl;
    cout << framed_v_cated << endl;
    cout << endl;

    {
        // another test
        cout << "another test:" << endl;
        cout << endl;

        Picture q = frame(p, '+', '!', '=');
        cout << q << endl;

        Picture r = hcat(p, q);
        Picture s = vcat(q, r);
        cout << frame(hcat(s, vcat(r, q))) << endl;
    }

    {
        // reframe
        cout << "reframe:" << endl;
        cout << endl;

        cout << framed_v_cated << endl;

        Picture reframe_framed_v_cated = reframe(framed_v_cated, '+', '!', '=');
        cout << reframe_framed_v_cated << endl;
    }

    {
        // hcat centre
        cout << p << endl;
        cout << vcat(p, p) << endl;
        cout << hcat(p, p) << endl;
        cout << hcat(p, vcat(p, p)) << endl;
        cout << hcat(vcat(p, p), p) << endl;
    }

    return 0;
}