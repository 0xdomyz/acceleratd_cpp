// g++ grade_mix.cpp student_info.cpp -o grade_mix && ./grade_mix < "mix.csv"

#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include "student_info.h"

using namespace std;

int main()
{
    vector<Core *> students; // store pointers, not objects
    Core *record;            // temporary must be a pointer as well
    char ch;
    string::size_type maxlen = 0;
    // read and store the data
    while (cin >> ch)
    {
        if (ch == 'U')
            record = new Core; // allocate a Core object
        else
            record = new Grad;                       // allocate a Grad object
        record->read(cin);                           // virtual call
        maxlen = max(maxlen, record->name().size()); // dereference
        students.push_back(record);
    }
    // pass the version of compare that works on pointers
    sort(students.begin(), students.end(), compare_Core_ptrs);
    // write the names and grades
    for (vector<Core *>::size_type i = 0;
         i != students.size(); ++i)
    {
        // students[i] is a pointer that we dereference to call the functions
        cout << students[i]->name()
             << string(maxlen + 1 - students[i]->name().size(), ' ');
        try
        {
            double final_grade = students[i]->grade();
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec) << endl;
        }
        catch (domain_error e)
        {
            cout << e.what() << endl;
        }
        delete students[i]; // free the object allocated when reading
    }
    return 0;
}
