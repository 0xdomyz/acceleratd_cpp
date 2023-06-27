// g++ test_Str.cpp -o test_Str && ./test_Str

#include <iostream>
#include "Str.h"

using namespace std;

int main(void)
{
    const char *cp = "hello";
    Str s1(cp);
    Str s2(3, 'a');
    Str s3 = s1 + Str() + "!" + Str(" ") + s2 + Str(cp, cp + 3);
    s2 = s3;
    s2[0] = 'H';

    cout << "Expected: Hello! aaahel, actual: " << s2 << endl;
    cout << "Expected: hello! aaahel, actual: " << s3 << endl;

    Vec<Str> vs;
    vs.push_back("Hello");
    vs.push_back("World");
    vs.push_back("!");
    cout << "Expected: Hello World !, actual: " << vs << endl;

    Ptr<Vec<Str>> pvs = new Vec<Str>;
    pvs->push_back("Hello");
    pvs->push_back("World");
    cout << "Expected: Hello World, actual: " << *pvs << endl;

    return 0;
}