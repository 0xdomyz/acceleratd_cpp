// g++ self_print.cpp -o self_print && ./self_print

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream in("self_print.cpp");
    string line;
    while (getline(in, line))
        cout << line << endl;
    return 0;
}
